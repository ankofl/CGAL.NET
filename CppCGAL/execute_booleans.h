#pragma once

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>

#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include "boolean_simple.h"
#include "fix_mesh.h"
#include "create_convex.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

bool execute_booleans(Mesh& first, std::vector<Mesh>& constrs, b_t type, Mesh& out, bool write_error = false){
	if (constrs.size() < 1) {
		return false;
	}	

	std::vector<Mesh> intersected;
	for (Mesh mesh : constrs) {
		if (PMP::do_intersect(first, mesh)) {
			intersected.push_back(mesh);
		}
	}
	if (intersected.size() == 0) {
		return false;
	}
	out = first;

	const std::string dir_build = "C:\\dev\\data\\objects\\building\\";	
	auto size = intersected.size();
	for (size_t i = 0; i < size; i++) {
		Mesh cur_inter = intersected[i];
		std::cout << i + 1 << '/' << size;
		Mesh local_out;
		if (boolean_simple(out, cur_inter, type, local_out)) {
			out = local_out;
		}
		else {
			Mesh convex;
			if (create_convex(cur_inter, convex)) {
				std::cout << "convex ";
				Mesh local_2;
				if (boolean_simple(out, convex, type, local_2)) {
					std::cout << "convexed\n";
					out = local_2;
				}
				else if(write_error){
					save_mesh(std::format("{}{}-1.off", dir_build, i + 1), out);
					save_mesh(std::format("{}{}-2.off", dir_build, i + 1), convex);
				}
			}			
		}	
	}
	std::cout << "ended\n";
	return true;
}