// Compute subset sums for all possible cardinalities
#include <stdio.h>
#include <stdlib.h>

//function that reads the input
void readInput(int* n,int* m,int** S,int** C)
{
    // Loads all input and allocates space
    int i;

    scanf("%d",n);
    scanf("%d",m);

    *S=(int*) malloc((*n+1)*sizeof(int));
    *C=calloc((*m+1)*(*n+1), sizeof(int));
    if (!(*S) || !(*C))
    {
        printf("malloc failed %d\n",__LINE__);
        exit(0);
    }

    (*S)[0]=0;                // Sentinel zero
    for (i=1;i<=*n;i++)
        scanf("%d",*S+i);
}

//function that calculates subsetSum
void subsetSum(int n,int m,int* S,int* C)
{
    int i,j,potentialSum,leftover, cardinality;


    //setting n+1 fail bits for the 0
    for(j = 1; j <= m; j++)
    {
        *(C + ((0) * (m+1)) + j) = n+1; 
    }

    //considering each cardinality,
    // For each potential sum, determine the smallest index such
    // that its input value is in a subset to achieve that sum.
    for(cardinality = 1; cardinality <=n; cardinality++)
    {
        for (potentialSum=0; potentialSum<=m; potentialSum++)
        {
            for (i=1;i<=n;i++)
            {
                leftover=potentialSum-S[i];      
                if (leftover>=0 && (*(C + ((cardinality-1) * (m+1) + (leftover))) < i))
                {
                    break;   
                }                                        
            }
            *(C + (cardinality * (m+1)) + (potentialSum)) = i; 
        }
    }
}

//writing outputs
void writeOutput(int n,int m,int* S,int* C)
{
    int i, cardinality; 
    //printing out what m is 
    printf("m is %d\n", m); 

    // Output the input set
    printf("  i   S\n");
    printf("---------\n");
    for (i=0;i<=n;i++)
        printf("%3d %3d\n",i,S[i]);

    // Output the DP table
    printf("   i   card  C\n");
    printf("-----------------\n");
    for(i = 0; i <= m; i++)
    {
        for(cardinality = 1; cardinality <= n; cardinality++)
        {
            printf("%4d %4d %4d\n", i, cardinality,*(C + (cardinality * (m+1)) + i));
        }
    }

    int j; 
    // Output the backtrace
    for(j = 1; j <= n; j++)
    {
        if (*(C + (j * (m+1)) + m)==n+1)
        {
            printf("No solution for %d elements\n", j);
        }
        else
        {
            printf("Solution with %d elements\n", j);
            printf("  i   S\n");
            printf("---------\n");

            int k = j; 
            
            //utilzing multiple initialization for loop running through the 2D array in an efficient manner. 
            for (i=m, k = j; (i>0) || (k>0); (i-=S[(*(C + (k * (m+1)) + i))]), k--)
            {
                printf("%3d %3d \n",(*(C + (k * (m+1)) + i)), S[(*(C + (k * (m+1)) + i))]);
            }
        }
    }
}

int main(void)
{
    int n;    // Size of input set
    int m;    // Target value
    int *S;   // Input set
    int *C;   // Cost table

    readInput(&n,&m,&S,&C);

    subsetSum(n,m,S,C);

    writeOutput(n,m,S,C);

    //freeing memory
    free(S);
    free(C);
    
    return 0; 
}
