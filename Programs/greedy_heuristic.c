#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 10
#define target 10
//#define FILENAME "8.txt"
#define FILENAME "txt10.txt"
//#define FILENAME "DAGS1.txt"
//#define FILENAME "c-fat200-5.clq.txt"
//#define FILENAME "p_hat300-3.clq.txt"
//#define FILENAME "hamming8-4.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "gen200_p0.9_44.b.txt"
//#define FILENAME "san200_0.7_2.clq.txt"
//#define FILENAME "sanr200_0.7.clq.txt"
//#define FILENAME "brock200_1.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller6.clq.txt" 


//time_t ti; srand((unsigned) time(&ti));
clock_t start; clock_t end;  clock_t dif;
int m=LEN+1,n=LEN+1,mxColor,mxS8atDeg;
char matrix[LEN+1][LEN+1];  //c[] is used to store clique vertices , c2[]stores color
int  c2[LEN+1], deg[LEN+1];// //MOV in MinOrdVertex,  it[] is to store # iteration/inclusion of a vertex in clique


 void colorvertex( int );

int main(){
    int i,j,k,r,t,nv=0;
    for(i=1;i<m;i++) { deg[i]=0;  for(j=1;j<m;j++) matrix[i][j]='0'; }	 //initializatin
	        
    FILE *f=fopen(FILENAME,"r");
     
    while(fscanf(f,"%d",&i)>0)
	    { fscanf(f,"%d",&j);
	      matrix[i][j]='1'; matrix[j][i]='1'; deg[i]++; deg[j]++;
	    }
   
  start=clock(); 
  colorvertex(m); //printf("\n MxColor=%d\n",mxColor);
   end=clock(); 
    dif=end-start;
       printf("\n#colors:%d \ttime spent %.5f\t",mxColor,(float)(dif)/CLOCKS_PER_SEC); 
       getch();
   return 0;
   }

 //...............................................................................
 void colorvertex( int N)
 { int i,j,k,mx,p, temp=0, T1[N],T2[N], T3[N],co[N],L[N]; // contains Vertex, degree, max chosen vertex, color  & L[] vertex index in max deg ordered  
 
 
   
    for(i=1;i<N;i++){ T1[i]=i;T2[i]=deg[i]; T3[i]=0; if(T2[i]>temp) {mx=i; temp=T2[i];}}// initialization &finding max deg vertex
  //max ordering.
  j=1; //printf("\nMaxDeg ordered vertex:");//printf("\n max deg vertex= %d\tN=%d\ttemp=%d\n \n", mx,N, temp);
 
  while(N>1)
   {  L[j]=T1[mx]; T1[mx]=T1[N-1]; T2[mx]=T2[N-1];T3[mx]=T3[--N]; temp=0; //printf("\t%d ", L[j]);
      for(i=1;i<N;i++)
          {if(matrix[L[j]][T1[i]]=='1')  {T2[i]=T2[i]-1; T3[i]++;}
		   if((T3[i]>temp)||((T3[i]==temp)&&(T2[i]>T2[mx]))) {mx=i; temp=T3[i];}  //1. max saturated vertex first
		   }  
      j++; 
   } //printf(" \n mxn ordered list: "); for(i=1;i<m;i++) printf("\t%d ", L[i]);
  //Coloring vertices in c2[],  
  c2[L[1]]=1; k=3*target; //probable # colors
  for(i=2;i<m;i++)      
      { j=1;  for(p=1;p<k;p++) co[p]=0;
       while(j<i) 
         { if(matrix[L[i]][L[j]]=='1')
                co[c2[L[j]]]=1; //store existing colors on neighbors, printf("%d\t",c[T1lor[1][minOrd[j]]]);
         j++; 
         }
       p=1;
	   while((co[p]>0)&&(p<k)) p++;  // find min availabe color
       c2[L[i]]=p;  if(p>mxColor) mxColor=p;
      }
      printf("\n& corresponding color:::"); for(i=1;i<m;i++) printf("%d\t ", L[i]);
      
      printf("\n& corresponding color:::"); for(i=1;i<m;i++) printf("%d\t ", c2[i]);
      int al=0.8,be=0.4;
	  int iter=LEN/4,loops=1;
	  int L[mxColor];
	 k=4;
      while(loops<iter)
	  {
		for(i=1;i<=mxColor;i++)
	  	{
			L[i]=i;
			}
		int flag=1;
		int l=1;
		while(l<=LEN&&flag)
		{
			j=1;
			while(j<k&&flag)
			{
				p=1;int c=0;
	   			while((co[p]>0)&&(p<k)) p++;  // find min availabe color
	   			c=p;
	   			if(c!=0)
	   			{
						
						}
				}
			}
      
     
}
// The End........................................................................... 

