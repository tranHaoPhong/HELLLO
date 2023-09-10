#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
int UCLN(int A, int B)
{
	if(B==0) return A;
	else return UCLN(B, A%B);
}
struct Fraction
{
	int nume, deno;
};
void swap(Fraction &a, Fraction &b)
{
	Fraction cache;
	cache=a;a=b;b=cache;
}
Fraction Frac(int a)
{
	Fraction cache;
	cache.nume=a;
	cache.deno=1;
	return(cache);
}
Fraction Simple(Fraction a)
{
	Fraction cache;
	cache.nume=a.nume/UCLN(a.nume,a.deno);
	cache.deno=a.deno/UCLN(a.nume,a.deno);
	if(cache.deno<0)
	{
		cache.deno=cache.deno*(-1);
		cache.nume=cache.nume*(-1);
	}
	return(cache);
}
int cmp(Fraction &a, Fraction &b)
{
	a=Simple(a);b=Simple(b);
	if(a.nume==b.nume && a.deno==b.deno){return(1);}
	else{return(0);}
}
Fraction Plus(Fraction a, Fraction b)
{
	Fraction cache;
	cache.nume=a.nume*b.deno+a.deno*b.nume;
	cache.deno=a.deno*b.deno;
	cache=Simple(cache);
	return(cache);
}
Fraction Minus(Fraction a, Fraction b)
{
	Fraction cache;
	cache.nume=a.nume*b.deno-a.deno*b.nume;
	cache.deno=a.deno*b.deno;
	cache=Simple(cache);
	return(cache);
}
Fraction Multiply(Fraction a, Fraction b)
{
	Fraction cache;
	cache.nume=a.nume*b.nume;
	cache.deno=a.deno*b.deno;
	cache=Simple(cache);
	return(cache);
}
Fraction Divide(Fraction a, Fraction b)
{
	Fraction cache;
	cache.nume=a.nume*b.deno;
	cache.deno=a.deno*b.nume;
	cache=Simple(cache);
	return(cache);
}
void View(Fraction a, int Control1, int Control2)
{
	if(abs(a.deno)>1)//Real fraction //
	{
		if(Control2>0){printf("+");}
	    printf("(%d/%d)",a.nume,a.deno);
	}
	else //Integer//
	{
		if(abs(a.nume*a.deno)>1) //More 1//
		{
			if(a.nume*a.deno>1 && Control2>0){printf("+");}
			printf("%d",a.nume*a.deno);
		}
		else //equal 1//
		{
			if(a.nume*a.deno==1 && Control2>0){printf("+");}
			if(a.nume*a.deno==-1){printf("-");}
			if(Control1==0){printf("1");}
		}
	}
}
struct Point
{
	Fraction x,y;
};
void SWAP(Point &a, Point &b)
{
	Point cache;
	cache.x=a.x;cache.y=a.y;
	a.x=b.x;a.y=b.y;
	b.x=cache.x;b.y=cache.y;
}
int CMP(Point &a, Point &b)
{
	if(cmp(a.x,b.x)==1 && cmp(a.y,b.y)==1){return(1);}
	else{return(0);}
}
struct Polynominal
{
	Fraction A[20];
};
void Reset(Polynominal &a)
{
	int i;
	for(i=0;i<=19;i++)
	{
		a.A[i]=Frac(0);
	}
}
Polynominal SUMF(Polynominal a, Polynominal b)
{
	int i;
	Polynominal cache;
	for(i=0;i<=19;i++)
	{
		cache.A[i]=Plus(a.A[i],b.A[i]);
	}
	return(cache);
}
Polynominal MUL1(Polynominal a, Polynominal b)
{
	int i,j;
	Polynominal cache;
	for(i=0;i<=19;i++)
	{
		cache.A[i]=Frac(0);
		for(j=0;j<=i;j++)
		{
			cache.A[i]=Plus(cache.A[i],Multiply(a.A[j],b.A[i-j]));
			//cache.A[i]=cache.A[i]+a.A[j]*b.A[i-j];//
		}
	}
	return(cache);
}
Polynominal MUL2(Polynominal a, Fraction K)
{
	int i;
	Polynominal cache;
	for(i=0;i<=19;i++)
	{
		cache.A[i]=Multiply(a.A[i],K);
	}
	return(cache);
}
int main()
{
	Point P[20];
	Polynominal f,g,Fx;
	Fraction Choice[19],cache;
	int n,i,j,z,cache1,cache2,Phong=0;
	while(n<2)
	{
		system("cls");
		printf("Nhap so luong Point: ");scanf("%d",&n);
	}
	printf("// VD: Nhap Point[0] = 3;4\n\n");
	for(i=1;i<=n;i++)
	{
		printf("Nhap Point[%d] = ",i);scanf("%d;%d",&cache1,&cache2);
		P[i].x=Frac(cache1);
		P[i].y=Frac(cache2);
		if(cache2>0){Phong=1;}
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(j!=i)
			{
				if(CMP(P[j],P[i])==1){SWAP(P[j],P[n]);n--;}
			}
		}
	}
	Reset(Fx);
	if(Phong==1)
	{
		for(i=1;i<=n;i++){Choice[i]=P[i].x;}
		for(j=1;j<=n;j++)
	    {
	    	swap(Choice[j],Choice[1]);
	        Reset(f);Reset(g);
	        cache=Frac(1);f.A[0]=Frac(1);
	        for(z=2;z<=n;z++)
	        {
	    	    g.A[0]=Minus(Frac(0),Choice[z]);
	    	    //g.A[0]=-Choice[z];//
	    	    g.A[1]=Frac(1);
	    	    f=MUL1(f,g);
	    	    cache=Multiply(cache,Minus(Choice[1],Choice[z]));
	    	    //cache=cache*(Choice[1]-Choice[z]);//
		    }
	        Fx=SUMF(Fx,MUL2(f,Divide(P[j].y,cache)));
		    //F=F+f*P[j].y/cache;//
	    }
	}
	else
	{
		Fx.A[0]=Frac(1);
		for(i=0;i<=19;i++){g.A[i]=Frac(0);}
		for(z=1;z<=n;z++)
	    {
	    	g.A[0]=Minus(Frac(0),P[z].x);
	    	//g.A[0]=-P[z].x;//
	    	g.A[1]=Frac(1);
	    	Fx=MUL1(Fx,g);
		}
	}
	Phong=0;
	printf("\n(*) Da thuc Lagrange:\ny = ");
	for(i=n;i>=0;i--)
	{
		if(Fx.A[i].nume!=0)
		{
			View(Fx.A[i],i,Phong);
		    if(i>0){printf("x");}
		    if(i>1){printf("^(%d)",i);}
		    printf(" ");
		    Phong=1;
		}
	}
	if(Phong==0){printf("Not exist!");}
	printf("\n\n");
	system("pause");
	return(0);
}
