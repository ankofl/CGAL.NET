using NetCGAL.Structs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL
{
	public class Tests
	{
		private static void TestMyArray()
		{
			MyArray myArray = new([0, 1, 2, 3]);

			int result = myArray.Cross(out MyArray output);
		}

		private static void Test()
		{
			var soup = new SoupStruct(
				[0.0f, 1.0f, 2.0f,
				3.0f, 4.0f, 5.0f,
				13.0f, 7.0f, 8.0f],
				[0, 1, 2]);

			SoupStruct soupOut = soup.Refine();

			var mesh = new MeshStruct(
				[0.0f, 1.0f, 2.0f,
				3.0f, 4.0f, 5.0f,
				13.0f, 7.0f, 8.0f],
				[0, 1, 2]);
			MeshStruct meshOut = mesh.Multiply();
		}
	}
}
