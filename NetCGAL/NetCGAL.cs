using NetCGAL.Structs;
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
				for (int i = 0; i < 1000000; i++)
				{
					MyMesh.Load("C:/dev/CGAL.NET/data/meshes/refined_elephant.off", out MyMesh elephant);
					//elephant.Save("C:/dev/CGAL.NET/data/meshes/refined_elephant_re.off");

					MyMesh.Load("C:/dev/CGAL.NET/data/meshes/bunny00.off", out MyMesh bunny);

					elephant.Boolean(bunny, BooleanType.Union, out MyMesh union);

					union.Save("C:/dev/CGAL.NET/data/meshes/refined_elephant_union.off");
				}
			}
		}

		private static void TestMyArray()
		{
			MyArray myArray = new([0, 1, 2, 3]);

			int result = myArray.Cross(out MyArray output);
		}

		private static void Test()
		{
			var soup = new SoupStruct(
				[0.0f, 1.0f, 2.0f,
				3.0f, 4.0f, 5.0f,
				13.0f, 7.0f, 8.0f],
				[0, 1, 2]);

			SoupStruct soupOut = soup.Refine();

			var mesh = new MeshStruct(
				[0.0f, 1.0f, 2.0f,
				3.0f, 4.0f, 5.0f,
				13.0f, 7.0f, 8.0f],
				[0, 1, 2]);
			MeshStruct meshOut = mesh.Multiply();
		}
	}
}
