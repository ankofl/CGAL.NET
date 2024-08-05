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

			//if (MyMesh.LoadDir(buildingDir, out var loadedChunks))
			//{
			//	Console.WriteLine("loaded dir");
			//}

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

				for (int cn = 0; cn < chunks.Count; cn++)
				{
					if (chunks[cn].UnionMeshes(out var unOne, out var errors))
					{
						unOne.Save($"{buildingDir}constructs-{cn}.off");
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
						if (errors.UnionMeshes(out var unTwo, out errors))
						{
							try
							{
								if (unOne.Boolean(unTwo, BooleanType.Union, out var unThree))
								{
									unThree.Save($"{buildingDir}constructs-{cn}.off");
								}
							}
							catch
							{
								unOne.Save($"{buildingDir}constructs-{cn}-one.off");
								unTwo.Save($"{buildingDir}constructs-{cn}-two.off");
							}						
						}
						else
						{
							throw new Exception("Re-Error union");
						}
					}
				}

				if(MyMesh.LoadDir(buildingDir, out var meshes))
				{

				}
			}
		}
	}
}
