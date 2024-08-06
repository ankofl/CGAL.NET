using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL.Utils
{
	public static class PMU
	{
		public enum Cats
		{
			Doors,
			Floors,
			Mass,
			Roofs,
			Walls,
			Windows,
			StructuralColumns,
		}

		public static bool LoadSpace(List<string> catFolders, out MyMesh space)
		{
			Console.Write("Space: ->");
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
				if (LoadCat(catFolders, c, listCat, out List<MyMesh> loaded))
				{
					constructs.AddRange(loaded);
				}
			}
			return constructs.Count > 0;
		}

		public static List<Cats> GetConstrCats()
		{
			return [
				Cats.Doors,
				Cats.Floors,
				Cats.Roofs,
				Cats.Walls,
				Cats.Windows,
				Cats.StructuralColumns,
			];
		}

		public static bool LoadCat(List<string> catFolders, int c, List<Cats> cats, out List<MyMesh> loadedMeshes)
		{
			loadedMeshes = [];

			string catDir = catFolders.Where(f => f.Contains(cats[c].ToString())).FirstOrDefault();

			var files = Directory.EnumerateFiles(catDir).ToList();

			for (int f = 0; f < files.Count; f++)
			{
				var file = files[f];
#if DEBUG
				Console.Write($"{c + 1}/{cats.Count} {f + 1}/{files.Count} {file.Split('\\').Last()} -> ");
#endif
				if (MyMesh.Load(file, out MyMesh loaded))
				{
					loadedMeshes.Add(loaded);
				}
				Console.WriteLine();
			}

			return loadedMeshes.Count > 0;
		}
	}
}
