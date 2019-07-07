#include "stdafx.h"
#include "CPhoneNumberService.h"
#include "CPhoneNumberDBSet.h"


CPhoneNumberService::CPhoneNumberService()
{
	m_oDb.InitiateConnection();
}

bool CPhoneNumberService::GetPhoneNumbers()
{
	CPhoneNumberDBSet oPhoneNumberDbSet(m_oDb);
	oPhoneNumberDbSet.GetAll(m_vPhoneNumbers);
	if (m_vPhoneNumbers.empty())
	{
		return false;
	}
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return true;
}

