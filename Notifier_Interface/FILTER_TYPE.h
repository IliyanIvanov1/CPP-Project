#pragma once

#include "afx.h"

#define NAME_LEN 64

struct FILTER_TYPE
{
	int nId;
	char szName[NAME_LEN + 1];

	FILTER_TYPE()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

