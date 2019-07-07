#pragma once

#include "afx.h"

#define CLIENT_TYPE_LEN 64

struct CLIENT_TYPE
{
	int nId;
	char szClientType[CLIENT_TYPE_LEN + 1];

	CLIENT_TYPE()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

