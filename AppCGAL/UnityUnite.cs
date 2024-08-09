using NetCGAL;
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
			string unitedDir = MyMeshUtils.CheckDir(dir + "building\\");
			MyMeshUtils.CheckDir(unitedDir + "splitted\\");

			List<string> dirs = [];
			foreach (var cat in PMU.GetConstrCats())
			{
				dirs.Add($"{dir}{cat}\\");
			}

			bool res = MyMesh.UnionDir(dirs);
		}
	}
}
