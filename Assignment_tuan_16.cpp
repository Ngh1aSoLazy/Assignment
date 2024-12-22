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

// Hàm kiểm tra chiều cao của cây
int height(NODE* root)
{
    if(root == NULL) return -1;
    else
    {
        int lheight = height(root->left);
        int rheight = height(root->right);
        if(lheight > rheight) return (lheight + 1);
        else return (rheight + 1);
    }
}

// Hàm kiểm tra hệ số cân bằng
int BAL_FACTOR(NODE* root)
{
    if(root == NULL) return -1;
    else return (height(root->left) - height(root->right)); 
}

// Hàm xoay đơn, kép
NODE* LL(NODE* root) // Left-left imbalance
{
    NODE* p = root->left;
    NODE* p2 = p->right;

    p->right = root;
    root->left = p2;

    return p;
}

NODE* RR(NODE* root) // Right-right imbalance
{
    NODE* p = root->right;
    NODE* p2 = p->left;

    p->left = root;
    root->right = p2;

    return p;
}

NODE* LR(NODE* root) // Left-right imbalance
{
    RR(root->left);
    LL(root);

    return root;
}

NODE* RL(NODE* root) // Right-left imbalance
{
    LL(root->right);
    RR(root);

    return root;
}

// Hàm insert
NODE* INSERT(NODE* root, int data)
{
    if(root == NULL) return MAKE_NODE(data);
    else if(data <= root->data) root->left = INSERT(root->left, data);
    else if(data > root->data)  root->right = INSERT(root->right, data);

    if(BAL_FACTOR(root) > 1 && (BAL_FACTOR(root->left) == 1 || BAL_FACTOR(root->left) == 0)) return LL(root);
    if(BAL_FACTOR(root) > 1 && BAL_FACTOR(root->left) < 0) return LR(root);
    if(BAL_FACTOR(root) < -1 && (BAL_FACTOR(root->right) == 1 || BAL_FACTOR(root->right) == 0)) return RL(root);
    if(BAL_FACTOR(root) < -1 && BAL_FACTOR(root->left) < 0) return RR(root);

    return root;
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

    // Hàm in cây ra theo kiểu tiền tố
    PREFIX(root);

    return 0;
}