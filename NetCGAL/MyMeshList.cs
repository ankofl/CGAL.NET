// MyMeshList.cs
using NetCGAL;
using System;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public struct MyMeshList
{
	private IntPtr datasPtr;
	private int datasLength;

	private IntPtr doublesPtr;
	private int doublesLength;

	private IntPtr intsPtr;
	private int intsLength;

	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
	private double[] arrayDouble;
	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
	private int[] arrayInt;
	[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1)]
	private int[] arrayData;

	public MyMeshList(int[] datas, double[] doubles, int[] ints)
	{
		arrayData = datas;
		arrayDouble = doubles;
		arrayInt = ints;
	}

	private void Prepare()
	{
		datasLength = arrayData.Length;
		datasPtr = Marshal.AllocHGlobal(datasLength * sizeof(int));
		Marshal.Copy(arrayData, 0, datasPtr, datasLength);

		doublesLength = 0;
		intsLength = 0;
		for (int i = 0; i < datasLength; i+=2)
		{
			doublesLength += arrayData[i];
			intsLength += arrayData[i+1];
		}
		doublesPtr = Marshal.AllocHGlobal(doublesLength * sizeof(double));
		Marshal.Copy(arrayDouble, 0, doublesPtr, doublesLength);

		intsPtr = Marshal.AllocHGlobal(intsLength * sizeof(int));
		Marshal.Copy(arrayInt, 0, intsPtr, intsLength);
	}

	public bool LoadAndClear(out List<MyMesh> listMyMesh)
	{
		listMyMesh = [];

		arrayData = new int[datasLength];
		Marshal.Copy(datasPtr, arrayData, 0, datasLength);

		arrayDouble = new double[doublesLength];
		Marshal.Copy(doublesPtr, arrayDouble, 0, doublesLength);

		arrayInt = new int[intsLength];
		Marshal.Copy(intsPtr, arrayInt, 0, intsLength);

		int curD = 0;
		int curI = 0;
		for (int n = 0; n < datasLength; n+=2)
		{
			double[] curDoubles = new double[arrayData[n]];
			for (int d = 0; d < curDoubles.Length; d++, curD++)
			{
				curDoubles[d] = arrayDouble[curD];
			}
			int[] curInts = new int[arrayData[n+1]];
			for (int i = 0; i < curInts.Length; i++, curI++)
			{
				curInts[i] = arrayInt[curI];
			}

			listMyMesh.Add(new(curDoubles, curInts));
		}
		

		ClearExtern(this);
		datasLength = 0;
		datasPtr = IntPtr.Zero;
		doublesLength = 0;
		doublesPtr = IntPtr.Zero;
		intsLength = 0;
		intsPtr = IntPtr.Zero;

		return listMyMesh.Count > 0;
	}

	private void ClearLocal()
	{
		if (doublesPtr != IntPtr.Zero)
		{
			Marshal.FreeHGlobal(doublesPtr);
			doublesPtr = IntPtr.Zero;
		}

		if (intsPtr != IntPtr.Zero)
		{
			Marshal.FreeHGlobal(intsPtr);
			intsPtr = IntPtr.Zero;
		}

		if (datasPtr != IntPtr.Zero)
		{
			Marshal.FreeHGlobal(datasPtr);
			datasPtr = IntPtr.Zero;
		}
	}

	[DllImport(MyMesh.pathDll, CallingConvention = CallingConvention.Cdecl)]
	private static extern int MultiplyExtern(MyMeshList one, out MyMeshList output);

	[DllImport(MyMesh.pathDll, CallingConvention = CallingConvention.Cdecl)]
	private static extern void ClearExtern(MyMeshList input);
}
