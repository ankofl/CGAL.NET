#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include "execute_boolean.h"
#include "fix_mesh.h"

typedef std::chrono::steady_clock::time_point TimePoint;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

bool execute_booleans(Mesh first, std::vector<Mesh>& constrs, b_t type, Mesh& out){
	if (constrs.size() < 1) {
		return false;
	}	

	const std::string dir_build = "C:\\dev\\data\\objects\\building\\";

	auto size = constrs.size();
	for (size_t i = 0; i < size; i++){		
		auto constr = constrs[i];
		if (PMP::do_intersect(first, constr)) {
			//std::cout << i + 1 << '/' << size;
			Mesh local_out;
			if (execute_boolean(first, constr, type, local_out)) {
				first = local_out;
			}		
			//save_mesh(std::format("{}{}-constr.off", dir_build, i), constr);
		}		
		else {
			//std::cout << " not_inter\n";
		}
	}
	std::cout << "ended\n";
	out = first;
	return fix_mesh(out);
}