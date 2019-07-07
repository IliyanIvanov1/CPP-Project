#include "stdafx.h"
#include "CFilterTypeDBSet.h"

CFilterTypeDBSet::CFilterTypeDBSet(DBContext& db) : ITable("filter_types", db)
{

	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(FILTER_TYPE::nId),  "id", ColType(Int), (int)offsetof(FILTER_TYPE, nId),true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(FILTER_TYPE::szName),  "name", ColType(String), (int)offsetof(FILTER_TYPE, szName)));
}
