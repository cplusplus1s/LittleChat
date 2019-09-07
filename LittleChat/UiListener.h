#pragma once
#include <string>

class UiListener
{
public:
	virtual void onLogin() = 0;
	virtual void onVCardReceived() = 0;
	virtual void onItemSubscribed() = 0;
	virtual void onItemAdded() = 0;
	virtual void onItemRemoved() = 0;
	virtual void onItemUpdated() = 0;
	virtual void onRosterUpdated() = 0;
	virtual void onRosterPresence() = 0;
	virtual void onSubscriptionRequest(const std::string& id) = 0;
	virtual void onMessageReceived(const std::string& msg, const std::string& id) = 0;
};