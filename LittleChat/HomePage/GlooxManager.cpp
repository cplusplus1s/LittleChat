#include "GlooxManager.h"

GlooxManager* GlooxManager::s_glooxMng = NULL;

GlooxManager::GlooxManager()
{
	m_client = NULL;
	m_rosterListener = NULL;
	m_vcardHandler = NULL;
	m_account = NULL;
	m_registration = NULL;
	m_msgSession = NULL;
	m_isInit = true;
	m_status = GM_NULL;

	::InitializeCriticalSection(&m_cs);

	//留意线程什么时候终止
	std::thread thread(&GlooxManager::threadRecv, this);
	thread.detach();
}

GlooxManager::~GlooxManager()
{
	if (NULL != m_client)
	{
		m_client->disposeMessageSession(m_msgSession);
		::EnterCriticalSection(&m_cs);
		MessageSessionMap::const_iterator it;
		for (it = m_msgSessions.begin(); it != m_msgSessions.end(); it++)
		{
			m_client->disposeMessageSession(it->second);
		}
		::LeaveCriticalSection(&m_cs);
		delete m_client;
	}

	delete m_rosterListener;
	delete m_vcardHandler;
	delete m_account;

	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners.begin(); it != m_uiListeners.end(); it++)
	{
		delete *it;
	}

	::DeleteCriticalSection(&m_cs);
}

GlooxManager* GlooxManager::createGlooxMng()
{
	if (NULL == s_glooxMng)
	{
		s_glooxMng = new GlooxManager();
	}
	return s_glooxMng;
}

int GlooxManager::login(const std::string &username, const std::string &password)
{
	m_status = GM_LOGIN;

	JID jid(username + "@" + SERVER_URL);
	if (NULL == m_client)
	{
		m_client = new Client(jid, password);
	}
	else
	{
		m_client->setUsername(username);
	}

	if (NULL == m_rosterListener)
	{
		assert(NULL != m_client);
		if (NULL == m_account)
		{
			m_account = new AccountInfo();
		}
		m_rosterListener = new CustomRosterListener(m_client, m_account);
		static_cast<CustomRosterListener*>(m_rosterListener)->registerUiListeners(&m_uiListeners);
	}

	if (NULL == m_mucRoom)
	{
		assert(NULL != m_client);
		if (NULL != m_account)
		{
			m_account = new AccountInfo();
		}
		m_mucRoom = new CustomMucRoom(m_client, m_account);
		m_mucRoom->registerUiListeners(&m_uiListeners);
	}

	assert(NULL != m_client);
	assert(NULL != m_rosterListener);
	assert(NULL != m_mucRoom);

	m_client->registerConnectionListener(this);
	m_client->registerMessageSessionHandler(this, 0);
	m_client->rosterManager()->registerRosterListener(m_rosterListener);
	//m_client->registerMUCInvitationHandler(m_mucRoom);
	m_client->disco()->setVersion("GlooxManager", GLOOX_VERSION);
	m_client->disco()->setIdentity("client", "bot");
	m_client->disco()->addFeature(XMLNS_CHAT_STATES);

	StringList ca;
	ca.push_back("/path/to/cacert.crt");
	m_client->setCACerts(ca);

	m_client->logInstance().registerLogHandler(LogLevelDebug, LogAreaAll, this);

	if (m_client->connect(false))
	{

		/*ConnectionError ce = ConnNoError;
		while (ConnNoError == ce)
		{
			printf("dada...\n");
			ce = m_client->recv();
		}
		printf("ce: %d\n", ce);*/

	}

	return 0;
}

int GlooxManager::logout()
{
	if (NULL != m_client)
	{
		m_client->disconnect();
	}
	return 0;
}

int GlooxManager::regist(std::string username, std::string password)
{
	m_status = GM_REGIST;

	m_regName = username;
	m_regPassword = password;

	m_client = new Client(SERVER_URL);
	m_client->disableRoster();
	m_client->registerConnectionListener(this);

	m_registration = new Registration(m_client);
	m_registration->registerRegistrationHandler(this);

	m_client->logInstance().registerLogHandler(LogLevelDebug, LogAreaAll, this);

	m_client->connect();

	delete m_registration;
	m_registration = NULL;
	delete m_client;
	m_client = NULL;

	return 0;
}

