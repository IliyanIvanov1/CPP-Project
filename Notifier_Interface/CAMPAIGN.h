#pragma once
#include "afx.h"

#define STATUS_LEN 64
#define NAME_LEN 64
#define VALID_FROM_DATE_LEN 64
#define VALID_UNTIL_DATE_LEN 64

struct CAMPAIGN
{
public:
	int  nId;
	char szStatus[STATUS_LEN + 1];
	char szName[NAME_LEN + 1];
	char szValidFromDate[VALID_FROM_DATE_LEN + 1];
	char szValidUntilDate[VALID_UNTIL_DATE_LEN + 1];
	int nAddedByUserId;
	int nApprovedByUserId;
	int nNotifSentCount;

	CAMPAIGN()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

