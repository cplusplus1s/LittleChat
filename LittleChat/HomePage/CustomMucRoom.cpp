#include "CustomMucRoom.h"

CustomMucRoom::CustomMucRoom(Client* client, AccountInfo *account /* = NULL */)
{
	m_client = client;
	m_account = account;
	m_room = NULL;
}

CustomMucRoom::~CustomMucRoom()
{
	delete m_room;
}

void CustomMucRoom::start(const std::string& room)
{
	JID nick(room);
	m_room = new MUCRoom(m_client, nick, this, 0);
	m_room->join();
	m_room->getRoomInfo();
	m_room->getRoomItems();
}

void CustomMucRoom::inviteContact(const std::string& id, const std::string& msg)
{
	assert(NULL != m_room);
	JID j(id);
	m_room->invite(j, msg);
}

void CustomMucRoom::sendToRoom(const std::string& msg)
{
	assert(NULL != m_room);
	m_room->send(msg);
}

void CustomMucRoom::registerUiListeners(std::list<UiListener *> *uls)
{
	if (NULL != uls)
	{
		m_uiListeners = uls;
	}
}

void CustomMucRoom::handleMUCParticipantPresence(MUCRoom* room, const MUCRoomParticipant participant, const Presence& presence)
{
	if (presence.presence() == Presence::Available)
		printf("!!!!!!!!!!!!!!!! %s is in the room, too\n", participant.nick->resource().c_str());
	else if (presence.presence() == Presence::Unavailable)
		printf("!!!!!!!!!!!!!!!! %s left the room\n", participant.nick->resource().c_str());
	else
		printf("Presence is %d of %s\n", presence.presence(), participant.nick->resource().c_str());
}

void CustomMucRoom::handleMUCMessage(MUCRoom* room, const Message& msg, bool priv)
{
	printf("%s said: '%s' (history: %s, private: %s)\n", msg.from().resource().c_str(), msg.body().c_str(),
		msg.when() ? "yes" : "no", priv ? "yes" : "no");
}

void CustomMucRoom::handleMUCSubject(MUCRoom* room, const std::string& nick, const std::string& subject)
{
	if (nick.empty())
		printf("Subject: %s\n", subject.c_str());
	else
		printf("%s has set the subject to: '%s'\n", nick.c_str(), subject.c_str());
}

void CustomMucRoom::handleMUCError(MUCRoom* room, StanzaError error)
{
	printf("!!!!!!!!got an error: %d", error);
}

void CustomMucRoom::handleMUCInfo(MUCRoom* room, int features, const std::string& name, const DataForm* infoForm)
{
	printf("features: %d, name: %s, form xml: %s\n",
		features, name.c_str(), infoForm->tag()->xml().c_str());
}

void CustomMucRoom::handleMUCItems(MUCRoom* room, const Disco::ItemList& items)
{
	Disco::ItemList::const_iterator it = items.begin();
	for (; it != items.end(); ++it)
	{
		printf("%s -- %s is an item here\n", (*it)->jid().full().c_str(), (*it)->name().c_str());
	}
}

void CustomMucRoom::handleMUCInviteDecline(MUCRoom* room, const JID& invitee, const std::string& reason)
{
	printf("Invitee %s declined invitation. reason given: %s\n", invitee.full().c_str(), reason.c_str());
}

bool CustomMucRoom::handleMUCRoomCreation(MUCRoom* room)
{
	printf("room %s didn't exist, beeing created.\n", room->name().c_str());
	return true;
}

//void CustomMucRoom::handleMUCInvitation(const JID& room, const JID& from, const std::string& reason, const std::string& body, const std::string& password, bool cont, const std::string& thread)
//{
//	m_room = new MUCRoom(m_client, room, this, 0);
//	m_room->join();
//}
