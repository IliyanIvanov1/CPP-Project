#include "stdafx.h"
#include "CClientTypeService.h"
#include "CClientTypeDBSet.h"

CClientTypeService::CClientTypeService()
{
	m_oDb.InitiateConnection();
}

bool CClientTypeService::GetClientTypes()
{
	CClientTypeDBSet oClientTypeDbSet(m_oDb);
	oClientTypeDbSet.GetAll(m_vClientTypes);
	if (m_vClientTypes.empty())
	{
		return false;
	}
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return true;
}