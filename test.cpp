#include<iostream>
#include<cstring>

using namespace std;

/*
Viết chương trình cài đặt đồ thị cho như trên bảng theo hai cấu trúc lưu trữ 
    Sử dụng ma trận lân cận -> nhập thông tin đồ thị 
    Sử dụng danh sách lân cận  -> nhập thông tin đồ thị 
    Duyệt đồ thị và in thứ tự các đỉnh theo 2 cách duyệt (BFS, DFS)
*/

/*
    Quy ước: 0 - Hà Nội
             1 - Hải Dương
             2 - Hưng Yên
             3 - Phủ Lý
             4 - Hòa Bình
             5 - Sơn Tây
             6 - Thái Nguyên
             7 - Bắc Ninh
             8 - Bắc Giang
             9 - Uông Bí
             10 - Hải Phòng
*/

// Xây dựng cấu trúc đồ thị sử dụng ma trận kề

// Khai báo đồ thị dưới dạng ma trận kề
int adjMatrix[11][11];
int n, m; // Với n là số đỉnh, m là số cạnh

// Xây dựng cấu trúc đồ thị sử dụng danh sách kề

// Khai báo cấu trúc của 1 node (đỉnh - vertex)
struct NODE
{
    int vertex;
    NODE* link;
};

// Khai báo danh sách lân cận
NODE* adjList[11];

// Hàm thêm cạnh mới
void ADD_EDGE(int u, int v)
{
    // Áp dụng cho đồ thị vô hướng

    // Khởi tạo pointer p có kiểu dữ liệu NODE
    // với giá trị khởi tạo: vertex = v, link = adjList[u]
    NODE* p = new NODE{v, adjList[u]}; 
    adjList[u] = p;

    p = new NODE{u, adjList[v]};
    adjList[v] = p;
}

// Hàm nhập đồ thị dưới dạng danh sách liên kết
void INPUT_adjList()
{
    cout << "Nhập số đỉnh và số cạnh: ";
    cin >> n >> m;

    // Khởi tạo danh sách liên kết
    for (int i = 0; i < n; i++) 
    {
        adjList[i] = nullptr;
    }

    cout << "Nhập các cạnh:" << endl;
    for (int i = 0; i < m; i++) 
    {
        int u, v;
        cin >> u >> v;
        ADD_EDGE(u, v);
    }
}

// Hàm nhập đồ thị dưới dạng ma trận kề
void INPUT_adjMatrix()
{
    cout << "Nhập số đỉnh và số cạnh: ";
    cin >> n >> m;

    // Khởi tạo đồ thị ban đầu không có kết nối
    memset(adjMatrix, 0, sizeof(adjMatrix));
    for(int i = 0; i < m; i++)
    {
        int u, v;
        cout << "Nhập index của hàng, cột:" << endl;
        cin >> u >> v;
        // Áp dụng cho đồ thị vô hướng
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }
}
void PRINT_GRAPH(int g[][11])
{
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
}

// Hàm in đồ thị dưới dạng danh sách lân cận
void printAdjList(int n) 
{
    for (int i = 0; i < n; i++) 
    {
        NODE* p = adjList[i];
        cout << "Đỉnh " << i << ": ";
        
        while (p != nullptr) 
        {
            cout << p->vertex << " ";
            p = p->link;
        }
        cout << endl;
    }
}

int main()
{
    INPUT_adjMatrix();
    PRINT_GRAPH(adjMatrix);

    INPUT_adjList();

    return 0;
}