using System;
using System.Runtime.InteropServices;

namespace NetCGAL.Structs
{
	[StructLayout(LayoutKind.Sequential)]
	public struct MyArray
	{
		private IntPtr floatsPtr;
		private int floatsLength;

		public MyArray(float[] floats)
		{
			this.floats = floats;
			Prepare();
		}
		private void Prepare()
		{
			floatsLength = floats.Length;
			floatsPtr = Marshal.AllocHGlobal(floats.Length * sizeof(float));
			Marshal.Copy(floats, 0, floatsPtr, floats.Length);
		}

		private void LoadAndClearExtern()
		{
			floats = new float[floatsLength];
			Marshal.Copy(floatsPtr, floats, 0, floatsLength);
			ClearMyArrayExtern(this);
		}

		[NonSerialized]
		private float[] floats;	

		public int Cross(out MyArray output)
		{
			int result = CrossExtern(this, out output);

			Marshal.FreeHGlobal(floatsPtr);

			output.LoadAndClearExtern();

			return result;
		}

		[DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern int CrossExtern(MyArray input, out MyArray output);

		[DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
		private static extern void ClearMyArrayExtern(MyArray input);
	}
}
