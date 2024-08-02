#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Polygon_mesh_processing/remesh.h>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

int RemeshMesh(Mesh& mesh, const double target_edge_length, const int number_of_iterations) {
    // Ремешинг для улучшения качества
    try {
        PMP::isotropic_remeshing(faces(mesh), target_edge_length, mesh,
            CGAL::parameters::
            number_of_iterations(number_of_iterations)
            .protect_constraints(true)
            .collapse_constraints(false));
    }
    catch (const std::exception& e) {
        std::cerr << "Error during remeshing: " << e.what() << std::endl;
    }

    return 0;
}
