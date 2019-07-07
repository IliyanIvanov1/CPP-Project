#include "stdafx.h"
#include "CPhoneNumberDBSet.h"

CPhoneNumberDBSet::CPhoneNumberDBSet(DBContext& db) : ITable("phone_numbers", db)
{
	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(PHONE_NUMBER::nId), "id", ColType(Int), (int)offsetof(PHONE_NUMBER, nId),true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(PHONE_NUMBER::szPhoneNumber), "phone_number", ColType(String), (int)offsetof(PHONE_NUMBER, szPhoneNumber)));
	vTableColSpecifications.push_back(TableColSpecification(3, sizeof(PHONE_NUMBER::nClientId),"client_id", ColType(Int), (int)offsetof(PHONE_NUMBER, nClientId)));
	vTableColSpecifications.push_back(TableColSpecification(4, sizeof(PHONE_NUMBER::szStatus), "status", ColType(String), (int)offsetof(PHONE_NUMBER, szStatus)));
	vTableColSpecifications.push_back(TableColSpecification(5, sizeof(PHONE_NUMBER::szIsVerified),  "is_verified", ColType(String), (int)offsetof(PHONE_NUMBER, szIsVerified)));
	vTableColSpecifications.push_back(TableColSpecification(6, sizeof(PHONE_NUMBER::szMsgsAgreed),"msgs_agreed", ColType(String), (int)offsetof(PHONE_NUMBER, szMsgsAgreed)));
}
