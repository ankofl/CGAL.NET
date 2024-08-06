#pragma once
#include <fstream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include "FixMesh.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;

typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

int LoadMesh(const char* path, Mesh& output) {

    std::ifstream input;
    input.open(path);
    if (!input)
    {
        return 1;
    }
    else if (!(input >> output)) {
        return 2;
    }

    input.close();

    size_t code = FixMesh(output);

    return code;
}