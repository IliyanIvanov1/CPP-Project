#pragma once
#include "afx.h"

struct CAMPAIGN_FILTER
{
	int nId;
	int nCampaignId;
	int nFilterTypeId;

	CAMPAIGN_FILTER()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

