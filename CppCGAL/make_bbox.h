#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Optimal_bounding_box/oriented_bounding_box.h>
#include <CGAL/aff_transformation_tags.h>
#include <array>

typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;
typedef K::Point_3                                Point_3;
typedef K::Vector_3                               Vector_3;

bool make_bbox(Mesh& mesh, Mesh& obb_sm, double margin = 0.01) {
    std::array<Point_3, 8> obb_points;
    CGAL::oriented_bounding_box(mesh, obb_points, CGAL::parameters::use_convex_hull(true));

    // Вычисляем центр OBB
    Point_3 center = CGAL::centroid(obb_points.begin(), obb_points.end());

    // Перемещаем точки OBB на 0.01 от центра
    for (auto& point : obb_points) {
        Vector_3 direction = point - center;            // Вектор от центра до точки
        point = point + margin * direction / sqrt(direction.squared_length()); // Смещаем точку
    }

    // Создаем новый OBB на основе смещенных точек
    CGAL::make_hexahedron(obb_points[0], obb_points[1], obb_points[2], obb_points[3],
        obb_points[4], obb_points[5], obb_points[6], obb_points[7], obb_sm);

    return fix_mesh(obb_sm);
}
