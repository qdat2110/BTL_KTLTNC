#pragma once
#include <vector>
#include <memory>
#include <string>
#include "raylib.h"
#include "Entity.hpp"
#include "TauVuTru.hpp"
#include "alien.hpp"
#include "VatCan.hpp"
#include "TauBiAn.hpp"
#include "laser.hpp"
using namespace std;
struct HatBui
{
    Vector2 viTri;
    Vector2 tocDo;
    float banKinh;
    float doMo;
    Color mauSac;
    bool hoatDong;
};

class TroChoi
{
public:
    TroChoi();
    ~TroChoi();
    void Ve();
    void CapNhat();
    void XuLyDauVao();
    void DatLai();
    bool dangChay;
    bool daThang = false;
    int soMang;
    int diemSo;
    int diemCao;
    Music nhacNen;
     vector< unique_ptr<ThucThe>> danhSachThucThe;

private:
    void KhoiTaoTroChoi();
    void KetThucTroChoi();
    void KiemTraVaCham();
    void DonDepThucThe();
    void TaoVatCan();
    void TaoNguoiNgoaiHanh();
    void XoaLaserKhongHoatDong();
    void DiChuyenNguoiNgoaiHanh();
    void DiChuyenXuongNguoiNgoaiHanh(int khoangCach);
    void NguoiNgoaiHanhBan();
    void KiemTraDiemCao();
    void LuuDiemCaoVaoFile(int diemCao);
    int DocDiemCaoTuFile();
    TauVuTru tauVuTru;
    TauBiAn tauBiAn;
     vector<NguoiNgoaiHanh> danhSachNguoiNgoaiHanh;
     vector<VatCan> danhSachVatCan;
     vector<TiaLaser> laserNguoiNgoaiHanh;
    int huongNguoiNgoaiHanh;
    float thoiGianBanCuoi;
    constexpr static float khoangCachBan = 0.35f;
    float khoangCachXuatHienTauBiAn;
    float thoiGianXuatHienCuoi;
    Sound amThanhNo;
    static const int SO_HAT_TOI_DA = 1000;
    HatBui khoHatBui[SO_HAT_TOI_DA];
    void KhoiTaoHatBui();
    void CapNhatHatBui();
    void VeHatBui();
    void PhatNoVuNo(Vector2 viTri, Color mauSac);
};
