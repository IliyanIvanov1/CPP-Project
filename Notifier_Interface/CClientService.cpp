#include "stdafx.h"
#include "CClientService.h"
#include "CEmailService.h"
#include "CPhoneNumberService.h"
#include "CClientTypeService.h"
#include "CCountryService.h"

ClientFullInfo::ClientFullInfo(const CString& strNames, const CString& strEmail, const CString& strPhone, const CString& strPinOrBulstat,
	 const CString& strClientType, const CString& strIsVerified, const CString& strMsgAgreed,const CString& strCountry)
{
	strcpy_s(szNames, (const char*)strNames);
	strcpy_s(szEmail, (const char*)strEmail);
	strcpy_s(szPhone, (const char*)strPhone);
	strcpy_s(szPinOrBulstat, (const char*)strPinOrBulstat);
	strcpy_s(szClientType, (const char*)strClientType);
	strcpy_s(szIsVerified, (const char*)strIsVerified);
	strcpy_s(szMsgAgreed, (const char*)strMsgAgreed);
	strcpy_s(szCountry, (const char*)strCountry);
}

CClientService::CClientService()
{
	m_oDb.InitiateConnection();
}

bool CClientService::Create(const CString& strNames, int nClientTypeId, const CString& strPinOrBulstat, int nCountryId, const CString& strEmail, const CString& strPhoneNumber, const CString& strIsVerified, const CString& strMsgAgreed)
{
	if (!CheckIfExists(strPinOrBulstat))
	{

		CString strStatus("active");

		int nClientId;

		CLIENT recClient;

		strcpy_s(recClient.szStatus, (const char*)strStatus);
		strcpy_s(recClient.szName, (const char*)strNames);
		recClient.nClientTypeId = nClientTypeId;
		strcpy_s(recClient.szPinOrBulstat, (const char*)strPinOrBulstat);
		recClient.nCountryId = nCountryId;

		CClientDBSet oClientDbSet(m_oDb);
		bool bClInsertSucc = oClientDbSet.Insert(recClient);

		if (!bClInsertSucc)
		{
			return false;
		}

		nClientId = oClientDbSet.GetScopeId();

		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);

		EMAIL recEmail;
		strcpy_s(recEmail.szEmail, (const char*)strEmail);
		recEmail.nClientId = nClientId;
		strcpy_s(recEmail.szStatus, (const char*)strStatus);
		strcpy_s(recEmail.szIsVerified, (const char*)strIsVerified);
		strcpy_s(recEmail.szMsgAgreed, (const char*)strMsgAgreed);

		CEmailDBSet oEmailDbSet(m_oDb);
		bool bEmInsertSucc = oEmailDbSet.Insert(recEmail);

		if (!bEmInsertSucc)
		{
			return false;
		}

		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);

		PHONE_NUMBER recPhoneNumber;
		strcpy_s(recPhoneNumber.szPhoneNumber, (const char*)strPhoneNumber);
		recPhoneNumber.nClientId = nClientId;
		strcpy_s(recPhoneNumber.szStatus, (const char*)strStatus);
		strcpy_s(recPhoneNumber.szIsVerified, (const char*)strIsVerified);
		strcpy_s(recPhoneNumber.szMsgsAgreed, (const char*)strMsgAgreed);

		CPhoneNumberDBSet oPhoneDbSet(m_oDb);
		bool bPhInsertSucc = oPhoneDbSet.Insert(recPhoneNumber);

		if (!bPhInsertSucc)
		{
			return false;
		}

		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);

		if (bClInsertSucc && bEmInsertSucc && bPhInsertSucc)
		{
			if (oClientDbSet.Commit(m_oDb.m_SqlConnHandle))
			{
				return true;
			}
			return false;
		}
		else
		{
			if (oClientDbSet.Rollback(m_oDb.m_SqlConnHandle))
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool CClientService::Update(const CString& strNames, int nClientTypeId, const CString& strPinOrBulstat, int nCountryId, const CString& strEmail, const CString& strPhoneNumber, const CString& strIsVerified, const CString& strMsgAgreed)
{
		CString strStatus("active");

		int nClientId;

		CLIENT recClient;

		strcpy_s(recClient.szStatus, (const char*)strStatus);
		strcpy_s(recClient.szName, (const char*)strNames);
		recClient.nClientTypeId = nClientTypeId;
		strcpy_s(recClient.szPinOrBulstat, (const char*)strPinOrBulstat);
		recClient.nCountryId = nCountryId;

		CClientDBSet oClientDbSet(m_oDb);
		bool bClUpdateSucc = oClientDbSet.Update(recClient, strPinOrBulstat);

		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);

		if (!bClUpdateSucc)
		{
			return false;
		}

		nClientId = FindClientId(strPinOrBulstat);


		EMAIL recEmail;
		strcpy_s(recEmail.szEmail, (const char*)strEmail);
		recEmail.nClientId = nClientId;
		strcpy_s(recEmail.szStatus, (const char*)strStatus);
		strcpy_s(recEmail.szIsVerified, (const char*)strIsVerified);
		strcpy_s(recEmail.szMsgAgreed, (const char*)strMsgAgreed);

		CEmailDBSet oEmailDbSet(m_oDb);
		bool bEmUpdateSucc = oEmailDbSet.Update(recEmail, nClientId);

		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);

		if (!bEmUpdateSucc)
		{
			return false;
		}


		PHONE_NUMBER recPhoneNumber;
		strcpy_s(recPhoneNumber.szPhoneNumber, (const char*)strPhoneNumber);
		recPhoneNumber.nClientId = nClientId;
		strcpy_s(recPhoneNumber.szStatus, (const char*)strStatus);
		strcpy_s(recPhoneNumber.szIsVerified, (const char*)strIsVerified);
		strcpy_s(recPhoneNumber.szMsgsAgreed, (const char*)strMsgAgreed);

		CPhoneNumberDBSet oPhoneDbSet(m_oDb);
		bool bPhUpdateSucc = oPhoneDbSet.Update(recPhoneNumber, nClientId);

		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);

		if (!bPhUpdateSucc)
		{
			return false;
		}

		if (bClUpdateSucc && bEmUpdateSucc && bPhUpdateSucc)
		{
			if (oClientDbSet.Commit(m_oDb.m_SqlConnHandle))
			{
				return true;
			}
			return false;
		}
		else
		{
			if (oClientDbSet.Rollback(m_oDb.m_SqlConnHandle))
			{
				return false;
			}
		}
		return true;
}

