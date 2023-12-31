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
    string makhachhang;
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
    cout << "Ma khach hang: \t"; getline(cin, x.makhachhang);
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
         << left << setw(30) << "Ma khach hang:" << hd.makhachhang << endl
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

string nhapkitu() 
{
    string x; cin >> x;
    return x;
}

void Sua_vat_lieu_theo_ma_hoa_don(ListHD &list)
{
    string maHoadon;
    string maVL;
    cout << "Moi ban nhap ma hoa don can sua vat lieu:"; maHoadon = nhapkitu();

    Node* node = list.Head;
    while (node != NULL) {
        HoaDon hd = node -> info;
        if(hd.maHoaDon == maHoadon) 
        {
            inDsVatLieu(hd.dsVatLieu, hd.dsVatLieu.size());
            cout << "Moi ban nhap ma vat lieu de sua vat lieu:"; maVL = nhapkitu();

            for(int i = 0; i < hd.dsVatLieu.size(); i++)
            {
                if(hd.dsVatLieu[i].maVL == maVL) 
                {
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
    cout << "Moi ban nhap ma hoa don can sua:"; maHD = nhapkitu();
    
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
        node = node -> next;
    }
    cout << "Khong tim thay\n";
}


void Thay_doi_thong_tin_HD_theo_ma_KH(ListHD &list){
    string maKH;
    cout << "Nhap ma khach hang de sua:"; maKH = nhapkitu();
    
    Node* node = list.Head;
    while (node != NULL)
    {
        HoaDon hd = node -> info;
        if(hd.makhachhang == maKH) {
            inHoaDon(hd);
            HoaDon hdsua = nhapHoaDon();
            node->info = hdsua;
            return;
        }
        node = node -> next;
    }
    cout << "Khong tim thay\n"; 
}

void Tim_HD_theo_ma(ListHD list) {
    string maHD;
    cout << "Nhap ma hoa don de tim:"; maHD = nhapkitu();

    Node* node = list.Head;
    while (node != NULL)
    {
        HoaDon hd = node -> info;
        if(hd.maHoaDon == maHD) {
            inHoaDon(hd);
            return;
        }
        node = node -> next;
    }
    cout << "Khong tim thay\n"; 
}

VatLieu VL_don_gia_cao_nhat(ListHD list)
{
    VatLieu max = list.Head->info.dsVatLieu[0];

    Node* node = list.Head;
    while (node != NULL)
    {
        HoaDon hd = node ->info;
        for(int i = 0; i < hd.dsVatLieu.size(); i++) 
        {
            if(max.thanhTien < hd.dsVatLieu[i].thanhTien) 
            {
                max = hd.dsVatLieu[i];
            }
        }
        node = node -> next;
    }
    return max;
}

HoaDon HD_tong_tien_cao_nhat(ListHD list)
{
    HoaDon HD = list.Head->info;

    Node* node = list.Head;
    while (node != NULL)
    {
        HoaDon hd = node ->info;
        if(HD.tongTien < hd.tongTien) {
            HD = hd;
        }
        node = node -> next;
    }
    return HD;
}

void SX_HD_tang_dan_theo_tong_tien(ListHD &list) 
{
     if (list.Head == NULL || list.Head->next == NULL) return; 

    bool swapped;
    Node *ptr1;
    Node *lptr = NULL;

    do {
        swapped = false;
        ptr1 = list.Head;

        while (ptr1->next != lptr) {

            if (ptr1->info.tongTien > ptr1->next->info.tongTien) {
                HoaDon temp = ptr1->info;
                ptr1->info = ptr1->next->info;
                ptr1->next->info = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


void SX_HD_tang_dan_theo_so_loai_vat_lieu(ListHD &list) 
{
     if (list.Head == NULL || list.Head->next == NULL) return; 

    bool swapped;
    Node *ptr1;
    Node *lptr = NULL;

    do {
        swapped = false;
        ptr1 = list.Head;

        while (ptr1->next != lptr) {

            if (ptr1->info.dsVatLieu.size() > ptr1->next->info.dsVatLieu.size()) {
                HoaDon temp = ptr1->info;
                ptr1->info = ptr1->next->info;
                ptr1->next->info = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


void SX_HD_giam_dan_theo_tong_tien(ListHD &list) 
{
    if (list.Head == NULL || list.Head->next == NULL) return; 

    bool swapped;
    Node *ptr1;
    Node *lptr = NULL;

    do {
        swapped = false;
        ptr1 = list.Head;

        while (ptr1->next != lptr) {

            if (ptr1->info.tongTien < ptr1->next->info.tongTien) {
                HoaDon temp = ptr1->info;
                ptr1->info = ptr1->next->info;
                ptr1->next->info = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void Them_HD_Tang_dan_theo_tong_tien(ListHD &list)
{
    HoaDon hd;
    hd = nhapHoaDon();
    addTail(list, hd);
    SX_HD_tang_dan_theo_tong_tien(list);
}

double Tong_tien_danh_sach_HD(ListHD list)
{
    double sum;

    Node* node = list.Head;
    while (node != NULL)
    {
        HoaDon hd = node ->info;
        sum += hd.tongTien;
        node = node -> next;
    }
    return sum;
}

string tachThang(string x) {
    int dem = 0;

    // Sử dụng istringstream để tách chuỗi
    istringstream ss(x);
    string thang;
    while (getline(ss, thang, '/')) {
        dem++;
        if(dem == 1) return thang;
    }
    return 0;
}


double Doanh_thu_trong_thang(ListHD list)
{
    double sum;
    string thang;
    int dem = 0;
    cout << "Nhap thang can lay doanh thu:";
    thang = nhapkitu();
    string thanghople[12] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
    for(int i = 0; i < thanghople->size(); i++) {
        if(thang != thanghople[i]) {
            dem++;
        }
    }
    if(dem == 12)  
    { 
        cout << "Khong hop le!";
        return 1; 
    }

    
    Node* node = list.Head;
    while (node != NULL)
    {
        HoaDon hd = node ->info;
        string thangHD = tachThang(hd.ngayLap);
        if(thangHD == thang) 
        {
            sum += hd.tongTien;
        }

        node = node -> next;
    }
    return sum;
}

void inMenu() {
    cout << "1. Them hoa don.\n"
         << "2. Luu vao file.\n"
         << "3. Doc tu file. \n"
         << "4. In danh sach hoa don.\n"
         << "5. Sua vat lieu mua theo ma hoa don.\n"
         << "6. Sua hoa don theo ma hoa don.\n"
         << "7. Thay doi thong tin hoa don theo ma khach hang.\n"
         << "8. Tim kiem hoa don theo ma hoa don.\n"
         << "9. Tim vat lieu co don gia cao nhat trong ma hoa don cu the\n"
         << "10.Tim kiem hoa don co tong tien lon nhat\n"
         << "11.Sap xep hoa don theo tong tien tang dan\n"
         << "12.Sap xep hoa don tang dan theo so loai vat vat lieu.\n"
         << "13.Sap xep hoa don theo tong tien giam dan.\n"
         << "14.Nhập vào từ bàn phím thông tin của Hóa đơn x , chèn Hóa đơn x vào danh sách sao cho vẫn đảm bảo danh sách được sắp xếp theo thứ tự tăng dần của tổng tiền từng Hóa đơn.\n"
         << "15.Tinh tong tien cua tat ca cac Hoa don.\n"
         << "16.Tinh doanh thu cua cua hang trong thang k(k duoc nhap tu ban phim).\n"
         << "0. Nau an.\n"
         << "Nhap lua chon:\t";
}

void doMenu(ListHD &list) {
    int n;
    VatLieu vl ;
    HoaDon hd;
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
            //ghiFileHoaDon(list);
            //cout << "Ghi thanh cong!\n";
            //pause; cls;
            break;
        case 3:
            //list = docFileHoaDon();
            //cout << "Danh sach hoa don sau khi doc: \n";
            //inListHoaDon(list);
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
        case 7:
            Thay_doi_thong_tin_HD_theo_ma_KH(list);
            break;
        case 8: 
            Tim_HD_theo_ma(list);
            break;
        case 9:
            vl = VL_don_gia_cao_nhat(list);
            cout << "Vat lieu co don gia cao nhat la:" << vl.tenVL << endl;
            break;
        case 10:
            hd = HD_tong_tien_cao_nhat(list);
            cout << "Hoa don co tong tien cao nhat la:\n";
            inHoaDon(hd);
            break;
        case 11:
            cout << "Danh sach hoa don sau khi sap xep tang dan la\n";
            SX_HD_tang_dan_theo_tong_tien(list);
            inListHoaDon(list);
            break;
        case 12:
            cout << "Danh sach hoa don sau khi sap xep tang dan so loai vat lieu la\n";
            SX_HD_tang_dan_theo_so_loai_vat_lieu(list);
            inListHoaDon(list);
            break;
        case 13:
            cout << "Danh sach hoa don sau khi sap xep giam dan theo tong tien la\n";
            SX_HD_giam_dan_theo_tong_tien(list);
            inListHoaDon(list);
            break;
        case 14:
            Them_HD_Tang_dan_theo_tong_tien(list);
            break;
        case 15:
            cout << "Tong tien danh sach hoa don la:" << Tong_tien_danh_sach_HD(list) << "\n";
            break;
        case 16:
            cout << "Tong doanh thu trong thang la:" << Doanh_thu_trong_thang(list) << "\n";
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
12.Sap xep hoa don tang dan theo so luong vat vat lieu.
13.Sap xep hoa don theo tong tien giam dan.
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

