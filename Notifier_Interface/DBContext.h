#pragma once
#include "stdafx.h"
#include <iostream>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include "afx.h"

#pragma comment(lib,"odbc32.lib") //!!!!!!!!!!!!!!!!!!

#define SQL_RESULT_LEN 256
#define SQL_RETURN_CODE_LEN 1024
using namespace std;

class DBContext
{
private:
	SQLHANDLE m_SqlEnvHandle = NULL;
	SQLWCHAR m_Retconstring[SQL_RETURN_CODE_LEN];

private:
	bool CheckConnection();
	void ConnectingDriver();

public:

	SQLHANDLE m_SqlConnHandle = NULL;
	SQLHANDLE m_SqlStmtHandle = NULL;
public:	

	DBContext();

	void CloseConnection();

	SQLRETURN ExecuteQuery(CStringA& strQueryString);

	void InitiateConnection();

	void StmtRealloc(SQLHANDLE& sqlStmtHandle);
};