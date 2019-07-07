#include "stdafx.h"
#include "CUserDBSet.h"


CUserDBSet::CUserDBSet(DBContext& db) : ITable("users", db)
{
	InsertFields();
}

void CUserDBSet::InsertFields()
{
	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(USER::nId), "id", ColType(Int), (int)offsetof(USER, nId)));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(USER::szNames), "names", ColType(String), (int)offsetof(USER, szNames))); //added_date must be corrected;
	vTableColSpecifications.push_back(TableColSpecification(3, sizeof(USER::szStatus),  "status", ColType(String), (int)offsetof(USER, szStatus)));
	vTableColSpecifications.push_back(TableColSpecification(4, sizeof(USER::szUsername), "username", ColType(String), (int)offsetof(USER, szUsername),true));
	vTableColSpecifications.push_back(TableColSpecification(5, sizeof(USER::szPassword),  "password", ColType(String), (int)offsetof(USER, szPassword)));
	vTableColSpecifications.push_back(TableColSpecification(6, sizeof(USER::nPositionId),  "position_id", ColType(Int), (int)offsetof(USER, nPositionId)));
}
