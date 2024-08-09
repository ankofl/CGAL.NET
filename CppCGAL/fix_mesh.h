#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include <CGAL/Polygon_mesh_processing/stitch_borders.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include <CGAL/Polygon_mesh_processing/self_intersections.h>

#include <CGAL/Polygon_mesh_processing/repair_self_intersections.h>
#include <CGAL/Polygon_mesh_processing/stitch_borders.h>
#include <CGAL/Polygon_mesh_processing/merge_border_vertices.h>
#include <CGAL/Polygon_mesh_processing/manifoldness.h>
#include <vector>
#include <iostream>
#include <CGAL/Polygon_mesh_processing/repair.h>
#include <CGAL/Polygon_mesh_processing/polygon_mesh_to_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>

#include <CGAL/Polygon_mesh_processing/remesh_planar_patches.h>
#include "my_timer.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

bool fix_mesh(Mesh& mesh) {
    Mesh remeshed;
    PMP::remesh_planar_patches(mesh, remeshed);
    mesh = remeshed;

    std::vector<std::array<FT, 3> > points;
    std::vector<std::vector<int>> polygons;
    PMP::polygon_mesh_to_polygon_soup(mesh, points, polygons);
    PMP::repair_polygon_soup(points, polygons, CGAL::parameters::geom_traits(Array_traits()));
    if (!PMP::is_polygon_soup_a_polygon_mesh(polygons)) {
        return false;
    }
    mesh.clear();
    PMP::polygon_soup_to_polygon_mesh(points, polygons, mesh);

    PMP::stitch_borders(mesh);
    PMP::duplicate_non_manifold_vertices(mesh);
    PMP::merge_duplicated_vertices_in_boundary_cycles(mesh);
    PMP::remove_connected_components_of_negligible_size(mesh);
    PMP::remove_isolated_vertices(mesh);
    PMP::remove_degenerate_faces(mesh);
    PMP::remove_degenerate_edges(mesh);
    if (PMP::does_self_intersect(mesh)) {
        if (!PMP::experimental::remove_self_intersections(mesh)) {
            return false;
        }
    }    
    if (!PMP::is_outward_oriented(mesh)) {
        PMP::orient(mesh);        
    }

    PMP::experimental::autorefine(mesh);
    return CGAL::is_valid_polygon_mesh(mesh);
}
