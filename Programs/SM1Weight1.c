// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 1035
//#define ed 0.16*LEN
//#define FILENAME "txt10.txt"
//#define FILENAME "ll.txt"
//#define FILENAME "c-fat500-5.clq.txt"
//#define FILENAME "p_hat500-3.clq.txt"
//#define FILENAME "hamming8-2.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C1000.9.clq.txt"
//#define FILENAME "gen200_p0.9_44.b.txt"
//#define FILENAME "san400_0.7_1.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
//#define FILENAME "brock400_4.b.txt"
//#define FILENAME "r500.5.txt"
#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller6.clq.txt" 
 
int Max=1;
int target=345;
int m=LEN+1,n=LEN+2;
int fixed[LEN+1][LEN+2];
int c0[LEN+1];
int cc0[2][LEN+1];
int arr[LEN+1];
int no=0;
int pre=0;
int select_Max_Var(int ,int,int,int);
int Greedy_Swap(int);
void Update_Deg(int, int);
void residual_graph_Update(int *, int  ,int *,int);
float mxdeg(int ,int (*)[m],int ,int );
clock_t start; clock_t end;  clock_t dif;
int main(){
       int i,j,k,r;
    printf("\nCliques getting computed\n");
    for(i=1;i<m;i++) 
      {fixed[i][0]=i; fixed[0][i]=i; arr[i]=i;for(j=1;j<n;j++) fixed[i][j]=0; }             
    FILE *f=fopen(FILENAME,"r");
    int integer1,integer2; 
    while(fscanf(f,"%d",&integer1)>0)
	    {fscanf(f,"%d",&integer2);
	      fixed[integer1][integer2]=1;
	      fixed[integer2][integer1]=1;
	      fixed[integer1][n-1]=fixed[integer1][n-1]+1;
	      fixed[integer2][n-1]=fixed[integer2][n-1]+1;
	     }
  /*/.sort min deg vertex first
    int big,loc,dum;
   	for(i=1;i<LEN;i++){ 
       big=fixed[arr[i]][n-1];loc=i;
       for(j=i+1;j<=LEN;j++)
        { if(fixed[arr[j]][n-1]<big){big=fixed[arr[j]][n-1];loc=j;}}
       dum=arr[i]; arr[i]=arr[loc];arr[loc]=dum;
    }  
   //  printf("\nsorted array\n"); for(j=1;j<m;j++)  printf("%d\t",arr[j]);
  ///*///SM1Weight......................
  int calls=0,countt=0; 
  time_t ti; srand((unsigned) time(&ti));
  start=clock();
  for(i=600;i<LEN;i++)
   { if(Max>=target) break;
      int t=i;//1+rand()%LEN; //printf("\nt=%d\n",t);
      for(j=1;j<m;j++)
        {cc0[0][j]=0;cc0[1][j]=0;if(fixed[t][j]==1) c0[j]=j; else c0[j]=0;}
      for(k=0;k<0.2*target;k++)
       {r= Greedy_Swap(t);
        if(r>Max) Max=r;
        if(Max>=target) break;
        for(j=1;j<m;j++) if(c0[j]==-1)c0[j]=j;
     }if(Max>=target) break;}
    end=clock(); 
    dif=end-start;
     printf("\ntime in seconds is %.5f\t",(float)(dif)/CLOCKS_PER_SEC); 
     printf("Max clique=%d, # Iterations=%d & repetation ...\n",Max,no);
       //for(i=1;i<m;i++) printf("%d\t",arr[i]);
       getch();
   return 0;
   }
//..................................................................................
int Greedy_Swap(int k) {
    int i,j,clen=1,c0len,cpos,it=0; 
    int cflen=fixed[k][n-1],c[cflen+1]; for(i=0;i<=cflen;i++) c[i]=0;
    c[clen]=k; c0len=cflen; 
    Update_Deg(clen, cflen);
  //printf("\ncalled vertex k=%d\t\n",k);  for(i=1;i<m;i++) printf("\n%d\t%d\t%d\n",c0[i],cc0[0][i],cc0[1][i]);
   
  while(cflen>0)
     { it++; //iteration++
       if((clen+cflen)<=Max) return;
        i=select_Max_Var(cflen,c0len,clen,it);
       if(c0[i]<=0) break; 
       c[++clen]=c0[i]; 
      // if((it<0.2*target)&&(cc0[1][i]<0.5*target)) cc0[1][i]=cc0[1][i]+2;  else 
       if((cc0[1][i]<0.2*target)) cc0[1][i]=cc0[1][i]+100;  else
	   if((cc0[1][i]<0.8*target)) cc0[1][i]=cc0[1][i]+10; 
       c0[i]=-1;cflen--; cpos=clen; 
       residual_graph_Update(c,cpos,&cflen,clen);
        Update_Deg(clen, cflen);
       no++;// for(i=1;i<m;i++) printf("\n%d\t%d\t%d\n",c0[i],cc0[0][i],cc0[1][i]);
     }
  clen++; end=clock(); 
    dif=end-start; 
  printf("\n vertex k:%d \t  cliques size(clen) :%d: Time %.6f # of iterations %d",k,clen-1,(float)(dif)/CLOCKS_PER_SEC, no);
// for(i=1;i<clen;i++)printf(" %d\t",c[i]);
   return clen-1;
  }
//...........................................................................
int select_Max_Var(int cflen,int c0len, int clen, int it)//done//change
    { int i,j,k,x,s1,s2,c0pos=0,c0max=0,count=0,list[2][cflen], cc0avg=0;  
        float y,mx=0.0,sum=0.0; int flag=0,f=0; x=0;  time_t ti;srand((unsigned) time(&ti));
        for(k=0;k<m;k++){if(c0[k]>0){flag=1;c0pos=k;c0max=cc0[0][k];break;}}
      if(flag==1)
         {for(j=k+1;j<m;j++)
           {if(c0[j]>0)
		     {if((cc0[0][j]>c0max)&&(cc0[1][j]<it))
              // if((cc0[0][j]>c0max)&&((cc0[1][j]<it)||((it<3)&&(cc0[0][j]<target/2))))
		     {f=1;c0pos=j;c0max=cc0[0][j];}}       
         }}
    return c0pos;
    }
//...................................................................................  
 void residual_graph_Update(int *c, int cpos,int *cflen,int clen)//update c1len, cflen, m
  {  int i,j,count=0;
      for(i=1;i<m;i++)
        { if(c0[i]>0)
             {if( fixed[c[cpos]][c0[i]]==0){ *cflen=*cflen-1; c0[i]=-1;cc0[0][i]=0;}}
        } 
    }     
  //................................................................................
 void Update_Deg(int clen, int cflen )
  {  int i,j,nu=0,count1=0,count2=0; //*mi=0;*ma=0;
     for(i=1;i<m;i++)cc0[0][i]=0;
     for(i=1;i<m-1;i++)
        { if(c0[i]>0)
           {for(j=i+1;j<m;j++)
             { if(c0[j]>0)
                {if(fixed[c0[i]][c0[j]]==1)
                  { cc0[0][i]=cc0[0][i]+1;  cc0[0][j]=cc0[0][j]+1;} 
        } }}} 
		
//for(i=1;i<m;i++) if(cc0[0][i]>target-clen-2) (*d)++;
}
// The End........................................................................... 

