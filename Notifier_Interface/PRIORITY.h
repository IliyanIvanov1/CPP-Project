#pragma once

#include "afx.h"

#define PRIORITY_LEN 64

struct PRIORITY
{
	int nId;
	char szPriority[PRIORITY_LEN + 1];

	PRIORITY()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

