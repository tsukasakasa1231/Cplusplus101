#include <iostream>
using namespace std;

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph




int main() {

    int n,B,t1,t2;
    int population[1000]={0};
    int cost[1000]={0};
    int graph[500][500]={{0}};
    int spSet[500][500]={{-1}};


    cin>>n>>B>>t1>>t2;


    for(int i=0;i<n;i++)
    {
        cin>>population[i];
    }
    for(int i=0;i<n;i++)
    {
        cin>>cost[i];
    }

    for(int i=0;i<n;i++)
    {
        graph[i][i]=0;
        for(int j=n-1;j>i;j--)
        {
            cin>>graph[i][j];
            graph[j][i]=graph[i][j];

        }

    }




    return 0;
}
