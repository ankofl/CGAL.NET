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
#include "MyMesh.h"
#include <CGAL/Polyhedron_items_with_id_3.h>
#include "FixMesh.h"

#include "MyTimer.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;
namespace PMP = CGAL::Polygon_mesh_processing;

int ConvertToMesh(MyMesh& myMesh, Mesh& output)
{
    std::vector<std::array<FT, 3> > points;

    for (int i = 0; i < myMesh.floatsLength; i+=3){
        points.push_back(CGAL::make_array<FT>(
            myMesh.floats[i],
            myMesh.floats[i+1],
            myMesh.floats[i+2])); // 0
    }

    std::vector<std::vector<int>> polygons;
    for (int i = 0; i < myMesh.indexesLength; i+=3){
        polygons.push_back({ 
            myMesh.indexes[i],
            myMesh.indexes[i+1],
            myMesh.indexes[i+2]});
    }
    
    auto ts = start("");
    PMP::polygon_soup_to_polygon_mesh(points, polygons, output);
    msg("soup", ts);

    return FixMesh(output);
}