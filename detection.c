#include<stdio.h>
struct process
{
    int allocated[10];
    int request[10];
}p[20];
int np,nr;
void isSafeState(int *available)
{
    int i,j,found,work[nr],finish[np],count,safeSeq[np];
    for(i=0;i<nr;i++)
        work[i]=available[i];
    for(i=0;i<np;i++)
        finish[i]=0;
    for(count=0;count<np;count++)
    {
        found=0;
        for(i=0;i<np;i++)
        {
            if(!finish[i])
            {
                for(j=0;j<nr;j++)
                {
                    if(p[i].request[j]>work[j])
                        break;
                }
            }
            if(j==nr)
            {
                found=1;
                for(j=0;j<nr;j++)
                    work[j]+=p[i].allocated[i];
                safeSeq[count]=i;
                finish[i]=1;
                break;
            }
        }
        if(found==0)
        {
            printf("Unsafe State");
            return;
        }
    }
    printf("\nSAFE STATE\nSafe Sequence: ");
    for(i=0;i<np;i++)
        printf("P[%d] ",safeSeq[i]);

}
int main()
{
    int i,j,available[10];
    printf("Enter the no. of processes: ");
    scanf("%d",&np);
    printf("Enter the no. of resources: ");
    scanf("%d",&nr);
    for(i=0;i<np;i++)
    {
        printf("Resources allocated to P[%d]: ",i);
        for(j=0;j<nr;j++)
            scanf("%d",&p[i].allocated[j]);
        printf("Resource request by P[%d]: ",i);
        for(j=0;j<nr;j++)
            scanf("%d",&p[i].request[j]);
    }
    printf("Enter the available resources: ");
    for(i=0;i<nr;i++)
        scanf("%d",&available[i]);

    //display process info
    printf("PROCESS\tALLOCATED\tREQUEST\n");
    for(i=0;i<np;i++)
    {
        printf("P[%d]\t",i);
        for(j=0;j<nr;j++)
            printf("%d ",p[i].allocated[j]);
        printf("\t\t");
        for(j=0;j<nr;j++)
            printf("%d ",p[i].request[j]);
        printf("\n");
    }
    isSafeState(available);
    return 0;
}
