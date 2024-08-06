#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <vector>
#include <map>
#include "MyMesh.h"
#include <CGAL/property_map.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include <CGAL/Polygon_mesh_processing/repair.h>
#include "FixMesh.h"
#include "MyTimer.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

int ConvertToMyMesh(Mesh& input, MyMesh& output) {

    int code = FixMesh(input);
    if (code != 0) {
        return code;
    }
    if (!CGAL::is_valid(input)) {
        return 1;
    }

    std::map<K::Point_3, int> pointIndexMap;
    int vertex_id = 0;

    for (auto vi = input.vertices_begin(); vi != input.vertices_end(); ++vi) {
        pointIndexMap[vi->point()] = vertex_id++;
    }

    int num_vertices = pointIndexMap.size();

    output.indexes = new int[input.size_of_facets() * 3];
    output.indexesLength = input.size_of_facets() * 3;

    output.floats = new double[num_vertices * 3];
    output.floatsLength = num_vertices * 3;

    // Fill vertex coordinates
    for (const auto& pair : pointIndexMap) {
        K::Point_3 point = pair.first;
        int index = pair.second;

        output.floats[index * 3] = point.x();
        output.floats[index * 3 + 1] = point.y();
        output.floats[index * 3 + 2] = point.z();
    }

    // Fill indices for polygons
    int index = 0;
    for (auto fi = input.facets_begin(); fi != input.facets_end(); ++fi) {
        auto hc = fi->facet_begin();
        // HC is the halfedge iterator around the facet
        do {
            K::Point_3 point = hc->vertex()->point();
            output.indexes[index++] = pointIndexMap[point];
        } while (++hc != fi->facet_begin());
    }

    return 0;    
}
