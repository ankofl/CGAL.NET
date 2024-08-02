#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/repair_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/orient_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <array>
#include <vector>
#include "Array_traits.h"
#include <CGAL/Polyhedron_items_with_id_3.h>
//#include "Remesher.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;

typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

typedef CGAL::Surface_mesh<K::Point_3>                        SurfaceMesh;

namespace PMP = CGAL::Polygon_mesh_processing;

int SurfaceToMesh(SurfaceMesh& surface, Mesh& output)
{
    

    PMP::polygon_soup_to_polygon_mesh(points, polygons, output);

    return 0;
}