#include <stdio.h>
#include <string.h>

typedef struct {
    int maSV;
    char ten[50];
    char lop[10];
    float diem;
} SinhVien;

SinhVien danhSachSV[100];
int soLuongSV = 0;

void hienThiMenu() {
    printf("========================================\n");
    printf("        HE THONG QUAN LY SINH VIEN      \n");
    printf("========================================\n");
    printf("         MENU QUAN LY SINH VIEN         \n");
    printf("----------------------------------------\n");
    printf("1. Hien thi danh sach sinh vien\n");
    printf("2. Them sinh vien\n");
    printf("0. Thoat chuong trinh\n");
    printf("----------------------------------------\n");
}
void themSinhVien() {
    if (soLuongSV >= 100) {
        printf("Danh sach da day, khong the them nua!\n");
        return;
    }
    printf("\n--- THEM SINH VIEN ---\n");
    printf("Nhap ma sinh vien: ");
    scanf("%d", &danhSachSV[soLuongSV].maSV);
    while(getchar() != '\n');

    printf("Nhap ten sinh vien: ");
    fgets(danhSachSV[soLuongSV].ten, 50, stdin);
    danhSachSV[soLuongSV].ten[strcspn(danhSachSV[soLuongSV].ten, "\n")] = '\0';

    printf("Nhap lop: ");
    fgets(danhSachSV[soLuongSV].lop, 10, stdin);
    danhSachSV[soLuongSV].lop[strcspn(danhSachSV[soLuongSV].lop, "\n")] = '\0';

    printf("Nhap diem: ");
    scanf("%f", &danhSachSV[soLuongSV].diem);
    
    while(getchar() != '\n');
    soLuongSV++;
    printf("\n Them sinh vien thanh cong!\n");
}
void hienThiDanhSach() {
    printf("\n--- DANH SACH SINH VIEN ---\n");
    if (soLuongSV == 0) {
        printf("Danh sach sinh vien trong!\n");
        return;
    }
    printf("%-10s %-25s %-10s %-10s\n", "Ma SV", "Ten SV", "Lop", "Diem");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < soLuongSV; i++) {
        printf("%-10d %-25s %-10s %-10.2f\n",
               danhSachSV[i].maSV,
               danhSachSV[i].ten,
               danhSachSV[i].lop,
               danhSachSV[i].diem);
    }
}
int main() {
    int luaChon;
    while (1) {
        hienThiMenu();
        printf("Vui long nhap lua chon cua ban: ");
        scanf("%d", &luaChon);
        while(getchar() != '\n');

        switch (luaChon) {
            case 1:
                hienThiDanhSach();
                break;
            case 2:
                themSinhVien();
                break;
            case 0:
                printf("\n--- Cam on da su dung he thong! ---\n");
                return 0; 
            default:
                printf("Lua chon khong hop le. Vui long nhap lai!\n");
        }
        printf("\n");
    }
    return 0;
}
