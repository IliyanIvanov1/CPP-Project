#pragma once
#include "ITable.h"
#include "OUTGOING_MESSAGES.h"
#include "sql.h"
class COutgoingMessagesDBSet : public ITable<OUTGOING_MESSAGES, int>
{
public:
	COutgoingMessagesDBSet(DBContext& db);
};

