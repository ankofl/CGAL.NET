using NetCGAL;
using System.Globalization;
using System.Reflection;

namespace AppCGAL
{
	public class Programm
	{
		public static void Main()
		{
			Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US");

			try
			{
				while (true)
				{
					string folder = "C:\\dev\\data\\objects\\";
					if (MyMesh.LoadLocal(folder + "rooms.off", out MyMesh rooms))
					{
						if (rooms.Split(out List<MyMesh> splitted))
						{
							for (int i = 0; i < splitted.Count; i++)
							{
								MyMesh room = splitted[i];
								room.Save($"{folder}room-{i}.off");
							}
						}
					}
					Console.ReadKey();
				}				
			}
			catch (Exception e)
			{
				Console.WriteLine(e);
			}
			Console.ReadKey();
		}
	}
}
