#pragma once

#include <iostream>
#include <filesystem>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include "fix_mesh.h"

#include "load_mesh.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

bool load_dir(std::string directory, std::vector<Mesh>& meshes, bool filter = false) {
	for (const auto& entry : std::filesystem::directory_iterator(directory)) {
		if (entry.is_regular_file() && entry.path().extension() == ".off") {
			if (filter) {
				if (entry.path().filename() != "10158482.off") {
					continue;
				}
			}

			std::string file_path = entry.path().string();
			Mesh loaded;
			if (load_mesh(file_path.c_str(), loaded)) {
				meshes.push_back(loaded);
			}
		}
	}
	return meshes.size() > 0;
}