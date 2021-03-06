// Greedy local search algorithm for finding maximum clique 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define LEN 10

//#define FILENAME "8.txt"
#define FILENAME "txt10.txt"
//#define FILENAME "DAGS1.txt"
//#define FILENAME "c-fat500-5.clq.txt"
//#define FILENAME "p_hat1500-3.clq.txt"
//#define FILENAME "hamming6-4.clq.txt"
//#define FILENAME "johnson8-4-4.clq.txt"
//#define FILENAME "C125.9.clq.txt"
//#define FILENAME "gen400_p0.9_75.b.txt"
//#define FILENAME "san400_0.9_1.clq.txt"
//#define FILENAME "sanr400_0.7.clq.txt"
//#define FILENAME "brock800_4.b.txt"
//#define FILENAME "r500.5.txt"
//#define FILENAME "MANN_a45.clq.b.txt" 
//#define FILENAME "keller5.clq.txt" 
 

//time_t ti; srand((unsigned) time(&ti));
//clock_t start; clock_t end;  clock_t dif;
int m=LEN+1,n=LEN+2;

char matrix[LEN+1][LEN+2];  //c[] is used to store clique vertices 

int main(){
    int i,j,k,temp, nc,incr,count, countt,deg[m], T1[m],T2[m], Ind[LEN]; // MOV : min ordered vertices
    for(i=1;i<m;i++) { T1[i]=i; deg[i]=0; for(j=1;j<n;j++) matrix[i][j]='0'; }	 //initializatin
	        
    FILE *f=fopen(FILENAME,"r");
     
    while(fscanf(f,"%d",&i)>0)
	    { fscanf(f,"%d",&j);
	      matrix[i][j]='1'; matrix[j][i]='1'; deg[i]=deg[i]+1; deg[j]=deg[j]+1;
	    }
   printf("\n.Ind set is getting computed\n");  printf(" \n degreelist:"); for(i=1;i<m;i++) printf("\t%d ", deg[i]);
 
    for(i=1;i<m;i++) T2[i]=deg[i];
   //sorting max deg first
   for(i=2;i<m;i++)
		 { temp=T2[i]; j=i-1;
           while((j>0)&&(T2[j]<temp))
		      { T1[j+1]=T1[j];T2[j+1]=T2[j]; j--;}
		   T1[j+1]=i;T2[j+1]=temp;                     
		}
   printf(" \n\n max sorted list\n\n "); for(i=1;i<m;i++) printf("\t%d ", T1[i]);
   
  incr=1;  Ind[incr++]=T1[1]; nc=1; count=2; k=1;
  while(count<m)
    { for(i=2;i<m;i++)
          { if(T1[i]>0)
		      {if(nc==incr) {Ind[incr++]=T1[i]; T1[i]=0;count++;}
		       else
			     {for(j=nc;j<incr;j++) {if(matrix[Ind[j]][T1[i]]=='1')  break; }
		          if(j==incr) {Ind[incr++]=T1[i]; T1[i]=0;count++; }//printf("\n incr=%d\t j=%d\t countt=%d\n ",incr,j,count);}
		        } 
			 }
		}
		nc=incr; k++;	 
    }
    printf(" \n\n #colors: k=%d\n\n ",k-1); //for(i=1;i<m;i++) printf("\t%d ", Ind[i]);
      
    getch();
   return 0;
   }
//..................................................................................
//................................................................
//The End........................................................................... 

