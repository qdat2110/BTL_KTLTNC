#include <raylib.h>
#include "game.hpp"
#include <string>
using namespace std;
string DinhDangSoCoSoKhong(int soNguyen, int doRong)
{
    string chuoiSo = to_string(soNguyen);
    int soKhongDem = doRong - (int)chuoiSo.length();
    return string(max(0, soKhongDem), '0') + chuoiSo;
}

int main()
{
    // --- 1. KHỞI TẠO CƠ BẢN ---
    const int leDuong = 50;
    const int chieuRongCuaSo = 750;
    const int chieuCaoCuaSo = 700;

    InitWindow(chieuRongCuaSo + leDuong, chieuCaoCuaSo + 2 * leDuong, "C++ I LOVE MISS DUNG - OOP Edition");
    InitAudioDevice();
    SetTargetFPS(60);

    // --- 2. LOAD TÀI NGUYÊN CHUNG ---
    Font phongChu = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D anhNen = LoadTexture("Graphics/anhh.jpg");
    Texture2D anhTauVuTru = LoadTexture("Graphics/spaceship.png"); // Dùng để vẽ UI mạng sống

    // Load texture cho Người Ngoài Hành Tinh TRƯỚC KHI tạo TroChoi
    NguoiNgoaiHanh::anhNguoiNgoaiHanh[0] = LoadTexture("Graphics/alien_1.png");
    NguoiNgoaiHanh::anhNguoiNgoaiHanh[1] = LoadTexture("Graphics/alien_2.png");
    NguoiNgoaiHanh::anhNguoiNgoaiHanh[2] = LoadTexture("Graphics/alien_3.png");

    // --- 3. KHỞI TẠO ĐỐI TƯỢNG TRÒ CHƠI ---
    TroChoi troChoi;

    // --- 4. VÒNG LẶP GAME ---
    while (!WindowShouldClose())
    {
        // Cập nhật
        UpdateMusicStream(troChoi.nhacNen);
        troChoi.XuLyDauVao();
        troChoi.CapNhat();

        // Vẽ
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(anhNen,
                       {0, 0, (float)anhNen.width, (float)anhNen.height},
                       {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
                       {0, 0}, 0, WHITE);

        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, YELLOW);
        DrawLineEx({25, 730}, {775, 730}, 3, GRAY);

        if (troChoi.dangChay)
        {
            DrawTextEx(phongChu, "NHOM 7", {570, 740}, 34, 2, WHITE);
        }
        else if (troChoi.daThang)
        {
            DrawTextEx(phongChu, "CHIEN THANG!", {570, 740}, 34, 2, GREEN);
            DrawTextEx(phongChu, "CHIEN THANG!", {250, 350}, 50, 2, GREEN);
            DrawTextEx(phongChu, "NHAN ENTER DE CHOI LAI", {190, 510}, 30, 2, WHITE);
        }
        else
        {
            DrawTextEx(phongChu, "THUA CUOC", {570, 740}, 34, 2, RED);
            DrawTextEx(phongChu, "NHAN ENTER DE CHOI LAI", {190, 510}, 34, 2, WHITE);
        }

        // Vẽ số mạng còn lại (UI)
        float viTriMang = 50.0f;
        for (int i = 0; i < troChoi.soMang; i++)
        {
            DrawTextureV(anhTauVuTru, {viTriMang, 745}, WHITE);
            viTriMang += 50.0f;
        }

        // Vẽ Điểm Số & Điểm Cao
        DrawTextEx(phongChu, "DIEM SO", {55, 15}, 34, 2, WHITE);
        DrawTextEx(phongChu, DinhDangSoCoSoKhong(troChoi.diemSo, 5).c_str(), {50, 40}, 34, 2, WHITE);

        DrawTextEx(phongChu, "DIEM CAO", {550, 15}, 34, 2, WHITE);
        DrawTextEx(phongChu, DinhDangSoCoSoKhong(troChoi.diemCao, 5).c_str(), {570, 40}, 34, 2, WHITE);

        // Gọi hàm Ve của TroChoi
        troChoi.Ve();

        EndDrawing();
    }

    // --- 5. GIẢI PHÓNG TÀI NGUYÊN ---
    UnloadTexture(anhNen);
    UnloadTexture(anhTauVuTru);
    UnloadFont(phongChu);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
