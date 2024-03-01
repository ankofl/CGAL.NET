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
    // Пытаемся открыть файл
    //std::ifstream input("C:/demo/ANKOBIM/Data/anchor_dense.off"); 
    std::ifstream input("C:/demo/CGAL-5.6/data/meshes/bunny00.off");

    if (!input) {
        std::cerr << "null" << std::endl;
    }

    Mesh mesh1, mesh2;
    if (!input || !(input >> mesh1))
    {
        std::cerr << "First mesh is not a valid off file." << std::endl;
        return 1;
    }
    input.close();
    input.open("C:/demo/CGAL-5.6/data/meshes/refined_elephant.off");
    //input.open("C:/demo/CGAL-5.6/data/meshes/diplodocus.off");

    if (!input || !(input >> mesh2))
    {
        std::cerr << "Second mesh is not a valid off file." << std::endl;
        return 1;
    }
    input.close();
    auto end_time = std::chrono::high_resolution_clock::now();
    std::cout << "End\n";
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    // Выводим разницу времени (в миллисекундах)
    std::cout << "DeltaTime: " << duration << " milliseconds\n";

    Mesh out;

    start_time = std::chrono::high_resolution_clock::now();
    std::cout << "Start\n";
    if (PMP::corefine_and_compute_union(mesh1, mesh2, out))
    {
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "End\n";
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        // Выводим разницу времени (в миллисекундах)
        std::cout << "DeltaTime: " << duration << " milliseconds\n";


        start_time = std::chrono::high_resolution_clock::now();
        std::ofstream output("union.off");
        output << out;
        end_time = std::chrono::high_resolution_clock::now();
        std::cout << "End\n";
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        // Выводим разницу времени (в миллисекундах)
        std::cout << "DeltaTime: " << duration << " milliseconds\n";
        return 0;
    }
    std::cout << "Union could not be computed\n";
    return 1;
}