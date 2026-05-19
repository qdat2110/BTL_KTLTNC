#pragma once
#include "Entity.hpp"
using namespace std;
class TiaLaser : public ThucThe {
private:
    int tocDo;
public:
    TiaLaser(Vector2 viTri, int tocDo);
    void CapNhat() override;
    void Ve() override;
    Rectangle LayHinhChuNhat() override;
    string LayLoai() override;
};
