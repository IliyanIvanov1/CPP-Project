#include "stdafx.h"
#include "CCountryService.h"
#include "CCountryDBSet.h"


CCountryService::CCountryService()
{
	m_oDb.InitiateConnection();
}

bool CCountryService::GetCountries()
{
	CCountryDBSet oCountryDbSet(m_oDb);
	oCountryDbSet.GetAll(m_vCountries);
	if (m_vCountries.empty())
	{
		return false;
	}
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return true;
}

