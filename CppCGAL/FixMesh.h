#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Polygon_mesh_processing/remesh.h>
#include <CGAL/Polygon_mesh_processing/repair.h>
#include <CGAL/Polygon_mesh_processing/stitch_borders.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include <CGAL/Polygon_mesh_processing/self_intersections.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <vector>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

int FixMesh(Mesh& mesh) {
    // Сшивание граничных рёбер
    PMP::stitch_borders(mesh);

    // Исправление самопересечений
    std::vector<std::pair<Mesh::Facet_const_handle, Mesh::Facet_const_handle>> self_intersections;
    PMP::self_intersections(mesh, std::back_inserter(self_intersections));
    if (!self_intersections.empty()) {
        std::cerr << "Mesh has self-intersections. Attempting to repair..." << std::endl;
        if (!CGAL::Polygon_mesh_processing::experimental::remove_self_intersections(mesh, CGAL::parameters::preserve_genus(false))) {            
            std::cerr << "Mesh remove_self_intersections false" << std::endl;
            return 1;
        }
    }

    // Исправление ориентации
    if (!PMP::is_outward_oriented(mesh)) {
        std::cerr << "Mesh is not outward oriented. Attempting to orient..." << std::endl;
        PMP::orient(mesh);
    }

    // Проверка корректности после обработки
    if (!CGAL::is_valid(mesh)) {
        std::cerr << "Mesh is not valid after processing." << std::endl;
    }

    return 0;
}
