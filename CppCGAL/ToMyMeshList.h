#pragma once
#include "MyMeshList.h"
#include <vector>
#include "MyMesh.h"

int ToMyMeshList(std::vector<MyMesh>& meshes, MyMeshList& output) {

    int n = meshes.size();

    output.datasLength = n * 2;
	output.datas = new int[output.datasLength];

	for (int i = 0; i < n; i++) {
		MyMesh myMesh = meshes[i];

        output.datas[i * 2] = myMesh.floatsLength;
		output.datas[i * 2 + 1] = myMesh.indexesLength;

		output.doublesLength += myMesh.floatsLength;
		output.intsLength += myMesh.indexesLength;
	}
    output.doubles = new double[output.doublesLength];
    output.ints = new int[output.intsLength];

    int curD = 0;
    int curI = 0;
    for (int k = 0; k < n; k++) {
        MyMesh mesh = meshes[k];

        for (int d = 0; d < mesh.floatsLength; d++, curD++)
        {
            double dp = mesh.floats[d];
            output.doubles[curD] = dp;
        }
        for (int i = 0; i < mesh.indexesLength; i++, curI++)
        {
            output.ints[curI] = mesh.indexes[i];
        }
    }

    return 0;
}
