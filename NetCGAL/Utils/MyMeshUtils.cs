using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Debug = NetCGAL.Utils.MyDebugUtils;

namespace NetCGAL.Utils
{
	public static class MyMeshUtils
	{
		public static bool Union(this List<MyMesh> meshes, out MyMesh first)
		{
			first = meshes[0];

			Debug.ClearLog();

			for (int i = 1; i < meshes.Count; i++)
			{
				if (Debug.bugs.Contains(i))
				{
					string oneName = $"one{i}.off";
					string twoName = $"two{i}.off";
					first.Save(Debug.logFolder + oneName);
					//first.Display(oneName);
					meshes[i].Save(Debug.logFolder + twoName);
					Debug.AddLog($"{Debug.Now()} error {i}");
					continue;
				}

				if (first.Boolean(meshes[i], BooleanType.Union, out var union))
				{
					Debug.AddLog($"{Debug.Now()} true {i}");
					first = union;
				}
				else
				{
					Debug.AddLog($"{Debug.Now()} false {i}");
				}
			}

			return first.Valid();
		}

		public static bool Valid(this MyMesh myMesh)
		{
			return myMesh.GetIndexes().Length > 0;
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
	}
}
