#include "Exit.h"
#include "Method.h"
#include "Boolean.h"

extern "C" __declspec(dllexport) void CallMethod()
{
    //Exit();

    //Method();

    for (int i = 0; i < 25; i++) {
        std::cout << "\n\n\n";
        Boolean();
        std::cout << "\n\n\n";
    }

    

    //Exit();
}