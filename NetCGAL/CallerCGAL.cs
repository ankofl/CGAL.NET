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
		public const string pathDll = "CppCGAL.dll";

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		public static extern void CallMethod();
	}
}
