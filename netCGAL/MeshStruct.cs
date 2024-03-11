using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace netCGAL
{
	[StructLayout(LayoutKind.Sequential)]
	public struct MeshStruct
	{
		public IntPtr FloatsPtr;
		public IntPtr IndexesPtr;
		public int PointsCount;
		public int IndexesCount;

		[NonSerialized]
		public float[] Floats;
		[NonSerialized]
		public int[] Indexes;
	}
}
