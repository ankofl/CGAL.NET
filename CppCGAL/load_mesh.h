#pragma once
#include <fstream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include "FixMesh.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;

typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

bool load_mesh(const char* path, Mesh& output) {

    using namespace std;
    ifstream input;
    input.open(path);
    if (!input) {
        return false;
    }
    else if (!(input >> output)) {
        return false;
    }

    input.close();

    return FixMesh(output);
}