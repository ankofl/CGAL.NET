using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace netCGAL
{
	public static class NetCGAL
	{ 
		public static int Multi(Mesh mesh)
		{
			// Создание GCHandle для объекта
			GCHandle objHandle = GCHandle.Alloc(mesh, GCHandleType.Pinned);
			int result = 0;
			try
			{
				IntPtr objPtr = objHandle.AddrOfPinnedObject();
				result = Multi(objPtr);
			}
			catch
			{
				result = -1;
			}
			finally
			{
				objHandle.Free();
			}

			return result;
		}

		const string pathDll = "cppCGAL.dll";

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
	    private static extern int Multi(IntPtr obj);

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		public static extern void CallMethod();
	}
}
