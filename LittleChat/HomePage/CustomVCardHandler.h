#pragma once

#include "gloox/client.h"
#include "gloox/vcardhandler.h"
#include "gloox/vcardmanager.h"

#include "UiListener.h"
#include "AccountInfo.h"

#include <string>
#include <list>

using namespace gloox;

class CustomVCardHandler : public VCardHandler
{
public:
	CustomVCardHandler();
	CustomVCardHandler(Client *client, AccountInfo *account = NULL);
	~CustomVCardHandler();

	void fetch(const std::string &id);
	void store(std::string &nickname, std::string &note);

	void registerUiListeners(std::list<UiListener*> *uls);
	void notifyUiVCardReceived();

private:
	virtual void handleVCard(const JID& jid, const VCard* vcard);
	virtual void handleVCardResult(VCardContext context, const JID& jid, StanzaError se = StanzaErrorUndefined);
private:
	Client *m_client;
	VCardManager *m_vManager;
	AccountInfo *m_account;
	std::string m_jid;
	std::list<UiListener*> *m_uiListeners;
};