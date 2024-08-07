#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include <CGAL/Polygon_mesh_processing/stitch_borders.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include <CGAL/Polygon_mesh_processing/self_intersections.h>

#include <CGAL/Polygon_mesh_processing/repair_self_intersections.h>

#include <vector>
#include <iostream>

#include "MyTimer.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

bool FixMesh(Mesh& mesh, bool time = false) {
    auto ts = start("");
    PMP::stitch_borders(mesh);    
    if (time) msg("s_b", ts);
    PMP::remove_degenerate_faces(mesh);
    if (time) msg("r_d_f", ts);
    PMP::remove_degenerate_edges(mesh);
    if (time) msg("r_d_e", ts);
    if (PMP::does_self_intersect(mesh)) {
        if (!PMP::experimental::remove_self_intersections(mesh)) {
            return false;
        }
        if (time) msg("r_s_i", ts);
        PMP::experimental::autorefine(mesh);
        if (time) msg("ar", ts);
    }    
    if (!PMP::is_outward_oriented(mesh)) {
        PMP::orient(mesh);        
    }
    if (time) msg("done", ts);
    return true;
}
