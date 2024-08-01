using NetCGAL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Debug = NetCGAL.Utils.MyDebugUtils;

namespace AppCGAL
{
	public static class Samples
	{
		public static void Test3()
		{
			if (MyMesh.Load("C:\\dev\\data\\Log\\two480.off", out MyMesh loaded))
			{
				if(loaded.Remesh(10, 20, out MyMesh remeshed))
				{

				}
			}
		}

		public static void Test1()
		{
			if (MyMesh.LoadLocal("C:\\dev\\data\\Log\\one480.off", out MyMesh loaded))
			{
				loaded.Save(Debug.logTemp + "tone480.off");

				if (MyMesh.Load(Debug.logTemp + "tone480.off", out MyMesh remeshed))
				{
					remeshed.Save(Debug.logTemp + "rone480.off");
				}
			}
		}

		public static void Test2()
		{
			if (Debug.SplitOneTwo(out var listOne, out var listTwo))
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
