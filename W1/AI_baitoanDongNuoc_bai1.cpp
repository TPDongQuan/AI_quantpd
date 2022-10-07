#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> jugs;                              // define structure data for jugs
void BFS(int a, int b, int target);                       // define BFS(Breadth-First Search) function
void printresult(map<jugs, jugs> node, jugs currentNode); // define function print results
void Input(int &, int &, int &);

int main()
{
    int a, b, target;
    /// viet ham nhap a,b, target tu ban phim
    Input(a, b, target);
    BFS(a, b, target);
    return 0;
}

void Input(int &a, int &b, int &target)
{
    cout << "Nhap gioi han Jug A: ";
    cin >> a;
    cout << "Nhap gioi han Jug B: ";
    cin >> b;
    cout << "Nhap target of da Jug: ";
    cin >> target;
}

void printresult(map<jugs, jugs> node, jugs currentNode)
{
    if (currentNode.first == 0 && currentNode.second == 0)
    {
        cout << 0 << " " << 0 << endl;
        return;
    }
    printresult(node, node[currentNode]);
    cout << currentNode.first << " " << currentNode.second << endl;
}
void BFS(int a, int b, int target)
{
    map<jugs, int> checkedList; // kiem tra cac node da duyet: 1 da duyet, 0 chua duyet (default = 0)
    bool isSolvable = false;    // ton tai ket qua
    map<jugs, jugs> node;       // Graph
    queue<jugs> q;              // Queue de duyet cay bang BFS

    q.push(make_pair(0, 0)); // Bat dau duyet cay cho ket qua vao hanh doi
    // Queue: 0,0 3,0 4,0
    while (!q.empty())
    {
        jugs currentNode = q.front();      // lay phan tu dau tien
        q.pop();                           // xoa phan tu dau tien khoi hang doi
        if (checkedList[currentNode] == 1) // node da duyet thi pass
            continue;
        checkedList[{currentNode.first, currentNode.second}] = 1; // da duyet

        if (currentNode.first == target || currentNode.second == target)
        {
            isSolvable = true;
            if (currentNode.first == target && currentNode.second != 0)
            {
                node[{currentNode.first, 0}] = currentNode;
                currentNode.second = 0;
            }
            if (currentNode.first == target && currentNode.second != 0)
            {
                node[{0, currentNode.second}] = currentNode;
                currentNode.first = 0;
            }
            printresult(node, currentNode);
            return;
        }
        // ======= Operation =====
        // ## Fill
        // fill into jug 1
        if (checkedList[{a, currentNode.second}] != 1)
        {
            q.push({a, currentNode.second});
            node[{a, currentNode.second}] = currentNode; // Set father
        }
        // fill into jug 2

        if (checkedList[{currentNode.first, b}] != 1)
        {
            q.push({currentNode.first, b});
            node[{currentNode.first, b}] = currentNode;
        }
        // ## Transfer of water
        // from jug 1 to jug 2
        int unfilledSpace1 = b - currentNode.second;
        if (currentNode.first >= unfilledSpace1)
        {
            int remainingValue1 = currentNode.first - unfilledSpace1; // transfer a little
            if (checkedList[{remainingValue1, b}] != 1)
            {
                q.push({remainingValue1, b});
                node[{remainingValue1, b}] = currentNode;
            }
        }
        else
        {
            int remainingValue1 = currentNode.first + currentNode.second;
            if (checkedList[{0, remainingValue1}] != 1)
            { /// transfer all
                q.push({0, remainingValue1});
                node[{0, remainingValue1}] = currentNode;
            }
        }
        // from jug 2 to j1
        int unfilledSpace2 = a - currentNode.first;
        if (currentNode.second >= unfilledSpace2)
        {
            int remainingValue2 = currentNode.second - unfilledSpace2; // transfer a little
            if (checkedList[{a, remainingValue2}] != 1)
            {
                q.push({a, remainingValue2});
                node[{a, remainingValue2}] = currentNode;
            }
        }
        else
        {
            int remainingValue2 = currentNode.first + currentNode.second;
            if (checkedList[{remainingValue2, 0}] != 1)
            { /// transfer all
                q.push({remainingValue2, 0});
                node[{remainingValue2, 0}] = currentNode;
            }
        }

        if (checkedList[{currentNode.first, 0}] != 1)
        {
            q.push({currentNode.first, 0});
            node[{currentNode.first, 0}] = currentNode;
        }

        if (checkedList[{0, currentNode.second}] != 1)
        {
            q.push({0, currentNode.second});
            node[{0, currentNode.second}] = currentNode;
        }
    }
    if (!isSolvable)
        cout << "No solution";
}
