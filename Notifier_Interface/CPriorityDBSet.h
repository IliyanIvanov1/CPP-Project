#pragma once
#include "ITable.h"
#include "PRIORITY.h"

class CPriorityDBSet : public ITable<PRIORITY, int>
{
public:
	CPriorityDBSet(DBContext& db);
};
