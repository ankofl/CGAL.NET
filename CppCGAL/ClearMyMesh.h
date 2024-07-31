#pragma once
#include "MyMesh.h"

void ClearMyMesh(MyMesh& input) {
    delete[] input.floats;
    input.floats = nullptr;

    delete[] input.indexes;
    input.indexes = nullptr;
}