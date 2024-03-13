#pragma once

#include <CGAL/license/Polyhedron.h>

#include <CGAL/Polyhedron_3.h>

#include <CGAL/IO/print_OFF.h>
#include <CGAL/IO/scan_OFF.h>

#include <CGAL/boost/graph/named_params_helper.h>
#include <CGAL/Named_function_parameters.h>
#include <CGAL/boost/graph/IO/OFF.h>
#include <CGAL/Has_conversion.h>
#include <CGAL/property_map.h>

#include <fstream>
#include <iostream>

namespace CGAL {

	template <
		class Traits,
		class Items,
		template < class T, class I, class A> class HDS, 
		class Alloc>
	std::istream& operator>>(
		std::istream& in,
		Polyhedron_3<Traits, Items, HDS, Alloc>& P)
	{
		read_OFF(in, P);
		return in;
	}

	template <class Traits,
		class Items,
		template < class T, class I, class A> class HDS,
		class Alloc, 
		class CGAL_NP_TEMPLATE_PARAMETERS>
	bool read_OFF(std::istream& in,
		Polyhedron_3<Traits, Items, HDS, Alloc>& P,
		const CGAL_NP_CLASS& np = parameters::default_values())
	{
		typedef typename boost::graph_traits<Polyhedron_3<Traits, Items, HDS, Alloc> >::vertex_descriptor Vertex;

		// reads a polyhedron from `in' and appends it to P.
		typedef typename property_map_selector<Polyhedron_3<Traits, Items, HDS, Alloc>, boost::vertex_point_t>::type      Def_VPM;
		typedef typename boost::property_traits<Def_VPM>::value_type                          Def_point;
		typedef typename Kernel_traits<Def_point>::Kernel                                     Def_kernel;

		typedef typename CGAL::GetVertexPointMap<Polyhedron_3<Traits, Items, HDS, Alloc>,
			CGAL_NP_CLASS>::type        VPM;
		typedef typename boost::property_traits<VPM>::value_type                              Point;
		typedef typename Kernel_traits<Point>::Kernel                                         Kernel;

		typedef typename CGAL::internal::Converter_selector<Def_kernel, Kernel>::type         Converter;

		using parameters::choose_parameter;
		using parameters::get_parameter;
		using parameters::is_default_parameter;

		const bool verbose = choose_parameter(get_parameter(np, internal_np::verbose), true);

		/*if (!(is_default_parameter<CGAL_NP_CLASS, internal_np::vertex_color_map_t>::value) ||
			!(is_default_parameter<CGAL_NP_CLASS, internal_np::face_color_map_t>::value) ||
			!(is_default_parameter<CGAL_NP_CLASS, internal_np::vertex_normal_map_t>::value) ||
			!(is_default_parameter<CGAL_NP_CLASS, internal_np::vertex_texture_map_t>::value))
		{
			return CGAL::IO::internal::read_OFF_BGL(in, P, np);
		}*/

		CGAL::scan_OFF(in, P, verbose);

		if (!parameters::is_default_parameter<CGAL_NP_CLASS, internal_np::vertex_point_t>::value)
		{
			Def_VPM def_vpm = get_property_map(CGAL::vertex_point, P);
			VPM vpm = choose_parameter(get_parameter(np, internal_np::vertex_point), get_property_map(CGAL::vertex_point, P));

			Converter to_vpm_type;
			for (Vertex v : vertices(P)) {
				put(vpm, v, to_vpm_type(get(def_vpm, v)));
			}
		}

		return !in.fail();
	}
}