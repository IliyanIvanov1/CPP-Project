#pragma once
#include "PHONE_NUMBER.h"
#include <vector>
#include "DBContext.h"
class CPhoneNumberService
{
private:
	DBContext m_oDb;
public:
	vector<PHONE_NUMBER>::iterator m_itPhoneNumber;
	vector<PHONE_NUMBER> m_vPhoneNumbers;
public:
	CPhoneNumberService();

	bool GetPhoneNumbers();
};

