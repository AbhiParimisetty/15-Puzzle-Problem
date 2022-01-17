/* Program to implement the 15-puzzle problem by Branch and bound
    and by backtracking process...
*/

// Headers

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <algorithm>
#include <omp.h>

using namespace std;

int nodesExplored;
int nodesGenerated;
int goal[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
string optrs[] = {"UP", "DOWN", "LEFT", "RIGHT"};
int n = 4;


// Defining the class.

class Node
{
    public:
            int puzzle[16];
            Node *parent;
            string optr;
            int static id;

            Node()
            {
                parent = NULL;
                optr = "";
                id++;
            }

            Node(int board[])
            {
                optr = "";
                parent = NULL;

                for(int i = 0; i <16 ; i++)
                    this->puzzle[i] = board[i];

                id++;
            }

            Node (Node *temp)
            {
                this->parent = temp->parent;
                optr = temp->optr;

                for(int i = 0; i < n; i++)
                    this->puzzle[i] = temp->puzzle[i];

                id++;
            }

            string Tostring()
            {
                string retStr = "";
                for(int i = 0; i < 16; i++)
                {
                    stringstream ss;
                    ss << puzzle[i];
                    string str = ss.str();
                    retStr = retStr + str;
                }
                return retStr;
            }
};

int Node :: id = 0;

void Print(int puzzle[], int n)
{
    if(n == 0)
        cout<<"\nSolution found : ";
    
    else
        cout<<"Step#"<<n<<": "<<endl;

    for(int i = 0; i < 16; i++)
    {
        cout<<puzzle[i]<<" ";
        if((i+1) % 4 == 0)
            cout<<endl;
    }
}

bool validate(int board[], string o)
{   
    if(o == "UP")
    {
        if(board[0] == 0 || board[1] == 0 || board[2]== 0 || board[3]== 0)
            return false;
        else 
            return true;
    }
     
    else if(o == "DOWN")
    {
        if(board[15] == 0 || board[14] == 0 || board[13]== 0 || board[12]== 0)
            return false;
        else 
            return true;         
    }
     
    else if(o == "LEFT")
    {
        if(board[0] == 0 || board[4] == 0 || board[8]== 0 || board[12]== 0)
           return false;
        else 
           return true;
    }
     
    else
    {
        if(board[3] == 0 || board[7] == 0 || board[11]== 0 || board[15]== 0)
            return false;
        else 
            return true;
    }
}

void SolPath(Node *head)
{
    Node *p = head;
    
	if(p==NULL)
    	return;
	  
    int i = 0;
    
	while(p!=NULL)
    {
		Print(p->puzzle,i);
		p = p->parent;
		i++;
    }
    
	cout<<endl;
}

int SearchBlank(int board[])
{
	for(int i=0;i<16;i++)
	  if(board[i] == 0)
		return i;
}

bool GoalTest(int board[])
{
    int count = 0;
    for(int i = 0; i < 16; i++)
    {
        if( board[i] == goal[i])
            count++;
    }

    if(count == 16)
        return true;

    return false;
}

int cal(int temp[10][10], int t[10][10])
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(temp[i][j] != t[i][j])
                count++;
        }
    }

    return count;
}

int check (int p[10][10], int t[10][10])
{
    int flag = 1;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <n; j++)
        {
            if( p[i][j] != t[i][j] )
            {
                flag = 0;
                break;
            }
        }
    }

    return flag;
}


