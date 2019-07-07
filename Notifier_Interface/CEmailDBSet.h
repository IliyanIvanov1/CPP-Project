#pragma once
#include "ITable.h"
#include "EMAIL.h"

class CEmailDBSet : public ITable<EMAIL, int>
{
public:
	CEmailDBSet(DBContext& db);
};

