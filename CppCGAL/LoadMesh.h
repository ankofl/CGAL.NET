#pragma once
#include <fstream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;

typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

int LoadMesh(const char* path, Mesh& output) {

    std::ifstream input;
    input.open(path);
    if (!input || !(input >> output))
    {
        std::cerr << "Second mesh is not a valid off file." << std::endl;
        return 1;
    }
    input.close();
    return 0;
}