#include<iostream>

using namespace std;

/*
    Mục lục của một cuốn sách được lưu trữ dưới dạng một cây trong đó 
mỗi node có thể là chapter, section, subsection, subsubsection.  
Khai báo cấu trúc cây để biểu diễn cuốn sách. Các thông tin chứa ở 
mỗi node sinh viên tự đưa vào để đảm bảo các nội dung sau được thực hiện:  
    + Xác định số chương của cuốn sách 
    + Tìm chương dài nhất của cuốn sách 
    + Thực hiện tìm một mục và xoá mục đó khỏi sách. Lưu ý cập nhật lại số trang của từng mục.  
*/

struct NODE // Lưu data của 1 chap
{
    int chapter; // Thứ tự các chap của sách
    int page; // Số trang của chap đó
    int section; // Số phần của chap
    int subsection; // Số tiểu mục
    NODE* left; 
    NODE* right;

    NODE(int c, int p, int s, int subs)
    {
        chapter = c;
        page = p;
        section = s;
        subsection = subs;
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
NODE* MAKE_NODE(int c, int p, int s, int subs)
{
    NODE* ptr = new NODE(c, p, s, subs); // Gán địa chỉ của node mới cho pointer ptr
    return ptr;
}

// Hàm insert
NODE* INSERT(NODE* root, int c, int p, int s, int subs) 
{
    if (root == NULL) return MAKE_NODE(c, p, s, subs);

    if (c < root->chapter) root->left = INSERT(root->left, c, p, s, subs);
    else if (c > root->chapter) root->right = INSERT(root->right, c, p, s, subs);

    return root;
}


// Hàm xác định số lượng chapter
void NUM_OF_CHAP(NODE* root)
{
    if(IS_EMPTY(root)) cout << "0 chapters";
    if(IS_EMPTY(root->right))
    {
        if(root->chapter == 1) cout << "1 chapter";
        else cout << root->chapter << " chapters";
    }
    else NUM_OF_CHAP(root->right);
}

// Hàm tìm chapter dài nhất dựa trên số trang của nó
int MAX_LEN(NODE* root, int &longest_chap)
{
    if(IS_EMPTY(root)) return 0;

    int max = 0;
    if(root->page > max) 
    {
        max = root->page;
        longest_chap = root->chapter;
    }
    MAX_LEN(root->left, longest_chap);
    MAX_LEN(root->right, longest_chap);

    return longest_chap;
}

// Hàm tìm kiếm
void FIND(NODE* root, int chapter)
{
    // Nếu cây rỗng in ra "EMPTY" và dừng tìm kiếm
    if(IS_EMPTY(root)) 
    {
        cout << "EMPTY !!!" << endl;
        return;
    }
    if(chapter == root->chapter) cout << "Found!" << endl;
    else FIND(root->right, chapter);
}

// Hàm thay đổi thứ tự chap 
void CHANGE(NODE* root, int del_chapter) 
{
    if (root == NULL) return; // Điều kiện dừng: cây rỗng

    // Nếu chương hiện tại lớn hơn chương bị xóa, giảm giá trị của nó
    if (root->chapter > del_chapter) 
    {
        root->chapter--;
    }

    // Tiếp tục cập nhật cho các node con
    CHANGE(root->left, del_chapter);
    CHANGE(root->right, del_chapter);
}


// Hàm xóa nếu node cần xóa ko phải root
void DEL1(NODE* root, int c)
{
    NODE* p1;
    int del_chapter;
    if(c == root->right->chapter)
    {
        p1 = root->right;
        if(!IS_EMPTY(root->right->right)) root->right = root->right->right;
        del_chapter = p1->chapter;
        delete p1;
    }
    CHANGE(root, del_chapter);
}   

// Hàm xóa 1 node khỏi cây
void DEL(NODE* root, int c)
{
    if(c == root->chapter)
    {
        root = root->right;
        delete root->right;
    }
    DEL1(root, c);
}

// Duyệt cây theo kiểu tiền tố (gốc - trái - phải)
void PREFIX(NODE* root)
{
    if(IS_EMPTY(root)) return;
    cout << "Chapter: " << root->chapter << "Page: " << root->page << " Section: " << root->section << " Subsection: " << root->subsection;
    cout << endl;
    PREFIX(root->left);
    PREFIX(root->right); 
}

int main()
{
    NODE* root = NULL;

    int chapter;
    int page;
    int section;
    int subsection;

    for(int i = 0; i < 3; i++)
    {
        cout << " Chapter: ";
        cin >> chapter;
        cout << " Page: ";
        cin >> page;
        cout << " Section: ";
        cin >> section;
        cout << " subsection: ";
        cin >> subsection;

        root = INSERT(root, chapter, page, section, subsection);
    }

    PREFIX(root); cout << endl;

    NUM_OF_CHAP(root); cout << endl;

    int longest_chap;
    longest_chap = MAX_LEN(root, longest_chap);
    cout << longest_chap << endl;
    FIND(root, 2); cout << endl;
    DEL(root, 2);


    return 0;
}