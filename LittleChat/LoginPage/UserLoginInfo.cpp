#include "UserLoginInfo.h"

UserLoginInfo::UserLoginInfo(QObject *parent /* = 0 */) : m_username("null"), m_password("null"), m_autologin(false), m_rememberpw(false)
{

}

UserLoginInfo::~UserLoginInfo()
{

}

void UserLoginInfo::SetUsername(QString name)
{
	m_username = name;
}

QString UserLoginInfo::GetUsername()
{
	return m_username;
}

void UserLoginInfo::SetPassword(QString password)
{
	m_password = password;
}

QString UserLoginInfo::GetPassword()
{
	return m_password;
}

void UserLoginInfo::SetAutologin(bool autologin)
{
	m_autologin = autologin;
}

bool UserLoginInfo::GetAutologin()
{
	return m_autologin;
}

void UserLoginInfo::SetRememberpw(bool rememberpw)
{
	m_rememberpw = rememberpw;
}

bool UserLoginInfo::GetRememberpw()
{
	return m_rememberpw;
}