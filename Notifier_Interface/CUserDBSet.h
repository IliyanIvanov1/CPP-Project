#pragma once
#include "ITable.h"
#include "USER.h"
class CUserDBSet : public ITable<USER, CString>
{
public:
	CUserDBSet(DBContext& db);
private:
	void InsertFields();
};

