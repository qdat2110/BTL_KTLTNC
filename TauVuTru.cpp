#include "TauVuTru.hpp"
#include <memory>
#include "laser.hpp"

TauVuTru::TauVuTru()
{
    anh = LoadTexture("Graphics/spaceship.png");
    amThanhLaser = LoadSound("Sounds/laser.ogg");
    DatLai();
}

TauVuTru::~TauVuTru()
{
    UnloadTexture(anh);
    UnloadSound(amThanhLaser);
}

void TauVuTru::DatLai()
{
    viTri = {(float)GetScreenWidth() / 2 - anh.width / 2, 730 - (float)anh.height - 10};
    hoatDong = true;
    thoiGianBanCuoi = 0.0;
}

void TauVuTru::CapNhat()
{
    // Xử lý di chuyển trực tiếp trong CapNhat
    if (IsKeyDown(KEY_LEFT) && viTri.x > 25)
    {
        viTri.x -= 7.0f;
    }
    if (IsKeyDown(KEY_RIGHT) && viTri.x < GetScreenWidth() - anh.width - 25)
    {
        viTri.x += 7.0f;
    }
}

void TauVuTru::Ve()
{
    if (hoatDong)
    {
        DrawTextureV(anh, viTri, WHITE);
    }
}

void TauVuTru::BanLaser(std::vector<std::unique_ptr<ThucThe>> &danhSachThucThe)
{
    if (GetTime() - thoiGianBanCuoi >= 0.35)
    {
        Vector2 viTriLaser = {viTri.x + anh.width / 2 - 2, viTri.y};
        danhSachThucThe.push_back(std::make_unique<TiaLaser>(viTriLaser, -6));
        PlaySound(amThanhLaser);
        thoiGianBanCuoi = GetTime();
    }
}

Rectangle TauVuTru::LayHinhChuNhat()
{
    return {viTri.x, viTri.y, (float)anh.width, (float)anh.height};
}

string TauVuTru::LayLoai()
{
    return "TauVuTru";
}

void TauVuTru::DiChuyenTrai()
{
    viTri.x -= 7;
    if (viTri.x < 25)
        viTri.x = 25;
}

void TauVuTru::DiChuyenPhai()
{
    viTri.x += 7;
    if (viTri.x > GetScreenWidth() - anh.width - 25)
    {
        viTri.x = GetScreenWidth() - anh.width - 25;
    }
}

void TauVuTru::BanLaser()
{
    if (GetTime() - thoiGianBanCuoi >= 0.35)
    {
        Vector2 viTriLaser = {viTri.x + anh.width / 2 - 2, viTri.y};
        danhSachLaser.push_back(TiaLaser(viTriLaser, -6));
        PlaySound(amThanhLaser);
        thoiGianBanCuoi = GetTime();
    }
}