int main()
{
    int p[10][10],temp[10][10],r[10][10];
    int m=0,x=0,y=0,d=1000,dmin=0,l=0,x1,y1;
    int i,j,k;

    cout<<"\nEnter the 4*4 matrix to be solved, space wit zero : "<<endl;
    for( i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            cin>>p[i][j];
        }
    }

    int t[10][10] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,0}
    };

    cout<<"\nYour Entered matrix is : "<<endl;
    for( i= 0; i < n; i++)
    {
        for( j = 0; j < n; j++)
        {
            cout<<p[i][j]<<" ";
        }
        cout<<endl;
    }

    ofstream file;        
    file.open("Input.txt");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            file << p[i][j]<<" ";
        }
        file << endl;
    }
    
    int puzzle[16];

    for(i = 0; i < 16; i++)
        in >> puzzle[i];


    Node node = new Node(puzzle);

    static bool flag = true;

    do
    {
        cout<<"\n1.Solve the 15-Puzzle by branch and bound method\n";
        cout<<"2.Solve the 15-Puzzle by Backtracking method\n";
        cout<<"\nEnter the choice : ";
        cin>>choice;

        switch(choice)
        {
            case 1 : 
                    while( !(check(p,t)) )
                    {
                        l++;
                        for(i = 0; i < n; i++)
                        {
                            for(j = 0; j < n; j++)
                            {
                                if( p[i][j] == 0)
                                {
                                    x = i;
                                    y = j;
                                }
                            }
                        }

                        //To move upwards...

                        for(i = 0; i < n; i++)
                        {
                            for(j = 0; j < n; j++)                           
                                temp[i][j] = p[i][j];                           
                        }

                        if( x != 0 )
                            swap(temp[x][y],temp[x-1][y]);
                        
                        m = cal(temp,t);
                        dmin = l + m;

                        if(dmin < d)
                        {
                            d = dmin;
                            for(i = 0; i < n; i++)
                            {
                                for(j = 0; j < n; j++)
                                    r[i][j] = temp[i][j];
                            }
                        }

                        //To move downwards...

                        for(i = 0; i < n; i++)
                        {
                            for(j = 0; j < n; j++)                           
                                temp[i][j] = p[i][j];                           
                        }

                        if (x != n-1)
                            swap(temp[x][y],temp[x+1][y]);

                        m = cal(temp,t);
                        dmin = l + m;

                        if(dmin < d)
                        {
                            d = dmin;
                            for(i = 0; i < n; i++)
                            {
                                for(j = 0; j < n; j++)
                                    r[i][j] = temp[i][j];
                            }
                        }
                        
                        //To move right side...

                        for(i = 0; i < n; i++)
                        {
                            for(j = 0; j < n; j++)                           
                                temp[i][j] = p[i][j];                           
                        }

                        if(y != n-1)
                            swap(temp[y][y],temp[x][y+1]);

                        m = cal(temp,t);
                        dmin = l + m;

                        if(dmin < d)
                        {
                            d = dmin;
                            for(i = 0; i < n; i++)
                            {
                                for(j = 0; j < n; j++)
                                    r[i][j] = temp[i][j];
                            }
                        }

                        //To move Left side..

                        for(i = 0; i < n; i++)
                        {
                            for(j = 0; j < n; j++)                           
                                temp[i][j] = p[i][j];                           
                        }
                        
                        if (y != 0)
                            swap(temp[x][y],temp[x][y-1]);

                        m = cal(temp,t);
                        dmin = l + m;

                        if(dmin < d)
                        {
                            d = dmin;
                            for(i = 0; i < n; i++)
                            {
                                for(j = 0; j < n; j++)
                                    r[i][j] = temp[i][j];
                            }
                        }

                        cout<<"Calculates intermediate matrix value : "<<endl;
                        for(i = 0; i < n; i++)
                        {
                            for(j = 0; j < n; j++)
                            {
                                cout<<r[i][j]<<" ";
                            }
                            cout<<endl;
                        }

                        for(i = 0; i < n; i++)
                        {
                            for(j = 0; j < n; j++)
                            {
                                p[i][j] = r[i][j];
                                temp[i][j] = 0;
                            }
                        }

                        if(b > 5)
                            break;
                            b++;        
                    }

                    if( check(p,t))
                        cout<<"Congratulations\n";

                    else
                        cout<<"Failure\n";

                    break;


            case 2 :
                    BFS_Q.push(node);

                    if(GoalTest(node.puzzle))
                        Print(node.puzzle,0);

                    else
                    {
                        list <string> hashSet;

                        #pragma omp parallel num_threads(8) shared(BFS_Q, hashSet, nodesExplored, nodesGenerated)
                        {
                            while(flag)
                            {
                                #pragma omp critical
                                {
                                    if( !BFS_Q.empty()){}

                                    Node* current = new Node(BFS_Q.front());

                                    //Pop it
                                    BFS_Q.pop();

                                    hashSet.push_back(current->Tostring());

                                    //Increment the nodes explored
                                    nodesExplored++;

                                    for(i=0; i<4 && flag; i++)
                                    {
                                        if(validate(current->puzzle,optrs[i]) == true)
                                        {
                                            int board[16];
                                            for(int j = 0; j < 16; j++)
                                                board[j] = current->puzzle[j];

                                            int blankIndex = SearchBlank(board);

                                            if(optrs[i] == "UP")
                                            {
                                                board[blankIndex] = board[blankIndex-4];
                                                board[blankIndex-4] = 0;
                                            }

                                            else if(optrs[i] == "DOWN")
                                            {
                                                board[blankIndex] = board[blankIndex+4];
                                                board[blankIndex+4] = 0;
                                            }

                                            else if(optrs[i] == "LEFT")
                                            {
                                                board[blankIndex] = board[blankIndex-1];
                                                board[blankIndex-1] = 0;
                                            }

                                            else
                                            {
                                                board[blankIndex] = board[blankIndex+1];
                                                board[blankIndex+1] = 0;
                                            }

                                            Node* child = new Node(board);

                                            child->parent = current;
                                            child->optr = optrs[i];

                                            nodesGenerated++;

                                            if(!(find(hashSet.begin(),hashSet.end(),child->Tostring()) != hashSet.end()))
                                            {
                                                if(GoalTest(child->puzzle) == true)
                                                {
                                                    SolPath(child);
                                                    flag = false;
                                                }

                                                BFS_Q.push(child);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    cout<<"Depth First Search Completed"<<endl;
                    cout<<"Nodes Explored: "<<nodesExplored<<endl;
                    cout<<"Nodes Generated: "<<nodesGenerated<<endl;

                    break;

            case 3 :
                    cout<<"Thank YOU !!";
                    exit(0);

            default : cout<<"\nPlease enter the correct choice\n";
        }
    }while(choice != 3);
}