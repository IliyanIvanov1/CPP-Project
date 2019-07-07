#pragma once

#include "afx.h"

#define NAME_LEN 64

struct COUNTRY
{
	int nId;
	char szName[NAME_LEN + 1];
	
	COUNTRY()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};