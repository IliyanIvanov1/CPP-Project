#pragma once
#include "afx.h"

#define NAME_LEN 64

struct POSITIONN
{
	int nId;
	char szPositionName[NAME_LEN + 1];

	POSITIONN()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

