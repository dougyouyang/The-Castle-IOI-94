//  Copyright © 2017 Dougy Ouyang. All rights reserved.

/*
 ID: ouyangd2
 PROG: castle
 LANG: C++
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int n, m, map[2502][5], visited[2502];
int room=0, lar, cnt;
int result=0, ansx=100, ansy=100;
char ans;

void mem()
{
    for(int i=0;i<2502;i++)
        visited[i]=0;
    return;
}

void check(int po, char dir)
{
    int x, y;
    char a;
    if(lar>result){
        if(dir=='S')
            ansx=po/m+2, ansy=po%m, ans='N';
        else
            ansx=po/(m+1)+1, ansy=po%m, ans='E';
        if(ansy==0)
            ansx--, ansy=m;
    }
    else{
        if(dir=='S')
            x=po/m+2, y=po%m, a='N';
        else
            x=po/m+1, y=po%m, a='E';
        if(y==0)
            x--, y=m;
        //check priority
        if(y<ansy)
            ansx=x, ansy=y, ans=a;
        else if(y==ansy){
            if(x>ansx)
                ansx=x, ansy=y, ans=a;
            else if(x==ansx){
                ans='N';
            }
        }
    }
    result=lar;
}

void floodfill(int x)
{
    cnt++, lar=max(lar, cnt);
    visited[x]=1;
    if(map[x][3] && !visited[x+1])
        floodfill(x+1);
    if(map[x][1] && !visited[x-1])
        floodfill(x-1);
    if(map[x][4] && !visited[x+m])
        floodfill(x+m);
    if(map[x][2] && !visited[x-m])
        floodfill(x-m);
}

int main()
{
    ofstream fout ("castle.out");
    ifstream fin ("castle.in");
    
    int i, j;
    
    fin >> m >> n;
    for(i=1;i<=n*m;i++){
        int num;
        fin >> num;
        if(num/8==0)
            map[i][4]=1;
        num%=8;
        if(num/4==0)
            map[i][3]=1;
        num%=4;
        if(num/2==0)
            map[i][2]=1;
        num%=2;
        if(num/1==0)
            map[i][1]=1;
    }
    
    //question 1 and 2
    for(i=1;i<=n*m;i++)
        if(!visited[i])
            cnt=0, floodfill(i), room++;
    fout << room << endl;
    fout << lar << endl;
    result=lar;
    
    //question 3 and 4
    for(i=0;i<n-1;i++){
        for(j=1;j<m;j++){
            if(i==3 && j==1){
                
            }
            if(!map[i*m+j][3]){
                mem();
                cnt=0, lar=0, map[i*m+j][3]=1;
                floodfill(i*m+j), map[i*m+j][3]=0;
                if(lar>=result)
                    check(i*m+j, 'E');
            }
            if(!map[i*m+j][4]){
                mem();
                cnt=0, lar=0, map[i*m+j][4]=1;
                floodfill(i*m+j), map[i*m+j][4]=0;
                if(lar>=result)
                    check(i*m+j, 'S');
            }
        }
    }
    for(i=0;i<n-1;i++){
        if(!map[i*m+m][4]){
            mem();
            cnt=0, lar=0, map[i*m+m][4]=1;
            floodfill(i*m+m), map[i*m+m][4]=0;
            if(lar>=result)
                check(i*m+m, 'S');
        }
    }
    for(i=1;i<m;i++){
        if(!map[(n-1)*m+i][3]){
            mem();
            cnt=0, lar=0, map[(n-1)*m+i][3]=1;
            floodfill((n-1)*m+i), map[(n-1)*m+i][3]=0;
            if(lar>=result)
                check((n-1)*m+i, 'E');
        }
    }
    
    fout << result << endl;
    fout << ansx << " " << ansy << " " << ans << endl;
    
    return 0;
}
