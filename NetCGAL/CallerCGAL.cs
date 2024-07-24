using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL
{
	public static class CallerCGAL
	{
		public const string pathDll = "CppCGAL.dll";

		[DllImport(pathDll, CallingConvention = CallingConvention.Cdecl)]
		public static extern void CallMethod();

		public static void Init()
		{
			var assembly = Assembly.GetExecutingAssembly();

			var res = nameof(NetCGAL) + ".Res.";

			foreach (var resName in assembly.GetManifestResourceNames())
			{
				if (resName.Contains(".dll"))
				{
					using var stream = assembly.GetManifestResourceStream(resName) ?? throw new Exception($"NotFound: {resName}");

					using var fileStream = new FileStream(resName.Replace(res, ""), FileMode.Create, FileAccess.Write);

					stream.CopyTo(fileStream);
				}
			}

			Console.WriteLine("Loaded");
		}
	}
}
