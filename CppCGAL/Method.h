#pragma once

#include <CGAL/Boolean_set_operations_2.h>
#include <list>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2                                   Point_2;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
typedef CGAL::Polygon_with_holes_2<Kernel>                Polygon_with_holes_2;
typedef std::list<Polygon_with_holes_2>                   Pwh_list_2;

void Method() {
    // Construct the two input polygons.
    Polygon_2 P;
    P.push_back(Point_2(0, 0));
    P.push_back(Point_2(5, 0));
    P.push_back(Point_2(3.5, 1.5));
    P.push_back(Point_2(2.5, 0.5));
    P.push_back(Point_2(1.5, 1.5));
        
    Polygon_2 Q;
    Q.push_back(Point_2(0, 2));
    Q.push_back(Point_2(1.5, 0.5));
    Q.push_back(Point_2(2.5, 1.5));
    Q.push_back(Point_2(3.5, 0.5));
    Q.push_back(Point_2(5, 2));

    // Compute the union of P and Q.
    Polygon_with_holes_2 unionR;

    if (CGAL::join(P, Q, unionR)) {
        std::cout << "The union: ";
    }
    else {
        std::cout << "P and Q are disjoint and their union is trivial." << std::endl;
    }        
    std::cout << std::endl;

    // Compute the intersection of P and Q.
    Pwh_list_2                  intR;
    Pwh_list_2::const_iterator  it;

    CGAL::intersection(P, Q, std::back_inserter(intR));

    std::cout << "The intersection:" << std::endl;
    for (it = intR.begin(); it != intR.end(); ++it) {
        std::cout << "--> ";
    }
}