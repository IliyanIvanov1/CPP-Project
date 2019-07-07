#include "stdafx.h"
#include "CCountryDBSet.h"

CCountryDBSet::CCountryDBSet(DBContext& db) : ITable("countries",db)
{
	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(COUNTRY::nId), "id", ColType(Int), (int)offsetof(COUNTRY, nId), true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(COUNTRY::szName), "name", ColType(String), (int)offsetof(COUNTRY, szName)));
}