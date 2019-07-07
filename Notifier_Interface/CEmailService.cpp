#include "stdafx.h"
#include "CEmailService.h"
#include "CEmailDBSet.h"


CEmailService::CEmailService()
{
	m_oDb.InitiateConnection();
}

bool CEmailService::GetEmails()
{
	CEmailDBSet oEmailDbSet(m_oDb);
	oEmailDbSet.GetAll(m_vEmails);
	if (m_vEmails.empty())
	{
		return false;
	}
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return true;
}