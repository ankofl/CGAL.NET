#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Polygon_mesh_processing/connected_components.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <vector>
#include <fstream>

#include "MyTimer.h"

// Определение типов данных
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

// Главная функция
int SplitMesh(Mesh& mesh, std::vector<Mesh>& components) {
    PMP::split_connected_components(mesh, components);
    return components.size();
}