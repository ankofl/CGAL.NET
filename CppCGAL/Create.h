#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/repair_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/orient_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include "SoupStruct.h"
#include "Array_traits.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef K::FT                                                   FT;
typedef K::Point_3                                              Point_3;
typedef CGAL::Surface_mesh<Point_3>                             Mesh;
typedef std::array<FT, 3>                                       Custom_point;
typedef std::vector<std::size_t>                                CGAL_Polygon;
namespace PMP = CGAL::Polygon_mesh_processing;

bool Create(SoupStruct soup)
{
    bool visual = false;

    // First, construct a polygon soup with some problems
    std::vector<std::array<FT, 3> > points;
    points.push_back(CGAL::make_array<FT>(0.3, 0.3, 0.5)); // 0
    points.push_back(CGAL::make_array<FT>(1, 0, 0)); // 1
    points.push_back(CGAL::make_array<FT>(0, 1, 0)); // 2
    points.push_back(CGAL::make_array<FT>(-1, 0, 0)); // 3
    points.push_back(CGAL::make_array<FT>(0, -1, 0)); // 4
    points.push_back(CGAL::make_array<FT>(0, 1, 0)); // 5 -- duplicate point with 2
    points.push_back(CGAL::make_array<FT>(0, -2, 0)); // 6 -- unused point

    std::vector<CGAL_Polygon> polygons;
    // normal face
    polygons.push_back({ 0,1,2 });
    // degenerate face
    polygons.push_back({ 0,0,0 });
    // duplicate faces with different orientations
    polygons.push_back({ 0,1,4 });
    polygons.push_back({ 0,4,1 });
    // normal face
    polygons.push_back({ 0,3,5 });
    // degenerate face
    polygons.push_back({ 0,3,0 });
    // normal face
    polygons.push_back({ 0,3,4 });
    // pinched and degenerate face
    polygons.push_back({ 0,1,2,3,4,3,2,1 });

    if (visual) {
        std::cout << "Before repairing, the soup has " << points.size() << " vertices and " << polygons.size() << " faces" << std::endl;
    }    
    PMP::repair_polygon_soup(points, polygons, CGAL::parameters::geom_traits(Array_traits()));
    if (visual) {
        std::cout << "After repairing, the soup has " << points.size() << " vertices and " << polygons.size() << " faces" << std::endl;
    }    
    Mesh mesh;
    PMP::orient_polygon_soup(points, polygons);
    PMP::polygon_soup_to_polygon_mesh(points, polygons, mesh);
    if (visual) {
        std::cout << "Mesh has " << num_vertices(mesh) << " vertices and " << num_faces(mesh) << " faces" << std::endl;
    }

    return true;
}