int GlooxManager::getVCard()
{
	assert(NULL != m_client);
	if (NULL != m_client)
	{
		if (NULL == m_account)
		{
			m_account = new AccountInfo();
		}
		if (NULL == m_vcardHandler)
		{
			m_vcardHandler = new CustomVCardHandler(m_client, m_account);
			static_cast<CustomVCardHandler*>(m_vcardHandler)->registerUiListeners(&m_uiListeners);
		}
		static_cast<CustomVCardHandler*>(m_vcardHandler)->fetch(m_client->jid().full());
	}
	return 0;
}

const AccountInfo::GroupsMap& GlooxManager::getGoupsMap() const
{
	return m_account->updateGroupsMap();
}

int GlooxManager::sendMessage(std::string dst, const std::string &msg)
{
	::EnterCriticalSection(&m_cs);
	MessageSessionMap::iterator it;
	it = m_msgSessions.find(dst);
	if (it != m_msgSessions.end())
	{
		it->second->send(msg.c_str());
	}
	else
	{
		JID jid(dst);
		MessageSession *msgSession = new MessageSession(m_client, jid);
		m_msgSessions[dst] = msgSession;
		msgSession->send(msg.c_str());
	}
	/*JID jid(dst);
	MessageSession *msgSession = new MessageSession(m_client, jid);
	msgSession->send(msg.c_str());
	m_client->disposeMessageSession(msgSession);*/
	::LeaveCriticalSection(&m_cs);

	return 0;
}

int GlooxManager::threadRecv()
{
	ConnectionError ce = ConnNoError;
	while (ConnNoError == ce)
	{
		if (NULL != m_client)
		{
			ce = m_client->recv();
		}
		else
		{
			Sleep(500);
		}
	}
	printf("ce: %d\n", ce);
	printf("thread ends\n");

	return 0;
}

void GlooxManager::handleRegistrationFields(const JID& from, int fields, std::string instructions)
{
	printf("fields: %d\ninstructions: %s\n", fields, instructions.c_str());
	RegistrationFields vals;
	vals.username = m_regName;
	vals.password = m_regPassword;
	m_registration->createAccount(fields, vals);
}

void GlooxManager::handleRegistrationResult(const JID& from, RegistrationResult regResult)
{
	printf("result: %d\n", regResult);
	m_client->disconnect();
}

void GlooxManager::handleAlreadyRegistered(const JID& from)
{
	printf("the account already exists.\n");
}

void GlooxManager::handleDataForm(const JID& from, const DataForm& form)
{
	printf("datForm received\n");
}

void GlooxManager::handleOOB(const JID& from, const OOB& oob)
{
	printf("OOB registration requested. %s: %s\n", oob.desc().c_str(), oob.url().c_str());
}

void GlooxManager::onConnect()
{
	printf("connected!!!\n");

	switch (m_status)
	{
	case GM_LOGIN:
		m_client->login();
		m_account->setId(m_client->jid().full());
		m_account->setNickname(m_client->jid().username());
		notifyUiLogin();
		//getVCard();
		break;
	case GM_REGIST:
		//触发虚函数handleRegistrationFields
		m_registration->fetchRegistrationFields();
		break;
	case GM_CHANGEPW:
		//m_registration->changePassword(m_client->username(), "newpassword");
		break;
	default:
		break;
	}
}

