#include <iostream>
#include <cstdio>
#include <limits.h>

using namespace std;

// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph



// Number of vertices in the graph

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree

bool checkCover(int answer[],int n,int scov[][500],int id,int sumcov[]);
bool checkSatisfied(int answer[],int n,int ssat[][500],int id,int sumsat[]);
bool checkCover(int answer[],int n,int s[][500]);
bool checkSatisfied(int answer[],int n,int s[][500]);
bool checkBudget(int answer[],int B,int cost[],int n);
void renewS(int answer[],int n,int s[][500]);
void renewSatisfy(int s[][500],int n, int satisfy[][500]);

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
    int fit = 501;
    int sumsat[500] ={0};
    int sumcov[500] ={0};
    int ssat[500][500]={0};
    int scov[500][500]={0};


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



    if(n>=fit)
    {
        for(int i = 0; i < n; i++)
        {
            int count = 0;
            int x = 0;
            for(int j = 0; j < n; j++)
            {
                if(s[i][j] > t1)
                    count++;
            }
            if(count == (n - 1)) //
            {
                choose[i] = 1;
                //
                output[outputCount] = i;
                outputCount++;
                //
                elecov[i] = 1;
            }
            if(count == (n - 2))
            {
                for(int j = 0; j < n; j++)
                {
                    if(s[i][j] <= t1 && i != j)
                        x = j;
                }
                choose[x] = 1;
                //
                output[outputCount] = x;
                outputCount++;
                //
                elecov[x] = 1;
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
    }
    else
    {
        int answer[500]={0};

        for (int i = 0; i<n; i++)  //距離矩陣更新  0表示不包含也不滿足 1表示包含 2表示滿足
        {
            for (int j = 0; j < n; j++)
            {
                if (s[i][j]>t1)
                    s[i][j] = 0;

                else if (s[i][j] <= t1 && t2 < s[i][j])
                {
                    s[i][j] = 1;
                    scov[i][j] = 0;
                    sumcov[j]+=1;
                }
                else if (s[i][j] <= t2 && 0 <= s[i][j])
                {
                    s[i][j] = 2;
                    ssat[i][j] = 1;
                    sumsat[j]+=1;
                }

            }
        }



        //int S[500][500]={0};      //不能更動的Ｓ

        //for (int i = 0; i<n; i++)
        //{
        //    for (int j = 0 ; j<n; j++)
        //    {
        //        S[i][j] = s[i][j];
        //    }
        //}


        //for(int i=0;i<n;i++)
        //{
        //    for(int j=0;j<n;j++)
        //    {
        //        cout<<s[i][j]<<" ";
        //    }
        //    cout<<endl;
        //}

        for (int i = 0; i<n; i++)  //第一步   選擇全部
            answer[i] = 1;

        int budget = 0;

        for (int i = 0; i<n; i++)
        {
            budget += cost[i];
        }
        //cout <<budget<<"\n";

        //第二步 抽去無影響數

        while (budget > B) // 檢查是否超出預算
        {
            int couldBeChosen[2][500]={0};//候選點們 第一列 編號 第二列 成本

            for (int i = 0; i<n; i++)
            {
                couldBeChosen[0][i] = -1;
                couldBeChosen[1][i] = -1;
            }

            bool continueOrNot = 0;         //要不要繼續檢查下去的檢查點  如果是1代表有滿足全部 如果是0表示沒有滿足全部

            for (int i=0; i<n; i++)  //找出候選點
            {
                if (answer[i] == 0)
                    continue;
                int tem = 0;
                tem = answer[i];
                answer[i] = 0;

                if (checkSatisfied (answer, n, ssat,i,sumsat) == 1)  //檢查是否滿足全部
                {
                    couldBeChosen[0][i] = i;
                    couldBeChosen[1][i] = cost[i];
                    continueOrNot = 1;
                }
                answer[i] = tem;

            }
            if (continueOrNot == 0)
                break;

            int maxNum = 0;                             //最貴候選點編號
            int maxCost = couldBeChosen[1][0];          //最貴候選點成本
            for (int i = 0; i<n; i++)
            {
                if (couldBeChosen[0][i] != -1)
                {
                    maxNum = couldBeChosen[0][i];
                    maxCost = couldBeChosen[1][i];
                    break;
                }
            }



            for (int i = maxNum; i<n; i++)               //找出候選點中最貴的
            {
                if (couldBeChosen[1][i] > maxCost)
                {
                    maxNum = i;
                    maxCost = couldBeChosen[1][i];
                }
            }
            answer[maxNum] = 0; //踢掉候選點
            budget = budget - cost[maxNum];



        }

        //for (int i = 0; i<n; i++)
        //    {
        //        if (answer[i]==1)
        //        {
        //            cout<<i+1<<" ";
        //        }
        //    }
        //    cout<<"\n"<<budget<<"\n";


        ///////////
        //第三步  抽去滿足

        //找滿足數最低的

        while (budget > B) //檢查是否超出預算
        {
            int couldBeChosen[2][500]={0};  //候選點們 第一列 編號 第二列 成本
            ///double couldBeChosenCostPerPerson[500] = {0};  //  候選點的成本/可滿足的人數
            bool continueOrNot = 0;      //要不要繼續檢查下去的檢查點  如果是1代表有包含全部 如果是0表示沒有包含全部


            for (int i = 0; i<n; i++)
            {
                couldBeChosen[0][i] = -1;
                couldBeChosen[1][i] = -1;
            }



            for (int i=0; i<n; i++)  //找出候選點
            {
                ///int satisfiedPopulation[500]={0};   //滿足人數矩陣
                ///for (int i=0; i<n; i++)
                ///{
                ///    for (int j = 0; j<n; j++)
                ///    {
                ///        if (s[i][j] == 2)
                ///        {
                ///            satisfiedPopulation[i] += population[i];
                ///        }
                ///    }
                ///}

                if (answer[i] == 0)
                    continue;
                int tem = 0;
                tem = answer[i];
                answer[i] = 0;

                if ( checkCover(answer,n,scov,i,sumcov) == 1 )   //檢查是否涵蓋全部
                {
                    couldBeChosen[0][i] = i;
                    couldBeChosen[1][i] = cost[i];
                    continueOrNot = 1;
                    ///couldBeChosenCostPerPerson[i] = cost[i]/satisfiedPopulation[i];   //單位人數最貴的？
                }
                answer[i] = tem;

            }
            if (continueOrNot == 0)             // 感覺可刪掉  如果沒有任何候選點就中止
                break;

            int maxNum = 0;                            //最貴候選點編號
            int maxCost = couldBeChosen[1][0];          //最貴候選點成本
            for (int i = 0; i<n; i++)
            {
                if (couldBeChosen[0][i] != -1)
                {
                    maxNum = couldBeChosen[0][i];
                    maxCost = couldBeChosen[1][i];
                    break;
                }
            }


            for (int i = maxNum; i<n; i++)               //找出候選點中最貴的
            {
                if (couldBeChosen[1][i] > maxCost)
                {
                    maxNum = i;
                    maxCost = couldBeChosen[1][i];
                }
            }

            answer[maxNum] = 0; //踢掉候選點
            budget = budget - cost[maxNum];




            ///float maxCostPerPerson = couldBeChosenCostPerPerson[0];

            ///for (int i = 1; i<n; i++)               //找出候選點中單位人數最貴的
            ///{
            ///if (couldBeChosenCostPerPerson[i] > maxCostPerPerson)
            ///    {
            ///        maxNum = i;
            ///        maxCostPerPerson = couldBeChosenCostPerPerson[i];
            ///    }
            ///}

            ///for (int i = 0; i<n; i++)
            ///{
            //    cout<<couldBeChosen[0][i]<<" ";
            //    cout<<couldBeChosenCostPerPerson[i]<<" ";

            ///}
            ///cout <<"\n";
            ///cout << maxNum<<"\n";

            ///answer[maxNum] = 0; //踢掉候選點
            ///budget = budget - cost[maxNum];

            ///for (int i = 0; i<n; i++)
            ///{
            ///    if (answer[i]==1)
            ///    {
            ///        cout<<i+1<<" ";
            ///    }
            ///}
            ///cout<<"\n"<<budget<<"\n";

            //renewS(answer, n, s);    //更新s
            //renewSatisfy(s, n, satisfy);   //更新滿足包含矩陣

        }



        bool k = 0;                     //印出答案
        for (int i = 0; i<n; i++)
        {

            if (answer[i] == 1)
            {
                if (k == 1)
                {
                    cout <<" ";
                }
                k = 1;
                cout<<i+1;
            }
        }
        //cout<<"\n"<<budget<<"\n";

        //for (int i = 0; i<n; i++)
        //{
        //    cout<<cost[i]<<" ";
        //}
    }

    return 0;
}

bool checkCover(int answer[],int n, int s[][500]) // 確認包含全部
{
    int A[500] ={0};        //  檢查用
    for (int i = 0; i < n; i++)
        A[i] = 1;           //全部預設為1 表示沒被包含

    for (int i = 0; i < n; i++)
    {
        if (answer[i] == 1)
        {
            for (int j = 0; j<n; j++)
            {
                if (s[i][j] != 0)
                {
                    A[j] = 0;   //如果有被包含到則變0
                }
            }

        }

    }
    for (int i = 0; i < n; i++)
    {
        if (A[i] == 1)
        {
            return false;
        }
    }
    return true;
}

bool checkCover(int answer[],int n, int scov[][500],int id,int sumcov[]) // 確認包含全部
{
    for(int j=0;j<n;j++)
    {
        if((sumcov[j]-scov[id][j])==0)
        {
            return false;
        }
    }
    for(int j=0;j<n;j++)
    {
        sumcov[j]-=scov[id][j];
    }
    return true;

}


//bool checkSatisfied(int answer[],int n,int s[][500])  //檢查是否滿足全部
//
//{
//    int A[500] ={0};        //  檢查用
//    for (int i = 0; i < n; i++)
//        A[i] = 1;           //全部預設為1 表示沒被滿足
//
//    for (int i = 0; i < n; i++)
//    {
//        if (answer[i] == 1)
//        {
//            for (int j = 0; j < n; j++)
//            {
//                if (s[i][j] == 2)
//                {
//                    A[j] = 0;   //變0表示有被滿足
//                }
//            }
//
//        }
//
//    }
//    for (int i = 0; i < n; i++)
//    {
//        if (A[i] == 1)
//        {
//            return false;
//        }
//    }
//    return true;
//
//
//}
bool checkSatisfied(int answer[],int n,int ssat[][500],int id,int sumsat[])  //檢查是否滿足全部

{
    for(int j=0;j<n;j++)
    {
        if((sumsat[j]-ssat[id][j])==0)
        {
            return false;
        }
    }
    for(int j=0;j<n;j++)
    {
        sumsat[id]-=ssat[id][j];
    }
    return true;

}



bool checkBudget(int answer[],int B,int cost[1000],int n)   //確認有沒有超出預算
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (answer[i] == 1)
        {
            sum += cost [i];
        }
    }
    if (sum <= B)
        return false;   //0表示沒有超出預算
    else
        return true;    //1表示超出預算範圍
}

void renewS(int answer[],int n,int s[][500])   //更新s
{
    for (int i=0; i<n; i++)
    {
        if (answer[i]==0)
        {
            for (int j = 0; j<n; j++) {
                s[i][j] = 0;
                s[j][i] = 0;
            }
        }
    }
}
