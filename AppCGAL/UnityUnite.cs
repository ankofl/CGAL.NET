using NetCGAL.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AppCGAL
{
	public static class UnityUnite
	{
		public static void Run()
		{
			string dir = MyMeshUtils.CheckDir("C:\\dev\\data\\objects\\");

			var catDirs = Directory.EnumerateDirectories(dir).ToList();

			if (PMU.LoadAllConstructs(catDirs, out var constrs))
			{
				if (constrs.UnionMeshes(out var unOne))
				{

				}
			}			
		}
	}
}
