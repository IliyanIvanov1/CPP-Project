#pragma once

#include "ITable.h"
#include "CAMPAIGN.h"

class CCampaignDBSet : public ITable<CAMPAIGN, int>
{
public:
	CCampaignDBSet(DBContext& db);
private:
	void InsertFields();
};

