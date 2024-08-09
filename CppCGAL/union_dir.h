#include <iostream>
#include <filesystem>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include "fix_mesh.h"

#include "load_mesh.h"
#include "split_vector.h"
#include "load_dir.h"
#include "clear_dir.h"
#include "boolean_simple.h"
#include "execute_booleans.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

bool union_dir(std::vector<std::string> dirs, size_t chunk_size) {
	const std::string dir_build = "C:\\dev\\data\\objects\\building\\";
	const std::string dir_split = dir_build +  "splitted\\";

	bool overwrite = false;

	std::vector<Mesh> splitted_list;
	if (overwrite) {
		clear_dir(dir_split);

		std::vector<Mesh> constrs;
		for (std::string dir : dirs) {
			if ((int)dir.find("Doors") != -1) {
				load_dir(dir, constrs, true);
			}
			else {
				load_dir(dir, constrs);
			}
		}

		std::vector<Mesh> masses;
		load_dir("C:\\dev\\data\\objects\\Mass\\", masses);

		size_t size = masses.size();
		for (size_t i = 0; i < size; i++) {
			std::cout << i + 1 << '/' << size << '\n';
			Mesh dif;
			if (execute_booleans(masses[i], constrs, b_t::dif, dif)) {
				std::vector<Mesh> splitted;
				if (split_mesh(dif, splitted) > 0) {
					for (size_t s = 0; s < splitted.size(); s++) {
						save_mesh(std::format("{}splitted\\{}-{}.off", dir_build, i, s), splitted[s]);
					}
				}
				else {
					std::cout << "failed_split " << i + 1 << '\n';
				}
			}
			else {
				std::cout << "failed_booleans " << i + 1 << '\n';
			}
		}
	}
	else {
		load_dir(std::format("{}splitted\\", dir_build), splitted_list);
	}

	size_t s_size = splitted_list.size();
	if (s_size > 1) {
		Mesh united = splitted_list[0];
		for (size_t i = 1; i < s_size; i++)
		{
			Mesh result;
			if (boolean_simple(united, splitted_list[i], b_t::united, result)) {
				united = result;
			}
			else if() {

			}
		}
		save_mesh(std::format("{}united.off", dir_build), united);
	}
	

	std::cout << "finished " << '\n';
	return true;
}
