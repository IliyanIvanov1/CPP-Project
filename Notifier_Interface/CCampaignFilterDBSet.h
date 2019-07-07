#pragma once
#include "ITable.h"
#include "CAMPAIGN_FILTER.h"
class CCampaignFilterDBSet : public ITable<CAMPAIGN_FILTER, int>
{
public:
	CCampaignFilterDBSet(DBContext& db);

};

