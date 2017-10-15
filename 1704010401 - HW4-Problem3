//this is not testing!!
#include <iostream>
using namespace std;
 
int main()
{
 
    //S=supply,s=shortage,C_0=invCost,C_u=shortageCost,I_0=invend
    int supply=0,shortageMin=0,invCost=0,shortageCost=0,inv_0=0,invEnd=0,totalcost=0,n=0,totalcostMin=0,shortageDays=0;
    cin>>supply>>invCost>>shortageCost>>inv_0;
    invEnd=inv_0;
    //逐日需求量
    cin>>n;
    //建立陣列
    int dailyDemand[10000];
    //迴圈輸入
    for(int i=0; i<n;i++)
    {
        cin>>dailyDemand[i];
    }
    //Do iteration to find the s when min total cost occurs
    for(int s=0;s < supply;s++ )
    {
        for(int i=0; i<n;i++)
        {
 
            //期初存貨＝昨日的期末存貨
            invEnd=invEnd-dailyDemand[i];
            //計算當日存貨是否足夠
            //足夠的話計算存貨成本
            if(invEnd>=0)
            {
                //當日的存貨成本加入總成本
                totalcost+=invEnd*invCost;
            }
                //不足的話計算缺貨成本
            else
            {
                //當日的缺貨成本加入總成本
                totalcost+=(-invEnd)*shortageCost;
                //本日缺貨
                shortageDays+=1;
                //期末沒貨了
                invEnd=0;
            }
 
            //商店每天打烊後會做檢查，並在需要時向上游下訂單。如果有訂貨，則會在隔天一早收到貨。
            if(invEnd<=s)
            {
                //補貨至supply
                invEnd=supply;
            }
            //每日
        }
        //Log the min total cost & the s when min total cost occurs
        if(totalcostMin==0||totalcostMin>totalcost)
        {
            totalcostMin=totalcost;
            shortageMin=s;
        }
        totalcost=0;
        invEnd=inv_0;
    }
    cout<<shortageMin<<" "<<totalcostMin;
 
    return 0;
}
