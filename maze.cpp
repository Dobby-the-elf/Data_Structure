#include <iostream>
#include<iomanip>
#include<queue>
#include<vector>
using namespace std;

typedef struct node {
    int data;
    int pace;
    bool visited;
//    用來記錄有沒有造訪過
    struct node* dir[8];
//    dir[8] 分別代表上 下 左 右 左上 左下 右上 右下
}node;

node** CreateArray(int row, int col){
//    輸入行列大小，這個函式可以輸入一個紀錄node指標的陣列
    node** temp = new node*[row];
    for (int i = 0; i < row; i++){
        temp[i] = new node[col];
    }
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            temp[i][j].data = -9;
            temp[i][j].pace = 0;
            temp[i][j].visited = false;
            for(int di = 0; di < 8; di++){
                temp[i][j].dir[di] = NULL;
            }
        }
    }
    return temp;
}

node** copy(node** copy, node** origin, int row, int col){
//    輸入兩個陣列，這個函數可以將第二個陣列的資訊複製給第一個（指標除外）
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            copy[i][j].data = origin[i][j].data;
            copy[i][j].pace = origin[i][j].pace;
        }
    }
    return copy;
}

void PrintArr(node** arr, int row, int col, int width){
//    輸入一個陣列及其行列、輸出空間寬 這個函數負責印出該陣列
    for (int i = 1; i < row-1; i++){
        for (int j = 1; j < col-1; j++){
            cout << setw(width) << arr[i][j].data;
        }
        cout << setw(width) << endl;
    }
}

void setlink(node** arr, int row ,int col, int pass){
//    輸入一個陣列及其行列、允許產生連接的值，這個函式可以建構連結
    for (int i = 1; i <= row; i++){
        for (int j = 1; j <= col; j++){
            if (arr[i-1][j].data == pass){
                arr[i][j].dir[0] = &arr[i-1][j];
            }
            if (arr[i+1][j].data == pass){
                arr[i][j].dir[1] = &arr[i+1][j];
            }
            if (arr[i][j-1].data == pass){
                arr[i][j].dir[2] = &arr[i][j-1];
            }
            if (arr[i][j+1].data == pass){
                arr[i][j].dir[3] = &arr[i][j+1];
            }
            if (arr[i-1][j-1].data == pass){
                arr[i][j].dir[4] = &arr[i-1][j-1];
            }
            if (arr[i+1][j-1].data == pass){
                arr[i][j].dir[5] = &arr[i+1][j-1];
            }
            if (arr[i-1][j+1].data == pass){
                arr[i][j].dir[6] = &arr[i-1][j+1];
            }
            if (arr[i+1][j+1].data == pass){
                arr[i][j].dir[7] = &arr[i+1][j+1];
            }
        }
    }
}


int FindNotParty(node** part, int row, int col, int* y, int* x){
//    這個函數用來找到還未成對的元素，如果找不到，回傳0
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (part[i][j].data == -1){
                *y = i;
                *x = j;
                return 1;
            }
        }
    }
    return 0;
}

void party(node** part, int row, int col, int y, int x, int* c){
//    這個函式用來計算區塊
//    使用queue來記錄下個要造訪的位置
//    在node當中新增visited來記錄有沒有造訪過，避免重複造訪
//    由於這個函式是被多次呼叫的，c代表的是儲存iteration的指標
//    只要go不為空，就會一直繼續造訪下去，反之，則已經走完
    *c = *c + 1;
    queue<node*> go;
    part[y][x].data = *c;
    go.push(&part[y][x]);
    for(int di = 0; di < 4; di++){
        if ((part[y][x].dir[di] != NULL) && (part[y][x].dir[di]->visited == false)){
            part[y][x].dir[di]->visited = true;
            part[y][x].dir[di]->data = *c;
            go.push(part[y][x].dir[di]);
        }
    }
    go.pop();
    while(go.size() != 0){
        node* temp = go.front();
        for(int di = 0; di < 4; di++){
            if (temp->dir[di] != NULL && (temp->dir[di]->visited == false) ){
                temp->dir[di]->visited = true;
                temp->dir[di]->data = *c;
                go.push(temp->dir[di]);
            }
        }
        go.pop();
    }
}

int CheckWalkOver(node** walk, int row, int col, int* y, int* x){
//    用來確認用來確認有沒有地方還沒走過的函式
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (walk[i][j].data == 1){
                *y = i;
                *x = j;
                return 1;
            }
        }
    }
    return 0;
}