bool CClientService::Delete(const CString& strPinOrBulstat)
{
	CClientDBSet oClientDbSet(m_oDb);
	bool bClSuccDeleted = oClientDbSet.Delete(strPinOrBulstat);
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	if (!bClSuccDeleted)
	{
		return false;
	}

	int nClientId = FindClientId(strPinOrBulstat);

	CEmailDBSet oEmailDbSet(m_oDb);
	bool bEmSuccDeleted = oEmailDbSet.Delete(nClientId);
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	if (!bEmSuccDeleted)
	{
		return false;
	}

	CPhoneNumberDBSet oPhoneNumberDbSet(m_oDb);
	bool bPhSuccDeleted = oPhoneNumberDbSet.Delete(nClientId);
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	if (!bPhSuccDeleted)
	{
		return false;
	}

	if (bClSuccDeleted && bEmSuccDeleted && bPhSuccDeleted)
	{
		if (oClientDbSet.Commit(m_oDb.m_SqlConnHandle))
		{
			return true;
		}
		return false;
	}
	else
	{
		if (oClientDbSet.Rollback(m_oDb.m_SqlConnHandle))
		{
			return false;
		}
	}
	return true;
}

bool CClientService::ListClients()
{
	if (!GetClients())
	{
		return false;
	}
	CEmailService oEmailService;
	if (!oEmailService.GetEmails())
	{
		return false;
	}

	
	auto vEmails = oEmailService.m_vEmails;
	auto itCurrentEmail = vEmails.begin();

	CPhoneNumberService oPhoneNumberService;
	if (!oPhoneNumberService.GetPhoneNumbers())
	{
		return false;
	}

	auto vPhoneNumbers = oPhoneNumberService.m_vPhoneNumbers;
	auto itCurrentPhoneNumber = vPhoneNumbers.begin();

	CClientTypeService oClientTypeService;
	if (!oClientTypeService.GetClientTypes())
	{
		return false;
	}
	
	auto vClientTypes = oClientTypeService.m_vClientTypes;
	auto itCurrentClientType = oClientTypeService.m_itClientType;

	CCountryService oCountryService;
	if (!oCountryService.GetCountries())
	{
		return false;
	}

	auto vCountries = oCountryService.m_vCountries;
	auto itCurrentCountry = oCountryService.m_itCountry;

	for (m_itCurrentClient = m_vClients.begin(); m_itCurrentClient < m_vClients.end(); m_itCurrentClient++, itCurrentEmail++,itCurrentPhoneNumber++)
	{
		if (strcmp(m_itCurrentClient->szStatus, "deleted") != 0)
		{
			CString strName = m_itCurrentClient->szName;
			CString strEmail = itCurrentEmail->szEmail;
			CString strPhone = itCurrentPhoneNumber->szPhoneNumber;
			CString strPinOrBulstat = m_itCurrentClient->szPinOrBulstat;
			CString strClientType;
			int nClientTypeId = m_itCurrentClient->nClientTypeId;

			for (itCurrentClientType = vClientTypes.begin(); itCurrentClientType < vClientTypes.end(); itCurrentClientType++)
			{
				if (nClientTypeId == itCurrentClientType->nId)
				{
					strClientType = itCurrentClientType->szClientType;
				}
			}
			CString strCountry;
			int nCountryId = m_itCurrentClient->nCountryId;

			for (itCurrentCountry = vCountries.begin(); itCurrentCountry < vCountries.end(); itCurrentCountry++)
			{
				if (nCountryId == itCurrentCountry->nId)
				{
					strCountry = itCurrentCountry->szName;
				}
			}
			CString strIsVerified = itCurrentEmail->szIsVerified;
			CString strMsgAgreed = itCurrentEmail->szMsgAgreed;
			m_vClientsFullInfo.push_back(ClientFullInfo(strName, strEmail, strPhone, strPinOrBulstat, strClientType, strIsVerified, strMsgAgreed, strCountry));
		}
	}
	return true;
}

