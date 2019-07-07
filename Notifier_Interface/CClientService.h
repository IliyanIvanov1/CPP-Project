#pragma once
#include "CLIENT.h"
#include "EMAIL.h"
#include "PHONE_NUMBER.h"
#include "CClientDBSet.h"
#include "CEmailDBSet.h"
#include "CPhoneNumberDBSet.h"
#include "DBContext.h"
#define NAMES_LEN 64
#define EMAIL_LEN 64
#define PHONE_LEN 64
#define PIN_OR_BULSTAT_LEN 64
#define ADDED_DATE_LEN 64
#define CLIENT_TYPE_LEN 64
#define ISVERIFIED_LEN 64
#define MSGAGREED_LEN 64
#define COUNTRY_LEN 64
struct ClientFullInfo
{
	char szNames[NAMES_LEN + 1];
	char szEmail[EMAIL_LEN + 1];
	char szPhone[PHONE_LEN + 1];
	char szPinOrBulstat[PIN_OR_BULSTAT_LEN + 1];
	char szClientType[CLIENT_TYPE_LEN + 1];
	char szIsVerified[ISVERIFIED_LEN + 1];
	char szMsgAgreed[MSGAGREED_LEN + 1];
	char szCountry[COUNTRY_LEN + 1];

	ClientFullInfo(const CString& strNames, const CString& strEmail, const CString& strPhone, const CString& strPinOrBulstat,
		const CString& strClientType, const CString& strIsVerified, const CString& strMsgAgreed,const CString& strCountry );
};

class CClientService
{
public:

	vector<ClientFullInfo> m_vClientsFullInfo;
	vector<ClientFullInfo>::iterator m_itCurrentClientFullInfo;
	vector<CLIENT> m_vClients;
	vector<CLIENT>::iterator m_itCurrentClient;
public:
	CClientService();
	bool Create(const CString& strNames, int nClientTypeId, const CString& strPinOrBulstat, int nCountryId, const CString& strEmail, const CString& strPhoneNumber, const CString& strIsVerified, const CString& strMsgAgreed);
	bool Update(const CString& strNames, int nClientTypeId, const CString& strPinOrBulstat, int nCountryId, const CString& strEmail, const CString& strPhoneNumber, const CString& strIsVerified, const CString& strMsgAgreed);
	bool Delete(const CString& strPinOrBulstat);
	bool ListClients();
private:
	DBContext m_oDb;
private:
	bool GetClients();

	bool CheckIfExists(const CString& strPinOrBulstat);

	int FindClientId(const CString& strPinOrBulstat);

	int FindNextId();

}; 