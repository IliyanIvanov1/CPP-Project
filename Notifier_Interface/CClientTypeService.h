#pragma once
#include "afx.h"
#include <vector>
#include "CLIENT_TYPE.h"
#include "DBContext.h"
using namespace std;
class CClientTypeService
{
private:

	DBContext m_oDb;
public: 
	vector<CLIENT_TYPE>::iterator m_itClientType;
	vector<CLIENT_TYPE> m_vClientTypes;
public:
	CClientTypeService();
	
	bool GetClientTypes();
};