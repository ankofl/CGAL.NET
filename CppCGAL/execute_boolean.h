#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include "my_timer.h"

typedef std::chrono::steady_clock::time_point TimePoint;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

enum b_t {
    uni,
    inter,
    dif
};

bool execute_boolean(Mesh& mesh1, Mesh& mesh2, b_t type, Mesh& out)
{
    std::cout << "started... ";
    int code = 0;
    if (type == b_t::uni) {
        if (!PMP::corefine_and_compute_union(mesh1, mesh2, out)){
            code = 1;
        }
    }
    else if (type == b_t::inter) {
        if (!PMP::corefine_and_compute_intersection(mesh1, mesh2, out)){
            code = 2;
        }
    }    
    else if (type == b_t::dif) {
        if (!PMP::corefine_and_compute_difference(mesh1, mesh2, out)){
            code = 3;
        }
    }  
    else {
        throw;
    }

    if (code != 0) {
        std::cout << "not_bool\n";
        return false;
    }
    else if(!fix_mesh(out)) {
        std::cout << "not_fix\n";
        return false;
    }
    std::cout << "succes\n";
    return true;
}