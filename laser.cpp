#include "laser.hpp"
using namespace std;
TiaLaser::TiaLaser(Vector2 viTri, int tocDo)
{
    this->viTri = viTri;
    this->tocDo = tocDo;
    this->hoatDong = true;
}

void TiaLaser::CapNhat()
{
    if (hoatDong)
    {
        // Di chuyển đạn theo trục Y
        viTri.y += tocDo;

        // Tự động vô hiệu hóa nếu đạn bay ra khỏi màn hình
        if (viTri.y > GetScreenHeight() || viTri.y < 0)
        {
            hoatDong = false;
        }
    }
}

void TiaLaser::Ve()
{
    if (hoatDong)
    {
        // Vẽ tia laser là một hình chữ nhật nhỏ màu xanh da trời
        DrawRectangleV(viTri, {4, 15}, SKYBLUE);
    }
}

Rectangle TiaLaser::LayHinhChuNhat()
{
    // Trả về khung va chạm cho tia đạn
    return {viTri.x, viTri.y, 4, 15};
}

string TiaLaser::LayLoai()
{
    return "TiaLaser";
}
