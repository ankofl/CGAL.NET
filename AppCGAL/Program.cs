using NetCGAL;
using System.Globalization;
using System.Reflection;
using Debug = NetCGAL.Utils.MyDebugUtils;

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
					Samples.Test3();					
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
