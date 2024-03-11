#include <iostream>
#include "MeshStruct.h"

extern "C" {
	__declspec(dllexport) int ProcessMesh(
		float* arrayF, int lengthF,
		int* array, int length,

		float** array2, int* size,
		int** arrayIndex, int* sizeIndex,
		
		MeshStruct mesh)
	{

		for (int i = 0; i < length; ++i) {
			//std::cout << array[i] << " ";
		}

		for (int i = 0; i < lengthF; ++i) {
			//std::cout << arrayF[i] << " ";
		}

		//*********************
		*size = 10;

		*array2 = new float[*size];

		// Заполнение массива данными (в данном случае - просто увеличение значений)
		for (int i = 0; i < *size; ++i) {
			(*array2)[i] = i * 1.5f;
		}
		//*********************


		//*********************
		*sizeIndex = 10;

		*arrayIndex = new int[*sizeIndex];

		// Заполнение массива данными (в данном случае - просто увеличение значений)
		for (int i = 0; i < *sizeIndex; ++i) {
			(*arrayIndex)[i] = i * 1.5f;
		}
		//*********************

		std::cout << mesh.IndexesCount << " " << mesh.PointsCount;

		// Ваш код обработки данных
		return 0;
	}
}

extern "C" {
    __declspec(dllexport) void GetFloatArray(float** array, int* size) {
        *size = 2;

        *array = new float[*size];

        // Заполнение массива данными (в данном случае - просто увеличение значений)
        for (int i = 0; i < *size; ++i) {
            (*array)[i] = i * 1.5f;
        }
    }

    __declspec(dllexport) void ReleaseFloatArray(float* array) {
        delete[] array;
    }
}