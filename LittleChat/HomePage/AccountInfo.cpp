#include "AccountInfo.h"

AccountInfo::AccountInfo()
	:m_id("null"),
	m_nickname("null"),
	m_password("")
{

}

AccountInfo::~AccountInfo()
{
	std::list<ContactInfo*>::const_iterator it;
	for (it = m_contactsList.begin(); it != m_contactsList.end(); it++)
	{
		delete (*it);
	}
}

void AccountInfo::setId(const std::string &id)
{
	m_id = id;
}

void AccountInfo::setNickname(const std::string &nickname)
{
	m_nickname = nickname;
}

void AccountInfo::setStatus(const std::string &status)
{
	m_status = status;
}

void AccountInfo::setPassword(const std::string &password)
{
	m_password = password;
}

void AccountInfo::addContact(ContactInfo* id)
{
	m_contactsList.push_back(id);
}

void AccountInfo::removeContact(const std::string &id)
{
	std::list<ContactInfo*>::const_iterator it = m_contactsList.begin();
	while (it != m_contactsList.end())
	{
		if (id == (*it)->getId())
		{
			//注意，这里一定要把erase的返回值（删除位置的下一个位置）赋给it，不然会报错
			it = m_contactsList.erase(it);
		}
	}
}

void AccountInfo::setContactPresence(const std::string &id, int presence)
{
	std::list<ContactInfo*>::const_iterator it;
	for (it = m_contactsList.begin(); it != m_contactsList.end(); it++)
	{
		if (id == (*it)->getId())
		{
			(*it)->setPresence(presence);
		}
	}
}

void AccountInfo::clearContact()
{
	m_contactsList.clear();
}

const AccountInfo::GroupsMap& AccountInfo::updateGroupsMap()
{
	m_groupsMap.clear();
	std::list<ContactInfo*>::const_iterator cit;
	for (cit = m_contactsList.begin(); cit != m_contactsList.end(); cit++)
	{
		std::list<std::string>::const_iterator git;
		for (git = (*cit)->m_groups.begin(); git != (*cit)->m_groups.end(); git++)
		{
			std::string group = *git;
			m_groupsMap[group].push_back(*cit);
		}
	}
	return m_groupsMap;
}

const std::string& AccountInfo::getId() const
{
	return m_id;
}

const std::string& AccountInfo::getNickname() const
{
	return m_nickname;
}

const std::string& AccountInfo::getStatus() const
{
	return m_status;
}

const std::string& AccountInfo::getPassword() const
{
	return m_password;
}

AccountInfo::ContactInfo::ContactInfo()
	:m_id("null"),
	m_nickname("null"),
	m_subscription(-1),
	m_presence(-1)
{

}

AccountInfo::ContactInfo::~ContactInfo()
{

}

void AccountInfo::ContactInfo::setId(const std::string &id)
{
	m_id = id;
}

void AccountInfo::ContactInfo::setNickname(const std::string &nickname)
{
	m_nickname = nickname;
}

void AccountInfo::ContactInfo::setSubscription(int subscriptiontype)
{
	m_subscription = subscriptiontype;
}

void AccountInfo::ContactInfo::setPresence(int presence)
{
	m_presence = presence;
}

void AccountInfo::ContactInfo::addGroup(const std::string &group)
{
	m_groups.push_back(group);
}

const std::string& AccountInfo::ContactInfo::getId() const
{
	return m_id;
}

const std::string& AccountInfo::ContactInfo::getNickname() const
{
	return m_nickname;
}

int AccountInfo::ContactInfo::getSubscription() const
{
	return m_subscription;
}

int AccountInfo::ContactInfo::getPresence() const
{
	return m_presence;
}

const std::list<std::string>& AccountInfo::ContactInfo::getGroups() const
{
	return m_groups;
}
