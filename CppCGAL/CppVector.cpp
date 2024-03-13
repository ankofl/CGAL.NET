#include <iostream>
#include "MeshStruct.h"

extern "C" {
	__declspec(dllexport) int ProcessMesh(
		MeshStruct mesh,
		MeshStruct* meshOut )
	{
		meshOut->IndexesCount = mesh.IndexesCount;
		meshOut->Indexes = new int[meshOut->IndexesCount];
		for (int i = 0; i < meshOut->IndexesCount; i++) {
			meshOut->Indexes[i] = mesh.Indexes[i];
			//std::cout << meshOut->Indexes[i] << "\n";
		}

		meshOut->FloatsCount = mesh.FloatsCount;
		meshOut->Floats = new float[meshOut->FloatsCount];
		for (int i = 0; i < meshOut->FloatsCount; i++) {
			meshOut->Floats[i] = mesh.Floats[i]*3;
			//std::cout << meshOut->Floats[i] << "\n";
		}

		// ¬аш код обработки данных
		return 0;
	}

	__declspec(dllexport) void ReleaseMesh(float* ptrFloat, int* ptrInt) {
		if (ptrFloat != nullptr) {
			delete[] ptrFloat;
			ptrFloat = nullptr; // Ќе об€зательно, но хороша€ практика обнулить указатель после освобождени€ пам€ти
		}

		if (ptrInt != nullptr) {
			delete[] ptrInt;
			ptrInt = nullptr; // “о же самое дл€ ptrInt
		}
	}
}

extern "C" {
    __declspec(dllexport) void GetFloatArray(float** array, int* size) {
        *size = 2;

        *array = new float[*size];

        // «аполнение массива данными (в данном случае - просто увеличение значений)
        for (int i = 0; i < *size; ++i) {
            (*array)[i] = i * 1.5f;
        }
    }
}