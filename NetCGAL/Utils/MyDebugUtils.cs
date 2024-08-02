using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL.Utils
{
	public static class MyDebugUtils
	{
		public static void AddLog(string msg)
		{
			bool writed = false;
			while (!writed)
			{
				try
				{
					File.AppendAllText(logPath, msg + '\n');
					writed = true;
				}
				catch (Exception e)
				{
					Console.WriteLine("Error append log" + msg);
				}
			}
		}

		public static bool SplitOneTwo(out List<MyMesh> listOne, out List<MyMesh> listTwo)
		{
			listOne = [];
			listTwo = [];

			if(MyMesh.LoadDir(logFolder, out List<MyMesh> meshes))
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

		public static void ClearLog()
		{
			File.Create(logPath);
		}

		public const string logFolder = "C:\\dev\\data\\objects\\";
		public const string logPath = logFolder + "log.txt";
		public const string logTemp = logFolder + "Temp\\";
	}
}
