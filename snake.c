#include<stdio.h>
void leftMovement(float *tab,int *tab1,int x)
{
		tab[0]-=0.1;	// top right
		tab[3]-=0.1;	// bottom right
		tab[6]-=0.1;	// bottom left
		tab[9]-=0.1;	// top left
		if(tab[6]<-1.01f)
		{
		tab[0]=1.0f;
		tab[3]=1.0f;
		tab[6]=0.9f;
		tab[9]=0.9f;
		}
		tab1[x]=1;
}
void bottomMovement(float *tab,int *tab1,int x)
{
		tab[1]-=0.1;	// top right
		tab[4]-=0.1;	// bottom right
		tab[7]-=0.1;	// bottom left
		tab[10]-=0.1;	// top left
		if(tab[4]<-1.01f)
		{
		tab[1]=1.0f;
		tab[4]=0.9f;
		tab[7]=0.9f;
		tab[10]=1.0f;
		}
		tab1[x]=1;
}
void topMovement(float *tab,int *tab1,int x)
{
		tab[1]+=0.1;	// top right
		tab[4]+=0.1;	// bottom right
		tab[7]+=0.1;	// bottom left
		tab[10]+=0.1;	// top left
		if(tab[1]>1.01f)
		{
		tab[1]=-0.9f;
		tab[4]=-1.0f;
		tab[7]=-1.0f;
		tab[10]=-0.9f;
		}
		tab1[x]=1;
}
void rightMovement(float *tab,int *tab1,int x)
{
		tab[0]+=0.1;	// top right
		tab[3]+=0.1;	// bottom right
		tab[6]+=0.1;	// bottom left
		tab[9]+=0.1;	// top left
		if(tab[3]>1.01f)
		{
		tab[0]=-0.9f;
		tab[3]=-0.9f;
		tab[6]=-1.0f;
		tab[9]=-1.0f;
		}
		tab1[x]=1;	
}
