#include "TauBiAn.hpp"

TauBiAn::TauBiAn()
{
    anh = LoadTexture("Graphics/mystery.png");
    hoatDong = false; // Mặc định chưa xuất hiện
}

TauBiAn::~TauBiAn()
{
    UnloadTexture(anh);
}

void TauBiAn::XuatHien()
{
    // Ngẫu nhiên xuất hiện bên trái hoặc bên phải màn hình
    int phia = GetRandomValue(0, 1);
    if (phia == 0)
    {
        viTri = {0, 40};
        tocDo = 3;
    }
    else
    {
        viTri = {(float)GetScreenWidth(), 40};
        tocDo = -3;
    }
    hoatDong = true;
}

void TauBiAn::CapNhat()
{
    if (hoatDong)
    {
        viTri.x += tocDo;

        // Nếu đi ra khỏi màn hình thì tắt hoạt động
        if (viTri.x > GetScreenWidth() || viTri.x < 0 - anh.width)
        {
            hoatDong = false;
        }
    }
}

void TauBiAn::Ve()
{
    if (hoatDong)
    {
        DrawTextureV(anh, viTri, WHITE);
    }
}

Rectangle TauBiAn::LayHinhChuNhat()
{
    if (hoatDong)
    {
        return {viTri.x, viTri.y, (float)anh.width, (float)anh.height};
    }
    return {0, 0, 0, 0};
}

string TauBiAn::LayLoai()
{
    return "TauBiAn";
}
