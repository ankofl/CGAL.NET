#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include "my_timer.h"
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

bool save_mesh(const std::string path, Mesh& input) {
    auto ts = start("saves... ");
    if (!CGAL::is_valid_polygon_mesh(input)) {
        return false;
    }

    try {
        if (CGAL::IO::write_polygon_mesh(path, input, CGAL::parameters::stream_precision(17))) {
            msg("saved", ts, true);
            return true;
        }
        else {
            msg("not_saved", ts, true);
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cout << "save_mesh: exception!" << std::endl;
    }    
    return false;
}
