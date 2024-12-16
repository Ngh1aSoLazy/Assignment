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
    NODE* ptr = new NODE(c, p, s, subs); // Gán địa chỉ của node mới cho pointer p
    return ptr;
}

// Hàm insert
NODE* INSERT(NODE* root, int c, int p, int s, int subs)
{
    if(IS_EMPTY(root)) 
    {
        root = MAKE_NODE(c, p, s, subs);
        return root;
    }
    else if(c == root->chapter && p == root->page && s == root->section && subs == root->subsection)
    {
        if(root->left == NULL) root->left = MAKE_NODE(c, p, s, subs);
        else INSERT(root->left, c, p, s, subs);
    }
    else if(c > root->chapter)
    {
        if(root->right == NULL) root->right = MAKE_NODE(c, p, s, subs);
        else INSERT(root->right, c, p, s, subs);
    }
    
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
int MAX_LEN(NODE* root)
{
    if(IS_EMPTY(root)) cout << "Empty!";
    int max = 0;
    int longest_chapter = 0;
    if(root->section > max) 
    {
        max = root->section;
        longest_chapter = root->chapter;
    }
    MAX_LEN(root->left);
    MAX_LEN(root->right);

    return longest_chapter;
}

// Hàm tìm kiếm
void FIND(NODE* root, int chapter, int s, int subs)
{
    // Nếu cây rỗng in ra "EMPTY" và dừng tìm kiếm
    if(IS_EMPTY(root)) 
    {
        cout << "EMPTY !!!" << endl;
        return;
    }
    if(chapter == root->chapter && s == root->section && subs == root->subsection) cout << "Found!" << endl;
    if(chapter == root->chapter) FIND(root->left, chapter, s, subs);
    if(chapter == root->chapter) FIND(root->right, chapter, s, subs);
}

// Hàm thay đổi thứ tự chap 
void CHANGE(NODE* root)
{
    if(IS_EMPTY(root->right)) root->right->chapter++;
    CHANGE(root->right);

}

// Hàm xóa nếu node cần xóa ko phải root
void DEL1(NODE* root, int c)
{
    NODE* p1;
    if(c == root->right->chapter)
    {
        p1 = root->right;
        if(!IS_EMPTY(root->right->right)) root->right = root->right->right;

        delete p1;
    }
    CHANGE(root);
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

int main()
{

    return 0;
}