void walker(node** walk, int row, int col, int y, int x){
//    用來計算步數的函式，結構上跟party有點像
//    但要有算步數的功能，所以不再使用queue，而是使用同樣可以push pop，且更容易索引的vector
    for (int i = 1; i < row-1; i++){
        for (int j = 1; j < col-1; j++){
            if (walk[i][j].data == 1){
                walk[i][j].visited = false;
            }
            else{
                walk[i][j].visited = true;
            }
            walk[i][j].pace =0;
        }
    }
    int c = 1;
    vector<node*> vec;
    vec.push_back(&walk[y][x]);
    for(int di = 0; di < 4; di++){
        if ((walk[y][x].dir[di] != NULL) && (walk[y][x].dir[di]->visited == false)){
            walk[y][x].dir[di]->visited = true;
            walk[y][x].dir[di]->pace = c;
            vec.push_back(walk[y][x].dir[di]);
        }
    }
//    vec, walk, go時常混淆打錯
    while(!vec.empty()){
//        cout<<"oh\n";
        for (int i = 0; i < vec.size(); i++){
            if (vec[i]->pace == c){
                for(int di = 0; di < 4; di++){
                    if ((vec[i]->dir[di] != NULL) && (vec[i]->dir[di]->visited == false)){
                        vec[i]->dir[di]->visited = true;
                        vec[i]->dir[di]->pace = c+1;
                        vec.push_back(vec[i]->dir[di]);
                    }
                }
            }
        }
//        新學到的東西，用iterator刪除vector中的元素
        vector<node*>::iterator iter;
        for (int i = 0; i < vec.size(); i++){
            if (vec[i]->pace <= c){
                iter = vec.begin()+i;
                vec.erase(iter);
            }
        }
        c++;
    }
    walk[y][x].pace = -1;
    for (int i = 1; i < row-1; i++){
        for (int j = 1; j < col-1; j++){
            walk[i][j].data = walk[i][j].pace;
        }
    }
}

int MinPace(node** walk, int row, int col){
//    輸入陣列，這個函式可以找到最短逃出路徑
//    檢查邊界上的值即可
//    由於地圖有大小限制，步數不可能超過1024步
//    比min還小的合法值取代min
    int min = 1024;
    for (int i = 1; i < col-1; i++){
        if ( walk[1][i].data > 0 && walk[1][i].data < min){
            min = walk[1][i].data;
        }
        if ( walk[row-2][i].data > 0 && walk[row-2][i].data < min){
            min = walk[row-2][i].data;
        }
        
    }
    for (int i = 1; i < row-1; i++){
        if ( walk[i][1].data > 0 && walk[i][1].data < min){
            min = walk[i][1].data;
        }
        if ( walk[i][col-2].data > 0 && walk[i][col-2].data < min){
            min = walk[i][col-2].data;
        }
    }
    return min;
}

void firer(node** walk, int row, int col, int y, int x){
//    除了方向變成8個以外，結構與walker完全相同
    for (int i = 1; i < row-1; i++){
        for (int j = 1; j < col-1; j++){
            if (walk[i][j].data == 1){
                walk[i][j].visited = false;
            }
            else{
                walk[i][j].visited = true;
            }
            walk[i][j].pace =0;
        }
    }
    int c = 1;
    vector<node*> vec;
    vec.push_back(&walk[y][x]);
    for(int di = 0; di < 8; di++){
        if ((walk[y][x].dir[di] != NULL) && (walk[y][x].dir[di]->visited == false)){
            walk[y][x].dir[di]->visited = true;
            walk[y][x].dir[di]->pace = c;
            vec.push_back(walk[y][x].dir[di]);
        }
    }
//    vec, walk, go會混淆打錯
    while(!vec.empty()){
        for (int i = 0; i < vec.size(); i++){
            if (vec[i]->pace == c){
                for(int di = 0; di < 8; di++){
                    if ((vec[i]->dir[di] != NULL) && (vec[i]->dir[di]->visited == false)){
                        vec[i]->dir[di]->visited = true;
                        vec[i]->dir[di]->pace = c+1;
                        vec.push_back(vec[i]->dir[di]);
                    }
                }
            }
        }
        vector<node*>::iterator iter;
        for (int i = 0; i < vec.size(); i++){
            if (vec[i]->pace <= c){
                iter = vec.begin()+i;
                vec.erase(iter);
            }
        }
        c++;
    }
    walk[y][x].pace = -1;
    for (int i = 1; i < row-1; i++){
        for (int j = 1; j < col-1; j++){
            walk[i][j].data = walk[i][j].pace;
        }
    }
}

