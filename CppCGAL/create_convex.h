#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/convex_hull_3.h>
#include <vector>
#include <fstream>
#include "make_bbox.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;
typedef K::Point_3                                Point_3;

bool create_convex(Mesh& mesh, Mesh& convex )
{
    std::vector<Point_3> points;
    for (auto vi = mesh.vertices_begin(); vi != mesh.vertices_end(); ++vi) {
        points.push_back(vi->point());
    }
    CGAL::convex_hull_3(points.begin(), points.end(), convex);
    if (fix_mesh(convex)) {
        Mesh bbox;
        if (make_bbox(convex, bbox)) {
            convex = bbox;
            return true;
        }
    }    
    return false;
}