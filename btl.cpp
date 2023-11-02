/*
    Author: Team
    File name: Quản lý hóa đơn vật tư
*/

#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define int long long int
#define F first
#define S second
#define pb push_back
#define vi vector<int>
#define endl '\n'
#define sz(x) ((int) x.size())
#define all(p) p.begin(),p.end()
#define pause system("pause")
#define cls system("clear")


template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
    const char* comma = strchr (names + 1, ',');
    cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}



struct VatLieu
{
    string maVL;
    string tenVL;
    int donGia;
    int soLuong;
    int thanhTien;
};

struct HoaDon
{
    string maHoaDon;
    string ngayLap;
    string khachHang;
    int soLoaiVatLieu;
    int tongTien = 0;
    string sdt;
    int thueVAT;
    int tongTienThanhToan;
    vector<VatLieu> dsVatLieu;
};

struct Node {
    HoaDon info;
    Node* next;
};

struct ListHD {
    Node* Head;
    Node* Tail;
};

int thanhTien(int dongia, int thanhTien) {
    return dongia * thanhTien;
}

VatLieu nhapVatLieu() {
    VatLieu x;
    fflush(stdin);
    cout << "Ma vat lieu: \t"; cin >> x.maVL;
    fflush(stdin);
    cout << "Ten vat lieu: \t"; getline(cin, x.tenVL);
    cout << "Don gia: \t"; cin >> x.donGia;
    cout << "So luong: \t"; cin >> x.soLuong;
    x.thanhTien = thanhTien(x.donGia, x.soLuong);
    return x;
}

HoaDon nhapHoaDon() {
    HoaDon x;
    fflush(stdin);
    cout << "Ma hoa don: \t"; cin >> x.maHoaDon;
    fflush(stdin);
    cout << "Ngay Lap: \t"; getline(cin, x.ngayLap);
    fflush(stdin);
    cout << "Khach hang: \t"; getline(cin, x.khachHang);
    cout << "So dien thoai: \t"; getline(cin, x.sdt);
    cout << "So loai vat lieu: \t"; cin >> x.soLoaiVatLieu;
    for (int i = 0; i < x.soLoaiVatLieu; i++) {
        cout << "\nVat lieu " << (i + 1) << ": \n";
        x.dsVatLieu.pb(nhapVatLieu());
    }
    cout << "Thue Vat: \t"; cin >> x.thueVAT;
    for (VatLieu v : x.dsVatLieu) {
        x.tongTien += v.thanhTien;
    }
    cout << "Tong tien: \t" << x.tongTien << endl;
    x.tongTienThanhToan = x.tongTien - x.thueVAT > 0 ? x.tongTien - x.thueVAT : 0;
    cout << "Tong tien thanh toan: \t" << x.tongTienThanhToan << endl;
    return x;
}

void init(ListHD &list) {
    list.Head = NULL;
    list.Tail = NULL;
}

bool isEmty(ListHD list) {
    if (list.Head == NULL) return true;
    return false;
}

Node* taoNode(HoaDon hd) {
    Node* p = new Node;
    if (p == NULL) {
        cout << "Khong du bo nho!\n";
        return NULL;
    }
    p -> info = hd;
    p -> next = NULL;
    return p;
}

void addHead(ListHD &list, HoaDon hd) {
    Node* node = taoNode(hd);
    if (node == NULL) exit(0);
    if (!isEmty(list)) {
        node -> next = list.Head;
        list.Head = node;
    } else {
        list.Head = node;
        list.Tail = node;
    }
}

void addTail(ListHD &list, HoaDon hd) {
    Node* node = taoNode(hd);
    if (node == NULL) exit(0);
    if (!isEmty(list)) {
        list.Tail -> next = node;
        list.Tail = node;
    } else {
        list.Head = node;
        list.Tail = node;
    }
}
void nhapListHD(ListHD &list) {
    int sl = 1;
    do {
        if (sl < 0) cout << "So luong phai lon hon 0!\n";
        cout << "Nhap so luong hoa don can them: \n";
        cin >> sl;
    } while (sl <= 0);

    for (int i = 0; i < sl; i++) {
        addTail(list, nhapHoaDon());
    }
}

