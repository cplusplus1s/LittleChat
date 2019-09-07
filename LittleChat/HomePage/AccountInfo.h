#pragma once
#include <string>
#include <list>
#include <map>

const std::string DEFAULT_GROUP = "Friends";

class AccountInfo
{
public:
	AccountInfo();
	~AccountInfo();

	class ContactInfo;
	typedef std::map<std::string, std::list<AccountInfo::ContactInfo*>> GroupsMap;

	void setId(const std::string &id);
	void setNickname(const std::string &nickname);
	void setStatus(const std::string &status);
	void setPassword(const std::string &password);

	void addContact(ContactInfo* id);
	void removeContact(const std::string &id);
	void setContactPresence(const std::string &id, int presence);
	void clearContact();
	const GroupsMap& updateGroupsMap();
	
	const std::string& getId() const;
	const std::string& getNickname() const;
	const std::string& getStatus() const;
	const std::string& getPassword() const;

private:
	std::string m_id;
	std::string m_nickname;
	std::string m_status;
	std::string m_password;
	std::list<ContactInfo*> m_contactsList;
	GroupsMap m_groupsMap;
	
};

class AccountInfo::ContactInfo
{
	friend class AccountInfo;
public:
	ContactInfo();
	~ContactInfo();

	void setId(const std::string &id);
	void setNickname(const std::string &nickname);
	void setSubscription(int subscriptiontype);
	void setPresence(int presence);
	void addGroup(const std::string &group);

	const std::string& getId() const;
	const std::string& getNickname() const;
	int getSubscription() const;
	int getPresence() const;
	const std::list<std::string>& getGroups() const;

private:
	std::string m_id;
	std::string m_nickname;
	int m_subscription;
	int m_presence;
	std::list<std::string> m_groups;
};
