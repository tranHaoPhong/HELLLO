#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
#define WIDTH 5
#define HEIGHT 5
int cells[HEIGHT+1][WIDTH+1];
int i,j;
int x,y,z;
int cursorX=1, cursorY=1;
int Mode=1;
float Rate;
void set_color ( int code ) 
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}
int Test(int cells[HEIGHT+1][WIDTH+1])
{
	int Test=0;
	for(i=1;i<=HEIGHT;i++)
	{
		for(j=1;j<=WIDTH;j++)
		{
			if(cells[i][j]==HEIGHT*(i-1)+j){Test++;}
		}
	}
	return(Test);
}
void Rotate(int m, int n)
{
	int a,b,c,d;
	a=cells[m][n];b=cells[m][n+1];
	c=cells[m+1][n+1];d=cells[m+1][n];
	cells[m][n]=d;
	cells[m][n+1]=a;
	cells[m+1][n+1]=b;
	cells[m+1][n]=c;
}
void PreTable()
{
	set_color(0x0E);printf("\tROTATE GAME\n");
	set_color(0x09);printf("Rules:\n");
	set_color(0x0F);printf("+Use UP,DOWN,RIGHT,LEFT to move\n");
	set_color(0x0F);printf("+Use SPACE to rotate\n");
	for(z=1;z<=WIDTH;z++){set_color(0x0F);printf("+----");}
	printf("+\n");
	for(y=1;y<=HEIGHT;y++)
	{
		for(z=1;z<=WIDTH;z++){set_color(0x0F);printf("|    ");};printf("|\n");
		for(x=1;x<=WIDTH;x++)
		{
			set_color(0x0F);printf("|");
			cells[y][x]=HEIGHT*(y-1)+x;
			set_color(0x09);
			if(cells[y][x]<10){printf(" 0%d ",cells[y][x]);}
			else{printf(" %d ",cells[y][x]);}
		}
		set_color(0x0F);printf("|\n");
		for(z=1;z<=WIDTH;z++){printf("+----");}
		printf("+\n");
	}
	printf("Move then ENTER to choose Difficult:\n");
	for(i=1;i<=5;i++)
	{
		if(i==Mode){set_color(0x0E);printf("  [%d]  ",i);}
		else{set_color(0x0F);printf("   %d   ",i);}
	}
}
void Setup()
{
	int GO=0;
	while(1)
	{
		PreTable();
		switch(getch())
		{
			case 13: 
			    GO=1;
			    break;
			default:
				switch(getch())
				{
			        case 75: if(Mode>1){Mode--;};break;
			        case 77: if(Mode<5){Mode++;};break;
			        default: break;
				}
		}
		system("cls");
		if(GO==1){break;}
	}
}
void Start()
{
	int m,n;
	Setup();
	srand((int)time(NULL));
	for(i=1;i<=Mode*3;i++)
	{
	    m=(rand()%(HEIGHT-1))+1;n=(rand()%(WIDTH-1))+1;
	    Rotate(m,n);
	}
}
int Table()
{
	set_color(0x0E);printf("\tROTATE GAME\n");
	set_color(0x09);printf("Rules:\n");
	set_color(0x0F);printf("+Use UP,DOWN,RIGHT,LEFT to move\n");
	set_color(0x0F);printf("+Use SPACE to rotate\n");
	for(z=1;z<=WIDTH;z++){set_color(0x0F);printf("+----");}
	printf("+\n");
	for(y=1;y<=HEIGHT;y++)
	{
		for(z=1;z<=WIDTH;z++){set_color(0x0F);printf("|    ");};printf("|\n");
		for(x=1;x<=WIDTH;x++)
		{
			set_color(0x0F);printf("|");
			if((y==cursorY && x==cursorX) || (y==cursorY && x==cursorX+1) || (y==cursorY+1 && x==cursorX) ||(y==cursorY+1 && x==cursorX+1))
			{
			    if((y==cursorY && x==cursorX) || (y==cursorY+1 && x==cursorX) )
				{
				    set_color(0x0C);
				    printf("[");
				    set_color(0x0E);
			        if(cells[y][x]<10){printf("0%d ",cells[y][x]);}
			        else{printf("%d ",cells[y][x]);}
				}
			    else
				{
				    set_color(0x0E);
			        if(cells[y][x]<10){printf(" 0%d",cells[y][x]);}
			        else{printf(" %d",cells[y][x]);}
			        set_color(0x0C);
				    printf("]");
				}
			}
			else
			{
			    set_color(0x09);
			    if(cells[y][x]<10){printf(" 0%d ",cells[y][x]);}
			    else{printf(" %d ",cells[y][x]);}
			}
		}
		set_color(0x0F);printf("|\n");
		for(z=1;z<=WIDTH;z++){printf("+----");}
		printf("+\n");
	}
	printf("Difficult:   %d\n",Mode);
	set_color(0x09);printf("Success:   %0.0f\n",Rate);
}
void Game()
{
	while(1)
	{
		Rate=(float)Test(cells)*100/(HEIGHT*WIDTH);
		Table();
		if(Rate==100){set_color(0x0E);printf("(^v^) You WIN!!\n");system("pause");break;}
		switch(getch())
		{
			case 32: 
			    Rotate(cursorY,cursorX);
			    break;
			default:
				switch(getch())
				{
					case 72: if(cursorY>1){cursorY--;};break;
			        case 80: if(cursorY<HEIGHT-1){cursorY++;};break;
			        case 75: if(cursorX>1){cursorX--;};break;
			        case 77: if(cursorX<WIDTH-1){cursorX++;};break;
				}
		}
		system("cls");
	}
}
int main()
{
	Start();
	Game();
	return 0;
}