string formatMoney(int a) {
    string s = "";
    while (a > 999) {
        s = "." + to_string(a % 1000) + s;
        a /= 1000;
    }
    return s;
}

void inDsVatLieu(const vector<VatLieu> v, int sl) {
    cout << left << setw(5) << "STT" << left << setw(30) << "Ma vat lieu"
         << left << setw(50) << "Ten vat lieu" << left << setw(20) << "Don gia"
         << left << setw(10) << "So luong" << left << setw(10) << "Thanh tien" << endl;
    for (int i = 0; i < sl; i++) {
        cout << left << setw(5) << (i + 1) << left << setw(30) << v[i].maVL
             << left << setw(50) << v[i].tenVL << left << setw(20) << v[i].donGia
             << left << setw(10) << v[i].soLuong << left << setw(10) << v[i].thanhTien;
        cout << endl;
    }

}

void inHoaDon(HoaDon hd) {
    cout << "\n__________________________HOADON___________________________\n";
    cout << left << setw(30) << "Ma hoa don: " << hd.maHoaDon << endl
         << left << setw(30) << "Ngay lap: " << hd.ngayLap << endl
         << left << setw(30) << "Khach hang: " << hd.khachHang << endl
         << left << setw(30) << "So loai vat lieu: " << hd.soLoaiVatLieu << endl;
    cout << "Danh sach vat lieu: \n";
    inDsVatLieu(hd.dsVatLieu, hd.dsVatLieu.size());
    cout << left << setw(30) << "Tong Tien: " << hd.tongTien << endl;
    cout << left << setw(30) << "Thue Vat" << hd.thueVAT << endl;
    cout << left << setw(30) << "Tong tien thanh toan: " << hd.tongTienThanhToan << endl;
}


void inListHoaDon(const ListHD list) {
    Node* node = list.Head;
    while (node != NULL) {
        HoaDon hd = node -> info;
        inHoaDon(hd);
        node = node -> next;
    }
}

void ghiFileHoaDon(const ListHD &list) {
    ofstream outFile("hoadon.dat", ios::binary);
    if (!outFile) {
        cout << "Không thể mở file để ghi." << endl;
        exit(0);
    }
    Node* n = list.Head;
    int slhd = 0;
    while (n != NULL) {
        slhd++;
        n = n -> next;
    }
    outFile.write(reinterpret_cast<const char*>(&slhd), sizeof(slhd));
    Node* node = list.Head;
    while (node != NULL) {
        outFile.write(reinterpret_cast<char*>(&(node -> info)), sizeof(node -> info));
        node = node -> next;
    }
    outFile.close();
}

ListHD docFileHoaDon() {
    ListHD listz;
    init(listz);
    ifstream inFile("hoadon.dat", ios::binary);
    if (!inFile) {
        cout << "Khong the mo file\n";
        exit(0);
    }
    int slhd;
    inFile.read(reinterpret_cast<char*>(&slhd), sizeof(slhd));
    for (int i = 0; i < slhd; i++) {
        HoaDon hd;
        inFile.read(reinterpret_cast<char*>(&hd), sizeof(HoaDon));
        addTail(listz, hd);
    }
    inFile.close();
    return listz;
}

void Sua_vat_lieu_theo_ma_hoa_don(ListHD &list)
{
    string maHoadon;
    string maVL;
    cout << "Moi ban nhap ma hoa don can sua vat lieu:"; cin >> maHoadon;
    Node* node = list.Head;
    while (node != NULL) {
        HoaDon hd = node -> info;
        if(hd.maHoaDon == maHoadon) 
        {
            inDsVatLieu(hd.dsVatLieu, hd.dsVatLieu.size());
            cout << "Moi ban nhap ma vat lieu de sua vat lieu:"; cin >> maVL;
            for(int i = 0; i < hd.dsVatLieu.size(); i++) {
                if(hd.dsVatLieu[i].maVL == maVL) {
                    VatLieu x = nhapVatLieu();
                    node->info.dsVatLieu[i] = x;
                    cout << "Sua thanh cong!\n";
                    return;
                }
            }
        }
        node = node -> next;
    }
    cout << "Khong tim thay ma vat lieu!";
}

