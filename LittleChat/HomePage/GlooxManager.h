#pragma once

#include "gloox/client.h"
#include "gloox/chatstatehandler.h"
#include "gloox/chatstatefilter.h"
#include "gloox/connectionlistener.h"
#include "gloox/connectiontcpclient.h"
#include "gloox/connectionsocks5proxy.h"
#include "gloox/connectionhttpproxy.h"
#include "gloox/disco.h"
#include "gloox/gloox.h"
#include "gloox/lastactivity.h"
#include "gloox/logsink.h"
#include "gloox/message.h"
#include "gloox/messagesessionhandler.h"
#include "gloox/messageeventhandler.h"
#include "gloox/messageeventfilter.h"
#include "gloox/messagehandler.h"
#include "gloox/registration.h"

#include "UiListener.h"
#include "CustomRosterListener.h"
#include "CustomVCardHandler.h"
#include "CustomMucRoom.h"
#include "AccountInfo.h"

#include <string>
#include <list>
#include <thread>
#include <map>
#include <assert.h>
#include <windows.h>

#define LOG_OUTPUT 0

using namespace gloox;

const std::string SERVER_URL = "localhost/gloox";
typedef std::map<std::string, MessageSession*> MessageSessionMap;

enum GlooxManagerStatus
{
	GM_NULL,
	GM_LOGIN,
	GM_REGIST,
	GM_CHANGEPW
};

class GlooxManager :public ConnectionListener,
					public ChatStateHandler,
					public LogHandler,
					public MessageHandler,
					public MessageEventHandler,
					public MessageSessionHandler,
					public RegistrationHandler
{
public:
	GlooxManager();
	~GlooxManager();

	static GlooxManager* createGlooxMng();

	int login(const std::string &username, const std::string &password);
	int logout();
	int regist(std::string username, std::string password);
	int getVCard();
	const AccountInfo::GroupsMap& getGoupsMap() const;
	int sendMessage(std::string dst, const std::string &msg);
	int threadRecv();

	void subscribe(const std::string& id);
	void unsubscribe(const std::string& id);
	void cancel(const std::string& id);
	void remove(const std::string& id);

	const std::string getId();
	const std::string getNickname();
	bool isMessageSessionExist(const std::string& id);
	void eraseMessageSession(const std::string& id);

	void registerUiListener(UiListener *ul);
	void notifyUiLogin();
	void notifyUiMessageReceived(const std::string& msg, const std::string& id);

private:
	//register
	virtual void handleRegistrationFields(const JID& from, int fields, std::string instructions);
	virtual void handleRegistrationResult(const JID& from, RegistrationResult regResult);
	virtual void handleAlreadyRegistered(const JID& from);
	virtual void handleDataForm(const JID& from, const DataForm& form);
	virtual void handleOOB(const JID& from, const OOB& oob);

	//message
	virtual void onConnect();
	virtual void onDisconnect(ConnectionError e);
	virtual bool onTLSConnect(const CertInfo& info);
	virtual void handleChatState(const JID& from, ChatStateType state);
	virtual void handleMessageEvent(const JID& from, MessageEventType event);
	virtual void handleMessageSession(MessageSession* session);
	virtual void handleMessage(const Message& msg, MessageSession* session);
	virtual void handleLog(LogLevel level, LogArea area, const std::string& message);

private:
	static GlooxManager* s_glooxMng;

	Client *m_client;
	RosterListener *m_rosterListener;
	VCardHandler *m_vcardHandler;
	CustomMucRoom *m_mucRoom;
	AccountInfo *m_account;

	Registration *m_registration;
	MessageSessionMap m_msgSessions;
	MessageSession *m_msgSession;
	MessageEventFilter *m_msgEventFilter;
	ChatStateFilter *m_chatStateFilter;

	std::string m_regName;
	std::string m_regPassword;
	int m_status;
	bool m_isInit;
	std::list<UiListener*> m_uiListeners;

	CRITICAL_SECTION m_cs;
};
