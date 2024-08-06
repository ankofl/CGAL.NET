using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL.Utils
{
	public static class MyDebugUtils
	{
		public static bool SplitOneTwo(out List<MyMesh> listOne, out List<MyMesh> listTwo)
		{
			listOne = [];
			listTwo = [];

			if(MyMesh.LoadDir(logFolder+"building\\", out List<MyMesh> meshes))
			{
				foreach (var mesh in meshes)
				{
					if (mesh.Name.Contains("two"))
					{
						listTwo.Add(mesh);
					}
					else if(mesh.Name.Contains("one"))
					{
						listOne.Add(mesh);
					}
				}
			}

			return listOne.Count > 0 && listOne.Count == listTwo.Count;
		}

		public static List<int> bugs = new()
		{
			480, 482, 571, 572, 573,
		};

		public static string Now()
		{
			return $"{DateTime.Now:yy.MM.dd HH.mm.ss.fff}";
		}

		public const string logFolder = "C:\\dev\\data\\objects\\";
	}
}
