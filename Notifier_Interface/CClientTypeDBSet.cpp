#include "stdafx.h"
#include "CClientTypeDBSet.h"

CClientTypeDBSet::CClientTypeDBSet(DBContext& db) : ITable("client_types", db)
{

	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(CLIENT_TYPE::nId),  "id", ColType(Int), (int)offsetof(CLIENT_TYPE, nId),true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(CLIENT_TYPE::szClientType),  "client_type", ColType(String), (int)offsetof(CLIENT_TYPE, szClientType)));
}
