#include "stdafx.h"
#include "CCampaignDBSet.h"

CCampaignDBSet::CCampaignDBSet(DBContext& db) : ITable("campaigns", db)
{
	InsertFields();
}
void CCampaignDBSet::InsertFields()
{
	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(CAMPAIGN::nId), "id", ColType(Int), (int)offsetof(CAMPAIGN, nId),true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(CAMPAIGN::szStatus), "status", ColType(String), (int)offsetof(CAMPAIGN, szStatus)));
	vTableColSpecifications.push_back(TableColSpecification(3, sizeof(CAMPAIGN::szName), "name", ColType(String), (int)offsetof(CAMPAIGN, szName)));
	vTableColSpecifications.push_back(TableColSpecification(4, sizeof(CAMPAIGN::szValidFromDate), "valid_from_date", ColType(String), (int)offsetof(CAMPAIGN, szValidFromDate)));
	vTableColSpecifications.push_back(TableColSpecification(5, sizeof(CAMPAIGN::szValidUntilDate),  "valid_until_date", ColType(String), (int)offsetof(CAMPAIGN, szValidUntilDate)));
	vTableColSpecifications.push_back(TableColSpecification(6, sizeof(CAMPAIGN::nAddedByUserId), "added_by_user_id", ColType(Int), (int)offsetof(CAMPAIGN, nAddedByUserId)));
	vTableColSpecifications.push_back(TableColSpecification(7, sizeof(CAMPAIGN::nApprovedByUserId), "approved_by_user_id", ColType(Int), (int)offsetof(CAMPAIGN, nApprovedByUserId)));
	vTableColSpecifications.push_back(TableColSpecification(8, sizeof(CAMPAIGN::nNotifSentCount),  "notifications_sent_count", ColType(Int), (int)offsetof(CAMPAIGN, nNotifSentCount)));
}
