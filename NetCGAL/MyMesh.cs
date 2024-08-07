using NetCGAL.Utils;
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

		[MarshalAs(UnmanagedType.BStr, SizeConst = 1)]
		public string Name = "";

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
			if(floatsLength > 0 && indexesLength > 0)
			{
				arrayDouble = new double[floatsLength];
				Marshal.Copy(floatsPtr, arrayDouble, 0, floatsLength);

				arrayInt = new int[indexesLength];
				Marshal.Copy(indexesPtr, arrayInt, 0, indexesLength);
			}			

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
				myMesh.Name = path.Split('\\').Last();
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

		public static bool LoadDir(string dir, out List<MyMesh> meshes)
		{
			meshes = [];
			var files = Directory.EnumerateFiles(dir).Where(f => f.EndsWith(".off")).ToList();
			for (int i = 0; i < files.Count; i++)
			{
				var file = files[i];
				Console.Write($"{i + 1}/{files.Count} {file.Split('\\').Last()} -> ");
				try
				{
					if (Load(file, out MyMesh loaded))
					{
						meshes.Add(loaded);
					}					
				}
				catch
				{
					Console.WriteLine($" error");
				}
				Console.WriteLine();
			}
			Console.WriteLine($"end cs");
			return meshes.Count > 0;
		}

		public bool Save(string path)
		{
			Prepare();
			int code = SaveExtern(path, this);
			if (code == 0)
			{
				Console.WriteLine($"saved {path.Split('\\').Last()}");
			}
			ClearLocal();
			return code == 0;
		}



		public bool Fix(out MyMesh fixing)
		{
			Prepare();

			int code = FixExtern(this, out fixing);

			fixing.LoadAndClear();

			ClearLocal();

			return code == 0;
		}

		public bool Remesh(out MyMesh fixing, double length = 0.05, int iterations = 3)
		{
			Prepare();

			int code = RemeshExtern(this, length, iterations, out fixing);

			fixing.LoadAndClear();

			ClearLocal();

			return code == 0;
		}

		public bool Boolean(MyMesh other, BooleanType type, out MyMesh output)
		{
			Prepare();
			other.Prepare();

			int result = BooleanExtern(this, other, type, out output);
			if (result == 0)
			{
				output.LoadAndClear();
			}			 
			

			ClearLocal();
			other.ClearLocal();
			return result == 0;
		}

		public bool Split(out List<MyMesh> meshes)
		{
			meshes = null;
			int code = -1;
			Prepare();

			code = SplitExtern(this, out MyMeshList myMeshList);
			myMeshList.LoadAndClear(out meshes);

			ClearLocal();

			return code == 0;
		}

		public static bool UnionDir(List<string> dirs, int chunkSize = 1000)
		{
			return union_dir_extern([.. dirs], dirs.Count, chunkSize);
		}

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern bool union_dir_extern(string[] paths, int count, int chunkSize);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int RemeshExtern(MyMesh one, double target_edge_length, int number_of_iterations, out MyMesh output);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int FixExtern(MyMesh one, out MyMesh output);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int BooleanExtern(MyMesh one, MyMesh two, BooleanType type, out MyMesh output);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void ClearMyMeshExtern(MyMesh input);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int LoadExtern(string path, out MyMesh output);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int SaveExtern(string path, MyMesh input);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		public static extern int SplitExtern(MyMesh myMesh, out MyMeshList myMeshList);

		public const string pathDll = "CppCGAL.dll";
	}
}
