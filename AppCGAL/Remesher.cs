using NetCGAL.Utils;
using NetCGAL;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AppCGAL
{
	internal class Remesher
	{
		public static void Run()
		{
			string objDir = MyDebugUtils.logFolder + "objects\\";

			double[] length = [1, 0.5];
			int[] iter = [3, 3];

			if (MyIO.Dirs(objDir, out var dirsFinded))
			{
				List<string> dirs = [dirsFinded[0], dirsFinded[1]];

				for (int k = 0; k < length.Length; k++)
				{
					var k0 = length[k];
					var k1 = iter[k];
					Console.WriteLine($"\n\nk:{k + 1}/{length.Length} length:{k0} iter:{k1}");

					for (int d = 0; d < dirs.Count; d++)
					{
						if (MyIO.Files(dirs[d], out var files))
						{
							foreach (var file in files)
							{
								if (file.Contains("_r.off"))
								{
									File.Delete(file);
								}
							}
						}

						if (MyIO.Files(dirs[d], out files))
						{
							for (int f = 0; f < files.Count; f++)
							{
								var file = files[f];
								if (MyMesh.Load(file, out var loaded))
								{

									int doubs = loaded.GetDoubles().Length;
									int ints = loaded.GetIndexes().Length;

									if (loaded.Remesh(out var fixing, k0, k1))
									{
										int doubs_f = fixing.GetDoubles().Length;
										int ints_f = fixing.GetIndexes().Length;

										fixing.Save(file.Replace(".off", $"_{k}_r.off"));
										Console.WriteLine($"{loaded.Name} {d + 1}/{dirs.Count} {f + 1}/{files.Count} doubs:{doubs}/{doubs_f} ints:{ints}/{ints_f}");
									}
								}
							}
						}
					}
				}
			}
		}

	}
}
