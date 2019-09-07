#pragma once

#include <QObject>

class UserLoginInfo : public QObject
{
public:
	explicit UserLoginInfo(QObject *parent = 0);
	~UserLoginInfo();

	void SetUsername(QString name);
	QString GetUsername();

	void SetPassword(QString password);
	QString GetPassword();

	void SetAutologin(bool autologin);
	bool GetAutologin();

	void SetRememberpw(bool rememberpw);
	bool GetRememberpw();

private:
	QString m_username;
	QString m_password;
	bool m_autologin;
	bool m_rememberpw;
};