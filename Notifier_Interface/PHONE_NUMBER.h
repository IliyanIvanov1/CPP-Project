#pragma once

#include "afx.h"

#define PHONE_NUMBER_LEN 64
#define STATUS_LEN 64
#define IS_VERIFIED_LEN 64
#define MSGS_AGREED_LEN 64

struct PHONE_NUMBER
{
	int  nId;
	char szPhoneNumber[PHONE_NUMBER_LEN + 1];
	int  nClientId;
	char szStatus[STATUS_LEN + 1];
	char szIsVerified[IS_VERIFIED_LEN+1];
	char szMsgsAgreed[MSGS_AGREED_LEN+1];

	PHONE_NUMBER()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

