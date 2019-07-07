#pragma once
#include "ITable.h"
#include "PHONE_NUMBER.h"
class CPhoneNumberDBSet : public ITable<PHONE_NUMBER, int>
{
public:
	CPhoneNumberDBSet(DBContext& db);
};

