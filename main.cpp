#include <bits/stdc++.h>
using namespace std;

const int N=1e5+2;          //Initialising a constant N globally which has a very large value.
bool vis[N];                //Initialising an array "vis[]" globally where I will keep track of all the nodes that I have visited.
vector<int> adj[N];         //Initialising a vector of length N to which I will implement the graph as an adjacency list. 


//My solution revolves around the concept of depth first traversal of the implemented graph.
//The function dfsprint() takes 2 arguments: node which signifies the current node at which we currently are and a pointer of the closeness factor.
//Normally when we traverse in a DFS manner, we keep on travelling in the depths from 1 child to another until we hit a rock bottom. I modified the function of DFS so that we only travel till we reach a node which is at a distance of the given closeness factor.
//For this, basically we are travelling in DFS manner wrt to a temporary variable closeness factor which keeps on decreasing until the value it becomes 0. When it becomes 0, we will kind of reset the value of the temporary variable back to k.
//For this, I made a DFS function "dfsprint()" and initialised a visited array vis[] which will keep track of the nodes that I have visited.
//Now, everytime we traverse through the vector (adjacency list) and find an element (potential node) which is not visited as per the visited array (vis[*it]==0), We call the function again recursively BUT WITH A TWIST.
//Before recursively calling the function, we are initialising a variable 'b' which is nothing but the pointer of k (the closeness factor) and decrementing it's value by 1 in every iteration.
//When we call the function again, we will call it wrt *it and &b (adress of b) i.e: dfsprint(*it,&b). The reason we did this will be clear later on.
//We also made an if block which checks if *k (which is been replaced by the local variable b and is decreasing in subsequent iterations) is 0 (*k==0). If it is,we surely know that we have travelled the required distance (closeness factor) and the current node is one of our required nodes.
//Thus, we print the required node and return the function which removes itself from the memory stack. As soon as it removes itself, the value of the local variable b (with respect to which the functions were called revursively) starts changing its value back to the original closeness factor *k and the local/temporary variable resets it's value.
//Now, since the function has been returned, the graph wont traverse further. Instead it will get back to the source node where it will begin traversing the other unvisited children till it traverses the required distance/height/closeness factor. This will continue until the final function returns and removes itself from the memory stack.

void dfsprint(int node,int *k)
{
    vis[node]=1;
    
    if((*k)==0)                     //Checking when the local variable becomes 0 after being decremented in every iteration.
    {
        cout<<"Required Node: "<<node<<endl;
        return;                    //Returning and removing the function from the memory stack.
    }

    vector<int> :: iterator it;    //Initialising an iterator "it" through which we plan to traverse in the vector.
    for(it=adj[node].begin();it!=adj[node].end();it++)
    {
        if(!vis[*it])           //Checking if the element is visited or not.
        {   
            int b = *k;         //Creating a local variable b which we will pass as the arguement in the recursive call.
            b--;                //Decrementing it's value by 1.
            dfsprint(*it,&b);   //Recursively calling the function 
        }
    }
}

int main()
{ 
    for(int i=0;i<N;i++)
    {
        vis[i]=0;          //Initialising all the elements of the array "vis" by false or 0 signifying that we haven't traversed in those indices in the adjacency list yet.
    }

    //Taking the input of the graph and implementing it to an adjacency list.

    int n,m;
    cout<<"Enter dimensions of graph:"<<endl;
    cin>>n>>m;

    int x,y;
    for(int i=0;i<m;i++)
    {
        cout<<"Enter elements:"<<endl;
        cin>>x>>y;
        adj[x].push_back(y);        //Linking the first input value to the other.
        adj[y].push_back(x);        //Linking the second input value to the first because it's an undirected graph.
    }

    //Taking input of the closeness factor k.

    int k;
    cout<<"Enter closeness factor:"<<endl;
    cin>>k;

    //Traversing through the graph in a depth first manner and the algorithm:

    dfsprint(1,&k);     //Function call.

    return 0;  
}
