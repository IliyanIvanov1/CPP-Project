#include "stdafx.h"
#include "Functions.h"

CStringA IntegerToCString(int n)
{
	CStringA strFormatedString;
	strFormatedString.Format("%d", n);
	return strFormatedString;
}

CStringA HashFunction(const CStringA password)
{
	CStringA strHashedPassword;
	unsigned int h = FIRST_HASH;
	for (int i = 0; i < password.GetLength(); i++)
	{
		h = (h*A) ^ (password[i] * B);
	}
	strHashedPassword.Format("%d", h);
	return strHashedPassword;
}

const char * const BoolToString(BOOL b)
{
	return b ? "1" : "0";
}