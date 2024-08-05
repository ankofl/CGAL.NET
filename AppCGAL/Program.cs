using NetCGAL;
using NetCGAL.Utils;
using System.Globalization;
using System.Reflection;
using MyDebug = NetCGAL.Utils.MyDebugUtils;

namespace AppCGAL
{
	public class Programm
	{
		public static void Main()
		{
			Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US");

			try
			{
				//PMU.Run();

				//Samples.TestOneTwo();

				Samples.Maniford();
			}
			catch (Exception e)
			{
				Console.WriteLine(e);
			}
			Console.ReadKey();
		}
	}
}
