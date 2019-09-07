#pragma once

#include <QObject>
#include "AccountInfo.h"

class AccountManager
{
public:
	AccountManager();
	~AccountManager();

public:
	static AccountManager* createAccountManager();

private:
	static AccountManager* s_accountManager;

	AccountInfo* m_currentAccount;
};