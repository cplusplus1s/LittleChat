#pragma once

#include "gloox/client.h"
#include "gloox/rosterlistener.h"
#include "gloox/rostermanager.h"

#include "UiListener.h"
#include "AccountInfo.h"

#include <list>
#include <assert.h>

using namespace gloox;

class CustomRosterListener : public RosterListener
{
public:
	CustomRosterListener();
	CustomRosterListener(Client *client, AccountInfo* account = NULL);
	~CustomRosterListener();

	void registerUiListeners(std::list<UiListener*> *uls);
	void notifyUiItemSubscribed();
	void notifyUiItemAdded();
	void notifyUiItemRemoved();
	void notifyUiItemUpdated();
	void notifyUiRosterUpdated();
	void notifyUiRosterPresence();
	void notifyUiSubscriptionRequest(const std::string& id);

private:
	virtual void handleItemSubscribed(const JID& jid);
	virtual void handleItemAdded(const JID& jid);
	virtual void handleItemUnsubscribed(const JID& jid);
	virtual void handleItemRemoved(const JID& jid);
	virtual void handleItemUpdated(const JID& jid);
	virtual void handleRoster(const Roster& roster);
	virtual void handleRosterError(const IQ& iq);
	virtual void handleRosterPresence(const RosterItem& item, const std::string& resource, Presence::PresenceType presence, const std::string& msg);
	virtual void handleSelfPresence(const RosterItem& item, const std::string& resource, Presence::PresenceType presence, const std::string& msg);
	virtual bool handleSubscriptionRequest(const JID& jid, const std::string& msg);
	virtual bool handleUnsubscriptionRequest(const JID& jid, const std::string& msg);
	virtual void handleNonrosterPresence(const Presence& presence);

private:
	Client *m_client;
	AccountInfo *m_account;
	std::list<UiListener*> *m_uiListeners;
};