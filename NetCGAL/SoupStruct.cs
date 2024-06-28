using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL
{
	[StructLayout(LayoutKind.Sequential)]
	public struct SoupStruct
	{
		private IntPtr PtrFloats;
		private IntPtr PtrIndexes;

		private int CountFloats;
		private int CountIndexes;

		[NonSerialized]
		private float[] Floats;
		[NonSerialized]
		private int[] Indexes;

		public SoupStruct(float[] floats, int[] indexes)
		{
			Floats = floats;
			Indexes = indexes;
		}

		[DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void ReleaseSoup(IntPtr ptrFloats, IntPtr ptrIndexes);

		[DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int RefineSoup(SoupStruct soupStruct, out SoupStruct soupStructResult);

		public SoupStruct Refine()
		{
			PtrCreate();
			int code = RefineSoup(this, out SoupStruct soupStructResult);
			soupStructResult.PtrLoadAndClear();
			PtrClear();
			return soupStructResult;
		}

		private void PtrLoadAndClear()
		{
			if(PtrFloats != IntPtr.Zero && PtrIndexes != IntPtr.Zero)
			{
				Floats = new float[CountFloats];
				Marshal.Copy(PtrFloats, Floats, 0, CountFloats);

				Indexes = new int[CountIndexes];
				Marshal.Copy(PtrIndexes, Indexes, 0, CountIndexes);

				PtrClear();
			}
			else
			{
				throw new Exception("Fail PtrLoad");
			}
		}

		private void PtrCreate()
		{
			if(PtrFloats == IntPtr.Zero && PtrIndexes == IntPtr.Zero)
			{
				CountFloats = Floats.Length;
				CountIndexes = Indexes.Length;

				PtrFloats = Marshal.AllocCoTaskMem(sizeof(float) * CountFloats);
				Marshal.Copy(Floats, 0, PtrFloats, CountFloats);

				PtrIndexes = Marshal.AllocCoTaskMem(sizeof(int) * CountIndexes);
				Marshal.Copy(Indexes, 0, PtrIndexes, CountIndexes);
			}
			else
			{
				throw new Exception("Fail PtrCreate");
			}
		}

		private void PtrClear()
		{
			if(PtrFloats != IntPtr.Zero && PtrIndexes != IntPtr.Zero)
			{
				ReleaseSoup(PtrFloats, PtrIndexes);
				PtrFloats = IntPtr.Zero;
				PtrIndexes = IntPtr.Zero;
			}
			else
			{
				throw new Exception("Fail Ptr Clear");
			}
		}
	}
}
