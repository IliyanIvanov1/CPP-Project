#pragma once
#include "EMAIL.h"
#include <vector>
#include "DBContext.h"
class CEmailService
{
private:
	DBContext m_oDb;
public:
	vector<EMAIL>::iterator m_itEmail;
	vector<EMAIL> m_vEmails;
public:
	CEmailService();

	bool GetEmails();
};

