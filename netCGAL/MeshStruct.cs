using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL
{
	[StructLayout(LayoutKind.Sequential)]
	public struct MeshStruct
	{
		public IntPtr FloatsPtr;
		public IntPtr IndexesPtr;
		public int FloatsCount;
		public int IndexesCount;

		[NonSerialized]
		public float[] Floats;
		[NonSerialized]
		public int[] Indexes;


		public void CopyDataFromPointers()
		{
			if (FloatsCount > 0)
			{
				Floats = new float[FloatsCount];
				Marshal.Copy(FloatsPtr, Floats, 0, FloatsCount);
			}

			if (IndexesCount > 0)
			{
				Indexes = new int[IndexesCount];
				Marshal.Copy(IndexesPtr, Indexes, 0, IndexesCount);
			}
		}

		public void CopyDataToPtrs()
		{
			if (FloatsCount > 0)
			{
				FloatsPtr = Marshal.AllocCoTaskMem(sizeof(float) * FloatsCount);
				Marshal.Copy(Floats, 0, FloatsPtr, FloatsCount);
			}

			if (IndexesCount > 0)
			{
				IndexesPtr = Marshal.AllocCoTaskMem(sizeof(int) * IndexesCount);
				Marshal.Copy(Indexes, 0, IndexesPtr, IndexesCount);
			}
		}
	}
}
