#pragma once

#include "gloox/client.h"
#include "gloox/mucroom.h"
#include "gloox/mucroomhandler.h"
#include "gloox/mucinvitationhandler.h"
#include "gloox/disco.h"
#include "gloox/stanza.h"
#include "gloox/message.h"
#include "gloox/dataform.h"
#include "gloox/presence.h"

#include "UiListener.h"
#include "AccountInfo.h"

#include <string>
#include <list>
#include <assert.h>

using namespace gloox;

class CustomMucRoom : public MUCRoomHandler
{
public:
	//CustomMucRoom();
	CustomMucRoom(Client* client, AccountInfo *account = NULL);
	~CustomMucRoom();

public:
	void start(const std::string& room);
	void inviteContact(const std::string& id, const std::string& msg);
	void sendToRoom(const std::string& msg);

	void registerUiListeners(std::list<UiListener*> *uls);

private:
	virtual void handleMUCParticipantPresence(MUCRoom* room, const MUCRoomParticipant participant, const Presence& presence);
	virtual void handleMUCMessage(MUCRoom* room, const Message& msg, bool priv);
	virtual void handleMUCSubject(MUCRoom* room, const std::string& nick, const std::string& subject);
	virtual void handleMUCError(MUCRoom* room, StanzaError error);
	virtual void handleMUCInfo(MUCRoom* room, int features, const std::string& name, const DataForm* infoForm);
	virtual void handleMUCItems(MUCRoom* room, const Disco::ItemList& items);
	virtual void handleMUCInviteDecline(MUCRoom* room, const JID& invitee, const std::string& reason);
	virtual bool handleMUCRoomCreation(MUCRoom* room);

	//virtual void handleMUCInvitation(const JID& room, const JID& from, const std::string& reason, const std::string& body, const std::string& password, bool cont, const std::string& thread);

private:
	Client *m_client;
	MUCRoom *m_room;
	AccountInfo *m_account;
	std::list<UiListener*> *m_uiListeners;
};