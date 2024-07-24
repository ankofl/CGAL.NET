using NetCGAL;
using NetCGAL.Structs;
using System.Reflection;

namespace AppCGAL
{
	public class Programm
	{
		public static void Main()
		{
			try
			{
				CallerCGAL.Init();

				while (true)
				{
					MyMesh.Load("C:/dev/CGAL.NET/data/meshes/refined_elephant.off", out MyMesh elephant);
					elephant.Save("C:/dev/CGAL.NET/data/meshes/refined_elephant_re.off");

					MyMesh.Load("C:/dev/CGAL.NET/data/meshes/bunny00.off", out MyMesh bunny);

					elephant.Boolean(bunny, BooleanType.Union, out MyMesh union);

					union.Save("C:/dev/CGAL.NET/data/meshes/refined_elephant_union.off");
				}
			}
			catch(Exception e)
			{
				Console.WriteLine(e);
			}

			Console.ReadKey();
		}
	}
}
