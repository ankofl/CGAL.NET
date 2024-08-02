using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL.Utils
{
	public static class PowerModelUtils
	{
		public enum Cats
		{
			Doors,
			Floors,
			Mass,
			Roofs,
			Walls,
			Windows,
		}

		public static bool LoadSpace(List<string> catFolders, out MyMesh space)
		{
			string massCat = catFolders.Where(c => c.Contains(Cats.Mass.ToString())).First();
			string massFile = Directory.EnumerateFiles(massCat).First();
			return MyMesh.Load(massFile, out space);
		}

		public static bool LoadAllConstructs(List<string> catFolders, out List<MyMesh> constructs)
		{
			constructs = [];
			List<Cats> listCat = GetConstrCats();
			for (int c = 0; c < listCat.Count; c++)
			{
				if (LoadCat(catFolders, listCat[c], out List<MyMesh> loaded))
				{
					constructs.AddRange(loaded);
				}
				else
				{
					throw new Exception($"Not loaded <{listCat[c]}>");
				}
			}
			return constructs.Count > 0;
		}

		public static List<Cats> GetConstrCats()
		{
			return
			[
				Cats.Doors,
				Cats.Floors,
				Cats.Roofs,
				Cats.Walls,
				Cats.Windows,
			];
		}

		public static bool LoadCat(List<string> catFolders, Cats cat, out List<MyMesh> loadedMeshes)
		{
			loadedMeshes = [];

			string catDir = catFolders.Where(f => f.Contains(cat.ToString())).FirstOrDefault();

			foreach (var off in Directory.EnumerateFiles(catDir))
			{
				if (MyMesh.Load(off, out MyMesh loaded))
				{
					loadedMeshes.Add(loaded);
				}
			}
			return loadedMeshes.Count > 0;
		}
	}
}
