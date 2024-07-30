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
					Console.WriteLine("Started");

					if (MyMesh.LoadLocal("C:\\dev\\data\\objects\\rooms.off", out MyMesh rooms))
					{
						if (rooms.Split(out List<MyMesh> splitted))
						{

						}
					}

					Console.WriteLine("Ended");
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
