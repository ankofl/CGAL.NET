#pragma once
#include "MyMeshList.h"
#include <vector>
#include "MyMesh.h"

int ConvertMyMeshListToVectorMyMesh(MyMeshList& one, std::vector<MyMesh>& listMyMesh) {
    int curD = 0;
    int curI = 0;
    for (int i = 0; i < one.datasLength; i += 2) {
        int curDcount = one.datas[i];
        int curIcount = one.datas[i + 1];

        MyMesh myMesh;

        myMesh.floats = new double[curDcount];
        myMesh.floatsLength = curDcount;
        for (int c = 0; c < curDcount; c++)
        {
            myMesh.floats[c] = one.doubles[c + curD];
        }
        myMesh.indexes = new int[curIcount];
        myMesh.indexesLength = curIcount;
        for (int c = 0; c < curI; c++)
        {
            myMesh.indexes[c] = one.ints[c + curI];
        }
        curD += curDcount;
        curI += curIcount;


        listMyMesh.push_back(myMesh);
    }

    return 0;
}