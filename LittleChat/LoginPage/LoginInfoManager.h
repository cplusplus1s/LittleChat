#pragma once
#include "inc.h"

class LoginInfoManager : public QObject
{
protected:
	explicit LoginInfoManager(QObject *parent = 0);
	~LoginInfoManager();
public:
	class UserLoginInfo;
	static LoginInfoManager* CreateLoginInfoManager();
	bool ReadUsers(QList<UserLoginInfo*> &userList);
	bool WriteUser(UserLoginInfo &userInfo);
private:
	static LoginInfoManager* s_loginInfoManager;
};

class LoginInfoManager::UserLoginInfo
{
public:
	UserLoginInfo();
	~UserLoginInfo();

	void SetUsername(const QString& name);
	const QString& GetUsername() const;

	void SetPassword(const QString& password);
	const QString& GetPassword() const;

	void SetAutologin(bool autologin);
	bool GetAutologin() const;

	void SetRememberpw(bool rememberpw);
	bool GetRememberpw() const;

private:
	QString m_username;
	QString m_password;
	bool m_autologin;
	bool m_rememberpw;
};