#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    int month, day, year;
} Date;

typedef struct {
    char studentId[10];
    char classroomId[10];
    char name[50];
    Date dateOfBirth;
    char gender[10];
    char email[50];
    char phone[20];
    char password[20];
    float diem;
} Student;

typedef struct {
    char teacherId[10];
    char name[50];
    char phone[20];
    char email[50];
    char classroomId[50];
} Teacher;

typedef struct {
    char classroomId[10];
    char className[50];
    char teacherId[10];
    int soLuongSV;
} Classroom;

Student danhSachSV[100];
int soLuongSV = 0;
int maSV_hienTai = 1;

Teacher danhSachGV[50];
int soLuongGV = 0;

Classroom danhSachLop[50];
int soLuongLop = 0;


void veDuongKe(int chieuDai);
void clearBuffer();
bool kiemTraKhongRong(const char* str);
bool kiemTraEmail(const char* email);
bool kiemTraSdt(const char* phone);
bool kiemTraTenHopLe(const char* name);
int kiemTraMaSV(const char* studentId);
bool kiemTraNamNhuan(int year);
bool kiemTraNgayHopLe(Date date);
bool kiemTraGioiTinh(const char* gender);
bool kiemTraDiem(float diem);
bool kiemTraMatKhau(const char* password);
int kiemTraMaGV(const char* teacherId);
int kiemTraEmailTrungGV(const char* newEmail, const char* currentId);
int kiemTraSdtTrungGV(const char* newPhone, const char* currentId);
int kiemTraTenTrungGV(const char* newName, const char* currentId);
int timLop(const char* classroomId);
void tuDongSinhMaSV(char* maSV);
void themSinhVien();
void hienThiDanhSach();
void suaThongTinSinhVien();
void xoaSinhVien();
void timKiemTheoKhoangDiem();
void timKiemTheoTenSV();
void sapXepTheoTenAZ();
void sapXepTheoTenZA();
void sapXepTheoDiemTangDan();
void sapXepTheoDiemGiamDan();
void sapXepSinhVien();
void luuDuLieuSV();
void menuQuanLySinhVien();
void tuDongSinhMaGV(char* maGV);
void themGiaoVien();
void hienThiDanhSachGiaoVien();
void suaThongTinGiaoVien();
void xoaGiaoVien();
void timKiemGiaoVienTheoTen();
void themLopChoGiaoVien();
void luuDuLieuGV();
void menuQuanLyGiaoVien();

// Hàm mới cho Quản lý Lớp
void hienThiDanhSachLop();
void themLop();
void suaThongTinLop();
void xoaLop();
void xemChiTietLop();
void themSinhVienVaoLop();
void xoaSinhVienKhoiLop();
void sapXepDanhSachLop();
void menuQuanLyLop();
int kiemTraMaLop(const char* id);
void khoiTaoDuLieu();
void luuDuLieuLop();
void docDuLieuLop();

void veDuongKe(int chieuDai) {
    for (int i = 0; i < chieuDai; i++) {
        printf("-");
    }
    printf("\n");
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool kiemTraKhongRong(const char* str) {
    return strlen(str) > 0;
}

bool kiemTraEmail(const char* email) {
    const char *at = strchr(email, '@');
    if (!at || at == email || at == email + strlen(email) - 1) {
        return false;
    }
    const char *dot = strrchr(email, '.');
    if (!dot || dot < at || dot == email + strlen(email) - 1) {
        return false;
    }
    for (int i = 0; email[i] != '\0'; i++) {
        if (isspace(email[i])) {
            return false;
        }
    }
    return true;
}

bool kiemTraSdt(const char* phone) {
    if (strlen(phone) < 8 || strlen(phone) > 12) {
        return false;
    }
    for (int i = 0; phone[i] != '\0'; i++) {
        if (!isdigit(phone[i])) {
            return false;
        }
    }
    return true;
}

bool kiemTraTenHopLe(const char* name) {
    if (strlen(name) == 0) {
        return false;
    }
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && !isspace(name[i])) {
            return false;
        }
    }
    return true;
}

int kiemTraMaSV(const char* studentId) {
    for (int i = 0; i < soLuongSV; i++) {
        if (strcmp(danhSachSV[i].studentId, studentId) == 0) {
            return i;
        }
    }
    return -1;
}

