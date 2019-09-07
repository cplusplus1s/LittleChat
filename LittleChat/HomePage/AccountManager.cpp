#include "AccountManager.h"

AccountManager* AccountManager::s_accountManager = NULL;

AccountManager::AccountManager()
{

}

AccountManager::~AccountManager()
{

}

AccountManager* AccountManager::createAccountManager()
{
	if (NULL == s_accountManager)
	{
		s_accountManager = new AccountManager();
	}
	return s_accountManager;
}
