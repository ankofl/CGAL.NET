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
			Console.WriteLine("Started");

			Stopwatch timer = new();
			timer.Start();
			var mesh = new MeshStruct(
					[0.0f, 1.0f, 2.0f,
						3.0f, 4.0f, 5.0f,
						13.0f, 7.0f, 8.0f],
					[0, 1, 2]
				);

			for (int i = 0; i < 1000000; i++)
			{
				MeshStruct meshOut = mesh.Multiply();
			}

			timer.Stop();
			Console.WriteLine(timer.ElapsedMilliseconds);

			timer.Start();
			for (int i = 0; i < 1000000; i++)
			{
				var mesh2 = new MeshStruct(
					[0.0f, 1.0f, 2.0f,
						3.0f, 4.0f, 5.0f,
						13.0f, 7.0f, 8.0f],
					[0, 1, 2]
				);

				MeshStruct meshOut = mesh2.Multiply();

				//MeshStruct meshOut2 = meshOut.Multiply();
			}
			timer.Stop();
			Console.WriteLine(timer.ElapsedMilliseconds);

			Console.WriteLine("Finished");
			Console.ReadKey();
		}
	}
}
