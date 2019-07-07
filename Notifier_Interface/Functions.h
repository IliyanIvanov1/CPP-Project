#pragma once
#include "afx.h"
#define A 54059
#define B 76963
#define C 86969
#define FIRST_HASH 37

CStringA IntegerToCString(int n);

CStringA HashFunction(CStringA password);

const char * const BoolToString(BOOL b);
