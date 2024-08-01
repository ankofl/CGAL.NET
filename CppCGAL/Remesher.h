#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/detect_features.h>
#include <CGAL/Polygon_mesh_processing/surface_Delaunay_remeshing.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Mesh_constant_domain_field_3.h>
#include <fstream>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include "MyTimer.h"
#include "SurfaceToMesh.h"
typedef CGAL::Exact_predicates_inexact_constructions_kernel   K;
typedef CGAL::Surface_mesh<K::Point_3>                        SurfaceMesh;

typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

typedef CGAL::Mesh_constant_domain_field_3<K, int> Sizing_field;
namespace PMP = CGAL::Polygon_mesh_processing;

int Remesher(SurfaceMesh& surface, double target_edge_length, double fdist, Mesh& mesh){

    Sizing_field size(target_edge_length);

    std::cout << "Detect features..." << std::endl;
    using EIFMap = boost::property_map<SurfaceMesh, CGAL::edge_is_feature_t>::type;
    EIFMap eif = get(CGAL::edge_is_feature, surface);
    PMP::detect_sharp_edges(surface, 45, eif);

    TimePoint tp = Start("Remeshing");

    surface = PMP::surface_Delaunay_remeshing(surface,
        CGAL::parameters::protect_constraints(true)
        .mesh_edge_size(size)
        .mesh_facet_distance(fdist)
        .edge_is_constrained_map(eif));

    tp = Msg(tp, "Ended");

    SurfaceToMesh(surface, mesh);    

    return 0;
}