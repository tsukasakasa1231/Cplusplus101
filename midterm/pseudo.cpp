// 輸入內容
// 變數：
// 總村莊數
// 預算
// 包含時間
// 滿足時間
// 村莊距離[][]
// 被選過的村莊[]

score_contain(給定一個村莊, 總村莊數,預算,包含時間,滿足時間,村莊距離[][],被選過的村莊[])
{
	
for(所有其它村莊)
{if(沒被選過)
	{
		//檢查能不能直接走過去
		if(可以直接走過去且<=包含時間)
			加總可以的村莊
			
		else (不行)
		{
			檢查所有能到這個村莊而且可以到給定村莊的其它村莊
			if(可以連通)
			{
				if(滿足包含時間)
				{
					找最短時間的
					加總可以的村莊數目
				}
			}
			else(不能連通)
				檢查所有能到這個村莊而且可以到給定村莊的其它村莊
						if(可以連通)
						{
							if(滿足包含時間)
							{
								找最短時間的
								加總可以的村莊數目
							}
						}		
					else(不能連通)
						檢查所有能到這個村莊而且可以到給定村莊的其它村莊
						….
						….
			//檢查是否連通 這邊感覺可以recursive
		
		}
	}
}

return 加總的村莊數目/成本

}

main()
{
//先選擇包含
while(沒有包含所有村莊)
{
	for(所有村莊)
	{
		if(這個村莊還沒被包含)
		{
		用func 算分數
		找分數最小值(平均成本最低)
		}
	}
	紀錄最小值村莊
	紀錄這個選的順序
	把(這個村莊可以包含的村莊)紀錄進去(選過的村莊)



}
//





}



------------------------------------------------------------
Init(start) // start：起點
{
    //for all vertex
    v_d = -1; // 起點到此頂點的最短距離
    s_d = 0; // 起點到自己的距離
}

Relax(u, v, w) 
{
    if v_d > (u_d + w)
    {
        v_d = u_d + w;
        v_f = u;
    }
}

Dijkstra(start)
{
    Init(start);
    bool s[] = {0}; // s = 1 表示已確定最短路徑
    Q[] = {起點到各頂點距離};
    while(Q != 0)
    {
        u = min(Q); //找一個s[]是0，且Q值最小的點當作u點
        s[u] = 1; 
        while(和u 相連的點)
        { 
            Relax(u, v, w); // w為起點直接到頂點的距離
        }
    }
} 
