#pragma once
#include "Entity.hpp"
using namespace std;
class TauBiAn : public ThucThe
{
private:
    Texture2D anh;
    int tocDo;

public:
    TauBiAn();
    ~TauBiAn() override;
    void CapNhat() override;
    void Ve() override;
    Rectangle LayHinhChuNhat() override;
    string LayLoai() override;
    void XuatHien();
};
