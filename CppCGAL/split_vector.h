#pragma once

#include <vector>
#include <algorithm> // для std::min

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

std::vector<std::vector<Mesh>> split_vector(const std::vector<Mesh>& source, size_t chunkSize) {
    std::vector<std::vector<Mesh>> chunks;
    for (size_t i = 0; i < source.size(); i += chunkSize) {
        size_t end = std::min(i + chunkSize, source.size());
        chunks.push_back(std::vector<Mesh>(source.begin() + i, source.begin() + end));
    }
    return chunks;
}
