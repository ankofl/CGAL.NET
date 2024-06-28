#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>

#include <fstream>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

int Boolean()
{    
    auto start_time = std::chrono::high_resolution_clock::now();

    std::ifstream input("C:/dev/CGAL.NET/data/meshes/bunny00.off");

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
    input.open("C:/dev/CGAL.NET/data/meshes/refined_elephant.off");


    if (!input || !(input >> mesh2))
    {
        std::cerr << "Second mesh is not a valid off file." << std::endl;
        return 1;
    }
    input.close();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "DeltaTime: " << duration << " milliseconds\n";

    Mesh out;
    start_time = std::chrono::high_resolution_clock::now();
    if (PMP::corefine_and_compute_union(mesh1, mesh2, out))
    {
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "union: " << duration << "\n";

        std::ofstream output("union.off");
        output << out;
        out = Mesh();
    }

    start_time = std::chrono::high_resolution_clock::now();
    if (PMP::corefine_and_compute_intersection(mesh1, mesh2, out))
    {
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "inter: " << duration << "\n";

        std::ofstream output("intersection.off");
        output << out;
        out = Mesh();
    }

    start_time = std::chrono::high_resolution_clock::now();
    if (PMP::corefine_and_compute_difference(mesh1, mesh2, out))
    {
        end_time = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "dif: " << duration << "\n";

        std::ofstream output("difference.off");
        output << out;
        out = Mesh();
    }

    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "DeltaTime: " << duration << " milliseconds\n";
    return 1;
}