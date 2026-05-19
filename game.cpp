#include "game.hpp"
#include <iostream>
#include <fstream>
#include <raymath.h>
using namespace std;
TroChoi::TroChoi()
{
    nhacNen = LoadMusicStream("Sounds/music.ogg");
    amThanhNo = LoadSound("Sounds/explosion.ogg");
    PlayMusicStream(nhacNen);
    // Khởi tạo kho hạt bụi
    KhoiTaoHatBui();

    KhoiTaoTroChoi();
}

TroChoi::~TroChoi()
{
    NguoiNgoaiHanh::GiaiPhongAnh();
    UnloadMusicStream(nhacNen);
    UnloadSound(amThanhNo);
}

void TroChoi::KhoiTaoHatBui()
{
    for (int i = 0; i < SO_HAT_TOI_DA; i++)
    {
        khoHatBui[i].hoatDong = false; // Ban đầu tất cả hạt đều tắt
    }
}

void TroChoi::PhatNoVuNo(Vector2 viTri, Color mauGoc)
{
    int soHat = GetRandomValue(25, 40); // Tăng số lượng hạt để vụ nổ dày hơn
    for (int i = 0; i < SO_HAT_TOI_DA && soHat > 0; i++)
    {
        if (!khoHatBui[i].hoatDong)
        {
            khoHatBui[i].hoatDong = true;

            // Thêm độ lệch vị trí để nổ không tụ lại 1 điểm
            khoHatBui[i].viTri = {
                viTri.x + GetRandomValue(-2, 2),
                viTri.y + GetRandomValue(-2, 2)};

            float goc = (float)GetRandomValue(0, 360) * DEG2RAD;
            float tocDoManh = (float)GetRandomValue(20, 60) / 10.0f;
            khoHatBui[i].tocDo = {cosf(goc) * tocDoManh, sinf(goc) * tocDoManh};

            khoHatBui[i].doMo = 1.0f;
            khoHatBui[i].banKinh = (float)GetRandomValue(15, 35) / 10.0f;

            // Quy luật màu vụ nổ
            int xacSuat = GetRandomValue(0, 100);
            if (xacSuat > 85)
            {
                khoHatBui[i].mauSac = WHITE;
            }
            else if (xacSuat > 50)
            {
                khoHatBui[i].mauSac = YELLOW; // Lửa mạnh
            }
            else if (xacSuat > 20)
            {
                khoHatBui[i].mauSac = ORANGE; // Lửa trung bình
            }
            else
            {
                khoHatBui[i].mauSac = RED; // Rìa vụ nổ
            }

            soHat--;
        }
    }
}

void TroChoi::CapNhatHatBui()
{
    for (int i = 0; i < SO_HAT_TOI_DA; i++)
    {
        if (khoHatBui[i].hoatDong)
        {
            khoHatBui[i].tocDo.x *= 0.88f;
            khoHatBui[i].tocDo.y *= 0.88f;

            khoHatBui[i].viTri.x += khoHatBui[i].tocDo.x;
            khoHatBui[i].viTri.y += khoHatBui[i].tocDo.y;

            // Thu nhỏ hạt dần theo thời gian
            khoHatBui[i].banKinh *= 0.97f;

            // Biến đổi màu sắc theo vòng đời
            if (khoHatBui[i].doMo < 0.3f)
            {
                khoHatBui[i].mauSac = GRAY;
            }
            else if (khoHatBui[i].doMo < 0.6f)
            {
                khoHatBui[i].mauSac.r = (unsigned char)(khoHatBui[i].mauSac.r * 0.95f);
                khoHatBui[i].mauSac.g = (unsigned char)(khoHatBui[i].mauSac.g * 0.8f);
            }

            khoHatBui[i].doMo -= 0.04f;
            if (khoHatBui[i].doMo <= 0)
                khoHatBui[i].hoatDong = false;
        }
    }
}