void Sua_hoa_don_theo_ma_hoa_don(ListHD &list){
    string maHD;
    cout << "Moi ban nhap ma hoa don can sua:"; cin >> maHD;
    
    Node* node = list.Head;
    while (node != NULL)
    {
        HoaDon hd = node -> info;
        if(hd.maHoaDon == maHD) 
        {
            inHoaDon(hd);
            HoaDon hdsua = nhapHoaDon();
            node->info = hdsua;
            return;
        }
    }

    cout << "Khong tim thay\n";
    

}



void inMenu() {
    cout << "1. Them hoa don.\n"
         << "2. Luu vao file.\n"
         << "3. Doc tu file. \n"
         << "4. In danh sach hoa don.\n"
         << "5. Sua vat lieu mua theo ma hoa don.\n"
         << "6. Sua hoa don theo ma hoa don.\n"
         << "7. Thay doi thong tin khach hang theo ma khach hang."
         << "0. Nau an.\n"
         << "Nhap lua chon:\t";
}

void doMenu(ListHD &list) {
    int n;
    do {
        inMenu();
        cin >> n;
        cls;
        switch (n) {
        case 0:
            cout << "Ban da cook!\n";
            pause;
            exit(0);
        case 1:
            nhapListHD(list); cout << endl;
            pause;
            cls;
            break;
        case 2:
            ghiFileHoaDon(list);
            cout << "Ghi thanh cong!\n";
            pause; cls;
            break;
        case 3:
            list = docFileHoaDon();
            cout << "Danh sach hoa don sau khi doc: \n";
            inListHoaDon(list);
            break;
        case 4:
            inListHoaDon(list);
            pause; cls;
            break;
        case 5:
            Sua_vat_lieu_theo_ma_hoa_don(list);
            break;
        case 6:
            Sua_hoa_don_theo_ma_hoa_don(list);
            break;
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }
		cls;
    } while (n != 0);
}
main() {

    ListHD list;
    init(list);
    doMenu(list);
}

/*
1.Nhap so luong hoa don
2.Nhập danh sách hóa đơn.
3.Hiện danh sách hóa đơn. 
4.Ghi file danh sach hoa don.
5.Doc file danh sach hoa don.
5.Sua vat lieu mua theo ma hoa don.
6.Sua hoa don theo ma hoa don.
7.Thay doi thong tin hoa don theo ma khach hang.
8.Tim kiem hoa don theo ma hoa don.
9.Tim vat lieu co don gia cao nhat.
10.Tim kiem hoa don co tong tien lon nhat
11.Sap xep hoa don theo tong tien tang dan.
12.Sap xep hoa don theo ma hoa don.
13.Sap xep hoa don theo so luong mua tang dan.
14.Nhập vào từ bàn phím thông tin của Hóa đơn x , chèn Hóa đơn x vào danh sách sao cho vẫn đảm bảo danh sách được sắp xếp theo thứ tự tăng dần của tổng tiền từng Hóa đơn.   
15.Tinh tong tien cua tat ca cac Hoa don
16.Tinh doanh thi cua cua hang trong thang k(k duoc nhap tu ban phim).
17.Tính tổng số lượng vật tư đã mua trong danh sách Hóa đơn. Tinh tong so luong vat tu da mua trong danh sach Hoa don
18.Tinh trung binh tong tien cua tat ca cac hoa don.
19.Diem so Hoa don co tong tien y
20.Dem so vat lieu xay dung co don gia tren x.
21.Xoa Hoa don co tong tien thap nhat.
22.Xoa hoa don theo ma Hoa don nhap tu ban phim
23.Thống kê – hiển thị các vật liệu xây dựng có đơn giá > y. Thong ke - hien thi cac vat lieu xay dung co don gia > y
24. Hiển thị danh sách mã vật liệu xây dựng và tên vật liệu xây dựng theo số lượng mua nhập từ bàn phím.	
*/

