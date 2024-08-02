using NetCGAL;
using NetCGAL.Utils;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AppCGAL
{
	internal class PMU
	{
		public static void Run()
		{
			string objs = "C:\\dev\\data\\objects\\";
			string buildingDir = objs + "building\\";

			if (MyMesh.LoadDir(buildingDir, out var loadedChunks))
			{
				Console.WriteLine("loaded dir");
			}
			return;

			if (Directory.Exists(buildingDir))
			{
				Directory.Delete(buildingDir, true);
			}
			Directory.CreateDirectory(buildingDir);

			var catFolders = Directory.EnumerateDirectories(objs).ToList();

			if (PowerModelUtils.LoadSpace(catFolders, out var space) &&
				PowerModelUtils.LoadAllConstructs(catFolders, out var constructs))
			{
				var chunks = constructs.Split(100);

				MyDebugUtils.ClearLog();

				for (int cn = 0; cn < chunks.Count; cn++)
				{
					if (chunks[cn].UnionMeshes(out var unitedConstr, out var errors))
					{
						unitedConstr.Save($"{buildingDir}constructs-{cn}.off");
						Console.WriteLine($"saved {cn}");
						//if (space.Boolean(unitedConstr, BooleanType.Dif, out var roomsSpace))
						//{
						//	int f = 0;

						//	if (roomsSpace.Split(out List<MyMesh> splitted))
						//	{
						//		for (int i = 0; i < splitted.Count; i++, f++)
						//		{
						//			MyMesh room = splitted[i];
						//			room.Save($"{buildingDir}{f}.off");
						//		}
						//	}
						//	else
						//	{
						//		roomsSpace.Save(objs + "rooms.off");
						//	}
						//}
					}
					else
					{
						unitedConstr.Save($"{buildingDir}constructs-{cn}-true.off");
						if (errors.UnionMeshes(out unitedConstr, out errors))
						{
							unitedConstr.Save($"{buildingDir}constructs-{cn}-errors.off");
						}
						else
						{
							foreach(var error in errors)
							{
								MyDebugUtils.AddLog(error.Name + "error        error");
							}
						}
					}
				}
			}
		}
	}
}