void GlooxManager::onDisconnect(ConnectionError e)
{
	printf("GlooxManager: disconnected: %d\n", e);
	switch (e)
	{
	case gloox::ConnNoError:
		printf("Not really an error. Everything went just fine.\n");
		break;
	case gloox::ConnStreamError:
		printf("A stream error occured. The stream has been closed.\n");
		break;
	case gloox::ConnStreamVersionError:
		printf("The incoming stream's version is not supported.\n");
		break;
	case gloox::ConnStreamClosed:
		printf("The stream has been closed (by the server).\n");
		break;
	case gloox::ConnProxyAuthRequired:
		printf("The HTTP/SOCKS5 proxy requires authentication.\n");
		break;
	case gloox::ConnProxyAuthFailed:
		printf("HTTP/SOCKS5 proxy authentication failed.\n");
		break;
	case gloox::ConnProxyNoSupportedAuth:
		printf("The HTTP/SOCKS5 proxy requires an unsupported auth mechanism.\n");
		break;
	case gloox::ConnIoError:
		printf("An I/O error occured.\n");
		break;
	case gloox::ConnParseError:
		printf("An XML parse error occurred.\n");
		break;
	case gloox::ConnConnectionRefused:
		printf("The connection was refused by the server (on the socket level).\n");
		break;
	case gloox::ConnDnsError:
		printf("Resolving the server's hostname failed.\n");
		break;
	case gloox::ConnOutOfMemory:
		printf("Out of memory. Uhoh.\n");
		break;
	case gloox::ConnNoSupportedAuth:
		printf("The auth mechanisms the server offers are not supported or the server offered no auth mechanisms at all.\n");
		break;
	case gloox::ConnTlsFailed:
		printf("The server's certificate could not be verified or the TLS handshake did not complete successfully.\n");
		break;
	case gloox::ConnTlsNotAvailable:
		printf("The server didn't offer TLS while it was set to be required, or TLS was not compiled in.\n");
		break;
	case gloox::ConnCompressionFailed:
		printf("Negotiating/initializing compression failed.\n");
		break;
	case gloox::ConnAuthenticationFailed:
		printf("Authentication failed. Username/password wrong or account does not exist.Use ClientBase::authError() to find the reason.\n");
		break;
	case gloox::ConnUserDisconnected:
		printf("The user (or higher-level protocol) requested a disconnect.\n");
		break;
	case gloox::ConnNotConnected:
		printf("There is no active connection.\n");
		break;
	default:
		break;
	}
}

bool GlooxManager::onTLSConnect(const CertInfo& info)
{
	return true;
}

void GlooxManager::handleChatState(const JID& from, ChatStateType state)
{
	printf("received chat state: %d from: %s\n", state, from.full().c_str());
}

void GlooxManager::handleMessageEvent(const JID& from, MessageEventType event)
{
	printf("received event: %d from: %s\n", event, from.full().c_str());
}

void GlooxManager::handleMessageSession(MessageSession* session)
{
	::EnterCriticalSection(&m_cs);
	MessageSessionMap::const_iterator it;
	std::string target = session->target().bare() + "/gloox";
	it = m_msgSessions.find(target);
	if (it == m_msgSessions.end())
	{
		printf("new message session\n");
		/*m_client->disposeMessageSession(m_msgSession);
		m_msgSession = session;
		m_msgSession->registerMessageHandler(this);
		m_msgEventFilter = new MessageEventFilter(m_msgSession);
		m_msgEventFilter->registerMessageEventHandler(this);
		m_chatStateFilter = new ChatStateFilter(m_msgSession);
		m_chatStateFilter->registerChatStateHandler(this);*/
		m_msgSessions[target] = session;
		session->registerMessageHandler(this);
		m_msgEventFilter = new MessageEventFilter(session);
		m_msgEventFilter->registerMessageEventHandler(this);
		m_chatStateFilter = new ChatStateFilter(session);
		m_chatStateFilter->registerChatStateHandler(this);
	}
	else
	{
		printf("old message session\n");
	}
	::LeaveCriticalSection(&m_cs);
}

void GlooxManager::handleMessage(const Message& msg, MessageSession* session)
{
	printf("%s is speaking\n", session->target().bare().c_str());
	printf("type: %d\nsub: %s\nmessage: %s\nthread: %s\n",
		msg.subtype(), msg.subject().c_str(), msg.body().c_str(), msg.thread().c_str());

	std::string target = session->target().bare() + "/gloox";
	if (Message::Chat == msg.subtype())
	{
		notifyUiMessageReceived(msg.body(), target);
	}

	m_msgEventFilter->raiseMessageEvent(MessageEventDisplayed);
#if defined(WIN32) || defined(_WIN32)
	Sleep(2000);
#else
	Sleep(2);
#endif
	m_msgEventFilter->raiseMessageEvent(MessageEventComposing);
	m_chatStateFilter->setChatState(ChatStateComposing);
#if defined(WIN32) || defined(_WIN32)
	Sleep(2000);
#else
	Sleep(2);
#endif

	//m_msgSession->send("answer");
}

