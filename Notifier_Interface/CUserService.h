#pragma once
#include "USER.h"
#include "CUserDBSet.h"
#include "DBContext.h"
#include "Functions.h"
class CUserService
{
private:
	DBContext m_oDb;
private:
	bool CheckIfExists(const CString& strUsername);
	int FindUserId(const CString& strUsername);

public:
	USER recLoggedUser;
public:
	CUserService();

	bool IsAdmin(const CString& strUsername);

	int FindNextId();

	bool Create(const CString& strNames,const CString& strUsername, const CString& strPassword, int nPositionId);

	bool Login(const CString& strUsername, const CString& strPassword);
};

