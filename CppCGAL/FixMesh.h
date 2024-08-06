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

int FixMesh(Mesh& mesh, bool logExept = false) {

    auto ts = Start("");

    // Сшивание граничных рёбер
    //int pre = mesh.facet_handles().size();
    PMP::stitch_borders(mesh);
    //ts = Msg("s_b", ts);

    // Исправление самопересечений
    std::vector<std::pair<Mesh::Facet_const_handle, Mesh::Facet_const_handle>> self_intersections;    

    if (PMP::does_self_intersect(mesh)) {
        if (PMP::experimental::remove_self_intersections(mesh)) {//, CGAL::parameters::preserve_genus(false))) {
            ts = Msg("rsi", ts);
        }
        else {
            std::cout << "rsi:- " << std::endl;
            return 1;
        }
    }    

    if (PMP::remove_degenerate_faces(mesh)) {
        //ts = Msg("d_f", ts);
    }
    else {
        std::cout << "d_f:- " << std::endl;
        return 1;
    }

    if (PMP::remove_degenerate_edges(mesh)) {
        //ts = Msg("d_e", ts);
    }
    else {
        std::cout << "d_e:- " << std::endl;
        return 1;
    }

    /*try {

        PMP::experimental::autorefine(mesh, CGAL::parameters::preserve_genus(false));
        std::cout << "ar:+ ";
    }
    catch (const std::exception& e) {
        std::cout << "ar:- " << std::endl;
        if (logExept) {
            std::cerr << e.what();
        }
        return 1;
    } */ 

    // Исправление ориентации
    if (!PMP::is_outward_oriented(mesh)) {
        std::cerr << "or:";
        PMP::orient(mesh);
        std::cerr << "+ ";
    }

    // Проверка корректности после обработки
    if (!CGAL::is_valid(mesh)) {
        std::cerr << "Mesh is not valid after processing." << std::endl;
    }

    //int after = mesh.facet_handles().size();
    //if (after != pre) {
    //    std::cout << "defs [" << after - pre << ']';
    //}
    

    return 0;
}