bool kiemTraNamNhuan(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool kiemTraNgayHopLe(Date date) {
    if (date.year < 1900 || date.year > 2025) {
        return false;
    }
    if (date.month < 1 || date.month > 12) {
        return false;
    }
    int soNgayTrongThang[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (kiemTraNamNhuan(date.year)) {
        soNgayTrongThang[1] = 29;
    }
    if (date.day < 1 || date.day > soNgayTrongThang[date.month - 1]) {
        return false;
    }
    return true;
}

bool kiemTraGioiTinh(const char* gender) {
    char tempGender[10];
    strcpy(tempGender, gender);
    for (int i = 0; tempGender[i]; i++) {
        tempGender[i] = tolower(tempGender[i]);
    }
    if (strcmp(tempGender, "nam") == 0 || strcmp(tempGender, "nu") == 0 || strcmp(tempGender, "khac") == 0) {
        return true;
    }
    return false;
}

bool kiemTraDiem(float diem) {
    return (diem >= 0 && diem <= 10);
}

bool kiemTraMatKhau(const char* password) {
    return (strlen(password) > 0);
}

int kiemTraMaGV(const char* teacherId) {
    for (int i = 0; i < soLuongGV; i++) {
        if (strcmp(danhSachGV[i].teacherId, teacherId) == 0) {
            return i;
        }
    }
    return -1;
}

int kiemTraEmailTrungGV(const char* newEmail, const char* currentId) {
    for (int i = 0; i < soLuongGV; i++) {
        if (currentId == NULL || strcmp(danhSachGV[i].teacherId, currentId) != 0) {
            if (strcmp(danhSachGV[i].email, newEmail) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int kiemTraSdtTrungGV(const char* newPhone, const char* currentId) {
    for (int i = 0; i < soLuongGV; i++) {
        if (currentId == NULL || strcmp(danhSachGV[i].teacherId, currentId) != 0) {
            if (strcmp(danhSachGV[i].phone, newPhone) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int kiemTraTenTrungGV(const char* newName, const char* currentId) {
    for (int i = 0; i < soLuongGV; i++) {
        if (currentId == NULL || strcmp(danhSachGV[i].teacherId, currentId) != 0) {
            if (strcmp(danhSachGV[i].name, newName) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int timLop(const char* classroomId) {
    for (int i = 0; i < soLuongLop; i++) {
        if (strcmp(danhSachLop[i].classroomId, classroomId) == 0) {
            return i;
        }
    }
    return -1;
}

// HÀM QUẢN LÝ SINH VIÊN
void tuDongSinhMaSV(char* maSV) {
    sprintf(maSV, "SV%03d", maSV_hienTai);
    while (kiemTraMaSV(maSV) != -1) {
        maSV_hienTai++;
        sprintf(maSV, "SV%03d", maSV_hienTai);
    }
}

void themSinhVien() {
    if (soLuongSV >= 100) {
        printf("Danh sach da day, khong the them nua!\n");
        return;
    }
    printf("\n--- THEM SINH VIEN ---\n");
    tuDongSinhMaSV(danhSachSV[soLuongSV].studentId);
    printf("Ma sinh vien : %s\n", danhSachSV[soLuongSV].studentId);

    do {
        printf("Nhap ten sinh vien: ");
        fgets(danhSachSV[soLuongSV].name, sizeof(danhSachSV[soLuongSV].name), stdin);
        danhSachSV[soLuongSV].name[strcspn(danhSachSV[soLuongSV].name, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachSV[soLuongSV].name)) {
            printf("Ten khong duoc de trong. Vui long nhap lai!\n");
        } else if (!kiemTraTenHopLe(danhSachSV[soLuongSV].name)) {
            printf("Ten khong hop le (chi duoc chua chu cai va khoang trang). Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(danhSachSV[soLuongSV].name) || !kiemTraTenHopLe(danhSachSV[soLuongSV].name));

    do {
        printf("Nhap lop: ");
        fgets(danhSachSV[soLuongSV].classroomId, sizeof(danhSachSV[soLuongSV].classroomId), stdin);
        danhSachSV[soLuongSV].classroomId[strcspn(danhSachSV[soLuongSV].classroomId, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachSV[soLuongSV].classroomId)) {
            printf("Lop khong duoc de trong. Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(danhSachSV[soLuongSV].classroomId));

    do {
        printf("Nhap email: ");
        fgets(danhSachSV[soLuongSV].email, sizeof(danhSachSV[soLuongSV].email), stdin);
        danhSachSV[soLuongSV].email[strcspn(danhSachSV[soLuongSV].email, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachSV[soLuongSV].email)) {
            printf("Email khong duoc de trong. Vui long nhap lai!\n");
        } else if (!kiemTraEmail(danhSachSV[soLuongSV].email)) {
            printf("Dinh dang email khong hop le. Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(danhSachSV[soLuongSV].email) || !kiemTraEmail(danhSachSV[soLuongSV].email));

    do {
        printf("Nhap so dien thoai: ");
        fgets(danhSachSV[soLuongSV].phone, sizeof(danhSachSV[soLuongSV].phone), stdin);
        danhSachSV[soLuongSV].phone[strcspn(danhSachSV[soLuongSV].phone, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachSV[soLuongSV].phone)) {
            printf("So dien thoai khong duoc de trong. Vui long nhap lai!\n");
        } else if (!kiemTraSdt(danhSachSV[soLuongSV].phone)) {
            printf("Dinh dang so dien thoai khong hop le (chi chua so, dai tu 8-12 ky tu). Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(danhSachSV[soLuongSV].phone) || !kiemTraSdt(danhSachSV[soLuongSV].phone));

    int valid_date = 0;
    do {
        printf("Nhap ngay sinh (dd mm yyyy): ");
        if (scanf("%d %d %d", &danhSachSV[soLuongSV].dateOfBirth.day, &danhSachSV[soLuongSV].dateOfBirth.month, &danhSachSV[soLuongSV].dateOfBirth.year) != 3) {
            printf("Dinh dang ngay sinh khong hop le. Vui long nhap lai!\n");
            clearBuffer();
        } else if (!kiemTraNgayHopLe(danhSachSV[soLuongSV].dateOfBirth)) {
            printf("Ngay sinh khong hop le. Vui long nhap lai!\n");
            clearBuffer();
        } else {
            valid_date = 1;
        }
    } while (!valid_date);
    clearBuffer();

    do {
        printf("Nhap gioi tinh (Nam/Nu/Khac): ");
        fgets(danhSachSV[soLuongSV].gender, sizeof(danhSachSV[soLuongSV].gender), stdin);
        danhSachSV[soLuongSV].gender[strcspn(danhSachSV[soLuongSV].gender, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachSV[soLuongSV].gender)) {
            printf("Gioi tinh khong duoc de trong. Vui long nhap lai!\n");
        } else if (!kiemTraGioiTinh(danhSachSV[soLuongSV].gender)) {
            printf("Gioi tinh khong hop le. Vui long nhap 'Nam', 'Nu' hoac 'Khac'.\n");
        }
    } while (!kiemTraKhongRong(danhSachSV[soLuongSV].gender) || !kiemTraGioiTinh(danhSachSV[soLuongSV].gender));

    do {
        printf("Nhap mat khau: ");
        fgets(danhSachSV[soLuongSV].password, sizeof(danhSachSV[soLuongSV].password), stdin);
        danhSachSV[soLuongSV].password[strcspn(danhSachSV[soLuongSV].password, "\n")] = '\0';
        if (!kiemTraMatKhau(danhSachSV[soLuongSV].password)) {
            printf("Mat khau khong duoc de trong. Vui long nhap lai!\n");
        }
    } while (!kiemTraMatKhau(danhSachSV[soLuongSV].password));

    int valid_score = 0;
    do {
        printf("Nhap diem: ");
        if (scanf("%f", &danhSachSV[soLuongSV].diem) != 1) {
            printf("Diem khong hop le. Vui long nhap so!\n");
            clearBuffer();
        } else if (!kiemTraDiem(danhSachSV[soLuongSV].diem)) {
            printf("Diem phai tu 0 den 10. Vui long nhap lai!\n");
        } else {
            valid_score = 1;
        }
    } while (!valid_score);
    clearBuffer();

    soLuongSV++;
    maSV_hienTai++;
    printf("\n Them sinh vien thanh cong!\n");
}

void hienThiDanhSach() {
    printf("\n--- DANH SACH SINH VIEN ---\n");
    if (soLuongSV == 0) {
        printf("Danh sach sinh vien trong!\n");
        return;
    }
    veDuongKe(120);
    printf("| %-8s | %-15s | %-10s | %-10s | %-10s | %-25s | %-15s | %-8s |\n", "Ma SV", "Ten SV", "Lop", "Ngay sinh", "Gioi tinh", "Email", "SDT", "Diem");
    veDuongKe(120);
    for (int i = 0; i < soLuongSV; i++) {
        printf("| %-8s | %-15s | %-10s | %02d/%02d/%04d | %-10s | %-25s | %-15s | %-8.2f |\n",
               danhSachSV[i].studentId,
               danhSachSV[i].name,
               danhSachSV[i].classroomId,
               danhSachSV[i].dateOfBirth.day,
               danhSachSV[i].dateOfBirth.month,
               danhSachSV[i].dateOfBirth.year,
               danhSachSV[i].gender,
               danhSachSV[i].email,
               danhSachSV[i].phone,
               danhSachSV[i].diem);
    }
    veDuongKe(120);
}

void suaThongTinSinhVien() {
    char idCanSua[10];
    int timThay = -1;
    printf("\n--- SUA THONG TIN SINH VIEN ---\n");
    printf("Nhap ma sinh vien can sua: ");
    fgets(idCanSua, 10, stdin);
    idCanSua[strcspn(idCanSua, "\n")] = '\0';

    timThay = kiemTraMaSV(idCanSua);
    if (timThay != -1) {
        printf("\n--- Thong tin hien tai cua sinh vien co ma %s ---\n", idCanSua);
        veDuongKe(120);
        printf("| %-8s | %-15s | %-10s | %-10s | %-10s | %-25s | %-15s | %-8s |\n", "Ma SV", "Ten SV", "Lop", "Ngay sinh", "Gioi tinh", "Email", "SDT", "Diem");
        veDuongKe(120);
        printf("| %-8s | %-15s | %-10s | %02d/%02d/%04d | %-10s | %-25s | %-15s | %-8.2f |\n",
               danhSachSV[timThay].studentId, danhSachSV[timThay].name, danhSachSV[timThay].classroomId,
               danhSachSV[timThay].dateOfBirth.day, danhSachSV[timThay].dateOfBirth.month, danhSachSV[timThay].dateOfBirth.year,
               danhSachSV[timThay].gender, danhSachSV[timThay].email, danhSachSV[timThay].phone, danhSachSV[timThay].diem);
        veDuongKe(120);

        int luaChonSua;
        do {
            printf("\nChon thong tin can sua:\n");
            printf("1. Ten\n");
            printf("2. Lop\n");
            printf("3. Ngay sinh\n");
            printf("4. Gioi tinh\n");
            printf("5. Email\n");
            printf("6. So dien thoai\n");
            printf("7. Diem\n");
            printf("8. Mat khau\n");
            printf("0. Quay lai menu chinh\n");
            printf("Nhap lua chon cua ban: ");
            scanf("%d", &luaChonSua);
            clearBuffer();

            switch(luaChonSua) {
                case 1:
                    do {
                        printf("Nhap ten moi: ");
                        fgets(danhSachSV[timThay].name, sizeof(danhSachSV[timThay].name), stdin);
                        danhSachSV[timThay].name[strcspn(danhSachSV[timThay].name, "\n")] = '\0';
                        if (!kiemTraKhongRong(danhSachSV[timThay].name)) {
                            printf("Ten khong duoc de trong. Vui long nhap lai!\n");
                        } else if (!kiemTraTenHopLe(danhSachSV[timThay].name)) {
                            printf("Ten khong hop le. Vui long nhap lai!\n");
                        }
                    } while (!kiemTraKhongRong(danhSachSV[timThay].name) || !kiemTraTenHopLe(danhSachSV[timThay].name));
                    printf("Sua ten sinh vien thanh cong!\n");
                    break;
                case 2:
                    do {
                        printf("Nhap lop moi: ");
                        fgets(danhSachSV[timThay].classroomId, sizeof(danhSachSV[timThay].classroomId), stdin);
                        danhSachSV[timThay].classroomId[strcspn(danhSachSV[timThay].classroomId, "\n")] = '\0';
                        if (!kiemTraKhongRong(danhSachSV[timThay].classroomId)) {
                            printf("Lop khong duoc de trong. Vui long nhap lai!\n");
                        }
                    } while (!kiemTraKhongRong(danhSachSV[timThay].classroomId));
                    printf("Sua lop sinh vien thanh cong!\n");
                    break;
                case 3:
                    int valid_date = 0;
                    do {
                        printf("Nhap ngay sinh moi (dd mm yyyy): ");
                        if (scanf("%d %d %d", &danhSachSV[timThay].dateOfBirth.day, &danhSachSV[timThay].dateOfBirth.month, &danhSachSV[timThay].dateOfBirth.year) != 3) {
                            printf("Dinh dang ngay sinh khong hop le. Vui long nhap lai.\n");
                            clearBuffer();
                        } else if (!kiemTraNgayHopLe(danhSachSV[timThay].dateOfBirth)) {
                            printf("Ngay sinh khong hop le. Vui long nhap lai!\n");
                            clearBuffer();
                        } else {
                            valid_date = 1;
                        }
                    } while (!valid_date);
                    clearBuffer();
                    printf("Sua ngay sinh sinh vien thanh cong!\n");
                    break;
                case 4:
                    do {
                        printf("Nhap gioi tinh moi (Nam/Nu/Khac): ");
                        fgets(danhSachSV[timThay].gender, sizeof(danhSachSV[timThay].gender), stdin);
                        danhSachSV[timThay].gender[strcspn(danhSachSV[timThay].gender, "\n")] = '\0';
                        if (!kiemTraKhongRong(danhSachSV[timThay].gender)) {
                            printf("Gioi tinh khong duoc de trong. Vui long nhap lai!\n");
                        } else if (!kiemTraGioiTinh(danhSachSV[timThay].gender)) {
                            printf("Gioi tinh khong hop le. Vui long nhap 'Nam', 'Nu' hoac 'Khac'.\n");
                        }
                    } while (!kiemTraKhongRong(danhSachSV[timThay].gender) || !kiemTraGioiTinh(danhSachSV[timThay].gender));
                    printf("Sua gioi tinh sinh vien thanh cong!\n");
                    break;
                case 5:
                    do {
                        printf("Nhap email moi: ");
                        fgets(danhSachSV[timThay].email, sizeof(danhSachSV[timThay].email), stdin);
                        danhSachSV[timThay].email[strcspn(danhSachSV[timThay].email, "\n")] = '\0';
                        if (!kiemTraKhongRong(danhSachSV[timThay].email)) {
                            printf("Email khong duoc de trong. Vui long nhap lai!\n");
                        } else if (!kiemTraEmail(danhSachSV[timThay].email)) {
                            printf("Dinh dang email khong hop le. Vui long nhap lai!\n");
                        }
                    } while (!kiemTraKhongRong(danhSachSV[timThay].email) || !kiemTraEmail(danhSachSV[timThay].email));
                    printf("Sua email sinh vien thanh cong!\n");
                    break;
                case 6:
                    do {
                        printf("Nhap so dien thoai moi: ");
                        fgets(danhSachSV[timThay].phone, sizeof(danhSachSV[timThay].phone), stdin);
                        danhSachSV[timThay].phone[strcspn(danhSachSV[timThay].phone, "\n")] = '\0';
                        if (!kiemTraKhongRong(danhSachSV[timThay].phone)) {
                            printf("So dien thoai khong duoc de trong. Vui long nhap lai!\n");
                        } else if (!kiemTraSdt(danhSachSV[timThay].phone)) {
                            printf("Dinh dang so dien thoai khong hop le. Vui long nhap lai!\n");
                        }
                    } while (!kiemTraKhongRong(danhSachSV[timThay].phone) || !kiemTraSdt(danhSachSV[timThay].phone));
                    printf("Sua so dien thoai sinh vien thanh cong!\n");
                    break;
                case 7:
                    int valid_score = 0;
                    do {
                        printf("Nhap diem moi: ");
                        if (scanf("%f", &danhSachSV[timThay].diem) != 1) {
                            printf("Diem khong hop le. Vui long nhap so!\n");
                            clearBuffer();
                        } else if (!kiemTraDiem(danhSachSV[timThay].diem)) {
                            printf("Diem phai tu 0 den 10. Vui long nhap lai!\n");
                        } else {
                            valid_score = 1;
                        }
                    } while (!valid_score);
                    clearBuffer();
                    printf("Sua diem sinh vien thanh cong!\n");
                    break;
                case 8:
                    do {
                        printf("Nhap mat khau moi: ");
                        fgets(danhSachSV[timThay].password, sizeof(danhSachSV[timThay].password), stdin);
                        danhSachSV[timThay].password[strcspn(danhSachSV[timThay].password, "\n")] = '\0';
                        if (!kiemTraMatKhau(danhSachSV[timThay].password)) {
                            printf("Mat khau khong duoc de trong. Vui long nhap lai!\n");
                        }
                    } while (!kiemTraMatKhau(danhSachSV[timThay].password));
                    printf("Sua mat khau sinh vien thanh cong!\n");
                    break;
                case 0:
                    printf("Quay lai menu chinh...\n");
                    break;
                default:
                    printf("Lua chon khong hop le. Vui long nhap lai!\n");
            }
        } while (luaChonSua != 0);
    } else {
        printf("Khong tim thay sinh vien co ma %s!\n", idCanSua);
    }
}

void xoaSinhVien() {
    char idCanXoa[10];
    int viTriXoa = -1;
    char xacNhan;
    printf("\n--- XOA SINH VIEN ---\n");
    printf("Nhap ma sinh vien can xoa: ");
    fgets(idCanXoa, 10, stdin);
    idCanXoa[strcspn(idCanXoa, "\n")] = '\0';

    viTriXoa = kiemTraMaSV(idCanXoa);

    if (viTriXoa != -1) {
        printf("Ban co chac chan muon xoa sinh vien co ma %s khong? (Y/N): ", idCanXoa);
        scanf(" %c", &xacNhan);
        clearBuffer();

        if (xacNhan == 'y' || xacNhan == 'Y') {
            for (int i = viTriXoa; i < soLuongSV - 1; i++) {
                danhSachSV[i] = danhSachSV[i+1];
            }
            soLuongSV--;
            printf("Xoa sinh vien co ma %s thanh cong!\n", idCanXoa);
        } else {
            printf("Huy thao tac xoa.\n");
        }
    } else {
        printf("Khong tim thay sinh vien co ma %s!\n", idCanXoa);
    }
}

void timKiemTheoKhoangDiem() {
    float diemMin, diemMax;
    int timThay = 0;

    printf("\n--- TIM KIEM SINH VIEN THEO KHOANG DIEM ---\n");
    printf("Nhap diem toi thieu: ");
    while (scanf("%f", &diemMin) != 1) {
        printf("Diem khong hop le. Vui long nhap lai: ");
        clearBuffer();
    }
    clearBuffer();

    printf("Nhap diem toi da: ");
    while (scanf("%f", &diemMax) != 1) {
        printf("Diem khong hop le. Vui long nhap lai: ");
        clearBuffer();
    }
    clearBuffer();

    if (diemMin > diemMax) {
        float temp = diemMin;
        diemMin = diemMax;
        diemMax = temp;
        printf("Da hoan doi khoang diem de dam bao diem toi thieu <= diem toi da.\n");
    }

    printf("\nKet qua tim kiem sinh vien trong khoang diem %.2f den %.2f:\n", diemMin, diemMax);
    veDuongKe(120);
    printf("| %-8s | %-15s | %-10s | %-10s | %-10s | %-25s | %-15s | %-8s |\n", "Ma SV", "Ten SV", "Lop", "Ngay sinh", "Gioi tinh", "Email", "SDT", "Diem");
    veDuongKe(120);

    for (int i = 0; i < soLuongSV; i++) {
        if (danhSachSV[i].diem >= diemMin && danhSachSV[i].diem <= diemMax) {
            printf("| %-8s | %-15s | %-10s | %02d/%02d/%04d | %-10s | %-25s | %-15s | %-8.2f |\n",
                   danhSachSV[i].studentId, danhSachSV[i].name, danhSachSV[i].classroomId,
                   danhSachSV[i].dateOfBirth.day, danhSachSV[i].dateOfBirth.month, danhSachSV[i].dateOfBirth.year,
                   danhSachSV[i].gender, danhSachSV[i].email, danhSachSV[i].phone, danhSachSV[i].diem);
            timThay = 1;
        }
    }

    if (timThay == 0) {
        printf("| %-116s |\n", "Khong tim thay sinh vien nao trong khoang diem nay.");
    }
    veDuongKe(120);
}

void timKiemTheoTenSV() {
    char tenCanTim[50];
    int timThay = 0;

    printf("\n--- TIM KIEM SINH VIEN THEO TEN ---\n");
    do {
        printf("Nhap ten (hoac mot phan ten) can tim: ");
        fgets(tenCanTim, sizeof(tenCanTim), stdin);
        tenCanTim[strcspn(tenCanTim, "\n")] = '\0';
        if (!kiemTraKhongRong(tenCanTim)) {
            printf("Ten khong duoc de trong. Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(tenCanTim));

    for(int i = 0; tenCanTim[i]; i++){
      tenCanTim[i] = tolower(tenCanTim[i]);
    }

    printf("\nKet qua tim kiem:\n");
    veDuongKe(120);
    printf("| %-8s | %-15s | %-10s | %-10s | %-10s | %-25s | %-15s | %-8s |\n", "Ma SV", "Ten SV", "Lop", "Ngay sinh", "Gioi tinh", "Email", "SDT", "Diem");
    veDuongKe(120);

    for (int i = 0; i < soLuongSV; i++) {
        char tenSV_thuong[50];
        strcpy(tenSV_thuong, danhSachSV[i].name);
        for(int j = 0; tenSV_thuong[j]; j++){
          tenSV_thuong[j] = tolower(tenSV_thuong[j]);
        }
        if (strstr(tenSV_thuong, tenCanTim) != NULL) {
            printf("| %-8s | %-15s | %-10s | %02d/%02d/%04d | %-10s | %-25s | %-15s | %-8.2f |\n",
                   danhSachSV[i].studentId, danhSachSV[i].name, danhSachSV[i].classroomId,
                   danhSachSV[i].dateOfBirth.day, danhSachSV[i].dateOfBirth.month, danhSachSV[i].dateOfBirth.year,
                   danhSachSV[i].gender, danhSachSV[i].email, danhSachSV[i].phone, danhSachSV[i].diem);
            timThay = 1;
        }
    }
    if (timThay == 0) {
        printf("| %-116s |\n", "Khong tim thay sinh vien nao.");
    }
    veDuongKe(120);
}

void sapXepTheoTenAZ() {
    Student temp;
    for (int i = 0; i < soLuongSV - 1; i++) {
        for (int j = i + 1; j < soLuongSV; j++) {
            if (strcmp(danhSachSV[i].name, danhSachSV[j].name) > 0) {
                temp = danhSachSV[i];
                danhSachSV[i] = danhSachSV[j];
                danhSachSV[j] = temp;
            }
        }
    }
    printf("\nSap xep danh sach sinh vien theo ten (A-Z) thanh cong!\n");
    hienThiDanhSach();
}

void sapXepTheoTenZA() {
    Student temp;
    for (int i = 0; i < soLuongSV - 1; i++) {
        for (int j = i + 1; j < soLuongSV; j++) {
            if (strcmp(danhSachSV[i].name, danhSachSV[j].name) < 0) {
                temp = danhSachSV[i];
                danhSachSV[i] = danhSachSV[j];
                danhSachSV[j] = temp;
            }
        }
    }
    printf("\nSap xep danh sach sinh vien theo ten (Z-A) thanh cong!\n");
    hienThiDanhSach();
}

void sapXepTheoDiemTangDan() {
    Student temp;
    for (int i = 0; i < soLuongSV - 1; i++) {
        for (int j = i + 1; j < soLuongSV; j++) {
            if (danhSachSV[i].diem > danhSachSV[j].diem) {
                temp = danhSachSV[i];
                danhSachSV[i] = danhSachSV[j];
                danhSachSV[j] = temp;
            }
        }
    }
    printf("\nSap xep danh sach sinh vien theo diem tang dan thanh cong!\n");
    hienThiDanhSach();
}

void sapXepTheoDiemGiamDan() {
    Student temp;
    for (int i = 0; i < soLuongSV - 1; i++) {
        for (int j = i + 1; j < soLuongSV; j++) {
            if (danhSachSV[i].diem < danhSachSV[j].diem) {
                temp = danhSachSV[i];
                danhSachSV[i] = danhSachSV[j];
                danhSachSV[j] = temp;
            }
        }
    }
    printf("\nSap xep danh sach sinh vien theo diem giam dan thanh cong!\n");
    hienThiDanhSach();
}

void sapXepSinhVien() {
    int luaChonSapXep;
    do {
        printf("\n--- SAP XEP DANH SACH SINH VIEN ---\n");
        printf("1. Sap xep theo ten (A-Z)\n");
        printf("2. Sap xep theo ten (Z-A)\n");
        printf("3. Sap xep theo diem (tang dan)\n");
        printf("4. Sap xep theo diem (giam dan)\n");
        printf("0. Quay lai menu truoc\n");
        printf("Nhap lua chon cua ban: ");
        if (scanf("%d", &luaChonSapXep) != 1) {
            printf("Lua chon khong hop le. Vui long nhap so nguyen!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch(luaChonSapXep) {
            case 1: sapXepTheoTenAZ(); break;
            case 2: sapXepTheoTenZA(); break;
            case 3: sapXepTheoDiemTangDan(); break;
            case 4: sapXepTheoDiemGiamDan(); break;
            case 0: printf("Quay lai menu truoc...\n"); break;
            default: printf("Lua chon khong hop le. Vui long nhap lai!\n");
        }
    } while (luaChonSapXep != 0);
}

void luuDuLieuSV() {
    FILE *file;
    file = fopen("danhsachsv.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file de luu du lieu!\n");
        return;
    }

    for (int i = 0; i < soLuongSV; i++) {
        fprintf(file, "%s,%s,%s,%d-%d-%d,%s,%s,%s,%.2f,%s\n",
                danhSachSV[i].studentId, danhSachSV[i].classroomId, danhSachSV[i].name,
                danhSachSV[i].dateOfBirth.day, danhSachSV[i].dateOfBirth.month, danhSachSV[i].dateOfBirth.year,
                danhSachSV[i].gender, danhSachSV[i].email, danhSachSV[i].phone,
                danhSachSV[i].diem, danhSachSV[i].password);
    }
    fclose(file);
    printf("\nLuu du lieu sinh vien vao file danhsachsv.txt thanh cong!\n");
}

void menuQuanLySinhVien() {
    int luaChon;
    do {
        printf("========================================\n");
        printf("        MENU QUAN LY SINH VIEN          \n");
        printf("----------------------------------------\n");
        printf("1. Hien thi danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("7. Luu du lieu vao file\n");
        printf("0. Quay lai menu chinh\n");
        printf("----------------------------------------\n");
        printf("Vui long nhap lua chon cua ban: ");
        if (scanf("%d", &luaChon) != 1) {
            printf("Lua chon khong hop le. Vui long nhap mot so tu 0 den 7!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        switch (luaChon) {
            case 1: hienThiDanhSach(); break;
            case 2: themSinhVien(); break;
            case 3: suaThongTinSinhVien(); break;
            case 4: xoaSinhVien(); break;
            case 5: {
                int luaChonTimKiem;
                printf("\n--- MENU TIM KIEM SINH VIEN ---\n");
                printf("1. Tim kiem theo ten\n");
                printf("2. Tim kiem theo khoang diem\n");
                printf("0. Quay lai\n");
                printf("Nhap lua chon cua ban: ");
                if (scanf("%d", &luaChonTimKiem) != 1) {
                    printf("Lua chon khong hop le. Vui long nhap so!\n");
                    clearBuffer();
                    break;
                }
                clearBuffer();
                switch (luaChonTimKiem) {
                    case 1: timKiemTheoTenSV(); break;
                    case 2: timKiemTheoKhoangDiem(); break;
                    case 0: break;
                    default: printf("Lua chon khong hop le.\n");
                }
                break;
            }
            case 6: sapXepSinhVien(); break;
            case 7: luuDuLieuSV(); break;
            case 0: printf("\nQuay lai menu chinh...\n"); break;
            default: printf("Lua chon khong hop le. Vui long nhap lai!\n");
        }
        printf("\n");
    } while (luaChon != 0);
}

// HÀM QUẢN LÝ GIÁO VIÊN
void tuDongSinhMaGV(char* maGV) {
    static int maGV_hienTai = 1;
    do {
        sprintf(maGV, "GV%03d", maGV_hienTai);
        maGV_hienTai++;
    } while (kiemTraMaGV(maGV) != -1);
}

void themGiaoVien() {
    if (soLuongGV >= 50) {
        printf("Danh sach giao vien da day, khong the them nua!\n");
        return;
    }
    printf("\n--- THEM GIAO VIEN ---\n");
    tuDongSinhMaGV(danhSachGV[soLuongGV].teacherId);
    printf("Ma giao vien : %s\n", danhSachGV[soLuongGV].teacherId);

    do {
        printf("Nhap ten giao vien: ");
        fgets(danhSachGV[soLuongGV].name, sizeof(danhSachGV[soLuongGV].name), stdin);
        danhSachGV[soLuongGV].name[strcspn(danhSachGV[soLuongGV].name, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachGV[soLuongGV].name)) {
            printf("Ten khong duoc de trong. Vui long nhap lai!\n");
        } else if (!kiemTraTenHopLe(danhSachGV[soLuongGV].name)) {
            printf("Ten khong hop le (chi duoc chua chu cai va khoang trang). Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(danhSachGV[soLuongGV].name) || !kiemTraTenHopLe(danhSachGV[soLuongGV].name));

    do {
        printf("Nhap so dien thoai: ");
        fgets(danhSachGV[soLuongGV].phone, sizeof(danhSachGV[soLuongGV].phone), stdin);
        danhSachGV[soLuongGV].phone[strcspn(danhSachGV[soLuongGV].phone, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachGV[soLuongGV].phone)) {
            printf("So dien thoai khong duoc de trong. Vui long nhap lai!\n");
        } else if (!kiemTraSdt(danhSachGV[soLuongGV].phone)) {
            printf("Dinh dang so dien thoai khong hop le (chi chua so, dai tu 8-12 ky tu). Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(danhSachGV[soLuongGV].phone) || !kiemTraSdt(danhSachGV[soLuongGV].phone));

    do {
        printf("Nhap email: ");
        fgets(danhSachGV[soLuongGV].email, sizeof(danhSachGV[soLuongGV].email), stdin);
        danhSachGV[soLuongGV].email[strcspn(danhSachGV[soLuongGV].email, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachGV[soLuongGV].email)) {
            printf("Email khong duoc de trong. Vui long nhap lai!\n");
        } else if (!kiemTraEmail(danhSachGV[soLuongGV].email)) {
            printf("Dinh dang email khong hop le. Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(danhSachGV[soLuongGV].email) || !kiemTraEmail(danhSachGV[soLuongGV].email));

    strcpy(danhSachGV[soLuongGV].classroomId, "Chua co");
    soLuongGV++;
    printf("\n Them giao vien thanh cong!\n");
}

void hienThiDanhSachGiaoVien() {
    printf("\n--- DANH SACH GIAO VIEN ---\n");
    if (soLuongGV == 0) {
        printf("Danh sach giao vien trong!\n");
        return;
    }
    veDuongKe(100);
    printf("| %-8s | %-15s | %-15s | %-25s | %-20s |\n", "Ma GV", "Ten GV", "SDT", "Email", "Lop Phu Trach");
    veDuongKe(100);
    for (int i = 0; i < soLuongGV; i++) {
        printf("| %-8s | %-15s | %-15s | %-25s | %-20s |\n",
               danhSachGV[i].teacherId,
               danhSachGV[i].name,
               danhSachGV[i].phone,
               danhSachGV[i].email,
               danhSachGV[i].classroomId);
    }
    veDuongKe(100);
}

void suaThongTinGiaoVien() {
    char idCanSua[10];
    int timThay = -1;

    printf("\n--- SUA THONG TIN GIAO VIEN ---\n");
    printf("Nhap ma giao vien can sua: ");
    fgets(idCanSua, 10, stdin);
    idCanSua[strcspn(idCanSua, "\n")] = '\0';

    timThay = kiemTraMaGV(idCanSua);
    if (timThay != -1) {
        printf("\n--- Thong tin hien tai cua giao vien co ma %s ---\n", idCanSua);
        veDuongKe(100);
        printf("| %-8s | %-15s | %-15s | %-25s | %-20s |\n", "Ma GV", "Ten GV", "SDT", "Email", "Lop Phu Trach");
        veDuongKe(100);
        printf("| %-8s | %-15s | %-15s | %-25s | %-20s |\n",
               danhSachGV[timThay].teacherId,
               danhSachGV[timThay].name,
               danhSachGV[timThay].phone,
               danhSachGV[timThay].email,
               danhSachGV[timThay].classroomId);
        veDuongKe(100);

        int luaChonSua;
        do {
            printf("\nChon thong tin can sua:\n");
            printf("1. Ten\n");
            printf("2. So dien thoai\n");
            printf("3. Email\n");
            printf("0. Quay lai menu chinh\n");
            printf("Nhap lua chon cua ban: ");
            scanf("%d", &luaChonSua);
            clearBuffer();

            switch(luaChonSua) {
                case 1:
                    do {
                        printf("Nhap ten moi: ");
                        fgets(danhSachGV[timThay].name, sizeof(danhSachGV[timThay].name), stdin);
                        danhSachGV[timThay].name[strcspn(danhSachGV[timThay].name, "\n")] = '\0';
                        if (!kiemTraKhongRong(danhSachGV[timThay].name)) {
                            printf("Ten khong duoc de trong. Vui long nhap lai!\n");
                        } else if (!kiemTraTenHopLe(danhSachGV[timThay].name)) {
                            printf("Ten khong hop le. Vui long nhap lai!\n");
                        }
                    } while (!kiemTraKhongRong(danhSachGV[timThay].name) || !kiemTraTenHopLe(danhSachGV[timThay].name));
                    printf("Sua ten giao vien thanh cong!\n");
                    break;
                case 2:
                    do {
                        printf("Nhap so dien thoai moi: ");
                        fgets(danhSachGV[timThay].phone, sizeof(danhSachGV[timThay].phone), stdin);
                        danhSachGV[timThay].phone[strcspn(danhSachGV[timThay].phone, "\n")] = '\0';
                        if (!kiemTraKhongRong(danhSachGV[timThay].phone)) {
                            printf("So dien thoai khong duoc de trong. Vui long nhap lai!\n");
                        } else if (!kiemTraSdt(danhSachGV[timThay].phone)) {
                            printf("Dinh dang so dien thoai khong hop le. Vui long nhap lai!\n");
                        }
                    } while (!kiemTraKhongRong(danhSachGV[timThay].phone) || !kiemTraSdt(danhSachGV[timThay].phone));
                    printf("Sua so dien thoai giao vien thanh cong!\n");
                    break;
                case 3:
                    do {
                        printf("Nhap email moi: ");
                        fgets(danhSachGV[timThay].email, sizeof(danhSachGV[timThay].email), stdin);
                        danhSachGV[timThay].email[strcspn(danhSachGV[timThay].email, "\n")] = '\0';
                        if (!kiemTraKhongRong(danhSachGV[timThay].email)) {
                            printf("Email khong duoc de trong. Vui long nhap lai!\n");
                        } else if (!kiemTraEmail(danhSachGV[timThay].email)) {
                            printf("Dinh dang email khong hop le. Vui long nhap lai!\n");
                        }
                    } while (!kiemTraKhongRong(danhSachGV[timThay].email) || !kiemTraEmail(danhSachGV[timThay].email));
                    printf("Sua email giao vien thanh cong!\n");
                    break;
                case 0:
                    printf("Quay lai menu chinh...\n");
                    break;
                default:
                    printf("Lua chon khong hop le. Vui long nhap lai!\n");
            }
        } while (luaChonSua != 0);
    } else {
        printf("Khong tim thay giao vien co ma %s!\n", idCanSua);
    }
}

void xoaGiaoVien() {
    char idCanXoa[10];
    int viTriXoa = -1;
    char xacNhan;
    printf("\n--- XOA GIAO VIEN ---\n");
    printf("Nhap ma giao vien can xoa: ");
    fgets(idCanXoa, 10, stdin);
    idCanXoa[strcspn(idCanXoa, "\n")] = '\0';

    viTriXoa = kiemTraMaGV(idCanXoa);
    if (viTriXoa != -1) {
        printf("Ban co chac chan muon xoa giao vien co ma %s khong? (Y/N): ", idCanXoa);
        scanf(" %c", &xacNhan);
        clearBuffer();

        if (xacNhan == 'y' || xacNhan == 'Y') {
            for (int i = viTriXoa; i < soLuongGV - 1; i++) {
                danhSachGV[i] = danhSachGV[i+1];
            }
            soLuongGV--;
            printf("Xoa giao vien co ma %s thanh cong!\n", idCanXoa);
        } else {
            printf("Huy thao tac xoa.\n");
        }
    } else {
        printf("Khong tim thay giao vien co ma %s!\n", idCanXoa);
    }
}

void timKiemGiaoVienTheoTen() {
    char tenCanTim[50];
    int timThay = 0;

    printf("\n--- TIM KIEM GIAO VIEN THEO TEN ---\n");
    do {
        printf("Nhap ten (hoac mot phan ten) can tim: ");
        fgets(tenCanTim, sizeof(tenCanTim), stdin);
        tenCanTim[strcspn(tenCanTim, "\n")] = '\0';
        if (!kiemTraKhongRong(tenCanTim)) {
            printf("Ten khong duoc de trong. Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(tenCanTim));

    for(int i = 0; tenCanTim[i]; i++){
      tenCanTim[i] = tolower(tenCanTim[i]);
    }

    printf("\nKet qua tim kiem:\n");
    veDuongKe(100);
    printf("| %-8s | %-15s | %-15s | %-25s | %-20s |\n", "Ma GV", "Ten GV", "SDT", "Email", "Lop Phu Trach");
    veDuongKe(100);

    for (int i = 0; i < soLuongGV; i++) {
        char tenGV_thuong[50];
        strcpy(tenGV_thuong, danhSachGV[i].name);
        for(int j = 0; tenGV_thuong[j]; j++){
          tenGV_thuong[j] = tolower(tenGV_thuong[j]);
        }
        if (strstr(tenGV_thuong, tenCanTim) != NULL) {
            printf("| %-8s | %-15s | %-15s | %-25s | %-20s |\n",
                   danhSachGV[i].teacherId,
                   danhSachGV[i].name,
                   danhSachGV[i].phone,
                   danhSachGV[i].email,
                   danhSachGV[i].classroomId);
            timThay = 1;
        }
    }
    if (timThay == 0) {
        printf("| %-96s |\n", "Khong tim thay giao vien nao.");
    }
    veDuongKe(100);
}

void themLopChoGiaoVien() {
    char idGVCanThem[10];
    char idLopCanThem[10];
    int viTriGV = -1;
    int viTriLop = -1;

    printf("\n--- THEM LOP CHO GIAO VIEN ---\n");
    printf("Nhap ma giao vien muon them lop: ");
    fgets(idGVCanThem, 10, stdin);
    idGVCanThem[strcspn(idGVCanThem, "\n")] = '\0';

    viTriGV = kiemTraMaGV(idGVCanThem);

    if (viTriGV == -1) {
        printf("Khong tim thay giao vien co ma %s!\n", idGVCanThem);
        return;
    }

    hienThiDanhSachLop();
    printf("Nhap ma lop muon them cho giao vien: ");
    fgets(idLopCanThem, 10, stdin);
    idLopCanThem[strcspn(idLopCanThem, "\n")] = '\0';

    viTriLop = timLop(idLopCanThem);

    if (viTriLop == -1) {
        printf("Loi: Khong tim thay lop co ma %s!\n", idLopCanThem);
        return;
    }

    if (strcmp(danhSachLop[viTriLop].teacherId, "") != 0) {
        printf("Loi: Lop %s da co giao vien phu trach!\n", idLopCanThem);
        return;
    }

    if (strcmp(danhSachGV[viTriGV].classroomId, "Chua co") == 0) {
        strcpy(danhSachGV[viTriGV].classroomId, idLopCanThem);
    } else {
        strcat(danhSachGV[viTriGV].classroomId, ",");
        strcat(danhSachGV[viTriGV].classroomId, idLopCanThem);
    }

    strcpy(danhSachLop[viTriLop].teacherId, idGVCanThem);
    printf("Them lop %s cho giao vien %s thanh cong!\n", idLopCanThem, danhSachGV[viTriGV].name);
}

void luuDuLieuGV() {
    FILE *file;
    file = fopen("danhsachgv.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file de luu du lieu!\n");
        return;
    }
    for (int i = 0; i < soLuongGV; i++) {
        fprintf(file, "%s,%s,%s,%s,%s\n",
                danhSachGV[i].teacherId,
                danhSachGV[i].name,


                danhSachGV[i].phone,
                danhSachGV[i].email,
                danhSachGV[i].classroomId);
    }
    fclose(file);
    printf("\nLuu du lieu giao vien vao file danhsachgv.txt thanh cong!\n");
}

void menuQuanLyGiaoVien() {
    int luaChon;
    do {
        printf("========================================\n");
        printf("        MENU QUAN LY GIAO VIEN          \n");
        printf("----------------------------------------\n");
        printf("1. Hien thi danh sach giao vien\n");
        printf("2. Them giao vien\n");
        printf("3. Sua thong tin giao vien\n");
        printf("4. Xoa giao vien\n");
        printf("5. Tim kiem giao vien\n");
        printf("6. Them lop cho giao vien\n");
        printf("7. Luu du lieu vao file\n");
        printf("0. Quay lai menu chinh\n");
        printf("----------------------------------------\n");
        printf("Vui long nhap lua chon cua ban: ");
        if (scanf("%d", &luaChon) != 1) {
            printf("Lua chon khong hop le. Vui long nhap mot so tu 0 den 7!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        switch (luaChon) {
            case 1: hienThiDanhSachGiaoVien(); break;
            case 2: themGiaoVien(); break;
            case 3: suaThongTinGiaoVien(); break;
            case 4: xoaGiaoVien(); break;
            case 5: timKiemGiaoVienTheoTen(); break;
            case 6: themLopChoGiaoVien(); break;
            case 7: luuDuLieuGV(); break;
            case 0: printf("\nQuay lai menu chinh...\n"); break;
            default: printf("Lua chon khong hop le. Vui long nhap lai!\n");
        }
        printf("\n");
    } while (luaChon != 0);
}

// HÀM QUẢN LÝ LỚP
int kiemTraMaLop(const char* id) {
    for (int i = 0; i < soLuongLop; i++) {
        if (strcmp(danhSachLop[i].classroomId, id) == 0) {
            return 1;
        }
    }
    return 0;
}

void hienThiDanhSachLop() {
    printf("\n--- DANH SACH CAC LOP HOC ---\n");
    if (soLuongLop == 0) {
        printf("Danh sach lop trong!\n");
        return;
    }
    veDuongKe(50);
    printf("| %-10s | %-20s | %-10s |\n", "Ma Lop", "Ten Lop", "GV Phu Trach");
    veDuongKe(50);
    for (int i = 0; i < soLuongLop; i++) {
        printf("| %-10s | %-20s | %-10s |\n", danhSachLop[i].classroomId, danhSachLop[i].className, danhSachLop[i].teacherId);
    }
    veDuongKe(50);
}

void themLop() {
    if (soLuongLop >= 50) {
        printf("Danh sach lop da day, khong the them nua!\n");
        return;
    }
    printf("\n--- THEM LOP HOC ---\n");
    do {
        printf("Nhap ma lop : ");
        fgets(danhSachLop[soLuongLop].classroomId, sizeof(danhSachLop[soLuongLop].classroomId), stdin);
        danhSachLop[soLuongLop].classroomId[strcspn(danhSachLop[soLuongLop].classroomId, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachLop[soLuongLop].classroomId)) {
            printf("Ma lop khong duoc de trong. Vui long nhap lai!\n");
        } else if (kiemTraMaLop(danhSachLop[soLuongLop].classroomId)) {
            printf("Ma lop da ton tai. Vui long nhap ma khac!\n");
        }
    } while (!kiemTraKhongRong(danhSachLop[soLuongLop].classroomId) || kiemTraMaLop(danhSachLop[soLuongLop].classroomId));

    do {
        printf("Nhap ten lop: ");
        fgets(danhSachLop[soLuongLop].className, sizeof(danhSachLop[soLuongLop].className), stdin);
        danhSachLop[soLuongLop].className[strcspn(danhSachLop[soLuongLop].className, "\n")] = '\0';
        if (!kiemTraKhongRong(danhSachLop[soLuongLop].className)) {
            printf("Ten lop khong duoc de trong. Vui long nhap lai!\n");
        }
    } while (!kiemTraKhongRong(danhSachLop[soLuongLop].className));

    strcpy(danhSachLop[soLuongLop].teacherId, "");
    soLuongLop++;
    printf("\n Them lop thanh cong!\n");
}

void suaThongTinLop() {
    char idCanSua[10];
    int viTriSua = -1;
    printf("\n--- SUA THONG TIN LOP ---\n");
    printf("Nhap ID lop muon sua: ");
    fgets(idCanSua, 10, stdin);
    idCanSua[strcspn(idCanSua, "\n")] = '\0';

    viTriSua = timLop(idCanSua);
    if (viTriSua == -1) {
        printf(" ID lop khong ton tai!\n");
        return;
    }

    printf("\n--- Thong tin hien tai cua lop %s ---\n", idCanSua);
    veDuongKe(50);
    printf("| %-10s | %-20s | %-10s |\n", "Ma Lop", "Ten Lop", "GV Phu Trach");
    veDuongKe(50);
    printf("| %-10s | %-20s | %-10s |\n", danhSachLop[viTriSua].classroomId, danhSachLop[viTriSua].className, danhSachLop[viTriSua].teacherId);
    veDuongKe(50);

    printf("\nNhap ten lop moi: ");
    fgets(danhSachLop[viTriSua].className, sizeof(danhSachLop[viTriSua].className), stdin);
    danhSachLop[viTriSua].className[strcspn(danhSachLop[viTriSua].className, "\n")] = '\0';

    printf("\n Sua thong tin lop thanh cong!\n");
}

void xoaLop() {
    char idCanXoa[10];
    int viTriXoa = -1;
    char xacNhan;
    printf("\n--- XOA LOP HOC ---\n");
    printf("Nhap ID lop muon xoa: ");
    fgets(idCanXoa, 10, stdin);
    idCanXoa[strcspn(idCanXoa, "\n")] = '\0';

    viTriXoa = timLop(idCanXoa);
    if (viTriXoa == -1) {
        printf(" ID lop khong ton tai!\n");
        return;
    }

    printf("Ban co chac chan muon xoa lop co ID %s khong? (Y/N): ", idCanXoa);
    scanf(" %c", &xacNhan);
    clearBuffer();

    if (xacNhan == 'y' || xacNhan == 'Y') {
        for (int i = viTriXoa; i < soLuongLop - 1; i++) {
            danhSachLop[i] = danhSachLop[i + 1];
        }
        soLuongLop--;
        printf("\n Xoa lop thanh cong!\n");
    } else {
        printf("\n Huy thao tac xoa lop.\n");
    }
}

void xemChiTietLop() {
    char idCanXem[10];
    int viTriLop = -1;
    printf("\n--- XEM CHI TIET LOP ---\n");
    printf("Nhap ID lop muon xem: ");
    fgets(idCanXem, 10, stdin);
    idCanXem[strcspn(idCanXem, "\n")] = '\0';

    viTriLop = timLop(idCanXem);
    if (viTriLop == -1) {
        printf(" ID lop khong ton tai!\n");
        return;
    }

    printf("\n--- CHI TIET LOP: %s ---\n", danhSachLop[viTriLop].className);
    veDuongKe(50);
    printf("| %-10s | %-20s | %-10s |\n", "Ma Lop", "Ten Lop", "GV Phu Trach");
    veDuongKe(50);
    printf("| %-10s | %-20s | %-10s |\n", danhSachLop[viTriLop].classroomId, danhSachLop[viTriLop].className, danhSachLop[viTriLop].teacherId);
    veDuongKe(50);

    printf("\n--- DANH SACH SINH VIEN THUOC LOP %s ---\n", danhSachLop[viTriLop].className);
    int soLuongSVTrongLop = 0;
    veDuongKe(120);
    printf("| %-8s | %-15s | %-10s | %-10s | %-10s | %-25s | %-15s | %-8s |\n", "Ma SV", "Ten SV", "Lop", "Ngay sinh", "Gioi tinh", "Email", "SDT", "Diem");
    veDuongKe(120);
    for (int i = 0; i < soLuongSV; i++) {
        if (strcmp(danhSachSV[i].classroomId, idCanXem) == 0) {
            printf("| %-8s | %-15s | %-10s | %02d/%02d/%04d | %-10s | %-25s | %-15s | %-8.2f |\n",
               danhSachSV[i].studentId,
               danhSachSV[i].name,
               danhSachSV[i].classroomId,
               danhSachSV[i].dateOfBirth.day,
               danhSachSV[i].dateOfBirth.month,
               danhSachSV[i].dateOfBirth.year,
               danhSachSV[i].gender,
               danhSachSV[i].email,
               danhSachSV[i].phone,
               danhSachSV[i].diem);
            soLuongSVTrongLop++;
        }
    }
    veDuongKe(120);
    if (soLuongSVTrongLop == 0) {
        printf("Lop nay hien khong co sinh vien nao.\n");
    }

    int luaChonChiTiet;
    do {
        printf("\n--- CHON CHUC NANG ---\n");
        printf("1. Them sinh vien vao lop\n");
        printf("2. Xoa sinh vien khoi lop\n");
        printf("0. Quay lai\n");
        printf("Nhap lua chon cua ban: ");
        if (scanf("%d", &luaChonChiTiet) != 1) {
            printf("Lua chon khong hop le. Vui long nhap so!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        switch (luaChonChiTiet) {
            case 1: themSinhVienVaoLop(); break;
            case 2: xoaSinhVienKhoiLop(); break;
            case 0: printf("\nQuay lai menu quan ly lop...\n"); break;
            default: printf("Lua chon khong hop le. Vui long nhap lai!\n");
        }
    } while (luaChonChiTiet != 0);
}

void themSinhVienVaoLop() {
    char idCanThem[10];
    char idLopCanThem[10];
    int viTriSV = -1;
    int viTriLop = -1;
    int soSVTrongLop = 0;

    printf("\n--- THEM SINH VIEN VAO LOP ---\n");


    printf("Nhap ID sinh vien muon them: ");
    fgets(idCanThem, 10, stdin);
    idCanThem[strcspn(idCanThem, "\n")] = '\0';
    viTriSV = kiemTraMaSV(idCanThem);
    if (viTriSV == -1) {
        printf(" ID sinh vien khong ton tai!\n");
        return;
    }

    if (strcmp(danhSachSV[viTriSV].classroomId, "Chua co") != 0 && strlen(danhSachSV[viTriSV].classroomId) > 0) {
        printf(" Sinh vien da nam trong lop khac (%s).\n", danhSachSV[viTriSV].classroomId);
        return;
    }
    hienThiDanhSachLop();
    printf("Nhap ID lop muon them sinh vien vao: ");
    fgets(idLopCanThem, 10, stdin);
    idLopCanThem[strcspn(idLopCanThem, "\n")] = '\0';
    viTriLop = timLop(idLopCanThem);
    if (viTriLop == -1) {
        printf(" ID lop khong ton tai!\n");
        return;
    }

    // Đếm số lượng sinh viên trong lớp để kiểm tra giới hạn
    for (int i = 0; i < soLuongSV; i++) {
        if (strcmp(danhSachSV[i].classroomId, idLopCanThem) == 0) {
            soSVTrongLop++;
        }
    }

    if (soSVTrongLop >= 50) { // Giả định mỗi lớp có tối đa 50 sinh viên
        printf(" Lop da du so luong sinh vien. Khong the them nua!\n");
        return;
    }

    // Thêm sinh viên vào lớp
    strcpy(danhSachSV[viTriSV].classroomId, idLopCanThem);
    printf("\n Them sinh vien %s vao lop %s thanh cong!\n", danhSachSV[viTriSV].name, danhSachLop[viTriLop].className);
}

void xoaSinhVienKhoiLop() {
    char idCanXoa[10];
    char idLopCanXoa[10];
    int viTriSV = -1;
    int viTriLop = -1;
    char xacNhan;

    printf("\n--- XOA SINH VIEN KHOI LOP ---\n");

    hienThiDanhSachLop();
    printf("Nhap ID lop chua sinh vien muon xoa: ");
    fgets(idLopCanXoa, 10, stdin);
    idLopCanXoa[strcspn(idLopCanXoa, "\n")] = '\0';
    viTriLop = timLop(idLopCanXoa);
    if (viTriLop == -1) {
        printf(" ID lop khong ton tai!\n");
        return;
    }

    printf("Nhap ID sinh vien muon xoa khoi lop: ");
    fgets(idCanXoa, 10, stdin);
    idCanXoa[strcspn(idCanXoa, "\n")] = '\0';
    viTriSV = kiemTraMaSV(idCanXoa);
    if (viTriSV == -1 || strcmp(danhSachSV[viTriSV].classroomId, idLopCanXoa) != 0) {
        printf(" ID sinh vien khong ton tai trong lop nay!\n");
        return;
    }

    printf("Ban co chac chan muon xoa sinh vien co ID %s khoi lop %s khong? (Y/N): ", idCanXoa, idLopCanXoa);
    scanf(" %c", &xacNhan);
    clearBuffer();

    if (xacNhan == 'y' || xacNhan == 'Y') {
        strcpy(danhSachSV[viTriSV].classroomId, "Chua co");
        printf("\n Xoa sinh vien thanh cong!\n");
    } else {
        printf("\n Huy thao tac xoa.\n");
    }
}

void sapXepDanhSachLop() {
    int luaChonSapXep;
    printf("\n--- SAP XEP DANH SACH LOP ---\n");
    printf("1. Theo ten lop (A-Z)\n");
    printf("2. Theo ten lop (Z-A)\n");
    printf("0. Quay lai\n");
    printf("Nhap lua chon cua ban: ");
    if (scanf("%d", &luaChonSapXep) != 1) {
        printf("Lua chon khong hop le. Vui long nhap so nguyen!\n");
        clearBuffer();
        return;
    }
    clearBuffer();

    switch (luaChonSapXep) {
        case 1: {
            Classroom temp;
            for (int i = 0; i < soLuongLop - 1; i++) {
                for (int j = i + 1; j < soLuongLop; j++) {
                    if (strcmp(danhSachLop[i].className, danhSachLop[j].className) > 0) {
                        temp = danhSachLop[i];
                        danhSachLop[i] = danhSachLop[j];
                        danhSachLop[j] = temp;
                    }
                }
            }
            printf("\n Sap xep danh sach lop theo ten (A-Z) thanh cong!\n");
            hienThiDanhSachLop();
            break;
        }
        case 2: {
            Classroom temp;
            for (int i = 0; i < soLuongLop - 1; i++) {
                for (int j = i + 1; j < soLuongLop; j++) {
                    if (strcmp(danhSachLop[i].className, danhSachLop[j].className) < 0) {
                        temp = danhSachLop[i];
                        danhSachLop[i] = danhSachLop[j];
                        danhSachLop[j] = temp;
                    }
                }
            }
            printf("\n Sap xep danh sach lop theo ten (Z-A) thanh cong!\n");
            hienThiDanhSachLop();
            break;
        }
        case 0:
            printf("Quay lai menu truoc...\n");
            break;
        default:
            printf(" Lua chon khong hop le!\n");
            break;
    }
}

void menuQuanLyLop() {
    int luaChon;
    do {
        printf("========================================\n");
        printf("        MENU QUAN LY LOP HOC\n");
        printf("----------------------------------------\n");
        printf("1. Hien thi danh sach lop\n");
        printf("2. Them lop\n");
        printf("3. Sua thong tin lop\n");
        printf("4. Xoa lop\n");
        printf("5. Xem chi tiet lop\n");
        printf("6. Sap xep danh sach lop\n");
        printf("0. Quay lai menu chinh\n");
        printf("----------------------------------------\n");
        printf("Vui long nhap lua chon cua ban: ");
        if (scanf("%d", &luaChon) != 1) {
            printf("Lua chon khong hop le. Vui long nhap mot so tu 0 den 6!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        switch (luaChon) {
            case 1: hienThiDanhSachLop(); break;
            case 2: themLop(); break;
            case 3: suaThongTinLop(); break;
            case 4: xoaLop(); break;
            case 5: xemChiTietLop(); break;
            case 6: sapXepDanhSachLop(); break;
            case 0: printf("\nQuay lai menu chinh...\n"); break;
            default: printf("Lua chon khong hop le. Vui long nhap lai!\n");
        }
        printf("\n");
    } while (luaChon != 0);
}


void khoiTaoDuLieu() {
}

void luuDuLieuLop() {
    FILE *file;
    file = fopen("danhsachlop.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file de luu du lieu!\n");
        return;
    }
    for (int i = 0; i < soLuongLop; i++) {
        fprintf(file, "%s,%s,%s\n",
                danhSachLop[i].classroomId,
                danhSachLop[i].className,
                danhSachLop[i].teacherId);
    }
    fclose(file);
    printf("\nLuu du lieu lop vao file danhsachlop.txt thanh cong!\n");
}

void docDuLieuLop() {
    FILE *file;
    file = fopen("danhsachlop.txt", "r");
    if (file == NULL) {
        printf("Khong tim thay file danhsachlop.txt. Chuong trinh se bat dau voi du lieu trong.\n");
        return;
    }
    while (soLuongLop < 50 && fscanf(file, "%[^,],%[^,],%[^\n]\n",
           danhSachLop[soLuongLop].classroomId,
           danhSachLop[soLuongLop].className,
           danhSachLop[soLuongLop].teacherId) == 3) {
        soLuongLop++;
    }
    fclose(file);
    printf("Doc du lieu lop tu file danhsachlop.txt thanh cong!\n");
}

int main() {
    khoiTaoDuLieu();
    docDuLieuLop();
    int luaChonMenuChinh;
    while (1) {
        printf("========================================\n");
        printf("        HE THONG QUAN LY TRUONG HOC\n");
        printf("========================================\n");
        printf("1. Quan ly sinh vien\n");
        printf("2. Quan ly giao vien\n");
        printf("3. Quan ly lop\n");
        printf("0. Thoat chuong trinh\n");
        printf("----------------------------------------\n");
        printf("Vui long nhap lua chon cua ban: ");
        if (scanf("%d", &luaChonMenuChinh) != 1) {
            printf("Lua chon khong hop le. Vui long nhap mot so!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (luaChonMenuChinh) {
            case 1:
                menuQuanLySinhVien();
                break;
            case 2:
                menuQuanLyGiaoVien();
                break;
            case 3:
                menuQuanLyLop();
                break;
            case 0:
                luuDuLieuLop();
                printf("\n--- Cam on da su dung he thong! ---\n");
                return 0;
            default:
                printf("Lua chon khong hop le. Vui long nhap lai!\n");
        }
    }
    return 0;
}
