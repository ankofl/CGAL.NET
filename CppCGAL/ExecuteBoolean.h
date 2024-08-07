#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include "MyTimer.h"
#include <fstream>

typedef std::chrono::steady_clock::time_point TimePoint;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

enum BooleanType {
    Union,
    Inter,
    Dif
};

bool ExecuteBoolean(Mesh& mesh1, Mesh& mesh2, BooleanType type, Mesh& out)
{
    int code = 0;
    auto ts = start("");

    if (type == BooleanType::Union) {
        if (!PMP::corefine_and_compute_union(mesh1, mesh2, out)){
            code = 1;
        }
    }
    else if (type == BooleanType::Inter) {
        if (!PMP::corefine_and_compute_intersection(mesh1, mesh2, out)){
            code = 2;
        }
    }    
    else if (type == BooleanType::Dif) {
        if (!PMP::corefine_and_compute_difference(mesh1, mesh2, out)){
            code = 3;
        }
    }  
    else {
        code = 4;
    }
    std::cout << "boolean[" << code << ']';
    msg("", ts);
    return code == 0;
}