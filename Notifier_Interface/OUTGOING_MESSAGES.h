#pragma once

#include "afx.h"

#define STATUS_LEN 64
#define TYPE_LEN 64
#define MSG_SUBJECT_LEN 64
#define MSG_TEXT_LEN 1024
#define RES_TEMPL_NAME_LEN 64
#define RES_TEMPL_CODE_LEN 64
#define HTML_DATA_LEN 1024

struct OUTGOING_MESSAGES
{
	int nId;
	char szStatus[STATUS_LEN + 1];
	int  nPriorityId;
	char szType[TYPE_LEN + 1];
	int  nCampaignId;
	int  nToClientId;
	char szMsgSubject[MSG_SUBJECT_LEN + 1];
	char szMsgText[MSG_TEXT_LEN + 1];
	char szResTemplName[RES_TEMPL_NAME_LEN + 1];
	char szResTemplCode[RES_TEMPL_CODE_LEN + 1];
	char szHtmlData[HTML_DATA_LEN + 1];

	OUTGOING_MESSAGES()
	{
		SecureZeroMemory(this, sizeof *this);
	}
};

