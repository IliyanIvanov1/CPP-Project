
#include "stdafx.h"
#include "CUserService.h"

CUserService::CUserService()
{
	m_oDb.InitiateConnection();
}

bool CUserService::CheckIfExists(const CString& strUsername)
{
	USER recUser;
	CUserDBSet oUserDBSet(m_oDb);
	oUserDBSet.GetByKey(recUser, strUsername);

	if (recUser.szUsername == strUsername)
	{
		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
		return true;
	}
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return false;
}

bool CUserService::IsAdmin(const CString& strUsername)
{
	USER recUser;
	CUserDBSet oUserDBSet(m_oDb);
	if (!oUserDBSet.GetByKey(recUser, strUsername))
	{
		return false;
	}

	if (recUser.nPositionId == 1)
	{
		return true;
	}
	return false;
}

bool CUserService::Create(const CString& strNames, const CString& strUsername, const CString& strPassword, int nPositionId)
{
		if (!CheckIfExists(strUsername))
		{
			CString userStatus("active");

			USER recUser;
			strcpy_s(recUser.szNames, (const char*)strNames);
			strcpy_s(recUser.szStatus, (const char*)userStatus);
			strcpy_s(recUser.szUsername, (const char*)strUsername);
			strcpy_s(recUser.szPassword, (const char*)strPassword);
			recUser.nPositionId = nPositionId;

			CUserDBSet oUserDbSet(m_oDb);
			bool bUserInsertSucc=oUserDbSet.Insert(recUser);

			if (!bUserInsertSucc)
			{
				return false;
			}

			m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
			if (bUserInsertSucc)
			{
				if (oUserDbSet.Commit(m_oDb.m_SqlConnHandle))
				{
					return true;
				}
			}
			else
			{
				if (oUserDbSet.Rollback(m_oDb.m_SqlConnHandle))
				{
					return false;
				}
			}
		}
	
	return false;
}

int CUserService::FindUserId(const CString& strUsername)
{
	USER recUser;
	CUserDBSet oUserDBSet(m_oDb);
	if (!oUserDBSet.GetByKey(recUser, strUsername))
	{
		return 0;
	}
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return recUser.nId;
}

bool CUserService::Login(const CString& strUsername, const CString& strPassword)
{
	USER recUser;
	CUserDBSet oUserDBSet(m_oDb);
	CString strHashedPassword = HashFunction(strPassword);
	oUserDBSet.GetByKey(recUser, strUsername);

	if (recUser.szUsername == strUsername && recUser.szPassword == strHashedPassword)
	{
		recLoggedUser = recUser;
		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
		return true;
	}
	else
	{
		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
		return false;
	}
}

int CUserService::FindNextId()
{
	CUserDBSet oUserDbSet(m_oDb);
	int nNextId = oUserDbSet.GetNextId();

	if (nNextId)
	{
		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
		return nNextId;
	}
	return 0;
}
