#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/repair.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/boost/graph/iterator.h>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
namespace PMP = CGAL::Polygon_mesh_processing;
namespace params = CGAL::parameters;
typedef CGAL::Exact_predicates_inexact_constructions_kernel          K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

int Manifold(Mesh& mesh1, Mesh& mesh2)
{
    Mesh out_union, out_intersection;
    std::array<boost::optional<Mesh*>, 4> output;
    output[PMP::Corefinement::UNION] = &out_union;
    output[PMP::Corefinement::INTERSECTION] = &out_intersection;
    // for the example, we explicit the named parameters, this is identical to
    // PMP::corefine_and_compute_boolean_operations(mesh1, mesh2, output)
    std::array<bool, 4> res =
        PMP::corefine_and_compute_boolean_operations(
            mesh1, mesh2,
            output,
            params::default_values(), // mesh1 named parameters
            params::default_values(), // mesh2 named parameters
            std::make_tuple(
                params::vertex_point_map(get(boost::vertex_point, out_union)), // named parameters for out_union
                params::vertex_point_map(get(boost::vertex_point, out_intersection)), // named parameters for out_intersection
                params::default_values(), // named parameters for mesh1-mesh2 not used
                params::default_values())// named parameters for mesh2-mesh1 not used)
        );
    if (res[PMP::Corefinement::UNION])
    {
        std::cout << "Union was successfully computed\n";
        CGAL::IO::write_polygon_mesh("union.off", out_union, CGAL::parameters::stream_precision(17));
    }
    else
        std::cout << "Union could not be computed\n";
    if (res[PMP::Corefinement::INTERSECTION])
    {
        std::cout << "Intersection was successfully computed\n";
        CGAL::IO::write_polygon_mesh("intersection.off", out_intersection, CGAL::parameters::stream_precision(17));
    }
    else
        std::cout << "Intersection could not be computed\n";

    return 1;
}
