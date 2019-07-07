#include "stdafx.h"
#include "CPositionDBSet.h"
#include "CPositionService.h"


CPositionService::CPositionService()
{
	m_oDb.InitiateConnection();
}

bool CPositionService::GetPositions()
{
	CPositionDBSet oPositionDbSet(m_oDb);
	oPositionDbSet.GetAll(m_vPositions);
	if (m_vPositions.empty())
	{
		return false;
	}
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return true;
}

