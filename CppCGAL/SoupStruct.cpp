#include <iostream>
#include "SoupStruct.h"
#include "Create.h"

extern "C" {
	__declspec(dllexport) int RefineSoup(SoupStruct soup, SoupStruct* soupOut) {
		bool d = false;

		int result = GoRefine(soup);
		SoupStruct soupRefined;

		soupOut->IndexesCount = soup.IndexesCount;
		soupOut->Indexes = new int[soupOut->IndexesCount];
		for (int i = 0; i < soup.IndexesCount; i++) {
			soupOut->Indexes[i] = soup.Indexes[i];
			if (d) {
				std::cout << soupOut->Indexes[i] << "\n";
			}
		}

		soupOut->FloatsCount = soup.FloatsCount;
		soupOut->Floats = new float[soupOut->FloatsCount];
		for (int i = 0; i < soup.FloatsCount; i++) {
			soupOut->Floats[i] = soup.Floats[i] * 3;

			if (d) {
				std::cout << soupOut->Floats[i] << "\n";
			}
		}

		return 0;
	}

	__declspec(dllexport) void ReleaseSoup(float* ptrFloat, int* ptrInt) {
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