#pragma once

#include "afx.h"

#define STATUS_LEN 64
#define NAME_LEN 64
#define PIN_OR_BULSTAT_LEN 64

struct CLIENT
{
	int nId;
	char szStatus[STATUS_LEN + 1];
	char szName[NAME_LEN + 1];
	int nClientTypeId;
	char szPinOrBulstat[PIN_OR_BULSTAT_LEN + 1];
	int nCountryId;

	CLIENT()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

