#pragma once
#include "Entity.hpp"
using namespace std;
class KhoiGach : public ThucThe {
public:
    KhoiGach(Vector2 viTri);
    void CapNhat() override;        // Khối gạch đứng yên
    void Ve() override;             // Vẽ hình vuông nhỏ
    Rectangle LayHinhChuNhat() override;   // Trả về va chạm
    string LayLoai() override;      // Trả về "KhoiGach"
};
