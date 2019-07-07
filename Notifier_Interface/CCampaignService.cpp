#include "stdafx.h"
#include "CCampaignService.h"
#include "CAMPAIGN.h"
#include "CCampaignDBSet.h"

CCampaignService::CCampaignService()
{
	m_oDb.InitiateConnection();
}

bool CCampaignService::AddPendingCampaign(const CString& strName, const CString& strValidFromDate, const CString& strValidUntilDate,
	int nAddedByUserId,  int nNotifSentCount, int nApprovedByUserId/*=NULL*/)
{
	CString strStatus("pending");

	CAMPAIGN recCampaign;
	strcpy_s(recCampaign.szStatus, (const char*)strStatus);
	strcpy_s(recCampaign.szName, (const char*)strName);
	strcpy_s(recCampaign.szValidFromDate, (const char*)strValidFromDate);
	strcpy_s(recCampaign.szValidUntilDate, (const char*)strValidUntilDate);
	recCampaign.nAddedByUserId = nAddedByUserId;
	recCampaign.nApprovedByUserId = nApprovedByUserId;
	recCampaign.nNotifSentCount = nNotifSentCount;


	CCampaignDBSet oCampaignDbSet(m_oDb);
	bool bCampaignInsertSucc = oCampaignDbSet.Insert(recCampaign);
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return true;
}