#pragma once
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Nef_polyhedron_3.h>
#include <CGAL/IO/Nef_polyhedron_iostream_3.h>
#include <CGAL/Nef_3/SNC_indexed_items.h>
#include <CGAL/convex_decomposition_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/boost/graph/copy_face_graph.h>
#include <list>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Polyhedron_3<K> Polyhedron_3;
typedef CGAL::Nef_polyhedron_3<K, CGAL::SNC_indexed_items> Nef_polyhedron_3;
typedef Nef_polyhedron_3::Volume_const_iterator Volume_const_iterator;
typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

bool mesh_decompose(Mesh& mesh, std::vector<Mesh>& output) {
    Nef_polyhedron_3 N(mesh);
    CGAL::convex_decomposition_3(N);
    std::list<Polyhedron_3> convex_parts;
    Volume_const_iterator ci = ++N.volumes_begin();
    for (; ci != N.volumes_end(); ++ci) {
        if (ci->mark()) {
            Polyhedron_3 P;
            N.convert_inner_shell_to_polyhedron(ci->shells_begin(), P);
            convex_parts.push_back(P);
        }
    }
    for (const auto& poly : convex_parts) {
        Mesh m;
        CGAL::copy_face_graph(poly, m); 
        output.push_back(m);
    }
    return output.size() > 0;
}
