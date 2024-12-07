#include<iostream>

using namespace std;

/*
    Cài đặt cây biểu thức cho biểu thức trên lớp ngày 3/12/2024, 
và in ra biểu thức theo các cách biểu diễn Trung tố, hậu tố, và tiền tố.
    Định nghĩa và khai báo các hàm sau:
        + Cài đặt thuộc tính cho 1 node trên cây 
        + Cài đặt hàm khởi tạo cây (không được bỏ qua hàm kiểm tra rỗng)
        + Cài đặt hàm nhập phần tử (bổ sung) vào cây 
        + In các phần tử trên cây theo 3 giải thuật duyệt 

    a*5 - b*c^6/d + (h - f) * e^(1/2)
*/

// Cấu trúc của 1 node
struct NODE
{
    char data; // Biến lưu giá trị của của node
    NODE* left;
    NODE* right;

    // val la gia tri duoc them vao
    NODE(char val) // Hàm khởi tạo của struct | Gọi tự động khi khởi tạo 1 đối tượng mới | Không có kiểu dữ liệu trả về
    {
        data = val;
        // Khởi tạo con trai, con phai
        left = NULL;
        right = NULL;
    }
};

// Hàm kiểm tra cây rỗng
int IS_EMPTY(NODE* root)
{
    return root == NULL;
}

// Hàm tạo 1 node
NODE* MAKE_NODE(char data)
{
    NODE* p = new NODE(data); // Gán địa chỉ của node mới cho pointer p
    return p;
}

// Hàm insert
NODE* INSERT(NODE* root, char data)
{
    if(IS_EMPTY(root)) 
    {
        root = MAKE_NODE(data);
        return root;
    }
    else if(root->left == NULL)
    {
        root->left = MAKE_NODE(data);
    }
    else if(root->right == NULL)
    {
        root->right = MAKE_NODE(data);
    }
    else
    {
        INSERT(root->left, data);
    }
    
    return root;
}

// Duyệt cây theo kiểu trung tố (trái - gốc - phải)
void INFIX(NODE* root)
{
    if(IS_EMPTY(root)) return;
    INFIX(root->left);
    cout << root->data << " ";
    INFIX(root->right);
}

// Duyệt cây theo kiểu tiền tố (gốc - trái - phải)
void PREFIX(NODE* root)
{
    if(IS_EMPTY(root)) return;
    cout << root->data << " ";
    PREFIX(root->left);
    PREFIX(root->right); 
}

// Duyệt cây theo kiểu hậu tố (trái - phải - gốc)
void POSTFIX(NODE* root)
{
    if(IS_EMPTY(root)) return;
    PREFIX(root->left);
    PREFIX(root->right);
    cout << root->data << " ";
}

int main()
{
    NODE* root = NULL;

    cout << "Test insert func:";
    char data;
    int n = 21; // Trên thực tế có thể là n bất kỳ 
               // nhưng vì đoạn code dưới đây chỉ 
               // để test func nên cho trc n = 4
    for(int i = 0; i < n; i++)
    {
        cin >> data;
        root = INSERT(root, data);
    }

    // In các cách biểu diễn
    cout << "Trung tố (Infix): ";
    INFIX(root);
    cout << endl;

    cout << "Hậu tố (Postfix): ";
    POSTFIX(root);
    cout << endl;

    cout << "Tiền tố (Prefix): ";
    PREFIX(root);
    cout << endl;
    
    return 0;
}