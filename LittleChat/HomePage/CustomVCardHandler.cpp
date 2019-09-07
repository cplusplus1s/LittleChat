#include "CustomVCardHandler.h"

CustomVCardHandler::CustomVCardHandler() : m_client(NULL), m_account(NULL)
{
	m_vManager = new VCardManager(m_client);
}

CustomVCardHandler::CustomVCardHandler(Client *client, AccountInfo *account /* = NULL */) : m_client(client), m_account(account)
{
	m_vManager = new VCardManager(m_client);
}

CustomVCardHandler::~CustomVCardHandler()
{
	delete m_vManager;
}

void CustomVCardHandler::fetch(const std::string &id)
{
	m_jid = id;
	JID jid(id);
	m_vManager->fetchVCard(jid, this);
}

void CustomVCardHandler::store(std::string &nickname, std::string &note)
{
	VCard *v = new VCard();
	v->setNickname(nickname);
	v->setNote(note);
	m_vManager->storeVCard(v, this);
	JID j(m_jid);
	m_vManager->fetchVCard(j, this);

}

void CustomVCardHandler::handleVCard(const JID& jid, const VCard* vcard)
{
	if (NULL == vcard)
	{
		printf("empty vcard!\n");
		return;
	}
	printf("received vcard for %s: %s", jid.full().c_str(), vcard->tag()->xml().c_str());

	if (NULL != m_account)
	{
		m_account->setId(jid.username().c_str());
		m_account->setNickname(vcard->nickname().c_str());
		m_account->setStatus(vcard->note().c_str());
	}
	notifyUiVCardReceived();
}

void CustomVCardHandler::handleVCardResult(VCardContext context, const JID& jid, StanzaError se /* = StanzaErrorUndefined */)
{
	printf("vcard result: context: %d, jid: %s, error: %d\n", context, jid.full().c_str(), se);
	JID j(m_jid);
	//m_vManager->fetchVCard(j, this);
}

void CustomVCardHandler::registerUiListeners(std::list<UiListener *> *uls)
{
	if (NULL != uls)
	{
		m_uiListeners = uls;
	}
}

void CustomVCardHandler::notifyUiVCardReceived()
{
	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners->begin(); it != m_uiListeners->end(); it++)
	{
		(*it)->onVCardReceived();
	}
}
