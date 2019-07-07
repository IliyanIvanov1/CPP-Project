#pragma once
#include "afx.h"
#include <vector>
#include "FILTER_TYPE.h"
#include "DBContext.h"
class CFilterServices
{
private:
	DBContext m_oDb;
public:
	vector<FILTER_TYPE> m_vFilters;
	vector<FILTER_TYPE>::iterator m_itFilter;
public:
	CFilterServices();

	bool GetFilters();
};

