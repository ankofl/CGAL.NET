using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL
{
	public enum BooleanType
	{
		Union,
		Inter,
		Dif
	}

	[StructLayout(LayoutKind.Sequential)]
	public struct MyMesh
	{
		private IntPtr floatsPtr;
		private IntPtr indexesPtr;

		private int floatsLength;
		private int indexesLength;

		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
		private double[] arrayDouble;
		[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
		private int[] arrayInt;

		public MyMesh(double[] arrayDouble, int[] arrayInt)
		{
			this.arrayDouble = arrayDouble;
			floatsLength = 0;
			floatsPtr = IntPtr.Zero;

			this.arrayInt = arrayInt;
			indexesLength = 0;
			indexesPtr = IntPtr.Zero;
		}

		public double[] GetDoubles()
		{
			return arrayDouble;
		}
		public int[] GetIndexes()
		{
			return arrayInt;
		}

		private void Prepare()
		{
			floatsLength = arrayDouble.Length;
			floatsPtr = Marshal.AllocHGlobal(floatsLength * sizeof(double));
			Marshal.Copy(arrayDouble, 0, floatsPtr, floatsLength);

			indexesLength = arrayInt.Length;
			indexesPtr = Marshal.AllocHGlobal(indexesLength * sizeof(int));
			Marshal.Copy(arrayInt, 0, indexesPtr, indexesLength);
		}

		private void LoadAndClear()
		{
			arrayDouble = new double[floatsLength];
			Marshal.Copy(floatsPtr, arrayDouble, 0, floatsLength);

			arrayInt = new int[indexesLength];
			Marshal.Copy(indexesPtr, arrayInt, 0, indexesLength);

			ClearMyMeshExtern(this);

			floatsLength = 0;
			floatsPtr = IntPtr.Zero;

			indexesLength = 0;
			indexesPtr = IntPtr.Zero;
		}

		private void ClearLocal()
		{
			Marshal.FreeHGlobal(floatsPtr);
			floatsLength = 0;

			Marshal.FreeHGlobal(indexesPtr);
			indexesLength = 0;
		}

		public static bool Load(string path, out MyMesh myMesh)
		{
			int code = LoadExtern(path, out myMesh);
			if(code == 0)
			{
				myMesh.LoadAndClear();
			}			
			return code == 0;
		}

		public static bool LoadLocal(string path, out MyMesh output)
		{
			output = default;

			string[] strings = File.ReadAllLines(path);

			string[] info = strings[1].Split(' ');

			List<double> doubles = [];
			List<int> ints = [];
			int dCount = int.Parse(info[0])+3;
			for (int i = 3; i < dCount; i++)
			{
				var vS = strings[i].Split(' ', StringSplitOptions.RemoveEmptyEntries);
				doubles.Add(double.Parse(vS[0]));
				doubles.Add(double.Parse(vS[1]));
				doubles.Add(double.Parse(vS[2]));
			}
			int iCount = int.Parse(info[1]) + dCount;
			for (int i = dCount; i < iCount; i++)
			{
				var vS = strings[i].Split(' ', StringSplitOptions.RemoveEmptyEntries);
				ints.Add(int.Parse(vS[1]));
				ints.Add(int.Parse(vS[2]));
				ints.Add(int.Parse(vS[3]));
			}
			if(doubles.Count > 0 && ints.Count > 0)
			{
				output = new MyMesh([.. doubles], [.. ints]);
				return true;
			}
			return false;			
		}

		public bool Save(string path)
		{
			Prepare();
			SaveExtern(path, this);
			ClearLocal();
			return true;
		}

		public bool Boolean(MyMesh other, BooleanType type, out MyMesh output)
		{
			Prepare();
			other.Prepare();

			int resut = BooleanExtern(this, other, type, out output);
			output.LoadAndClear();

			ClearLocal();
			other.ClearLocal();
			return resut == 0;
		}

		public bool Split(out List<MyMesh> meshes)
		{
			meshes = [];

			Prepare();

			IntPtr outputArrayPtr;
			int outputLength;

			int code = SplitExtern(this, out outputArrayPtr, out outputLength);

			for (int i = 0; i < outputLength; i++)
			{
				IntPtr currentPtr = Marshal.ReadIntPtr(outputArrayPtr, i * Marshal.SizeOf(typeof(MyMesh)));
				MyMesh mesh = Marshal.PtrToStructure<MyMesh>(currentPtr);
				meshes.Add(mesh);
			}

			ClearLocal();

			return meshes.Count > 0;
		}


		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int BooleanExtern(MyMesh one, MyMesh two, BooleanType type, out MyMesh output);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void ClearMyMeshExtern(MyMesh input);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int LoadExtern(string path, out MyMesh output);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int SaveExtern(string path, MyMesh input);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		public static extern int SplitExtern(MyMesh myMesh, out IntPtr outputArray, out int outputLength);

		private const string pathDll = "CppCGAL.dll";
	}
}
