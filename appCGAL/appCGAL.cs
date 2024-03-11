using netCGAL;
using System;
using System.Runtime.InteropServices;

class appCGAL
{
	public static void Main()
	{

		Console.WriteLine("Started");

		//NetCGAL.GetFloatArray(out IntPtr arrayPtr, out int size);

		//float[] managedArray = new float[size];
		//Marshal.Copy(arrayPtr, managedArray, 0, size);

		//NetCGAL.ReleaseFloatArray(arrayPtr);

		//// Теперь у вас есть массив float в C#
		//Console.WriteLine("Float Array:");
		//foreach (var value in managedArray)
		//{
		//	Console.WriteLine(value);
		//}



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

		Console.WriteLine(ToCpp(mesh));


		Console.WriteLine("Finished");
		Console.ReadKey();
	}

	static int ToCpp(MeshStruct mesh)
	{
		int result;

		mesh.CopyDataToPtrs();

		try
		{
			result = NetCGAL.ProcessMesh(
				mesh.Floats, mesh.Floats.Length,
				mesh.Indexes, mesh.Indexes.Length,

				out IntPtr ptrFloats, out int FloatsSize,
				out IntPtr ptrIndexes, out int IndexesSize,
				
				mesh,
				out MeshStruct meshOut);

			meshOut.Indexes = new int[meshOut.IndexesCount];
			Marshal.Copy(meshOut.IndexesPtr, meshOut.Indexes, 0, meshOut.IndexesCount);

			if (ptrFloats != IntPtr.Zero && ptrIndexes != IntPtr.Zero)
			{
				float[] resultArray = new float[FloatsSize];
				Marshal.Copy(ptrFloats, resultArray, 0, FloatsSize);

				int[] resultIndexes = new int[IndexesSize];
				Marshal.Copy(ptrIndexes, resultIndexes, 0, FloatsSize);

				result = resultArray.Length + resultIndexes.Length;

				//NetCGAL.FreeArray(ptrFloats, ptrIndexes);

				Marshal.FreeCoTaskMem(ptrFloats);
				Marshal.FreeCoTaskMem(ptrIndexes);
			}
		}
		catch
		{
			result = -1;
		}

		return result;
	}
}

