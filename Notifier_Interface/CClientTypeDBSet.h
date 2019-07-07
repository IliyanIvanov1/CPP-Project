#pragma once
#include "ITable.h"
#include "CLIENT_TYPE.h"
class CClientTypeDBSet : public ITable<CLIENT_TYPE, int>
{
public:
	CClientTypeDBSet(DBContext& db);
};

