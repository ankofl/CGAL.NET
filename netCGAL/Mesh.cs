using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace netCGAL
{
	public class Mesh
	{
		[MarshalAs(UnmanagedType.LPArray)]
		public float[] Points;

		public int[] Indexes;

		public Mesh()
		{

		}
	}
}
