using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace netCGAL
{
	public class NetCGAL
	{ 
		[DllImport("cppCGAL.dll", CallingConvention = CallingConvention.Cdecl)]
		public static extern void  CallMethod();
	}
}
