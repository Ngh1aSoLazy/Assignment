#include<iostream>

using namespace std;

/*
    Cài đặt cây AVL để nhập một dãy số cho trước (dãy cho trên lớp) thành một cây AVL 

    Yêu cầu:
        Cài đặt hàm nhập node mới
        Cài đặt hàm xoay đơn/kép
        Cài đặt hàm kiểm tra cân bằng
        Cài đặt hàm in cây AVL (theo thứ tự duyệt)
*/

// Cấu trúc 1 node
struct NODE
{
    int data; // Biến lưu giá trị của của node
    NODE* left;
    NODE* right;

    // val la gia tri duoc them vao
    NODE(int val) // Hàm khởi tạo của struct | Gọi tự động khi khởi tạo 1 đối tượng mới | Không có kiểu dữ liệu trả về
    {
        data = val;
        // Khởi tạo con trai, con phai
        left = NULL;
        right = NULL;
    }
};

// Hàm tạo 1 node
NODE* MAKE_NODE(int data)
{
    NODE* p = new NODE(data); // Gán địa chỉ của node mới cho pointer p
    return p;
}

// Hàm insert
NODE* INSERT(NODE* root, int data)
{
    if(root == NULL) return MAKE_NODE(data);
    else if(data <= root->data) root->left = INSERT(root->left, data);
    else if(data > root->data)  root->right = INSERT(root->right, data);
    
    return root;
}

// Hàm xoay đơn, kép
void LL(NODE* root)
{
    
}

// Hàm kiểm tra cân bằng
int IS_BALANCE(NODE* root, int &bal_factor)
{
    int hl, hr;

    bal_factor = hl - hr;

    
    if(bal_factor == -1 || bal_factor == 0 || bal_factor == 1) return 1;
    else return 0;


}

// Duyệt cây theo kiểu tiền tố (gốc - trái - phải)
void PREFIX(NODE* root)
{
    if(root == NULL) return;
    cout << root->data << " ";
    PREFIX(root->left);
    PREFIX(root->right); 
}

int main()
{
    NODE* root = NULL; // Khởi tạo cây ban đầu rỗng
    int n, data; // n là số phần tử cần nhập | data là giá trị nhập vào
    cin >> n;
    
    // Vòng lặp để nhập n lần
    for(int i = 0; i < n; i++)
    {
        cin >> data;
        root = INSERT(root, data); // Hàm nhập
    }

    // Hàm in cây ra theo kiểu tiền tốtố
    PREFIX(root);


    return 0;
}