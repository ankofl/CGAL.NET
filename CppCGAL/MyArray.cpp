#include <iostream>
#include "MyArray.h"

extern "C" {
    __declspec(dllexport) void ClearMyArrayExtern(MyArray input) {
        if (input.floatsPtr != nullptr) {
            delete[] input.floatsPtr;
            input.floatsPtr = nullptr;
        }
    }

    __declspec(dllexport) int CrossExtern(MyArray input, MyArray* output) {
        if (output == nullptr) {
            return -1; // Ошибка, не удалось выделить память
        }

        output->floatsLength = input.floatsLength * 2;
        output->floatsPtr = new float[output->floatsLength];
        if (output->floatsPtr == nullptr) {
            delete[] output;
            return -2; // Ошибка, не удалось выделить память для массива
        }

        for (int i = 0; i < input.floatsLength; i++) {
            output->floatsPtr[i] = input.floatsPtr[i]*0.3f;
            output->floatsPtr[input.floatsLength + i] = input.floatsPtr[i]*0.6f;
        }

        return 0;
    }
}
