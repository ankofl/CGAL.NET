#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>

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

int ExecuteBoolean(Mesh& mesh1, Mesh& mesh2, BooleanType type, Mesh& out)
{
    TimePoint start_time = std::chrono::high_resolution_clock::now();

    if (type == BooleanType::Union) {
        if (!PMP::corefine_and_compute_union(mesh1, mesh2, out)){
            throw;
        }
    }
    else if (type == BooleanType::Inter) {
        if (!PMP::corefine_and_compute_intersection(mesh1, mesh2, out)){
            throw;
        }
    }    
    else if (type == BooleanType::Dif) {
        if (!PMP::corefine_and_compute_difference(mesh1, mesh2, out)){
            throw;
        }
    }  
    else {
        throw;
    }

    long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start_time).count();

    std::cout << "DeltaTime: " << duration << " milliseconds\n";
    return 1;
}