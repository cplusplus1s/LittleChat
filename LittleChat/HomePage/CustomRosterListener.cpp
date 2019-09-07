#include "CustomRosterListener.h"

CustomRosterListener::CustomRosterListener() : m_client(NULL)
{

}

CustomRosterListener::CustomRosterListener(Client *client, AccountInfo* account /* = NULL */) : m_client(client), m_account(account)
{

}

CustomRosterListener::~CustomRosterListener()
{

}

void CustomRosterListener::handleItemSubscribed(const JID& jid)
{
	printf("RosterListener: item subscribed: %s\n", jid.full().c_str());

	//在用户没有subscribe对方之前，getRosterItem得到的将是NULL，即使对方已经subscribe我方
	//要注意本函数和handleItemAdded，handleSubscriptionRequest之间的执行顺序
	RosterItem *rosteritem = m_client->rosterManager()->getRosterItem(jid);
	assert(NULL != rosteritem);
	AccountInfo::ContactInfo *contact = new AccountInfo::ContactInfo();
	contact->setId(rosteritem->jid());
	contact->setNickname(rosteritem->name());
	contact->setSubscription(rosteritem->subscription());
	contact->addGroup(DEFAULT_GROUP);
	m_account->addContact(contact);

	m_client->rosterManager()->add(jid, rosteritem->name(), contact->getGroups());

	notifyUiItemSubscribed();
}

void CustomRosterListener::handleItemAdded(const JID& jid)
{
	printf("RosterListener: item added: %s\n", jid.full().c_str());

	/*RosterItem *rosteritem = m_client->rosterManager()->getRosterItem(jid);
	AccountInfo::ContactInfo *contact = new AccountInfo::ContactInfo();
	contact->setId(rosteritem->jid());
	contact->setNickname(rosteritem->name());
	contact->setSubscription(rosteritem->subscription());
	contact->addGroup(DEFAULT_GROUP);
	m_account->addContact(contact);

	m_client->rosterManager()->add(jid, rosteritem->name(), contact->getGroups());*/

	notifyUiItemAdded();
}

void CustomRosterListener::handleItemUnsubscribed(const JID& jid)
{
	printf("RosterListener: item subscribed: %s\n", jid.full().c_str());
}

void CustomRosterListener::handleItemRemoved(const JID& jid)
{
	printf("RosterListener: item removed: %s\n", jid.full().c_str());
	
	m_account->removeContact(jid.full());
	
	notifyUiItemRemoved();
}

void CustomRosterListener::handleItemUpdated(const JID& jid)
{
	printf("RosterListener: item updated: %s\n", jid.full().c_str());

	notifyUiItemUpdated();
}

void CustomRosterListener::handleRoster(const Roster& roster)
{
	printf("RosterListener:: handle roster\n");

	m_account->clearContact();	
	Roster::const_iterator it;
	for (it = roster.begin(); it != roster.end(); it++)
	{
		AccountInfo::ContactInfo *contact = new AccountInfo::ContactInfo();
		contact->setId((*it).second->jidJID().full());
		contact->setNickname((*it).second->name());
		contact->setSubscription((*it).second->subscription());
		contact->setPresence(Presence::PresenceType::Probe);

		StringList groups = (*it).second->groups();
		StringList::const_iterator git;
		for (git = groups.begin(); git != groups.end(); git++)
		{
			contact->addGroup(*git);
			//printf("RosterListener: group %s\n", git->c_str());
		}

		m_account->addContact(contact);
		//printf("RosterListener: contact %s\n", contact->getId().c_str());
	}
	//m_account->updateGroupsMap();

	notifyUiRosterUpdated();
}

void CustomRosterListener::handleRosterError(const IQ& iq)
{

}

void CustomRosterListener::handleRosterPresence(const RosterItem& item, const std::string& resource,
	Presence::PresenceType presence, const std::string& msg)
{
	printf("RosterListener: roster presence updated: %s, %d\n", item.jidJID().full().c_str(), presence);

	m_account->setContactPresence(item.jid(), presence);

	notifyUiRosterPresence();
}

void CustomRosterListener::handleSelfPresence(const RosterItem& item, const std::string& resource,
	Presence::PresenceType presence, const std::string& msg)
{

}

bool CustomRosterListener::handleSubscriptionRequest(const JID& jid, const std::string& msg)
{
	printf("RosterListener: subscription request: %s\n", jid.full().c_str());

	//发送好友请求即subscribe(jid)，此时被请求的jid已经被添加至服务器
	//之后handleItemAdded()，handleItemUpdated()会被触发
	//对方接受请求即subscribe了我方，触发handleSubscriptionRequest()，此函数返回true后触发handleItemSubscribed()
	//If the handler is registered as a asynchronous handler for subscription requests，那么本函数返回值将无效
	//那种情况下需要使用ackSubscriptionRequest()函数

	m_client->rosterManager()->subscribe(jid);

	//以后改进：此消息传到UI层之后，UI决定是否同意好友申请，然后再调用逻辑层的ackSubscriptionRequest()函数答复申请
	//还可以设置一个flag，是否需要本人同意才能添加好友
	//notifyUiSubscriptionRequest(jid.full());

	return true;
}

bool CustomRosterListener::handleUnsubscriptionRequest(const JID& jid, const std::string& msg)
{
	printf("RosterListener: unsubscription request: %s\n", jid.full().c_str());

	return true;
}

void CustomRosterListener::handleNonrosterPresence(const Presence& presence)
{

}

void CustomRosterListener::registerUiListeners(std::list<UiListener *> *uls)
{
	if (NULL != uls)
	{
		m_uiListeners = uls;
	}
}

void CustomRosterListener::notifyUiItemSubscribed()
{
	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners->begin(); it != m_uiListeners->end(); it++)
	{
		(*it)->onItemSubscribed();
	}
}

void CustomRosterListener::notifyUiItemAdded()
{
	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners->begin(); it != m_uiListeners->end(); it++)
	{
		(*it)->onItemAdded();
	}
}

void CustomRosterListener::notifyUiItemRemoved()
{
	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners->begin(); it != m_uiListeners->end(); it++)
	{
		(*it)->onItemRemoved();
	}
}

void CustomRosterListener::notifyUiItemUpdated()
{
	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners->begin(); it != m_uiListeners->end(); it++)
	{
		(*it)->onItemUpdated();
	}
}

void CustomRosterListener::notifyUiRosterUpdated()
{
	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners->begin(); it != m_uiListeners->end(); it++)
	{
		(*it)->onRosterUpdated();
	}
}

void CustomRosterListener::notifyUiRosterPresence()
{
	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners->begin(); it != m_uiListeners->end(); it++)
	{
		(*it)->onRosterPresence();
	}
}

void CustomRosterListener::notifyUiSubscriptionRequest(const std::string& id)
{
	std::list<UiListener*>::const_iterator it;
	for (it = m_uiListeners->begin(); it != m_uiListeners->end(); it++)
	{
		(*it)->onSubscriptionRequest(id);
	}
}
