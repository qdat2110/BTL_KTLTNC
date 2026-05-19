#pragma once
#include <vector>
#include <memory>
#include <string>
#include "raylib.h"
#include "Entity.hpp"
#include "laser.hpp"

class TauVuTru : public ThucThe
{
public:
    TauVuTru();
    ~TauVuTru() override;
    void CapNhat() override;
    void Ve() override;
    Rectangle LayHinhChuNhat() override;
    string LayLoai() override;
    void DiChuyenTrai();
    void DiChuyenPhai();
    void BanLaser(std::vector<std::unique_ptr<ThucThe>> &danhSachThucThe);
    void DatLai();
    void BanLaser(); // Nạp chồng không tham số
    std::vector<TiaLaser> danhSachLaser; // Danh sách laser riêng của tàu
    Texture2D anh;
    double thoiGianBanCuoi;
    Sound amThanhLaser;
};
