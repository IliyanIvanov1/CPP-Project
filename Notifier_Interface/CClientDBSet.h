#pragma once
#include "ITable.h"
#include "CLIENT.h"
#include "sql.h"
class CClientDBSet : public ITable<CLIENT, CString>
{
public:
	CClientDBSet(DBContext& db);
};

