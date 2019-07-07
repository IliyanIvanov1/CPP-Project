#pragma once
#include "afx.h"
#include <vector>
#include "COUNTRY.h"
#include "DBContext.h"
class CCountryService
{
private:

	DBContext m_oDb;
public:
	vector<COUNTRY>::iterator m_itCountry;
	vector<COUNTRY> m_vCountries;
public:
	CCountryService();

	bool GetCountries();
};

