#include <bits/stdc++.h>
#include <time.h>
using namespace std;
#define N 4
void delay(float s);
void pattern();
int z = 1;

struct Node
{
    Node *parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};
int printMatrix(int mat[N][N])
{
    cout << endl;
    cout << "#step" << z++ << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}
Node *newNode(int mat[N][N], int x, int y, int newX,
              int newY, int level, Node *parent)
{
    Node *node = new Node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;
    return node;
}
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};
int calculateCost(int initial[N][N], int final[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] && initial[i][j] != final[i][j])
                count++;
    return count;
}
int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}
void printPath(Node *root)
{
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);

    printf("\n");
}
struct comp
{
    bool operator()(const Node *lhs, const Node *rhs) const
    {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};
void solve(int initial[N][N], int x, int y,int final[N][N])
{
    priority_queue<Node *, std::vector<Node *>, comp> pq;
    Node *root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);
    pq.push(root);
    while (!pq.empty())
    {
        Node *min = pq.top();
        pq.pop();
        if (min->cost == 0)
        {
            printPath(min);
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            if (isSafe(min->x + row[i], min->y + col[i]))
            {
                Node *child = newNode(min->mat, min->x,
                                      min->y, min->x + row[i],
                                      min->y + col[i],
                                      min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                pq.push(child);
            }
        }
    }
    cout << endl;
    cout << endl;
}

int main()
{
    int initial[N][N], x, y, s;
    int final[N][N] =
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 0}};
    system("cls");
    pattern();
    system("cls");
    do
    {
        cout << "1.Auto " << endl;
        cout << "2.Manual" << endl;
        cout << "3.Exit" << endl;
        cout << "Enter your Choice: " << endl;
        cin >> s;
        switch (s)
        {
        case 1:
        {
            int initial2[N][N] = {
                {1, 0, 3, 4},
                {5, 2, 6, 8},
                {9, 10, 7, 11},
                {13, 14, 15, 12}};
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (initial2[i][j] == 0)
                    {
                        x = i;
                        y = j;
                    }
                }
            }
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    cout << initial2[i][j] << " ";
                }
                cout << endl;
            }
            printf("\tYour Puzzle is Solving ...");

            for (int i = 0; i < 3; i++)
            {

                delay(2);
                printf("..");
                delay(2);
                printf("\b!\b");
                printf("\b!\b");
                printf("\b!\b");
            }
            system("cls");
            cout << "The Puzzle is solved!" << endl;
            solve(initial2, x, y, final);
        }
        break;
        case 2:
        {
            int i, j;
            cout << "Enter the your puzzle(Enter zero for space): " << endl;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    cin >> initial[i][j];
                    if (initial[i][j] == 0)
                    {
                        x = i;
                        y = j;
                    }
                }
            }
            printf("\tYour Puzzle is Solving ...");

            for (i = 0; i < 3; i++)
            {

                delay(2);
                printf("..");
                delay(2);
                printf("\b!\b");
                printf("\b!\b");
                printf("\b!\b");
            }
            system("cls");
            cout << "The Puzzle is solved!" << endl;
            solve(initial, x, y, final);
        }
        break;
        case 3:
            cout << "Thank You!" << endl;
            cout << "Exit is done!" << endl;
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
            cout << "Enter from 1 to 3 Only" << endl;
            break;
        }
    } while (s != 3);
}
void pattern()
{
    int x;
    char text1[] = "\n \t\t\t Welcome To 16 Puzzle Solver";
    char text2[] = "\n \t\t\t\t\t By ";
    char text3[] = "\n \t\t\t\t\t GROUP 11...... ";
    char text4[] = "\n \t\t\tBranch Bound Technique";

    printf("\n\n");

    for (x = 0; text1[x] != NULL; x++)
    {
        printf("%c", text1[x]);
        delay(0.1);
    }

    printf("\n");

    for (x = 0; text2[x] != NULL; x++)
    {
        printf("%c", text2[x]);
        delay(0.1);
    }

    printf("\n");
    for (x = 0; text3[x] != NULL; x++)
    {
        printf("%c", text3[x]);
        delay(0.1);
    }
    printf("\n");
    for (x = 0; text4[x] != NULL; x++)
    {
        printf("%c", text4[x]);
        delay(0.1);
    }
    printf("\n");
    delay(0.1);
}

void delay(float s)
{
    int ms = 1000 * s;
    clock_t t = clock();
    while (clock() < t + ms)
        ;
}