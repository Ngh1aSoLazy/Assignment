#include<iostream>
#include<queue>

using namespace std;

// Binary search tree

// Cấu trúc 1 node của cây
struct NODE
{
    int data;
    NODE* left; 
    NODE* right;

    NODE(int val)
    {
        data = val;
        // Khởi tạo pointer trỏ đến con trái và con phải
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
NODE* MAKE_NODE(int data)
{
    NODE* p = new NODE(data); // Gán địa chỉ của node mới cho pointer p
    return p;
}

// Hàm insert
NODE* INSERT(NODE* root, int data)
{
    if(IS_EMPTY(root)) 
    {
        root = MAKE_NODE(data);
        return root;
    }
    else if(data <= root->data)
    {
        if(root->left == NULL) root->left = MAKE_NODE(data);
        else INSERT(root->left, data);
    }
    else if(data > root->data)
    {
        if(root->right == NULL) root->right = MAKE_NODE(data);
        else INSERT(root->right, data);
    }
    
    return root;
}

// Hàm tìm kiếm
void FIND(NODE* root, int a)
{
    // Nếu cây rỗng in ra "EMPTY" và dừng tìm kiếm
    if(IS_EMPTY(root)) 
    {
        cout << "EMPTY !!!" << endl;
        return;
    }
    if(a == root->data) cout << "Found!" << endl;
    if(a < root->data) FIND(root->left, a);
    if(a > root->data) FIND(root->right, a);
}

// Duyệt cây theo kiểu tiền tố (gốc - trái - phải)
void PREFIX(NODE* root)
{
    if(IS_EMPTY(root)) return;
    cout << root->data << " ";
    PREFIX(root->left);
    PREFIX(root->right); 
}

// Hàm duyệt và insert vào queue
void INS_Q(NODE* root, queue<int>* q)
{
    if(IS_EMPTY(root)) return;
    if(!IS_EMPTY(root->left))
    {
        (*q).push(root->left->data);
        INS_Q(root->left, q);
    }
    if(!IS_EMPTY(root->right))
    {
        (*q).push(root->right->data);
        INS_Q(root->right, q);
    }
}

void FUNC(NODE* root)
{
    if(root->left != NULL)
    {
        FUNC(root->left);
        delete root->left;
    }
    if(root->right != NULL)
    {
        FUNC(root->right);
        delete root->right;
    }
}
// Hàm tìm để xóa
void FIND_TO_DEL(NODE* root, int a)
{
    if(IS_EMPTY(root))  return;
    if(a == root->data) 
    {
        FUNC(root);
        delete root;
    }
    if(a < root->data) FIND(root->left, a);
    if(a > root->data) FIND(root->right, a);
}

// Hàm xóa node
void DEL(NODE* root, int a, queue<int>* q)
{
    /* 
        Idea là cả node được chọn và các node con, cháu của nó
        Các node con bị xóa sẽ được cho vào 1 queue rồi 
        insert lại từ đầu, tạo thành 1 cây nhị phân mới
    */
   // Tách node con ra cho vào queue 
   // Xóa node được chọn và các node con
   // Insert lại các node con trong queue

   if(IS_EMPTY(root)) return;
   if(a == root->data)
   {
        INS_Q(root, q);
        FIND_TO_DEL(root, a);
        while(!(*q).empty())
        {
            INSERT(root, (*q).front());
            (*q).pop();
        }
   } 
   if(a > root->data) DEL(root->left, a, q);
   if(a < root->data) DEL(root->right, a, q);
}

int main()
{
    NODE* root = NULL; // Khởi tạo node gốc
    queue<int> q;
    cout << "Test func:" << endl;

    // Tạo cây, nhập data
    int data; // Data của 1 node  
    int n; // Số node 
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> data;
        root = INSERT(root, data);
    }

    // Tìm kiếm phần tử
    // cout << "Find: ";
    // int a; // Số cần tìm
    // cin >> a;
    // cout << endl << "Result: "; 
    // FIND(root, a);

    // Duyệt cây và in ra giá trị của các node theo kiểu tiền tố
    cout << "PREFIX:" << endl;
    PREFIX(root);
    cout << endl;

    // Xóa phần tử
    DEL(root, 17, &q);

    PREFIX(root);

    return 0;
}