#pragma once

#include "afx.h"
#define NAME_LEN 64
#define ADDED_DATE_LEN 64
#define STATUS_LEN 64
#define USERNAME_LEN 64
#define PASSWORD_LEN 64

struct USER
{
	int nId;
	char szNames[NAME_LEN +1];
	char szStatus[STATUS_LEN +1];
	char szUsername[USERNAME_LEN +1];
	char szPassword[PASSWORD_LEN +1];
	int nPositionId;

	USER()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

