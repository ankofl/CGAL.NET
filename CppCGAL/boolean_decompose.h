#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include "my_timer.h"
#include "boolean_simple.h"
#include "mesh_decompose.h"
#include "fix_mesh.h"

typedef std::chrono::steady_clock::time_point TimePoint;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

bool boolean_decompose(Mesh& one, Mesh& two, b_t type, Mesh& out) {
	std::vector<Mesh> one_meshes;
	if (!mesh_decompose(one, one_meshes)) {
		return false;
	}

	std::vector<Mesh> two_meshes;
	if (!mesh_decompose(two, two_meshes)) {
		return false;
	}

	Mesh out_local = one_meshes[0];
	for (size_t i = 1; i < one_meshes.size(); i++)
	{
		Mesh one_part = one_meshes[i];
		for (Mesh two_part : two_meshes) {
			if (boolean_simple(one_part, two_part, type, out_local)) {
				out = out_local;
			}
		}
	}

	return fix_mesh(out);
}