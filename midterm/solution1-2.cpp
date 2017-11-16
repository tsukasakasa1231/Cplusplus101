// version 2017/11/15 彥中 included and satisfied

#include <iostream>
#include <cstdio>
#include <limits.h>

using namespace std;

// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph



// Number of vertices in the graph

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[], int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int n,int V)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d tt %d\n", i, dist[i]);
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[][500], int src, int V, int s[][500])
{
    int dist[V];     // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[V]; // sptSet[i] will true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in first iteration.
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u]+graph[u][v] < dist[v]&& graph[u][v] != (-1))
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    for(int i = 0; i < V; i++)
    {
        s[src][i] = dist[i];
    }
}

float score_cover(const int ele[],const int cost, const int cover[], int eleCnt)
{
    int count = 0;
    float result = 10001;
    for(int i = 0; i < eleCnt; i++)
    {
        if(cover[i] == 1 && ele[i] == 0)
            count++;
    }
    if(count != 0)
        result = cost / count;
    return result;
}

float score_satisfy(const int ele[], const int cost, const int sat[],const int pop[] , int eleCnt)
{
    int count = 0;
    int population_sum = 0;
    float result = 10001;
    for(int i = 0; i < eleCnt; i++)
    {
        if(sat[i] == 1 && ele[i] == 0)
            population_sum += pop[i];
    }
    if(population_sum != 0)
        result = cost / population_sum;
    return result;
}


int main()
{
    int n, B, t1, t2;
    int population[1000] = {0};
    int cost[1000] = {0};
    int graph[500][500] = {{0}};
    int s[500][500] = {0};
    float score_c = 0;
    float score_s = 0;
    int cover[500][500] = {0}; // 記錄若蓋某村莊有無覆蓋其它村莊
    int satisfy[500][500] = {0};// 記錄若蓋在某村有無滿足他村
    int choose[500] = {0}; 
    int elecov[500] = {0}; // 某村有無被覆蓋
    int elesat[500] = {0};// 某村有無被滿足
    int output[500] = {0};
    int firsttime = 1;
    int outputCount = 0;
    int costlimit = 0;

    cin >> n >> B >> t1 >> t2;

    
    for(int i = 0; i < n; i++)
    {
        cin >> population[i];
    }
    for(int i = 0; i < n; i++)
    {
        cin >> cost[i];
    }

    for(int i = 0; i < n; i++)
    {
        graph[i][i] = 0;
        for(int j = i + 1; j < n; j++)
        {
            cin >> graph[i][j];
            graph[j][i] = graph[i][j];
        }
    }
    for(int i = 0; i < n; i++)
    {
        dijkstra(graph, i, n, s);
    }

    /*  
      for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << s[i][j] << " ";
        }
        cout << endl;
    }
    */ 
    for(int i = 0; i < n; i++)
    {
        int count = 0;
        for(int j = 0; j < n; j++)
        {
            if(s[i][j] > t1)
                count++;
        }
        if(count == (n - 1)) //
        {
            choose[i] = 1;
            elecov[i] = 1;
        }

    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {   
            if(s[i][j] <= t1)
                cover[i][j] = 1;
            if(s[i][j] <= t2)
                satisfy[i][j] = 1;
        }
    }
    int stop = 0;
    int cost_sum = 0;
    while(stop != n)
    {
        float min = 10001;
        int k = 0;
        for(int i = 0; i < n; i++)
        {
            if(choose[i] != 1)
            {
                score_c = score_cover(elecov, cost[i], cover[i], n);
                if(min > score_c)
                {
                    min = score_c;
                    k = i;
                }
            }
        }
        choose[k] = 1;
        output[outputCount] = k;
        outputCount += 1;
        cost_sum += cost[k];
        
        for(int i = 0; i < n; i++)
        {
            if(cover[k][i] == 1)
                elecov[i] = 1;
            if(satisfy[k][i] == 1)
                elesat[i] = 1;
        }
        stop = 0;
        for(int i = 0; i < n; i++)
        {
            if(elecov[i] == 1)
                stop++;
        }
    }
    int remain = B - cost_sum; 
    
    while(remain >= 0)
    {
        int count_A = 0;
        int count_B = 0;
        for(int i = 0; i < n; i++)
        {
            if(choose[i] == 0)
            {
                count_A++;
                if(cost[i] > remain)
                    count_B++;
            }
        }
        if(count_A == count_B)
            break;
        /* for(int i = 0; i < n; i++)
        {
            if(choose[i] == 0)
            {
                if(cost[i] > remain)
                    count++;
            }
        }
        if(count == n - count_cover)
            break;
        */
        float min = 10001;
        int k = 0;
        for(int i = 0; i < n; i++)
        {
            if(choose[i] == 0)
            {
                score_s = score_satisfy(elesat, cost[i], satisfy[i], population, n);
                if(min > score_s)
                {
                    min = score_s;
                    k = i;
                }
            }
        }
        if(cost[k] <= remain)
        {
            choose[k] = 1;
       //     cout << k + 1 << " ";
            output[outputCount] = k;
            outputCount++;
            remain -= cost[k];
        }
        else
            choose[k] = 1;
    }
    //output
    for(int i=0;i<outputCount;i++)
    {
        if(firsttime==1){
            cout << output[i]+1;
            firsttime=0;
        }
        else
        {
            cout <<" "<<output[i]+1;
        }
    }
    return 0;
}
