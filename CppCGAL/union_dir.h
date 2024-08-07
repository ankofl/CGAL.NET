#include <iostream>
#include <filesystem>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include "FixMesh.h"

#include "load_mesh.h"
#include "split_vector.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

namespace PMP = CGAL::Polygon_mesh_processing;

bool union_dir(std::vector<std::string> dirs, size_t chunk_size) {
	namespace fs = std::filesystem;
	auto ts = start("");	
	auto ts_total = start("");
	std::vector<Mesh> meshes;
	for (std::string directory : dirs) {
		for (const auto& entry : fs::directory_iterator(directory)) {
			if (entry.is_regular_file() && entry.path().extension() == ".off") {
				std::string file_path = entry.path().string();
				Mesh mesh;
				if (load_mesh(file_path.c_str(), mesh)) {
					meshes.push_back(mesh);	
					
					msg(entry.path().filename().string(), ts, true);
				}
			}
		}	
	}

	std::vector<std::vector<Mesh>> chunks = split_vector(meshes, chunk_size);

	size_t cn_size = chunks.size();
	bool first_chunk = true;
	Mesh first;
	for (size_t cn = 0; cn < cn_size; cn++) {
		std::vector<Mesh> chunk = chunks[cn];
		auto size = chunk.size();
		if (size > 1) {
			Mesh current_boolean = chunk[0];
			for (size_t i = 1; i < size; i++) {
				std::cout << cn + 1 << '/' << cn_size << ' ' << i + 1 << '/' << size << ' ';
				Mesh other = chunk[i];
				if (FixMesh(other)) {
					Mesh out;
					if (PMP::corefine_and_compute_union(current_boolean, other, out)) {
						PMP::stitch_borders(out);
						PMP::remove_degenerate_faces(out);
						PMP::remove_degenerate_edges(out);
						if (CGAL::is_valid_polygon_mesh(out)) {
							current_boolean = out;
						}
					}
					msg("boolean", ts);
				}
				std::cout << current_boolean.points().size() << std::endl;
			}
			if (FixMesh(current_boolean, true)) {
				if (first_chunk) {
					first = current_boolean;
					first_chunk = false;
				}
				else {
					msg("start_check_first", ts);
					if (FixMesh(first)) {
						msg("end_check_first", ts);
						if (FixMesh(current_boolean)) {
							msg("end_check_current_boolean", ts);
							Mesh out_united;
							std::ostringstream oss;
							oss << "start:" << first.points().size() << '/' << current_boolean.points().size();
							msg(oss.str(), ts);
							if (PMP::corefine_and_compute_union(first, current_boolean, out_united)) {
								msg("succes_boolean_union", ts);
								if (FixMesh(out_united, true)) {
									first = out_united;
									msg("succes_check_union", ts);
								}
								else {
									msg("failed_check_union", ts);
								}
							}
							else {
								msg("failed_boolean_union", ts, true);
							}							
						}						
					}					
				}
			}
		}
	}

	msg("united_end", ts_total);

	SaveMesh("C:\\dev\\data\\objects\\building\\united.off", first);


	return true;
}
