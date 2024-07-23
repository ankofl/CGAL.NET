#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polygon_mesh_processing/repair_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/orient_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include "Array_traits.h"
#include "MyMesh.h"

#include <CGAL/Polyhedron_items_with_id_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;

typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

typedef std::vector<int>                                CGAL_Polygon;

namespace PMP = CGAL::Polygon_mesh_processing;

int ConvertToMesh(MyMesh& myMesh, Mesh& output)
{
    bool visual = false;

    // First, construct a polygon soup with some problems
    std::vector<std::array<FT, 3> > points;

    for (int i = 0; i < myMesh.floatsLength; i+=3){
        points.push_back(CGAL::make_array<FT>(
            myMesh.floatsPtr[i],
            myMesh.floatsPtr[i+1],
            myMesh.floatsPtr[i+2])); // 0
    }

    std::vector<CGAL_Polygon> polygons;
    for (int i = 0; i < myMesh.indexesLength; i+=3){
        polygons.push_back({ 
            myMesh.indexesPtr[i],
            myMesh.indexesPtr[i+1],
            myMesh.indexesPtr[i+2]});
    }

    if (visual) {
        std::cout << "Before repairing, the soup has " << points.size() << " vertices and " << polygons.size() << " faces" << std::endl;
    }
    PMP::repair_polygon_soup(points, polygons, CGAL::parameters::geom_traits(Array_traits()));
    if (visual) {
        std::cout << "After repairing, the soup has " << points.size() << " vertices and " << polygons.size() << " faces" << std::endl;
    }

    PMP::orient_polygon_soup(points, polygons);
    PMP::polygon_soup_to_polygon_mesh(points, polygons, output);
    if (visual) {
        std::cout << "Mesh has " << num_vertices(output) << " vertices and " << num_faces(output) << " faces" << std::endl;
    }

    return 0;
}