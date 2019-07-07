#pragma once
#include "ITable.h"
#include "POSITIONN.h"
class CPositionDBSet : public ITable<POSITIONN, int>
{
public:
	CPositionDBSet(DBContext& db);
};

