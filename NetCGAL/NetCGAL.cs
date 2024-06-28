using System;
using System.Collections.Generic;
using System.Diagnostics;
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
			while (true)
			{
				Console.Clear();

				//CallerCGAL.CallMethod();

				for(int i = 0; i < 1000000; i++)
				{
					var mesh = new MeshStruct(
						[0.0f, 1.0f, 2.0f,
						3.0f, 4.0f, 5.0f,
						13.0f, 7.0f, 8.0f],
						[0, 1, 2]);

					MeshStruct meshOut = mesh.Multiply();
				}
			}
		}
	}
}
