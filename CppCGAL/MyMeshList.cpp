// MyMeshList.cpp
#include "MyMeshList.h"
#include "MyMesh.h"
#include <vector>

extern "C" {
    __declspec(dllexport) void ClearExtern(MyMeshList input) {
        delete[] input.doubles;
        input.doubles = nullptr;

        delete[] input.ints;
        input.ints = nullptr;

        delete[] input.datas;
        input.datas = nullptr;
    }
}
