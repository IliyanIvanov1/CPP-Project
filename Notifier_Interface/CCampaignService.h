#pragma once
#include "DBContext.h"
class CCampaignService
{
private:
	DBContext m_oDb;
public:
	CCampaignService();

	bool AddPendingCampaign(const CString& strName,const CString& strValidFromDate,const CString& strValidUntilDate,
		int nAddedByUserId,int nNotifSentCount, int nApprovedByUserId=NULL);


};