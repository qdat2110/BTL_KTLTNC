#pragma once
#include <vector>
#include <memory>
#include "KhoiGach.hpp"

class VatCan {
public:
    VatCan(Vector2 viTri);
    void Ve();
    Vector2 viTri;
    std::vector<std::unique_ptr<KhoiGach>> danhSachKhoi;
    static std::vector<std::vector<int>> luoi;
};
