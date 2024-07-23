#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <vector>
#include "MyMesh.h"
#include <CGAL/Polyhedron_items_with_id_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;

typedef CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3> Mesh;

typedef std::vector<int>                                CGAL_Polygon;

typedef Mesh::Vertex_handle Vertex_handle;
typedef Mesh::Vertex_iterator Vertex_iterator;
typedef Mesh::Facet_iterator Facet_iterator;

int ConvertToMyMesh(Mesh& input, MyMesh* output)
{
    std::map<K::Point_3, int> pointIndexMap;
    int vertex_id = 0;

    for (auto vi = input.vertices_begin(); vi != input.vertices_end(); ++vi) {
        pointIndexMap[vi->point()] = vertex_id++;
    }

    int num_vertices = pointIndexMap.size();
    std::cout << "Number of unique vertices: " << num_vertices << std::endl;

    output->indexesPtr = new int[input.size_of_facets() * 3];
    output->indexesLength = input.size_of_facets() * 3;

    output->floatsPtr = new double[num_vertices * 3];
    output->floatsLength = num_vertices * 3;

    // Fill vertex coordinates
    for (const auto& pair : pointIndexMap) {
        K::Point_3 point = pair.first;
        int index = pair.second;

        output->floatsPtr[index * 3] = point.x();
        output->floatsPtr[index * 3 + 1] = point.y();
        output->floatsPtr[index * 3 + 2] = point.z();
    }

    // Fill indices for polygons
    int index = 0;
    for (auto fi = input.facets_begin(); fi != input.facets_end(); ++fi) {
        auto hc = fi->facet_begin();
        // HC is the halfedge iterator around the facet
        do {
            K::Point_3 point = hc->vertex()->point();
            output->indexesPtr[index++] = pointIndexMap[point];
        } while (++hc != fi->facet_begin());
    }

    return 0;
}