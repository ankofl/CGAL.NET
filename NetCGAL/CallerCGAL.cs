using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
//using UnityEngine;

namespace NetCGAL
{
	public static class CallerCGAL
	{ 
		const string pathDll = "CppCGAL.dll";

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		public static extern int ProcessMesh(
			//float[] Points, int pointsLength,
			//int[] Indexes, int indexesLength,
			//out IntPtr prtFloats, out int FloatsSize,
			//out IntPtr prtIndexes, out int IndexesSize,
			MeshStruct mesh,
			out MeshStruct meshOut);


		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		public static extern void FreeArray(IntPtr prrFloats, IntPtr prtIndexes);


		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		public static extern void CallMethod();




		[DllImport(pathDll)] // Замените на имя вашей DLL
		public static extern void GetFloatArray(out IntPtr array, out int size);

		[DllImport(pathDll)]
		public static extern void ReleaseFloatArray(IntPtr array);
	}
}
