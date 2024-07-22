using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL.Structs
{
    [StructLayout(LayoutKind.Sequential)]
    public struct SoupStruct
    {
        private nint PtrFloats;
        private nint PtrIndexes;

        private int CountFloats;
        private int CountIndexes;

        [NonSerialized]
        private float[] Floats;
        [NonSerialized]
        private int[] Indexes;

        public SoupStruct(float[] floats, int[] indexes)
        {
            Floats = floats;
            Indexes = indexes;
        }

        [DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern void ReleaseSoup(nint ptrFloats, nint ptrIndexes);

        [DllImport(CallerCGAL.pathDll, CallingConvention = CallingConvention.Cdecl)]
        private static extern int RefineSoup(SoupStruct soupStruct, out SoupStruct soupStructResult);

        public SoupStruct Refine()
        {
            PtrCreate();
            int code = RefineSoup(this, out SoupStruct soupStructResult);
            soupStructResult.PtrLoadAndClear();
            PtrClear();
            return soupStructResult;
        }

        private void PtrLoadAndClear()
        {
            if (PtrFloats != nint.Zero && PtrIndexes != nint.Zero)
            {
                Floats = new float[CountFloats];
                Marshal.Copy(PtrFloats, Floats, 0, CountFloats);

                Indexes = new int[CountIndexes];
                Marshal.Copy(PtrIndexes, Indexes, 0, CountIndexes);

                PtrClear();
            }
            else
            {
                throw new Exception("Fail PtrLoad");
            }
        }

        private void PtrCreate()
        {
            if (PtrFloats == nint.Zero && PtrIndexes == nint.Zero)
            {
                CountFloats = Floats.Length;
                CountIndexes = Indexes.Length;

                PtrFloats = Marshal.AllocCoTaskMem(sizeof(float) * CountFloats);
                Marshal.Copy(Floats, 0, PtrFloats, CountFloats);

                PtrIndexes = Marshal.AllocCoTaskMem(sizeof(int) * CountIndexes);
                Marshal.Copy(Indexes, 0, PtrIndexes, CountIndexes);
            }
            else
            {
                throw new Exception("Fail PtrCreate");
            }
        }

        private void PtrClear()
        {
            if (PtrFloats != nint.Zero && PtrIndexes != nint.Zero)
            {
                ReleaseSoup(PtrFloats, PtrIndexes);
                PtrFloats = nint.Zero;
                PtrIndexes = nint.Zero;
            }
            else
            {
                throw new Exception("Fail Ptr Clear");
            }
        }

        public static SoupStruct Sample()
        {
            return new SoupStruct(
                [0.3f, 0.3f, 0.5f,
            1, 0, 0,
            0, 1, 0,
            -1, 0, 0,
            0, -1, 0,
            0, 1, 0,
            0, -2, 0],

                [0, 1, 2,
            0,0,0,
            0,1,4,
            0,4,1,
            0,3,5,
            0,3,0,
            0,3,4,
            0,1,2,3,4,3,2,1,]);
        }
    }
}
