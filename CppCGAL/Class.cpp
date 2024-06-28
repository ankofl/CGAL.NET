#include "Exit.h"
#include "Method.h"
#include "Boolean.h"
#include <iostream>

extern "C" __declspec(dllexport) void CallMethod()
{
    Boolean();
}