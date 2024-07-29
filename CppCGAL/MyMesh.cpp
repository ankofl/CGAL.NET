#include <iostream>
#include "MyMesh.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include "ConvertToMesh.h"
#include "ExecuteBoolean.h"
#include "LoadMesh.h"
#include "ConvertToMyMesh.h"
#include "SaveMesh.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

extern "C" {
    __declspec(dllexport) void ClearMyMeshExtern(MyMesh input) {
        delete[] input.floats;
        input.floats = nullptr;

        delete[] input.indexes;
        input.indexes = nullptr;
    }

    __declspec(dllexport) int SaveExtern(const char* path, MyMesh input) {
        Mesh mesh;
        ConvertToMesh(input, mesh);
        SaveMesh(path, mesh);
        return 0;
    }

    __declspec(dllexport) int LoadExtern(const char* path, MyMesh* output) {
        Mesh mesh;
        int gg = LoadMesh(path, mesh);
        if (gg == 0) {
            ConvertToMyMesh(mesh, output);
        }       
        return gg;
    }

    __declspec(dllexport) int BooleanExtern(MyMesh one, MyMesh two, BooleanType type, MyMesh* output) {

        Mesh oneMesh;
        ConvertToMesh(one, oneMesh);
        
        Mesh twoMesh;
        ConvertToMesh(two, twoMesh);

        Mesh out;
        ExecuteBoolean(oneMesh, twoMesh, type, out);

        ConvertToMyMesh(out, output);

        return 0;
    }
}