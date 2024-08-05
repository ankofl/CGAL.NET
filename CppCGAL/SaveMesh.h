#pragma once
#include <fstream>
#include <iomanip> // Для использования std::setprecision
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

int SaveMesh(const char* path, Mesh& input) {
    std::ofstream output(path);

    if (!output.is_open()) {
        std::cerr << "Failed to open file for writing: " << path << std::endl;
        return 1;
    }

    // Устанавливаем точность
    output << std::fixed << std::setprecision(16);

    // Сохраняем mesh
    output << "OFF\n";
    output << input.size_of_vertices() << " " << input.size_of_facets() << " 0\n";

    // Сохраняем вершины
    for (auto v = input.vertices_begin(); v != input.vertices_end(); ++v) {
        const auto& point = v->point();
        output << point.x() << " " << point.y() << " " << point.z() << "\n";
    }

    // Сохраняем грани
    for (auto f = input.facets_begin(); f != input.facets_end(); ++f) {
        auto h = f->facet_begin();
        CGAL_assertion(CGAL::circulator_size(h) >= 3);
        output << CGAL::circulator_size(h);
        do {
            output << " " << std::distance(input.vertices_begin(), h->vertex());
        } while (++h != f->facet_begin());
        output << "\n";
    }

    output.close();
    return 0;
}
