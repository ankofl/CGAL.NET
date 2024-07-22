using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace NetCGAL.Structs
{
	[StructLayout(LayoutKind.Sequential)]
	public struct MeshStruct
    {
        private nint FloatsPtr;
        private nint IndexesPtr;

        private int FloatsLength;
        private int IndexesLength;

        [NonSerialized]
        private float[] Floats;
        [NonSerialized]
        private int[] Indexes;

        public MeshStruct(float[] floats, int[] indexes)
        {
            Floats = floats;
            Indexes = indexes;
        }

        [DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern void ReleaseMesh(nint ptrFloats, nint ptrIndexes);

        [DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern int ProcessMesh(MeshStruct mesh, out MeshStruct meshOut);

        public MeshStruct Multiply()
        {
            PtrCreate();
            int code = ProcessMesh(this, out MeshStruct meshOut);
            meshOut.PtrLoadAndClear();
            PtrClear();
            return meshOut;
        }

        private void PtrClear()
        {
            if (FloatsPtr != nint.Zero && IndexesPtr != nint.Zero)
            {
                ReleaseMesh(FloatsPtr, IndexesPtr);
                FloatsPtr = nint.Zero;
                IndexesPtr = nint.Zero;
            }
            else
            {
                throw new Exception("Failed Ptr Clear");
            }
        }

        private void PtrCreate()
        {
            if (FloatsPtr == nint.Zero && IndexesPtr == nint.Zero)
            {
                FloatsLength = Floats.Length;
                IndexesLength = Indexes.Length;

                FloatsPtr = Marshal.AllocCoTaskMem(sizeof(float) * FloatsLength);
                Marshal.Copy(Floats, 0, FloatsPtr, FloatsLength);

                IndexesPtr = Marshal.AllocCoTaskMem(sizeof(int) * IndexesLength);
                Marshal.Copy(Indexes, 0, IndexesPtr, IndexesLength);
            }
            else
            {
                throw new Exception("Fail PtrCreate");
            }
        }

        private void PtrLoadAndClear()
        {
            if (FloatsPtr != nint.Zero && IndexesPtr != nint.Zero)
            {
                Floats = new float[FloatsLength];
                Marshal.Copy(FloatsPtr, Floats, 0, FloatsLength);

                Indexes = new int[IndexesLength];
                Marshal.Copy(IndexesPtr, Indexes, 0, IndexesLength);

                PtrClear();
            }
            else
            {
                throw new Exception("Failed Ptr Load");
            }
        }
    }
}
