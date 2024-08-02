using NetCGAL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MyDebug = NetCGAL.Utils.MyDebugUtils;

namespace AppCGAL
{
	public static class Samples
	{
		public static void DoorsTest()
		{
			if(MyMesh.LoadDir("C:\\dev\\data\\objects\\Doors\\", out List<MyMesh> meshes))
			{
				Console.ReadKey();
			}
		}

		public static void Test1()
		{
			if (MyMesh.LoadLocal("C:\\dev\\data\\Log\\one480.off", out MyMesh loaded))
			{
				loaded.Save(MyDebug.logTemp + "tone480.off");

				if (MyMesh.Load(MyDebug.logTemp + "tone480.off", out MyMesh remeshed))
				{
					remeshed.Save(MyDebug.logTemp + "rone480.off");
				}
			}
		}

		public static void Test2()
		{
			if (MyDebug.SplitOneTwo(out var listOne, out var listTwo))
			{
				for (int i = 0; i < listOne.Count; i++)
				{
					if (listOne[i].Boolean(listTwo[i], BooleanType.Union, out var union))
					{

					}
				}
			}
		}
	}
}
