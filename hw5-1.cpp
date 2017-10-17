//1704010501 - HW5-Problem1
#include <iostream>
using namespace std;
int main() {
    //輸入資料
    int m,n,k,h;
    int times=0;
    int count=0;
    //輸入mnkh
    cin>>m>>n>>k>>h;
    int B[100][100]={ {0} };
    int L[100]={0};
    int rating[100]={0};
    int order[100]={0};
    int max[100]={0};
    //輸入B
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>B[i][j];
        }
    }
    //輸入Li
    for(int i=0;i<h;i++){
        cin>>L[i];
    }

    //計算Ri
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            rating[i]=rating[i]+B[i][j];
            if(B[i][j]!=0)
            {
                times++;
            }
        }
        rating[i]-=times*k;
        times=0;
    }
    //順序排列
    for(int i=0;i<m;i++)
    {
        max[i]=-400;
        for(int j=0;j<m;j++)
        {
            if (rating[j] > max[i])
            {
                max[i]=rating[j];
                order[i]=j;
            }
        }
        rating[order[i]]=-400;
        order[i]=order[i]+1;
    }
    //符合條件
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<h;j++)
        {
            if(order[i]==L[j]& i==0)
            {
                cout<<order[i];
            }
            else if(order[i]==L[j])
            {
                cout<<" "<<order[i];
            }
        }
    }

    return 0;
}