void TroChoi::VeHatBui()
{
    // BLEND_ADDITIVE giúp các màu cộng dồn tạo ra màu trắng rực ở tâm vụ nổ
    BeginBlendMode(BLEND_ADDITIVE);

    for (int i = 0; i < SO_HAT_TOI_DA; i++)
    {
        if (khoHatBui[i].hoatDong)
        {
            // Vẽ lớp hào quang - Rộng và mờ
            DrawCircleV(khoHatBui[i].viTri, khoHatBui[i].banKinh * 2.5f,
                        Fade(khoHatBui[i].mauSac, khoHatBui[i].doMo * 0.2f));

            // Vẽ lõi hạt - Đặc và sáng
            DrawCircleV(khoHatBui[i].viTri, khoHatBui[i].banKinh,
                        Fade(khoHatBui[i].mauSac, khoHatBui[i].doMo));
        }
    }

    EndBlendMode();
}

void TroChoi::CapNhat()
{
    if (dangChay)
    {
        double thoiGianHienTai = GetTime();
        if (thoiGianHienTai - thoiGianXuatHienCuoi > khoangCachXuatHienTauBiAn)
        {
            tauBiAn.XuatHien();
            thoiGianXuatHienCuoi = GetTime();
            khoangCachXuatHienTauBiAn = GetRandomValue(10, 20);
        }

        for (auto &laser : tauVuTru.danhSachLaser)
        {
            laser.CapNhat();
        }

        DiChuyenNguoiNgoaiHanh();

        NguoiNgoaiHanhBan();

        for (auto &laser : laserNguoiNgoaiHanh)
        {
            laser.CapNhat();
        }

        XoaLaserKhongHoatDong();

        tauBiAn.CapNhat();
        CapNhatHatBui();

        KiemTraVaCham();

        // Kiểm tra nếu hết người ngoài hành tinh thì thắng
        if (danhSachNguoiNgoaiHanh.empty())
        {
            daThang = true;
            dangChay = false;
        }
    }
    else
    {
        if (IsKeyDown(KEY_ENTER))
        {
            DatLai();
            KhoiTaoTroChoi();
        }
    }
}

void TroChoi::Ve()
{
    // Vẽ quầng sáng hắt (Glow) cho tàu vũ trụ
    float tamX = tauVuTru.viTri.x + tauVuTru.LayHinhChuNhat().width / 2.0f;
    float tamY = tauVuTru.viTri.y + tauVuTru.LayHinhChuNhat().height;

    DrawCircleGradient((int)tamX, (int)tamY, 30.0f, Fade(ORANGE, 0.2f), (Color){0, 0, 0, 0});
    tauVuTru.Ve();

    for (auto &laser : tauVuTru.danhSachLaser)
    {
        laser.Ve();
    }

    for (auto &vatCan : danhSachVatCan)
    {
        vatCan.Ve();
    }

    for (auto &nguoiNgoaiHanh : danhSachNguoiNgoaiHanh)
    {
        nguoiNgoaiHanh.Ve();
    }

    for (auto &laser : laserNguoiNgoaiHanh)
    {
        laser.Ve();
    }

    tauBiAn.Ve();
    VeHatBui();
}

void TroChoi::XuLyDauVao()
{
    if (dangChay)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            tauVuTru.DiChuyenTrai();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            tauVuTru.DiChuyenPhai();
        }
        else if (IsKeyPressed(KEY_SPACE))
        {
            tauVuTru.BanLaser();
        }
    }
}