void GlooxManager::handleLog(LogLevel level, LogArea area, const std::string& message)
{
#if LOG_OUTPUT
	printf("log: level: %d, area: %d, %s\n", level, area, message.c_str());
#endif
}

//void GlooxManager::handleItemSubscribed(const JID& jid)
//{
//
//}
//
//void GlooxManager::handleItemAdded(const JID& jid)
//{
//
//}
//
//void GlooxManager::handleItemUnsubscribed(const JID& jid)
//{
//
//}
//
//void GlooxManager::handleItemRemoved(const JID& jid)
//{
//
//}
//
//void GlooxManager::handleItemUpdated(const JID& jid)
//{
//
//}
//
//void GlooxManager::handleRoster(const Roster& roster)
//{
//
//}
//
//void GlooxManager::handleRosterError(const IQ& iq)
//{
//
//}
//
//void GlooxManager::handleRosterPresence(const RosterItem& item, const std::string& resource,
//										Presence::PresenceType presence, const std::string& msg)
//{
//
//}
//
//void GlooxManager::handleSelfPresence(const RosterItem& item, const std::string& resource,
//										Presence::PresenceType presence, const std::string& msg)
//{
//
//}
//
//bool GlooxManager::handleSubscriptionRequest(const JID& jid, const std::string& msg)
//{
//	return true;
//}
//
//bool GlooxManager::handleUnsubscriptionRequest(const JID& jid, const std::string& msg)
//{
//	return true;
//}
//
//void GlooxManager::handleNonrosterPresence(const Presence& presence)
//{
//
//}

void GlooxManager::subscribe(const std::string& id)
{
	if (NULL != m_client)
	{
		JID jid(id);
		m_client->rosterManager()->subscribe(jid);
	}
}

void GlooxManager::unsubscribe(const std::string& id)
{
	if (NULL != m_client)
	{
		JID jid(id);
		m_client->rosterManager()->unsubscribe(jid);
	}
}

void GlooxManager::cancel(const std::string& id)
{
	if (NULL != m_client)
	{
		JID jid(id);
		m_client->rosterManager()->cancel(jid);
	}
}

void GlooxManager::remove(const std::string& id)
{
	if (NULL != m_client)
	{
		JID jid(id);
		m_client->rosterManager()->remove(jid);
	}
}

const std::string GlooxManager::getId()
{
	return m_account->getId();
}

const std::string GlooxManager::getNickname()
{
	return m_account->getNickname();
}

bool GlooxManager::isMessageSessionExist(const std::string& id)
{
	::EnterCriticalSection(&m_cs);
	MessageSessionMap::const_iterator it;
	it = m_msgSessions.find(id);
	if (it != m_msgSessions.end())
	{
		return true;
	}
	else
	{
		return false;
	}
	::LeaveCriticalSection(&m_cs);
}

void GlooxManager::eraseMessageSession(const std::string& id)
{
	::EnterCriticalSection(&m_cs);
	MessageSessionMap::iterator it;
	it = m_msgSessions.find(id);
	if (it != m_msgSessions.end())
	{
		m_client->disposeMessageSession(it->second);
		m_msgSessions.erase(it);
	}
	::LeaveCriticalSection(&m_cs);
}

void GlooxManager::registerUiListener(UiListener *ul)
{
	if (NULL != ul)
	{
		m_uiListeners.push_back(ul);
	}
}

void GlooxManager::notifyUiLogin()
{
	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners.begin(); it != m_uiListeners.end(); it++)
	{
		(*it)->onLogin();
	}
}

void GlooxManager::notifyUiMessageReceived(const std::string& msg, const std::string& id)
{
	if (!msg.empty())
	{
		std::list<UiListener*>::const_iterator it;
		for (it = m_uiListeners.begin(); it != m_uiListeners.end(); it++)
		{
			(*it)->onMessageReceived(msg, id);
		}
	}
}
