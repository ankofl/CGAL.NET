#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

int SaveMesh(const char* path, Mesh& input, bool logExept = false) {
    auto ts = Start("save");

    try {
        CGAL::IO::write_polygon_mesh(path, input, CGAL::parameters::stream_precision(17));
    }
    catch (const std::exception& e) {
        std::cout << "SaveMesh: exception!" << std::endl;
        if (logExept) {
            std::cerr << e.what();
        }
        return 1;
    }    

    Msg("", ts);

    return 0;
}
