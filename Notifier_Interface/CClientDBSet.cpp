#include "stdafx.h"
#include "CClientDBSet.h"

CClientDBSet::CClientDBSet(DBContext& db) : ITable("clients", db)
{

	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(CLIENT::nId),  "id", ColType(Int), (int)offsetof(CLIENT, nId)));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(CLIENT::szStatus),  "status", ColType(String), (int)offsetof(CLIENT, szStatus)));
	vTableColSpecifications.push_back(TableColSpecification(3, sizeof(CLIENT::szName),  "name", ColType(String), (int)offsetof(CLIENT, szName)));
	vTableColSpecifications.push_back(TableColSpecification(4, sizeof(CLIENT::nClientTypeId),  "client_type_id", ColType(Int), (int)offsetof(CLIENT, nClientTypeId)));
	vTableColSpecifications.push_back(TableColSpecification(5, sizeof(CLIENT::szPinOrBulstat), "pin_or_bulstat", ColType(String), (int)offsetof(CLIENT, szPinOrBulstat),true));
	vTableColSpecifications.push_back(TableColSpecification(6, sizeof(CLIENT::nCountryId), "country_id", ColType(Int), (int)offsetof(CLIENT, nCountryId)));
}

