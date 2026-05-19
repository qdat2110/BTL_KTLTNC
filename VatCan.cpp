#include "VatCan.hpp"

// Định nghĩa lưới cấu tạo của vật cản (1 là có gạch, 0 là trống)
std::vector<std::vector<int>> VatCan::luoi = {
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}};

VatCan::VatCan(Vector2 viTri)
{
    this->viTri = viTri;

    for (int hang = 0; hang < (int)luoi.size(); hang++)
    {
        for (int cot = 0; cot < (int)luoi[hang].size(); cot++)
        {
            if (luoi[hang][cot] == 1)
            {
                float x = viTri.x + cot * 3;
                float y = viTri.y + hang * 3;
                danhSachKhoi.push_back(std::make_unique<KhoiGach>(Vector2{x, y}));
            }
        }
    }
}

void VatCan::Ve()
{
    for (auto &khoi : danhSachKhoi)
    {
        khoi->Ve();
    }
}
