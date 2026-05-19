#include "alien.hpp"
using namespace std;
Texture2D NguoiNgoaiHanh::anhNguoiNgoaiHanh[3] = {0};
NguoiNgoaiHanh::NguoiNgoaiHanh(int loai, Vector2 viTri)
{
    this->loai = loai;
    this->viTri = viTri;
    this->hoatDong = true;
}

void NguoiNgoaiHanh::CapNhat()
{
}

void NguoiNgoaiHanh::Ve()
{
    if (hoatDong)
    {
        if (loai >= 1 && loai <= 3)
        {
            DrawTextureV(anhNguoiNgoaiHanh[loai - 1], viTri, WHITE);
        }
    }
}

Rectangle NguoiNgoaiHanh::LayHinhChuNhat()
{
    if (loai >= 1 && loai <= 3)
    {
        return {viTri.x, viTri.y,
                (float)anhNguoiNgoaiHanh[loai - 1].width,
                (float)anhNguoiNgoaiHanh[loai - 1].height};
    }
    return {viTri.x, viTri.y, 0, 0};
}

string NguoiNgoaiHanh::LayLoai()
{
    return "NguoiNgoaiHanh";
}

void NguoiNgoaiHanh::GiaiPhongAnh()
{
    for (int i = 0; i < 3; i++)
    {
        if (anhNguoiNgoaiHanh[i].id > 0)
        {
            UnloadTexture(anhNguoiNgoaiHanh[i]);
        }
    }
}
