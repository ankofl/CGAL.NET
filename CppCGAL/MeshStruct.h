#pragma once

struct MeshStruct {
    float* Points;
    int* Indexes;
    int PointsCount;  // Добавлено для хранения длины массива Points
    int IndexesCount; // Добавлено для хранения длины массива Indexes
};
