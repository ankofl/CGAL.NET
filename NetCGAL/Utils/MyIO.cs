using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL.Utils
{
	public static class MyIO
	{
		public static bool Dirs(string folder, out List<string> dirs)
		{
			dirs = null;
			if (Directory.Exists(folder))
			{
				dirs = Directory.EnumerateDirectories(folder).ToList();
			}
			return dirs != null;
		}

		public static bool Files(string folder, out List<string> files)
		{
			files = null;
			if (Directory.Exists(folder))
			{
				files = Directory.EnumerateFiles(folder).ToList();
			}
			return files != null;
		}
	}
}