bool CClientService::GetClients()
{
	CClientDBSet oClientDbSet(m_oDb);
	oClientDbSet.GetAll(m_vClients);
	if (m_vClients.empty())
	{
		return false;
	}
	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return true;
}

bool CClientService::CheckIfExists(const CString& strPinOrBulstat)
{
	CLIENT recClient;
	CClientDBSet oClientDbSet(m_oDb);
	oClientDbSet.GetByKey(recClient, strPinOrBulstat);

	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);

	if (strcmp(recClient.szStatus, "deleted") == 0)
	{
		return false;
	} 

	if (recClient.szPinOrBulstat == strPinOrBulstat)
	{
		return true;
	} 
		
	return false;
}

int CClientService::FindClientId(const CString& strPinOrBulstat)
{
	CLIENT recClient;
	CClientDBSet oClientDbSet(m_oDb);
	oClientDbSet.GetByKey(recClient, strPinOrBulstat);

	m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
	return recClient.nId;
}



int CClientService::FindNextId()
{
	CClientDBSet oClientDbSet(m_oDb);
	int nNextId=oClientDbSet.GetNextId();

	if (nNextId)
	{
		m_oDb.StmtRealloc(m_oDb.m_SqlStmtHandle);
		return nNextId;
	}

	return 0;
}
