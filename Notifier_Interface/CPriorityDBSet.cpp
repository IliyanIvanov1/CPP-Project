#include "stdafx.h"
#include "CPriorityDBSet.h"

CPriorityDBSet::CPriorityDBSet(DBContext& db) : ITable("priorities", db)
{

	vTableColSpecifications.push_back(TableColSpecification(1, sizeof(PRIORITY::nId),  "id", ColType(Int), (int)offsetof(PRIORITY, nId),true));
	vTableColSpecifications.push_back(TableColSpecification(2, sizeof(PRIORITY::szPriority),  "priority", ColType(String), (int)offsetof(PRIORITY, szPriority)));
}
