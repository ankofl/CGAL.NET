using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace NetCGAL.Utils
{
	public static class MyMeshUtils
	{
		public static string CheckDir(string path, bool delete = false)
		{
			var dir = path;
			if (path.EndsWith(".off"))
			{
				dir = path.Replace(path.Split('\\').Last(), "");
			}

			if (delete)
			{
				if (Directory.Exists(dir))
				{
					Directory.Delete(dir, true);
				}
				Directory.CreateDirectory(dir);
			}
			else
			{
				if (!Directory.Exists(dir))
				{
					Directory.CreateDirectory(dir);
				}				
			}

			return path;
		}

		public static bool UnionMeshes(this List<MyMesh> meshes, out MyMesh total)
		{
			total = default;
			if (meshes.Count > 0)
			{
				total = meshes[0];
			}			

			var buildDir = "C:\\dev\\data\\objects\\building\\";

			bool removes = false;

			string erDir = CheckDir(buildDir + "errors\\", removes);
			string chunkDir = CheckDir(buildDir + "chunks\\", removes);			

			if (removes)
			{
				var chunks = meshes.Split(100);

				for (int cn = 0; cn < chunks.Count; cn++)
				{
					var chunk = chunks[cn];
					var first = chunk[0];
					for (int i = 1; i < chunk.Count; i++)
					{
						MyMesh cur = chunk[i];

						Console.Write($"{cn + 1}/{chunks.Count} {i + 1}/{chunk.Count} {cur.Name} -> ");

						if (first.Boolean(cur, BooleanType.Union, out var union))
						{
							first = union;
						}
						else
						{
							cur.Save($"{erDir}{cn}-{i}.off");
						}

						Console.WriteLine();
					}
					first.Save($"{chunkDir}{cn}.off");
				}
			}

			string unitedDir = CheckDir(buildDir + "united\\", true);
			if (MyMesh.LoadDir(chunkDir, out var chunkMeshes))
			{
				var first = chunkMeshes[0];
				for (int c = 1; c < chunkMeshes.Count; c++)
				{
					var file = chunkMeshes[c];

					Console.Write($"{c + 1}/{chunkMeshes.Count} {file.Name} -> ");
					if (first.Boolean(file, BooleanType.Union, out var united))
					{
						first = united;						
					}
					else
					{
						if(file.Split(out var splitted))
						{
							for (int s = 0; s < splitted.Count; s++)
							{
								var split = splitted[s];
								Console.Write($"\n\t{c + 1}/{chunkMeshes.Count} {s+1}/{splitted.Count} {file.Name} -> ");
								if(first.Boolean(split, BooleanType.Union, out var splitUnion))
								{
									first = splitUnion;
								}
							}
						}
					}
					Console.WriteLine();				}
			}


			return true;
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