int main(int argc, const char * argv[]) {
    int r, c, y, x, minpath, safepath;
    int many = 0, manx = 0, count = 0;
    cout << "enter row&column, y&x, matrix:\n";
    cin >> r >> c >> y >> x;
//    讀入r, c, y, x 並透過判斷式找到並記錄小戴的座標
    char input;
    node** arr = CreateArray(r+2, c+2);
//    使用node結構對資料進行儲存
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            cin >> input;
            if ( input == '+'){
                arr[i][j].data = 1;
            }
            else if ( input == '%'){
                arr[i][j].data = -1;
                many = i;
                manx = j;
            }
            else{
                arr[i][j].data = 0;
            }
        }
    }
//    創造一個結構為node的陣列part來計算區塊
    node** part = CreateArray(r+2, c+2);
    part = copy(part, arr, r+2, c+2);
    for (int i = 0; i < r+2; i++){
        for (int j = 0; j < c+2; j++){
            if (part[i][j].data == 1){
                part[i][j].data = 0;
            }
            else if (part[i][j].data == 0){
                part[i][j].data = -1;
            }
        }
    }
    setlink(part, r, c,-1);
//    呼叫函式party來分出區塊
    party(part, r+2, c+2, many,manx, &count);
    int par = 1;
    int pary = many;
    int parx = manx;
    while(FindNotParty(part, r+2, c+2, &pary, &parx)){
//        cout << "oh";
        party(part, r+2, c+2, pary, parx, &count);
        par++;
    }
    
//      創造一個結構為node的陣列walk來儲存步數
    node** walk = CreateArray(r+2, c+2);
    walk = copy(walk, part, r+2, c+2);
//    如果walk複製part的位置，不能更改walk的指標
//    所以只複製值是比較好的做法
    setlink(walk, r, c, 1);
//    呼叫setlink來為walk設置連結
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            if (walk[i][j].data > 1 ){
                walk[i][j].data = 0;
            }
        }
    }
    walker(walk, r+2, c+2, many, manx);
//  呼叫walker來判斷走到每個座標所需的最少步數
    minpath = MinPace(walk, r+2, c+2);
//   呼叫minpace來計算走出迷宮需要的最少步數
    if (minpath== 1024){
        minpath = -1;
    }
//  創造一個結構為node的陣列fire來計算火的步數
    node** fire = CreateArray(r+2, c+2);
    fire = copy(fire, part, r+2, c+2);
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
            if (fire[i][j].data > 1 ){
                fire[i][j].data = 1;
            }
        }
    }
    setlink(fire, r, c, 1);
//    呼叫setlink來為fire設置連結
    firer(fire, r+2, c+2, y+1, x+1);
//    呼叫firer來計算火的步數
    
    node** safe = CreateArray(r+2, c+2);
//    創造一個結構為node的陣列safe來儲存路能不能走
    safe = copy(safe, fire, r+2, c+2);
    safe[y][x].data++;
    for (int i = 1; i <= r; i++){
        for (int j = 1; j <= c; j++){
                safe[i][j].data = safe[i][j].data - walk[i][j].data;
            if (safe[i][j].data > 1){
                safe[i][j].data = 1;
            }
        }
    }
    setlink(safe, r, c, 1);
//  呼叫setlink來為safe的可行走區域設置連結
    walker(safe, r+2, c+2, many, manx);
//    呼叫walker來判斷走到每個可走區域所需的最少步數
    safepath = MinPace(safe, r+2, c+2);
    if (safepath == 1024){
        safepath = -1;
    }
    
    
//  依序呼叫PrintArr印出每個陣列
    cout << endl << "[1]show the map:" << endl;
    PrintArr(arr, r+2, c+2, 2);
    cout << "===========================";
    
    cout << endl << "[2]show the map:" << endl;
    PrintArr(part, r+2, c+2, 3); // part 3 is width
    cout << endl << "The number of regions is? " << par << endl;
    cout << "===========================";
    
    cout << endl << "[3]show the map:" << endl;
    PrintArr(walk, r+2, c+2, 3); // walk 3 is width
    cout<< endl << "Is there a minimum path? "<< minpath << endl;
    cout << "===========================";
    
    cout << endl << "[4]show the map:" << endl;;
    PrintArr(fire, r+2, c+2, 3);
    cout << endl << "Can they escape from the fire? " << safepath << endl;
    
//    釋放記憶體
    delete []safe;
    delete []walk;
    delete []part;
    delete []arr;
    return 0;
}
//4 6 1 5 ++++++ +$$%$$ $$++++ ++$+$$
