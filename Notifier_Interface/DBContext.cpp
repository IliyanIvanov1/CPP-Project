#include "stdafx.h"

#include "DBContext.h"
#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

using namespace std;

DBContext::DBContext()
{

}

void DBContext::CloseConnection()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_SqlStmtHandle);
	SQLDisconnect(m_SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, m_SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, m_SqlEnvHandle);
};

bool DBContext::CheckConnection()
{

	int nSqlAllocEnvHandleFail = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_SqlEnvHandle);
	int nSqlSetEnvAttrFail = SQLSetEnvAttr(m_SqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
	int nSqlAllocConnHandleFail = SQLAllocHandle(SQL_HANDLE_DBC, m_SqlEnvHandle, &m_SqlConnHandle);

	if (nSqlAllocEnvHandleFail || nSqlSetEnvAttrFail || nSqlAllocConnHandleFail) //Allocates EnvironmentHandle using Null Handle
	{
		CloseConnection();
		return false;
	}
	return true;
}

void DBContext::ConnectingDriver()
{
	switch (SQLDriverConnectW(m_SqlConnHandle,		//ConnectionHandle
		NULL, //WindowHandle
			  //m_szConnectionString,
		(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=DT-VN00483,1433;DATABASE=Notifier_DB;UID=il.ivanov;PWD=Pa$$w0rd;",
		//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=DT-VN00483,1433;DATABASE=Notifier_DB;Trusted=true;", //ConnString
		SQL_NTS,		//ConnStringLength
		m_Retconstring,	//Buffer
		SQL_RETURN_CODE_LEN,			//BufferLength
		NULL,
		SQL_DRIVER_NOPROMPT)) { //Flag
	case SQL_SUCCESS:
		cout << "Successfully connected to SQL Server";
		cout << "\n";
		break;
	case SQL_SUCCESS_WITH_INFO:
		cout << "Successfully connected to SQL Server";
		cout << "\n";
		break;
	case SQL_INVALID_HANDLE:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		CloseConnection();
	case SQL_ERROR:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		CloseConnection();
	default:
		break;
	}

	if (SQL_SUCCESS!= SQLSetConnectAttr(m_SqlConnHandle, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, SQL_NTS))
		CloseConnection();

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, m_SqlConnHandle, &m_SqlStmtHandle))
		CloseConnection();
};

SQLRETURN DBContext::ExecuteQuery(CStringA& strQueryString)
{
	if (CheckConnection())
	{
		
		int nSqlExecFail = SQLExecDirect(m_SqlStmtHandle, (SQLCHAR*)(strQueryString.GetString()), strQueryString.GetLength() + 1);
		if (nSqlExecFail)
		{
			cout << "Error executing the query..." << endl;
			return nSqlExecFail;
		}
		else
		{
			cout << "Query successfully executed" << endl;
			return SQL_SUCCESS;
		}
	}
	else
	{
		CloseConnection();
		return SQL_ERROR;
	}
}

void DBContext::InitiateConnection()
{
	cout << "Attempting connection to SQL Server..." << endl;
	if (CheckConnection())
	{
		ConnectingDriver();
	}
	else
	{
		cout << "Error connecting the database" << endl;
	}
}

void DBContext::StmtRealloc(SQLHANDLE& sqlStmtHandle)
{
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, m_SqlConnHandle, &sqlStmtHandle))
		CloseConnection();
}
