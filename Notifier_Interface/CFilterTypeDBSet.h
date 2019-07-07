#pragma once
#include "ITable.h"
#include "FILTER_TYPE.h"
class CFilterTypeDBSet : public ITable<FILTER_TYPE, int>
{
public:
	CFilterTypeDBSet(DBContext& db);
};

