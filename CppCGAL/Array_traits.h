#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel     K;
typedef K::FT                                                   FT;
typedef std::array<FT, 3>                                       Custom_point;

struct Array_traits
{
    struct Equal_3
    {
        bool operator()(const Custom_point& p, const Custom_point& q) const {
            return (p == q);
        }
    };

    struct Less_xyz_3
    {
        bool operator()(const Custom_point& p, const Custom_point& q) const {
            return std::lexicographical_compare(p.begin(), p.end(), q.begin(), q.end());
        }
    };

    Equal_3 equal_3_object() const {
        return Equal_3();
    }

    Less_xyz_3 less_xyz_3_object() const {
        return Less_xyz_3();
    }
};