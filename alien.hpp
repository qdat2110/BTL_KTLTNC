#pragma once
#include <string>
#include "raylib.h"
#include "Entity.hpp"
using namespace std;
class NguoiNgoaiHanh : public ThucThe
{
public:
    int loai;
    static Texture2D anhNguoiNgoaiHanh[3];
    NguoiNgoaiHanh(int loai, Vector2 viTri);
    void CapNhat() override;
    void Ve() override;
    Rectangle LayHinhChuNhat() override;
    string LayLoai() override;
    static void GiaiPhongAnh();
};
