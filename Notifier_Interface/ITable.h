#pragma once

#include "afx.h"
#include "DBContext.h"
#include <iostream>
#include <vector>
#include "Functions.h"

#define NAME_LEN 64

using namespace std;

struct TableColSpecification
{
	int nNum;
	int nSize;
	bool fIsPKey;
	char szName[NAME_LEN + 1];
	int nType;
	int nFieldOffset;

	TableColSpecification(int nOrder, int nSize,  CStringA strColName, int nType, int nObjRef, bool fIsPKey = 0)
	{
		this->nNum = nOrder;
		this->nSize = nSize;
		this->fIsPKey = fIsPKey;
		strcpy_s(szName, strColName.GetBuffer());
		this->nType = nType;
		this->nFieldOffset = nObjRef;
	}
};

enum ColType
{
	Int, String
};

template <typename T, typename KType>
class ITable
{
protected:
	vector<TableColSpecification> vTableColSpecifications;
	DBContext m_oDb;
	CStringA m_strTableName;

protected:
	ITable(const CStringA strTableName, DBContext& db)
	{
		m_strTableName = strTableName;
		m_oDb = db;
	};

public:

	bool Insert(T &entity)
	{
		vector<TableColSpecification>::iterator itCurrentColumn;

		CStringA strExecutableQuery;

		CStringA strQueryStatement = "INSERT INTO %s(";
		for (itCurrentColumn = vTableColSpecifications.begin() + 1; itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
		{
			if (itCurrentColumn != vTableColSpecifications.end() - 1)
			{
				strQueryStatement += itCurrentColumn->szName;
				strQueryStatement += ", ";
			}
			else
			{
				strQueryStatement += itCurrentColumn->szName;
			}
		}

		strQueryStatement += ") VALUES(";

		for (itCurrentColumn = vTableColSpecifications.begin() + 1; itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
		{
			byte* pEntityPtr = (byte*)&entity;
			int* pFieldOffset = (int*)(pEntityPtr + itCurrentColumn->nFieldOffset);

			switch (itCurrentColumn->nType)
			{
			case ColType(Int):
				if (itCurrentColumn != vTableColSpecifications.end() - 1)
				{
					strQueryStatement += IntegerToCString(*pFieldOffset); 
					strQueryStatement += ", ";
				}
				else
				{
					strQueryStatement += IntegerToCString(*pFieldOffset);
				}
				break;
			case ColType(String):
				char cInputArr[512] = { 0 };

				memcpy(cInputArr, pFieldOffset, itCurrentColumn->nSize);

				if (itCurrentColumn != vTableColSpecifications.end() - 1)
				{
					strQueryStatement += "'";
					strQueryStatement += cInputArr;
					strQueryStatement += "'";
					strQueryStatement += ", ";
				}
				else
				{
					strQueryStatement += "'";
					strQueryStatement += cInputArr;
					strQueryStatement += "'";
				}
				break;
			}
		}

		strQueryStatement += ")";

		strExecutableQuery.Format(strQueryStatement, m_strTableName);

		if (SQL_SUCCESS!= m_oDb.ExecuteQuery(strExecutableQuery))
		{
			return false;
		}

		 return true;
	}

	bool Delete(KType key)
	{
		vector<TableColSpecification>::iterator itCurrentColumn;

		int nKType = 0;

		CStringA strExecutableQuery;
		CStringA strQueryStatement = "UPDATE %s SET status='deleted' WHERE ";

		for (itCurrentColumn = vTableColSpecifications.begin(); itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
		{
			bool bIsPK = itCurrentColumn->fIsPKey;
			if (bIsPK)
			{
				strQueryStatement += itCurrentColumn->szName;
				nKType = itCurrentColumn->nType;
				break;
			}
		}

		switch (nKType)
		{
		case ColType(Int):
			strQueryStatement += "=%d";
			break;
		case ColType(String):
			strQueryStatement += "='%s'";
			break;
		}

		strExecutableQuery.Format(strQueryStatement, m_strTableName, key);

		if (SQL_SUCCESS != m_oDb.ExecuteQuery(strExecutableQuery))
		{
			return false;
		}

		return true;
	}

	bool Update(T &recEntity, KType primaryKey)
	{
		vector<TableColSpecification>::iterator itCurrentColumn;
		CStringA strExecutableQuery;
		int nKType = 0;

		CStringA strQueryStatement = "UPDATE %s SET ";

		for (itCurrentColumn = vTableColSpecifications.begin() + 1; itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
		{
			byte* pEntityPtr = (byte*)&recEntity;
			int* pFieldOffset = (int*)(pEntityPtr + itCurrentColumn->nFieldOffset);

			switch (itCurrentColumn->nType)
			{
			case ColType(Int):
				if (itCurrentColumn != vTableColSpecifications.end() - 1)
				{
					strQueryStatement += itCurrentColumn->szName;
					strQueryStatement += "=";
					strQueryStatement += IntegerToCString(*pFieldOffset);
					strQueryStatement += ", ";
				}
				else
				{
					strQueryStatement += itCurrentColumn->szName;
					strQueryStatement += "=";
					strQueryStatement += IntegerToCString(*pFieldOffset);
				}
				break;
			case ColType(String):
				char cInputArr[512] = { 0 };

				memcpy(cInputArr, pFieldOffset, itCurrentColumn->nSize);

				if (itCurrentColumn != vTableColSpecifications.end() - 1)
				{
					strQueryStatement += itCurrentColumn->szName;
					strQueryStatement += "=";
					strQueryStatement += "'";
					strQueryStatement += cInputArr;
					strQueryStatement += "'";
					strQueryStatement += ", ";
				}
				else
				{
					strQueryStatement += itCurrentColumn->szName;
					strQueryStatement += "=";
					strQueryStatement += "'";
					strQueryStatement += cInputArr;
					strQueryStatement += "'";
				}
				break;
			}
		}

		strQueryStatement += " WHERE ";

		for (itCurrentColumn = vTableColSpecifications.begin(); itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
		{
			bool bIsPK = itCurrentColumn->fIsPKey;
			if (bIsPK)
			{
				strQueryStatement += itCurrentColumn->szName;
				nKType = itCurrentColumn->nType;
				break;
			}
		}

		switch (nKType)
		{
		case ColType(Int):
			strQueryStatement += "=%d";
			break;
		case ColType(String):
			strQueryStatement += "='%s'";
			break;
		}

		strExecutableQuery.Format(strQueryStatement, m_strTableName, primaryKey);

		if (SQL_SUCCESS != m_oDb.ExecuteQuery(strExecutableQuery))
		{
			return false;
		}


		return true;
	}

	bool GetAll(vector<T> &vEntityInfo)
	{

		CStringA strExecutableQuery;
		CStringA strQueryStatement = "SELECT ";

		vector<TableColSpecification>::iterator itCurrentColumn;
		for (itCurrentColumn = vTableColSpecifications.begin(); itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
		{
			if (itCurrentColumn != vTableColSpecifications.end() - 1)
			{
				strQueryStatement += itCurrentColumn->szName;
				strQueryStatement += ", ";
			}
			else
			{
				strQueryStatement += itCurrentColumn->szName;
			}
		}

		strQueryStatement += " FROM %s";

		strExecutableQuery.Format(strQueryStatement, m_strTableName);

		int nExecuteQueryFail = m_oDb.ExecuteQuery(strExecutableQuery);
		if (nExecuteQueryFail)
		{
			m_oDb.CloseConnection();
			return false;
		}
		else
		{
			while (SQL_SUCCESS == SQLFetch(m_oDb.m_SqlStmtHandle))
			{
				T recEntity;

				for (itCurrentColumn = vTableColSpecifications.begin(); itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
				{
					int nColNum = itCurrentColumn->nNum;
					int nColSize = itCurrentColumn->nSize;
					SQLLEN nNullTerminator;
					byte* pEntityPtr = (byte*)&recEntity;
					int* pTargetBufferPtr = (int*)(pEntityPtr + itCurrentColumn->nFieldOffset);

					switch (itCurrentColumn->nType)
					{
					case ColType(Int):
						if (SQL_SUCCESS!= SQLGetData(m_oDb.m_SqlStmtHandle, nColNum, SQL_C_ULONG, pTargetBufferPtr, nColSize, NULL) || pTargetBufferPtr==NULL)
						{
							return false;
						}
						break;             

					case ColType(String):                                                                    
						if (SQL_SUCCESS != SQLGetData(m_oDb.m_SqlStmtHandle, nColNum, SQL_CHAR, pTargetBufferPtr, nColSize, &nNullTerminator) || pTargetBufferPtr==NULL)
						{
							return false;
						}
						pTargetBufferPtr[nNullTerminator] = '\0'; //Adds \0 so it knows where it ends
						break;
					}
				}
				vEntityInfo.push_back(recEntity);
			}
		}

		return true;
	}
	bool GetByKey(T &entity, KType key)
	{
		vector<TableColSpecification>::iterator itCurrentColumn;

		int nKType = 0;
		CStringA strExecutableQuery;
		CStringA strQueryStatement = "SELECT ";

		for (itCurrentColumn = vTableColSpecifications.begin(); itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
		{
			if (itCurrentColumn != vTableColSpecifications.end() - 1)
			{
				strQueryStatement += itCurrentColumn->szName;
				strQueryStatement += ", ";
			}
			else
			{
				strQueryStatement += itCurrentColumn->szName;
			}
		}

		strQueryStatement += " FROM %s WHERE ";

		for (itCurrentColumn = vTableColSpecifications.begin(); itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
		{
			bool fIsPK = itCurrentColumn->fIsPKey;
			if (fIsPK)
			{
				strQueryStatement += itCurrentColumn->szName;
				nKType = itCurrentColumn->nType;
				break;
			}
		}

		switch (nKType)
		{
		case ColType(Int):
			strQueryStatement += "=%d";
			break;
		case ColType(String):
			strQueryStatement += "='%s'";
			break;
		}

		strExecutableQuery.Format(strQueryStatement, m_strTableName, key);

		if (SQL_SUCCESS != m_oDb.ExecuteQuery(strExecutableQuery))
		{
			m_oDb.CloseConnection();
			return false;
		}
		else
		{
			while (SQL_SUCCESS == SQLFetch(m_oDb.m_SqlStmtHandle))
			{
				for (itCurrentColumn = vTableColSpecifications.begin(); itCurrentColumn != vTableColSpecifications.end(); itCurrentColumn++)
				{
					int nColNum = itCurrentColumn->nNum;
					int nColSize = itCurrentColumn->nSize;
					SQLLEN nNullTerminator;
					byte* pEntityPtr = (byte*)&entity;
					int* pTargetBufferPtr = (int*)(pEntityPtr + itCurrentColumn->nFieldOffset);

					switch (itCurrentColumn->nType)
					{
					case ColType(Int):
						if (SQL_SUCCESS!= SQLGetData(m_oDb.m_SqlStmtHandle, nColNum, SQL_C_ULONG, pTargetBufferPtr, nColSize, NULL) || pTargetBufferPtr==NULL)
						{
							return false;
						}

						break;
					case ColType(String):
						if (SQL_SUCCESS!= SQLGetData(m_oDb.m_SqlStmtHandle, nColNum, SQL_CHAR, pTargetBufferPtr, nColSize, &nNullTerminator) || pTargetBufferPtr==NULL)
						{
							return false;
						}
						pTargetBufferPtr[nNullTerminator] = '\0';

						break;
					}
				}
			}
		}
		cout << endl;

		return true;
	}

	bool Commit(SQLHANDLE& SqlConnHandle)
	{
		if (SQL_SUCCESS != SQLEndTran(SQL_HANDLE_DBC, SqlConnHandle, SQL_COMMIT))
		{
			return false;
		}
		return true;
	}

	bool Rollback(SQLHANDLE& SqlConnHandle)
	{
		if (SQL_SUCCESS != SQLEndTran(SQL_HANDLE_DBC, SqlConnHandle, SQL_ROLLBACK))
		{
			return false;
		}
		return true;
	}

	int GetNextId()
	{
		int nNextId;
		CString strExecutableQuery;
		strExecutableQuery.Format("SELECT IDENT_CURRENT('%s') + IDENT_INCR('%s')",m_strTableName,m_strTableName);

		if (SQL_SUCCESS!=m_oDb.ExecuteQuery(strExecutableQuery))
		{
			m_oDb.CloseConnection();
			return 0;
		}
		else
		{
			while (SQL_SUCCESS==SQLFetch(m_oDb.m_SqlStmtHandle))
			{
				int* pNextIdPtr = &nNextId;
				
				if (SQL_SUCCESS!= SQLGetData(m_oDb.m_SqlStmtHandle, 1, SQL_INTEGER, pNextIdPtr, sizeof(nNextId), NULL))
				{
					return false;
				}
			}
		}
		return nNextId;
	}

	int GetScopeId()
	{
		int nScopeId;
		CString strExecutableQuery= "SELECT SCOPE_IDENTITY()";

		if (SQL_SUCCESS != m_oDb.ExecuteQuery(strExecutableQuery))
		{
			m_oDb.CloseConnection();
			return false;
		}
		else
		{
			while (SQL_SUCCESS == SQLFetch(m_oDb.m_SqlStmtHandle))
			{
				int* pNextIdPtr = &nScopeId;

				if (SQL_SUCCESS != SQLGetData(m_oDb.m_SqlStmtHandle, 1, SQL_INTEGER, pNextIdPtr, sizeof(nScopeId), NULL))
				{
					return false;
				}
			}
		}
		return nScopeId;
	}
};