void TroChoi::XoaLaserKhongHoatDong()
{
    for (auto it = tauVuTru.danhSachLaser.begin(); it != tauVuTru.danhSachLaser.end();)
    {
        if (!it->hoatDong)
        {
            it = tauVuTru.danhSachLaser.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = laserNguoiNgoaiHanh.begin(); it != laserNguoiNgoaiHanh.end();)
    {
        if (!it->hoatDong)
        {
            it = laserNguoiNgoaiHanh.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void TroChoi::TaoVatCan()
{
    danhSachVatCan.clear();
    int chieuRongVatCan = VatCan::luoi[0].size() * 3;
    float khoangCach = (GetScreenWidth() - (4 * chieuRongVatCan)) / 5.0f;

    for (int i = 0; i < 4; i++)
    {
        float doLechX = (i + 1) * khoangCach + i * chieuRongVatCan;
        danhSachVatCan.emplace_back(Vector2{doLechX, (float)GetScreenHeight() - 200});
    }
}

void TroChoi::TaoNguoiNgoaiHanh()
{
    danhSachNguoiNgoaiHanh.clear();
    for (int hang = 0; hang < 5; hang++)
    {
        for (int cot = 0; cot < 11; cot++)
        {
            int loaiNguoiNgoaiHanh;
            if (hang == 0)
            {
                loaiNguoiNgoaiHanh = 3; // Hàng trên cùng là loại 3
            }
            else if (hang == 1 || hang == 2)
            {
                loaiNguoiNgoaiHanh = 2; // Hai hàng tiếp theo là loại 2
            }
            else
            {
                loaiNguoiNgoaiHanh = 1; // Các hàng còn lại là loại 1
            }

            float x = 75 + cot * 55;
            float y = 110 + hang * 55;

            danhSachNguoiNgoaiHanh.push_back(NguoiNgoaiHanh(loaiNguoiNgoaiHanh, {x, y}));
        }
    }
}

void TroChoi::DiChuyenNguoiNgoaiHanh()
{
    bool canDiXuong = false;

    for (auto &nguoiNgoaiHanh : danhSachNguoiNgoaiHanh)
    {
        if (nguoiNgoaiHanh.viTri.x + nguoiNgoaiHanh.anhNguoiNgoaiHanh[nguoiNgoaiHanh.loai - 1].width > GetScreenWidth() - 25)
        {
            huongNguoiNgoaiHanh = -1;
            canDiXuong = true;
            break;
        }
        if (nguoiNgoaiHanh.viTri.x < 25)
        {
            huongNguoiNgoaiHanh = 1;
            canDiXuong = true;
            break;
        }
    }

    if (canDiXuong)
        DiChuyenXuongNguoiNgoaiHanh(4);

    for (auto &nguoiNgoaiHanh : danhSachNguoiNgoaiHanh)
    {
        nguoiNgoaiHanh.viTri.x += huongNguoiNgoaiHanh * 2;
    }
}

void TroChoi::DiChuyenXuongNguoiNgoaiHanh(int khoangCach)
{
    for (auto &nguoiNgoaiHanh : danhSachNguoiNgoaiHanh)
    {
        nguoiNgoaiHanh.viTri.y += khoangCach;
    }
}

void TroChoi::NguoiNgoaiHanhBan()
{
    double thoiGianHienTai = GetTime();
    if (thoiGianHienTai - thoiGianBanCuoi >= khoangCachBan && !danhSachNguoiNgoaiHanh.empty())
    {
        int chiSoNgauNhien = GetRandomValue(0, danhSachNguoiNgoaiHanh.size() - 1);
        NguoiNgoaiHanh &nguoiNgoaiHanh = danhSachNguoiNgoaiHanh[chiSoNgauNhien];
        laserNguoiNgoaiHanh.push_back(TiaLaser(
            {nguoiNgoaiHanh.viTri.x + nguoiNgoaiHanh.anhNguoiNgoaiHanh[nguoiNgoaiHanh.loai - 1].width / 2,
             nguoiNgoaiHanh.viTri.y + nguoiNgoaiHanh.anhNguoiNgoaiHanh[nguoiNgoaiHanh.loai - 1].height},
            6));
        thoiGianBanCuoi = GetTime();
    }
}

void TroChoi::KiemTraVaCham()
{
    // Laser của tàu vũ trụ
    for (auto &laser : tauVuTru.danhSachLaser)
    {
        auto it = danhSachNguoiNgoaiHanh.begin();
        while (it != danhSachNguoiNgoaiHanh.end())
        {
            if (CheckCollisionRecs(it->LayHinhChuNhat(), laser.LayHinhChuNhat()))
            {
                PlaySound(amThanhNo);
                Color mauNguoiNgoaiHanh = WHITE;
                if (it->loai == 1)
                {
                    diemSo += 100;
                    mauNguoiNgoaiHanh = RED;
                }
                else if (it->loai == 2)
                {
                    diemSo += 200;
                    mauNguoiNgoaiHanh = ORANGE;
                }
                else if (it->loai == 3)
                {
                    diemSo += 300;
                    mauNguoiNgoaiHanh = YELLOW;
                }
                Vector2 viTriNo = {it->viTri.x + it->LayHinhChuNhat().width / 2,
                                   it->viTri.y + it->LayHinhChuNhat().height / 2};
                PhatNoVuNo(viTriNo, mauNguoiNgoaiHanh);
                KiemTraDiemCao();

                it = danhSachNguoiNgoaiHanh.erase(it);
                laser.hoatDong = false;
            }
            else
            {
                ++it;
            }
        }

        for (auto &vatCan : danhSachVatCan)
        {
            auto it = vatCan.danhSachKhoi.begin();
            while (it != vatCan.danhSachKhoi.end())
            {
                if (CheckCollisionRecs((*it)->LayHinhChuNhat(), laser.LayHinhChuNhat()))
                {
                    it = vatCan.danhSachKhoi.erase(it);
                    laser.hoatDong = false;
                }
                else
                    ++it;
            }
        }

        if (CheckCollisionRecs(tauBiAn.LayHinhChuNhat(), laser.LayHinhChuNhat()))
        {
            tauBiAn.hoatDong = false;
            laser.hoatDong = false;
            diemSo += 500;
            Vector2 viTriNo = {tauBiAn.viTri.x + tauBiAn.LayHinhChuNhat().width / 2,
                               tauBiAn.viTri.y + tauBiAn.LayHinhChuNhat().height / 2};
            PhatNoVuNo(viTriNo, MAGENTA);
            KiemTraDiemCao();
            PlaySound(amThanhNo);
        }
    }

    // Laser của người ngoài hành tinh
    for (auto &laser : laserNguoiNgoaiHanh)
    {
        if (CheckCollisionRecs(laser.LayHinhChuNhat(), tauVuTru.LayHinhChuNhat()))
        {
            laser.hoatDong = false;
            soMang--;
            if (soMang == 0)
            {
                KetThucTroChoi();
            }
        }

        for (auto &vatCan : danhSachVatCan)
        {
            auto it = vatCan.danhSachKhoi.begin();
            while (it != vatCan.danhSachKhoi.end())
            {
                if (CheckCollisionRecs((*it)->LayHinhChuNhat(), laser.LayHinhChuNhat()))
                {
                    it = vatCan.danhSachKhoi.erase(it);
                    laser.hoatDong = false;
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    // Người ngoài hành tinh va chạm với vật cản và tàu
    for (auto &nguoiNgoaiHanh : danhSachNguoiNgoaiHanh)
    {
        for (auto &vatCan : danhSachVatCan)
        {
            auto it = vatCan.danhSachKhoi.begin();
            while (it != vatCan.danhSachKhoi.end())
            {
                if (CheckCollisionRecs((*it)->LayHinhChuNhat(), nguoiNgoaiHanh.LayHinhChuNhat()))
                {
                    it = vatCan.danhSachKhoi.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

        if (CheckCollisionRecs(nguoiNgoaiHanh.LayHinhChuNhat(), tauVuTru.LayHinhChuNhat()))
        {
            KetThucTroChoi();
        }
    }
}

void TroChoi::KetThucTroChoi()
{
    dangChay = false;
}

void TroChoi::KhoiTaoTroChoi()
{
    TaoVatCan();
    TaoNguoiNgoaiHanh();
    huongNguoiNgoaiHanh = 1;
    thoiGianBanCuoi = 0.0;
    thoiGianXuatHienCuoi = 0.0;
    soMang = 3;
    diemSo = 0;
    diemCao = DocDiemCaoTuFile();
    dangChay = true;
    khoangCachXuatHienTauBiAn = GetRandomValue(10, 20);
    daThang = false;
}

void TroChoi::KiemTraDiemCao()
{
    if (diemSo > diemCao)
    {
        diemCao = diemSo;
        LuuDiemCaoVaoFile(diemCao);
    }
}

void TroChoi::LuuDiemCaoVaoFile(int diemCao)
{
    ofstream fileDiemCao("highscore.txt");
    if (fileDiemCao.is_open())
    {
        fileDiemCao << diemCao;
        fileDiemCao.close();
    }
    else
    {
        cerr << "Khong the luu diem cao vao file" << endl;
    }
}

int TroChoi::DocDiemCaoTuFile()
{
    int diemCaoDaDoc = 0;
    ifstream fileDiemCao("highscore.txt");
    if (fileDiemCao.is_open())
    {
        fileDiemCao >> diemCaoDaDoc;
        fileDiemCao.close();
    }
    else
    {
        cerr << "Khong the doc diem cao tu file." << endl;
    }
    return diemCaoDaDoc;
}

void TroChoi::DatLai()
{
    tauVuTru.DatLai();
    danhSachNguoiNgoaiHanh.clear();
    laserNguoiNgoaiHanh.clear();
    danhSachVatCan.clear();
}
