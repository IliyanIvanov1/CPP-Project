#include "stdafx.h"
#include "CFilterServices.h"
#include "CFilterTypeDBSet.h"


CFilterServices::CFilterServices()
{
	m_oDb.InitiateConnection();
}

bool CFilterServices::GetFilters()
{
	CFilterTypeDBSet oFilterType(m_oDb);
	oFilterType.GetAll(m_vFilters);
	if (m_vFilters.empty())
	{
		return false;
	}
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return true;
}

