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

	//���û�û��subscribe�Է�֮ǰ��getRosterItem�õ��Ľ���NULL����ʹ�Է��Ѿ�subscribe�ҷ�
	//Ҫע�Ȿ������handleItemAdded��handleSubscriptionRequest֮���ִ��˳��
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

	//���ͺ�������subscribe(jid)����ʱ�������jid�Ѿ��������������
	//֮��handleItemAdded()��handleItemUpdated()�ᱻ����
	//�Է���������subscribe���ҷ�������handleSubscriptionRequest()���˺�������true�󴥷�handleItemSubscribed()
	//If the handler is registered as a asynchronous handler for subscription requests����ô����������ֵ����Ч
	//�����������Ҫʹ��ackSubscriptionRequest()����

	m_client->rosterManager()->subscribe(jid);

	//�Ժ�Ľ�������Ϣ����UI��֮��UI�����Ƿ�ͬ��������룬Ȼ���ٵ����߼����ackSubscriptionRequest()����������
	//����������һ��flag���Ƿ���Ҫ����ͬ�������Ӻ���
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
