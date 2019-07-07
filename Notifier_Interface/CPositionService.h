#pragma once
#include "afx.h"
#include <vector>
#include "POSITIONN.h"
#include "DBContext.h"
class CPositionService
{
private:
	DBContext m_oDb;
public:
	vector<POSITIONN> m_vPositions;
	vector<POSITIONN>::iterator m_itPosition;
public:
	CPositionService();

	bool GetPositions();
};

