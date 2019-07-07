#pragma once

#include "afx.h"

#define EMAIL_LEN 64
#define STATUS_LEN 64
#define ISVERIFIED_LEN 64
#define MSGAGREED_LEN 64

struct EMAIL
{
	int nId;
	char szEmail[EMAIL_LEN + 1];
	int nClientId;
	char szStatus[STATUS_LEN + 1];
	char szIsVerified[ISVERIFIED_LEN+1];
	char szMsgAgreed[MSGAGREED_LEN+1];

	EMAIL()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

