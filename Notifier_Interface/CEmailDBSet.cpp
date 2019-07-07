#include "stdafx.h"
#include "CEmailDBSet.h"

CEmailDBSet::CEmailDBSet(DBContext& db) : ITable("emails", db)
{

	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(EMAIL::nId), "id", ColType(Int), (int)offsetof(EMAIL, nId),true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(EMAIL::szEmail),"email", ColType(String), (int)offsetof(EMAIL, szEmail)));
	vTableColSpecifications.push_back(TableColSpecification(3, sizeof(EMAIL::nClientId), "client_id", ColType(Int), (int)offsetof(EMAIL, nClientId)));
	vTableColSpecifications.push_back(TableColSpecification(4, sizeof(EMAIL::szStatus), "status", ColType(String), (int)offsetof(EMAIL, szStatus)));
	vTableColSpecifications.push_back(TableColSpecification(5, sizeof(EMAIL::szIsVerified), "is_verified", ColType(String), (int)offsetof(EMAIL, szIsVerified)));
	vTableColSpecifications.push_back(TableColSpecification(6, sizeof(EMAIL::szMsgAgreed),"msgs_agreed", ColType(String), (int)offsetof(EMAIL, szMsgAgreed)));
}
