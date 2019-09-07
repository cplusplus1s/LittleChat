#include "LoginInfoManager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>

LoginInfoManager* LoginInfoManager::s_loginInfoManager = NULL;

LoginInfoManager::LoginInfoManager(QObject *parent /* = 0 */)
{

}

LoginInfoManager::~LoginInfoManager()
{

}

LoginInfoManager* LoginInfoManager::CreateLoginInfoManager()
{
	if (NULL == s_loginInfoManager)
	{
		s_loginInfoManager = new LoginInfoManager();
	}
	return s_loginInfoManager;
}

bool LoginInfoManager::ReadUsers(QList<UserLoginInfo*> &userList)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("login.db");

	if (!db.open())
	{
		qDebug() << "cannot find login database!";
		return false;
	}
	else
	{
		qDebug() << "succeed to open login database!";
	}

	QSqlQuery query;
	bool isTableExist;
	query.exec("select count(*) from sqlite_master where type='table' and name='users'");
	if (query.first())
	{
		isTableExist = query.value(0).toBool();
	}
	if (isTableExist)
	{
		qDebug() << "table exist!";
		if (!query.exec("select name,password,autologin,rememberpassword from users order by date desc"))
		{
			qDebug() << query.lastError();
			return false;
		}
		qDeleteAll(userList);
		userList.clear();
		while (query.next())
		{
			UserLoginInfo *info = new UserLoginInfo();
			info->SetUsername(query.value(0).toString());
			info->SetPassword((query.value(1)).toString());
			info->SetAutologin((query.value(2)).toBool());
			info->SetRememberpw((query.value(3)).toBool());
			userList.append(info);
		}
		return true;
	}
	else
	{
		qDebug() << "table not exist";
		return false;
	}
}

bool LoginInfoManager::WriteUser(UserLoginInfo &userInfo)
{
	QString username = userInfo.GetUsername();
	QString password = userInfo.GetPassword();
	QString autologin = (userInfo.GetAutologin()) ? "true" : "false";
	QString remember = (userInfo.GetRememberpw()) ? "true" : "false";
	QString cmdline = "replace into users values('" + username + "','" + password + "','" + autologin + "','" + remember + "',datetime('now'))";

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("login.db");

	if (!db.open())
	{
		qDebug() << "cannot find login database!";
		return false;
	}
	else
	{
		qDebug() << "succeed to open login database!";
	}

	QSqlQuery query;
	bool isTableExist;
	query.exec("select count(*) from sqlite_master where type='table' and name='users'");
	if (query.first())
	{
		isTableExist = query.value(0).toBool();
	}
	if (!isTableExist)
	{
		query.exec("create table users(name varchar primary key, password varchar, autologin boolean, rememberpassword boolean, date integer)");
	}
	int totalItems;
	query.exec("select count(*) from users");
	if (query.first())
	{
		totalItems = query.value(0).toInt();
	}
	if (totalItems > MAX_USRS_SAVED)
	{
		if (!query.exec("delete from users where date in (select date from users order by date asc limit 1)"))
		{
			qDebug() << query.lastError();
		}
	}
	query.exec(cmdline);
	return true;
}

LoginInfoManager::UserLoginInfo::UserLoginInfo() : m_username("null"), m_password("null"), m_autologin(false), m_rememberpw(false)
{

}

LoginInfoManager::UserLoginInfo::~UserLoginInfo()
{

}

void LoginInfoManager::UserLoginInfo::SetUsername(const QString& name)
{
	m_username = name;
}

const QString& LoginInfoManager::UserLoginInfo::GetUsername() const
{
	return m_username;
}

void LoginInfoManager::UserLoginInfo::SetPassword(const QString& password)
{
	m_password = password;
}

const QString& LoginInfoManager::UserLoginInfo::GetPassword() const
{
	return m_password;
}

void LoginInfoManager::UserLoginInfo::SetAutologin(bool autologin)
{
	m_autologin = autologin;
}

bool LoginInfoManager::UserLoginInfo::GetAutologin() const
{
	return m_autologin;
}

void LoginInfoManager::UserLoginInfo::SetRememberpw(bool rememberpw)
{
	m_rememberpw = rememberpw;
}

bool LoginInfoManager::UserLoginInfo::GetRememberpw() const
{
	return m_rememberpw;
}
