#pragma once

struct MeshStruct {
    float* Floats;
    int* Indexes;

    int FloatsCount;  // Добавлено для хранения длины массива Floats
    int IndexesCount; // Добавлено для хранения длины массива Indexes
};
