#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>

using namespace std;

void initial(char matrix[20][20]){
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            if(i==0||i==19)
                matrix[i][j]=char(205);
            else{
                if(j==0||j==19){
                    matrix[i][j]=char(179);
                }
                else{
                    matrix[i][j]=char(32);
                }
            }
        }
    }
}

void show(char matrix[20][20]){
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void draw(int body[2][20],char bodychar[20], char matrix[20][20], int snakesize){
    int x, y;
    for(int i=0;i<snakesize;i++){
        y=body[0][i];
        x=body[1][i];
        matrix[y][x]=bodychar[i];
    }
}

void snakemove(int body[2][20],char bodychar[20], int direction, int snakesize){
    for(int i=(snakesize-1);i>0;i--){
        body[0][i]=body[0][i-1];
        body[1][i]=body[1][i-1];
    }
    switch(direction){//If segun la direccion
        case 6:{
            body[1][0]+=1;
            break;
            }
        case 8:{
            body[0][0]-=1;
            break;
        }
        case 4:{
            body[1][0]-=1;
            break;
        }
        case 2:{
            body[0][0]+=1;
            break;
        }
    }
    for(int i=(snakesize-1);i>0;i--){
        bodychar[i]=bodychar[i-1];
    }
    if(direction==8||direction==2)//If segun direccion
        bodychar[1]=char(124);
    if(direction==6||direction==4)
        bodychar[1]=char(196);
}

int key(int direction){
    int dir;
    if(kbhit()){
        dir=getch();
        if(dir==224)
            dir=getch();
        switch(dir){
            case 72:{//case arriba
                if(direction!=2)
                    direction=8;
                break;
            }
            case 80:{//case abajo
                if(direction!=8)
                    direction=2;
                break;
            }
            case 77:{//case derecha
                if(direction!=4)
                    direction=6;
                break;
            }
            case 75:{//case izquierda
                if(direction!=6)
                    direction=4;
                break;
            }
        }
   }
   return direction;
}

bool fruit(char matrix[20][20], bool newcord, int body[2][20]){
    int x,y;
    bool eat=false;
    if(newcord==true){
        do{
            x=rand()%18+1;
            y=rand()%18+1;
        }while(matrix[y][x]!=char(32));
        matrix[y][x]=char(42);
        newcord=false;
    }else{
        if(body[0][0]==y&&body[0][1]==x){
            eat=true;
            newcord=true;
        }
    }

    return eat;
}

int main()
{
    char board[20][20];
    int body[2][20]={0}, snakesize=3, direction=6;
    char bodychar[20]={char(00)};
    bool gameover=false, newcord=true, eat=false;
    bodychar[0]=char(111);
    bodychar[1]=char(196);
    bodychar[2]=char(196);
    body[0][0]=10;
    body[1][0]=10;
    body[0][1]=10;
    body[1][1]=9;
    body[0][2]=10;
    body[1][2]=8;
    do{
    initial(board);
    newcord=fruit(board,newcord,body);
    draw(body,bodychar,board,snakesize);
    show(board);
    direction=key(direction);
    snakemove(body, bodychar, direction, snakesize);
    Sleep(1000);
    system("cls");

    }while(gameover==false);
    return 0;
}
