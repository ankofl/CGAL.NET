using NetCGAL;
using NetCGAL.Utils;
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
		public static void Maniford()
		{
			MyMesh.Load("C:\\dev\\data\\objects\\building\\remeshed\\59-one.off", out var one);
			MyMesh.Load("C:\\dev\\data\\objects\\building\\remeshed\\59-two.off", out var two);

			List<MyMesh> temp = [];

			if (two.Split(out var twos))
			{
				temp.AddRange(twos);
			}

			//temp.UnionMeshes(out var u_1, out var u_err);
		}

		public static void DoorsTest()
		{
			if(MyMesh.LoadDir("C:\\dev\\data\\objects\\Doors\\", out List<MyMesh> meshes))
			{
				Console.ReadKey();
			}
		}

		public static void TestOneTwo()
		{
			if (MyDebug.SplitOneTwo(out var listOne, out var listTwo))
			{
				for (int i = 0; i < listOne.Count; i++)
				{
					if (listOne[i].Boolean(listTwo[i], BooleanType.Union, out var union))
					{

					}

					Console.WriteLine();
				}
			}
		}
	}
}
