#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Polygon_mesh_processing/connected_components.h>
#include <CGAL/IO/Polyhedron_iostream.h>
#include <vector>
#include <fstream>

// ����������� ����� ������
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

// ������� �������
int SplitMesh(Mesh& mesh, std::vector<Mesh>& components) {

    // ���������� ����� �� ���������� ���������
    CGAL::Polygon_mesh_processing::split_connected_components(mesh, components);

    return components.size();
}