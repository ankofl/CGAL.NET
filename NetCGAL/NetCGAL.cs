using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL
{
	public class NetCGAL
	{
		public static void Main()
		{
			string pipeMesh = "pipeMesh";

			MeshStruct meshToSend = new()
			{
				Indexes = [1, 2, 3],
				Floats = [1.1f, 2.2f, 3.3f]
			};

			//PipesIO.Output(pipeMesh, meshToSend);


			Console.WriteLine("Started");

			CallerCGAL.GetFloatArray(out IntPtr arrayPtr, out int size);

			float[] managedArray = new float[size];
			Marshal.Copy(arrayPtr, managedArray, 0, size);

			CallerCGAL.ReleaseFloatArray(arrayPtr);

			// Теперь у вас есть массив float в C#
			Console.WriteLine("Float Array:");
			foreach (var value in managedArray)
			{
				Console.WriteLine(value);
			}

			IFCIO ifcIO = new();
			ifcIO.Load(@"C:\demo\CGAL.NET\Data\bim\RVT22_П_Домик_АР.ifc");

			var mesh = new MeshStruct()
			{
				Floats = [
						0.0f, 1.0f, 2.0f,
						3.0f, 4.0f, 5.0f,
						13.0f, 7.0f, 8.0f],
				Indexes = [0, 1, 2],
			};
			mesh.FloatsCount = mesh.Floats.Length;
			mesh.IndexesCount = mesh.Indexes.Length;

			for (int i = 0; i < 100000; i++)
			{
				Console.WriteLine(ToCpp(mesh));
			}

			


			Console.WriteLine("Finished");
			Console.ReadKey();
		}

		static int ToCpp(MeshStruct mesh)
		{
			int result;

			//mesh.CopyDataToPtrs();

			try
			{
				mesh.FloatsPtr = Marshal.AllocCoTaskMem(sizeof(float) * mesh.FloatsCount);
				Marshal.Copy(mesh.Floats, 0, mesh.FloatsPtr, mesh.FloatsCount);

				mesh.IndexesPtr = Marshal.AllocCoTaskMem(sizeof(int) * mesh.IndexesCount);
				Marshal.Copy(mesh.Indexes, 0, mesh.IndexesPtr, mesh.IndexesCount);

				result = CallerCGAL.ProcessMesh(
					//mesh.Floats, mesh.Floats.Length,
					//mesh.Indexes, mesh.Indexes.Length,

					//out IntPtr ptrFloats, out int FloatsSize,
					//out IntPtr ptrIndexes, out int IndexesSize,

					mesh,
					out MeshStruct meshOut);

				meshOut.Indexes = new int[meshOut.IndexesCount];
				Marshal.Copy(meshOut.IndexesPtr, meshOut.Indexes, 0, meshOut.IndexesCount);

				meshOut.FloatsPtr = Marshal.AllocCoTaskMem(sizeof(float) * meshOut.FloatsCount);
				Marshal.Copy(meshOut.Floats, 0, meshOut.FloatsPtr, meshOut.FloatsCount);

				//if (ptrFloats != IntPtr.Zero && ptrIndexes != IntPtr.Zero)
				//{
				//	float[] resultArray = new float[FloatsSize];

				//	Marshal.Copy(ptrFloats, resultArray, 0, FloatsSize);

				//	int[] resultIndexes = new int[IndexesSize];
				//	Marshal.Copy(ptrIndexes, resultIndexes, 0, FloatsSize);

				//	result = resultArray.Length + resultIndexes.Length;

				//	//CallerCGAL.FreeArray(ptrFloats, ptrIndexes);

				//	Marshal.FreeCoTaskMem(ptrFloats);
				//	Marshal.FreeCoTaskMem(ptrIndexes);
				//}
			}
			catch
			{
				result = -1;
			}
			finally
			{
				Marshal.FreeHGlobal(mesh.IndexesPtr);
				Marshal.FreeCoTaskMem(mesh.FloatsPtr);
			}

			return result;
		}
	}
}
