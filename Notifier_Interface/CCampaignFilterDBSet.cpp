#include "stdafx.h"
#include "CCampaignFilterDBSet.h"

CCampaignFilterDBSet::CCampaignFilterDBSet(DBContext& db) : ITable("campaign_filters", db)
{
	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(CAMPAIGN_FILTER::nId), "id", ColType(Int), (int)offsetof(CAMPAIGN_FILTER, nId), true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(CAMPAIGN_FILTER::nCampaignId),"campaign_id", ColType(Int), (int)offsetof(CAMPAIGN_FILTER, nCampaignId)));
	vTableColSpecifications.push_back(TableColSpecification(3, sizeof(CAMPAIGN_FILTER::nFilterTypeId), "filter_type_id", ColType(Int), (int)offsetof(CAMPAIGN_FILTER, nFilterTypeId)));
}

