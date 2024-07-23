using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL.Structs
{
	public enum BooleanType
	{
		Union,
		Inter,
		Dif
	}

	public struct MyMesh
	{
		private nint floatsPtr;
		private nint indexesPtr;

		private int floatsLength;
		private int indexesLength;

		[NonSerialized]
		private double[] floats;
		[NonSerialized]
		private int[] indexes;

		public MyMesh(double[] floats, int[] indexes)
		{
			this.floats = floats;
			this.indexes = indexes; 
		}
		private void Prepare()
		{
			floatsLength = floats.Length;
			floatsPtr = Marshal.AllocHGlobal(floatsLength * sizeof(double));
			Marshal.Copy(floats, 0, floatsPtr, floatsLength);

			indexesLength = indexes.Length;
			indexesPtr = Marshal.AllocHGlobal(indexesLength * sizeof(int));
			Marshal.Copy(indexes, 0, indexesPtr, indexesLength);
		}

		private void LoadAndClear()
		{
			floats = new double[floatsLength];
			Marshal.Copy(floatsPtr, floats, 0, floatsLength);

			indexes = new int[indexesLength];
			Marshal.Copy(indexesPtr, indexes, 0, indexesLength);

			ClearMyMeshExtern(this);
			floatsPtr = IntPtr.Zero;
			indexesPtr = IntPtr.Zero;
		}

		private void ClearLocal()
		{
			Marshal.FreeHGlobal(floatsPtr);
			Marshal.FreeHGlobal(indexesPtr);
		}

		public static bool Load(string path, out MyMesh myMesh)
		{
			LoadExtern(path, out myMesh);
			myMesh.LoadAndClear();
			return true;
		}

		public bool Save(string path)
		{
			Prepare();
			SaveExtern(path, this);
			ClearLocal();
			return true;
		}

		public int Boolean(MyMesh other, BooleanType type, out MyMesh output)
		{
			Prepare();
			other.Prepare();
			int resut = BooleanExtern(this, other, type, out output);
			output.LoadAndClear();

			ClearLocal();
			other.ClearLocal();
			return resut;
		}

		[DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
		public static extern int BooleanExtern(MyMesh one, MyMesh two, BooleanType type, out MyMesh output);

		[DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void ClearMyMeshExtern(MyMesh input);

		[DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int LoadExtern(string path, out MyMesh output);

		[DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int SaveExtern(string path, MyMesh input);
	}
}
