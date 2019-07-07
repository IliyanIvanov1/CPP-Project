#include "stdafx.h"
#include "CPositionDBSet.h"

CPositionDBSet::CPositionDBSet(DBContext& db) : ITable("positions", db)
{
	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(POSITIONN::nId), "id", ColType(Int), (int)offsetof(POSITIONN, nId),true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(POSITIONN::szPositionName), "position_name", ColType(String), (int)offsetof(POSITIONN, szPositionName)));
}
