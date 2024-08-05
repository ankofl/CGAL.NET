using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace NetCGAL.Utils
{
	public static class MyMeshUtils
	{
		public static bool UnionMeshes(this List<MyMesh> meshes, out MyMesh first, out List<MyMesh> errors)
		{
			errors = [];
			first = meshes[0];

			string r = "C:\\dev\\data\\objects\\building\\remeshed\\re\\";

			for (int i = 0; i < meshes.Count; i++)
			{
				MyMesh cur = meshes[i];

				Console.Write($"{i + 1}/{meshes.Count} {cur.Name} -> ");

				try
				{
					if (first.Boolean(cur, BooleanType.Union, out var union))
					{
						first = union;
					}
					else
					{
						first.Save($"{r}{i}-one.off");
						cur.Save($"{r}{i}-two.off");
					}
				}
				catch
				{
					errors.Add(cur);
				}
				Console.WriteLine();
			}

			return errors.Count == 0;
		}

		public static bool Save(this List<MyMesh> meshes, string dir)
		{
			try
			{
				foreach (var off in Directory.EnumerateFiles(dir).Where(f => f.EndsWith(".off")))
				{
					File.Delete(off);

					if (MyMesh.Load(off, out MyMesh loaded))
					{
						meshes.Add(loaded);
					}
				}

				foreach(var mesh in meshes)
				{
					mesh.Save(dir + mesh.Name);
				}

				return true;
			}
			catch { }

			return false;
		}

		public static List<List<MyMesh>> Split(this List<MyMesh> source, int chunkSize)
		{
			List<List<MyMesh>> chunks = [];
			for (int i = 0; i < source.Count; i += chunkSize)
			{
				chunks.Add(source.GetRange(i, Math.Min(chunkSize, source.Count - i)));
			}
			return chunks;
		}
	}
}
