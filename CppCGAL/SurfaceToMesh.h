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
    std::vector<std::array<FT, 3> > points;
    for (auto v : surface.vertices()) {
        auto p = surface.point(v);
        points.push_back(CGAL::make_array<FT>(
            p.x(), p.y(), p.z()));
    }

    // Получение индексов вершин треугольников
    std::vector<std::array<std::size_t, 3>> polygons;
    for (auto f : surface.faces()) {
        auto hf = surface.halfedge(f);
        std::array<std::size_t, 3> triangle;
        for (int i = 0; i < 3; ++i) {
            triangle[i] = surface.target(hf).idx();
            hf = surface.next(hf);
        }
        polygons.push_back(triangle);
    }

    PMP::repair_polygon_soup(points, polygons, CGAL::parameters::geom_traits(Array_traits()));

    PMP::orient_polygon_soup(points, polygons);

    PMP::polygon_soup_to_polygon_mesh(points, polygons, output);

    return 0;
}