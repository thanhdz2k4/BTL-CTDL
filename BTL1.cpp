#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

struct VatLieu 
{
    string maVL;
    string tenVL;
    float donGia;
    int soLuong;
    double thanhTien;
};

struct HoaDon 
{
    string maHoaDon;
    string ngayLap;
    string tenCuaHang;
    string khachHang;
    string makhachhang;
    int soLoaiVatLieu;
    double tongTien;
    string sdt;
    float thueVAT;
    double tongTienThanhToan;
    VatLieu ds_vatlieu[100];
};

void NhapVatLieu(VatLieu &vatlieu)
{
    cout << "Nhap ma vat lieu:"; cin >> vatlieu.maVL;
    cin.ignore();
    cout << "Nhap ten vat lieu:"; getline(cin, vatlieu.tenVL);
    cout << "Nhap so luong:"; cin >> vatlieu.soLuong;
    cout << "Nhap don gia:"; cin >> vatlieu.donGia;
    vatlieu.thanhTien = vatlieu.donGia * vatlieu.soLuong;
}


void XuatVatLieu(VatLieu vatlieu)
{
    cout 
    << setw(15) << vatlieu.maVL 
    << setw(15) << vatlieu.tenVL 
    << setw(15) << vatlieu.soLuong 
    << setw(15) << vatlieu.donGia 
    << setw(15) << vatlieu.thanhTien << endl;
}


void NhapDanhSachVatLieu(VatLieu dsvl[], int soloaivatlieu) 
{
    for(int i = 0; i < soloaivatlieu; i++) 
    {
        NhapVatLieu(dsvl[i]);
    }
}

double tongtien(HoaDon hoadon) 
{
    double sum = 0;
    for(int i = 0; i < hoadon.soLoaiVatLieu; i++) 
    {
        sum += hoadon.ds_vatlieu[i].thanhTien;
    }
    return sum;
}

double thanhtienVAT(HoaDon hoadon) 
{
    return tongtien(hoadon) + (tongtien(hoadon)*hoadon.thueVAT/100);
}



void XuatDanhSachVatLieu(VatLieu dsvl[], int soloaivatlieu) 
{
    for(int i = 0; i < soloaivatlieu; i++) 
    {
        XuatVatLieu(dsvl[i]);
    }
}


void NhapHoaDon(HoaDon &hoadon) 
{
    cout << "Nhap ma hoa don:"; cin >> hoadon.maHoaDon;
    cout << "Nhap ngay/thang/nam:"; cin >> hoadon.ngayLap;
    cin.ignore();
    cout << "Nhap ten cua hang:"; getline(cin, hoadon.tenCuaHang);
    cout << "Nhap sdt khach hang:"; cin >> hoadon.sdt;
    cin.ignore();
    cout << "Nhap ten khach hang:"; getline(cin, hoadon.khachHang);
    cout << "Nhap ma khach hang:"; getline(cin, hoadon.makhachhang);
    cout << "Nhap so loai vat lieu:"; cin >> hoadon.soLoaiVatLieu;
    cout << "Nhap danh sach vat lieu\n";
    NhapDanhSachVatLieu(hoadon.ds_vatlieu, hoadon.soLoaiVatLieu);
    cout << "Nhap thue vat:"; cin >> hoadon.thueVAT; 
}

void XuatHoaDon(HoaDon hoadon) 
{
    cout << "Ma hoa don:" << hoadon.maHoaDon << endl;
    cout << "Ngay/thang/nam:" << hoadon.ngayLap << endl;
    cout << "Ten cua hang:" << hoadon.tenCuaHang << endl;
    cout << "Ten khach hang:" << hoadon.khachHang << endl;
    cout << "Ma khach hang:" << hoadon.makhachhang << endl;
    cout << "SDT:" << hoadon.sdt << endl;
    XuatDanhSachVatLieu(hoadon.ds_vatlieu, hoadon.soLoaiVatLieu);
    cout << "Tong tien thanh toan:" << thanhtienVAT(hoadon);
}



struct NodeHD
{
    HoaDon infor;
    NodeHD *next;
};

struct List
{
    NodeHD* PHead;
    NodeHD* pTail;
};

void CreateList(List &l)
{
    l.pTail = NULL;
    l.PHead = NULL;
}


NodeHD* CreateNode(HoaDon iniData)
{
    NodeHD* p = new NodeHD;
    p->infor = iniData;
    p->next = NULL;
    return p;
}

void AddHead(List &l, NodeHD* p)
{
    if(l.PHead == NULL)
    {
        l.PHead = p;
        l.pTail = p;
    } 
    else
    {
        p->next =l.PHead;
        l.PHead = p;
    }
}

void XuatDanhSachHoaDon(List l) 
{
    NodeHD *p = l.PHead;
    while (p != NULL)
    {
        XuatHoaDon(p->infor);
        p = p -> next;
    }    
}

void NhapDanhSachHoaDon(List &list, int soluongHD)
{
    for(int i = 0; i < soluongHD; i++) 
    {
        HoaDon hoadon;
        NhapHoaDon(hoadon);
        NodeHD *x = CreateNode(hoadon);
        AddHead(list, x);
    }
}
void ghiDanhSachHoaDon(const List& dsHD, const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (outFile.is_open()) {
        NodeHD* p = dsHD.PHead;
        while (p != NULL) {
            // Ghi từng hóa đơn vào file nhị phân
            outFile.write(reinterpret_cast<char*>(&p->infor), sizeof(HoaDon));
            p = p->next;
        }
        outFile.close();
        cout << "Danh sach hoa don da duoc ghi vao " << filename << endl;
    } else {
        cerr << "Loi: Khong the mo tep de ghi." << endl;
    }
}


List docDanhSachHoaDon(const string& filename) {
    List dsHD;
    CreateList(dsHD);
    ifstream inFile(filename, ios::binary);
    if (inFile.is_open()) {
        while (inFile.read(reinterpret_cast<char*>(&dsHD.PHead->infor), sizeof(HoaDon))) {
            NodeHD* x = CreateNode(dsHD.PHead->infor);
            AddHead(dsHD, x);
        }
        inFile.close();
        cout << "Danh sach hoa don da duoc doc tu " << filename << endl;
    } else {
        cerr << "Loi: Khong the mo tep de doc." << endl;
    }
    return dsHD;
}

int main() {
    //  List dsHD;
    // CreateList(dsHD);
    // NhapDanhSachHoaDon(dsHD, 2);
    // ghiDanhSachHoaDon(dsHD, "danhsachhoadon.bin");
    List dsHDRead = docDanhSachHoaDon("danhsachhoadon.bin");

   
    cout << "Danh sach hoa don da doc:" << endl;
    XuatDanhSachHoaDon(dsHDRead);
    return 0;
}
