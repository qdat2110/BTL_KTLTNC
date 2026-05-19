#include "KhoiGach.hpp"
using namespace std;
KhoiGach::KhoiGach(Vector2 viTri)
{
    this->viTri = viTri;
    this->hoatDong = true;
}

void KhoiGach::CapNhat()
{
}

void KhoiGach::Ve()
{
    if (hoatDong)
    {
        DrawRectangleV(viTri, {3, 3}, GRAY);
    }
}

Rectangle KhoiGach::LayHinhChuNhat()
{
    return {viTri.x, viTri.y, 3, 3};
}

string KhoiGach::LayLoai()
{
    return "KhoiGach";
}
