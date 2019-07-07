#pragma once
#include "ITable.h"
#include "COUNTRY.h"

class CCountryDBSet : public ITable<COUNTRY, CString>
{
public :
	CCountryDBSet(DBContext& db);
};