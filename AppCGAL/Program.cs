using NetCGAL;
using System.Reflection;

namespace AppCGAL
{
	public class Programm
	{
		public static void Main()
		{
			try
			{
				while (true)
				{
					MyMesh.LoadLocal("C:\\dev\\data\\objects\\6854.off", out MyMesh output);
					output.Save("C:\\dev\\data\\objects\\f6854.off");


					MyMesh.Load("C:\\dev\\data\\fixed.off", out MyMesh mF);

					//MyMesh.Load("C:\\dev\\data\\objects\\6854.off", out MyMesh m6854);

					//MyMesh.Load("../../data/meshes/refined_elephant.off", out MyMesh elephant);
					//elephant.Save("../../data/meshes/refined_elephant_re.off");
					//MyMesh.Load("../../data/meshes/bunny00.off", out MyMesh bunny);

					//elephant.Boolean(bunny, BooleanType.Union, out MyMesh union);

					//union.Save("../../data/meshes/refined_elephant_union.off");
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
