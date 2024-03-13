#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>

#include "MyOff.h"

#include <fstream>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

int Boolean()
{    
    std::ifstream input("C:/demo/CGAL.NET/Data/meshes/bunny00.off");

    if (!input) {
        std::cerr << "null" << std::endl;
    }

    Mesh mesh1, mesh2;
    if (!input || !(input >> mesh1))
    {
        std::cerr << "First mesh is not a valid off file." << '\n';
        return 1;
    }
    input.close();
    input.open("C:/demo/CGAL.NET/Data/meshes/refined_elephant.off");
    //input.open("C:/demo/CGAL.NET/Data/meshes/diplodocus.off");

    if (!input || !(input >> mesh2))
    {

        std::cerr << "Second mesh is not a valid off file." << std::endl;
        return 1;
    }
    input.close();

    Mesh out;
    auto start_time = std::chrono::high_resolution_clock::now();
    if (PMP::corefine_and_compute_union(mesh1, mesh2, out))
    {
        std::ofstream output("union.off");
        output << out;
        out = Mesh();
    }
    if (PMP::corefine_and_compute_intersection(mesh1, mesh2, out))
    {
        std::ofstream output("intersection.off");
        output << out;
        out = Mesh();
    }
    if (PMP::corefine_and_compute_difference(mesh1, mesh2, out))
    {
        std::ofstream output("difference.off");
        output << out;
        out = Mesh();
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "DeltaTime: " << duration << " milliseconds\n";
    return 1;
}