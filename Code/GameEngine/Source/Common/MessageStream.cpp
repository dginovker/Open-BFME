// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "PreRTS.h"
#include "Common/MessageStream.h"

MessageStream *TheMessageStream = NULL;
CommandList *TheCommandList = NULL;

const GameMessageArgumentType *GameMessage::getArgument(Int argIndex) const
{
	static const GameMessageArgumentType junk = { 0 };

	int i = 0;
	for (GameMessageArgument *a = m_argList; a; a = a->m_next, i++)
		if (i == argIndex)
			return &a->m_data;

	DEBUG_CRASH(("argument not found"));
	return &junk;
}

void GameMessageList::appendMessage(GameMessage *msg)
{
	msg->friend_setNext(NULL);

	if (m_lastMessage)
	{
		m_lastMessage->friend_setNext(msg);
		msg->friend_setPrev(m_lastMessage);
		m_lastMessage = msg;
	}
	else
	{
		m_firstMessage = msg;
		m_lastMessage = msg;
		msg->friend_setPrev(NULL);
	}

	msg->friend_setList(this);
}

void GameMessageList::insertMessage(GameMessage *msg, GameMessage *messageToInsertAfter)
{
	msg->friend_setNext(messageToInsertAfter->next());
	msg->friend_setPrev(messageToInsertAfter);

	if (msg->next())
		msg->next()->friend_setPrev(msg);
	else
		m_lastMessage = msg;

	messageToInsertAfter->friend_setNext(msg);
	msg->friend_setList(this);
}

void GameMessageList::removeMessage(GameMessage *msg)
{
	if (msg->next())
		msg->next()->friend_setPrev(msg->prev());
	else
		m_lastMessage = msg->prev();

	if (msg->prev())
		msg->prev()->friend_setNext(msg->next());
	else
		m_firstMessage = msg->next();

	msg->friend_setList(NULL);
}

Bool GameMessageList::containsMessageOfType(GameMessage::Type type)
{
	GameMessage *msg = getFirstMessage();
	while (msg) {
		if (msg->getType() == type) {
			return true;
		}
		msg = msg->next();
	}
	return false;
}

MessageStream::~MessageStream()
{
	TranslatorData *trans, *nextTrans;
	for (trans = m_firstTranslator; trans; trans = nextTrans)
	{
		nextTrans = trans->m_next;
		delete trans;
	}
}

TranslatorID MessageStream::attachTranslator(GameMessageTranslator *translator, UnsignedInt priority)
{
	MessageStream::TranslatorData *newSS = NEW MessageStream::TranslatorData;
	MessageStream::TranslatorData *ss;

	newSS->m_translator = translator;
	newSS->m_priority = priority;
	newSS->m_id = m_nextTranslatorID++;

	if (m_firstTranslator == NULL)
	{
		newSS->m_prev = NULL;
		newSS->m_next = NULL;
		m_firstTranslator = newSS;
		m_lastTranslator = newSS;
		return newSS->m_id;
	}

	for (ss = m_firstTranslator; ss; ss = ss->m_next)
		if (ss->m_priority > newSS->m_priority)
			break;

	if (ss)
	{
		if (ss->m_prev)
		{
			ss->m_prev->m_next = newSS;
			newSS->m_prev = ss->m_prev;
			newSS->m_next = ss;
			ss->m_prev = newSS;
		}
		else
		{
			newSS->m_prev = NULL;
			newSS->m_next = m_firstTranslator;
			m_firstTranslator->m_prev = newSS;
			m_firstTranslator = newSS;
		}
	}
	else
	{
		m_lastTranslator->m_next = newSS;
		newSS->m_prev = m_lastTranslator;
		newSS->m_next = NULL;
		m_lastTranslator = newSS;
	}

	return newSS->m_id;
}

GameMessageTranslator *MessageStream::findTranslator(TranslatorID id)
{
	MessageStream::TranslatorData *translatorData;

	for (translatorData = m_firstTranslator; translatorData; translatorData = translatorData->m_next)
	{
		if (translatorData->m_id == id)
			return translatorData->m_translator;
	}

	return NULL;
}

void MessageStream::removeTranslator(TranslatorID id)
{
	MessageStream::TranslatorData *ss;

	for (ss = m_firstTranslator; ss; ss = ss->m_next)
		if (ss->m_id == id)
		{
			if (ss->m_prev)
				ss->m_prev->m_next = ss->m_next;
			else
				m_firstTranslator = ss->m_next;

			if (ss->m_next)
				ss->m_next->m_prev = ss->m_prev;
			else
				m_lastTranslator = ss->m_prev;

			delete ss;
			break;
		}
}

void buildRegion(const ICoord2D *anchor, const ICoord2D *dest, IRegion2D *region)
{
	if (anchor->x < dest->x)
	{
		region->lo.x = anchor->x;
		region->hi.x = dest->x;
	}
	else
	{
		region->lo.x = dest->x;
		region->hi.x = anchor->x;
	}

	if (anchor->y < dest->y)
	{
		region->lo.y = anchor->y;
		region->hi.y = dest->y;
	}
	else
	{
		region->lo.y = dest->y;
		region->hi.y = anchor->y;
	}
}

AsciiString GameMessage::getCommandAsAsciiString(void)
{
	return getCommandTypeAsAsciiString(m_type);
}
