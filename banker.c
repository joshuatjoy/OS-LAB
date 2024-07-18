#include<stdio.h>
struct process
{
    int max[10];
    int allocated[10];
    int need[10];
}p[20];
int np,nr;

void isSafeState(int *available)
{
    int i,j,count=0,found,work[nr],finish[np],safeSeq[np];

    //initialize work and finish
    for(i=0;i<nr;i++)
    {
        work[i]=available[i];
    }

    for(i=0;i<np;i++)
    {
        finish[i]=0;
    }
    for(count=0;count<np;count++)
    {
        found=0;
        for(i=0;i<np;i++)
        {
            if(!finish[i])
            {
                for(j=0;j<nr;j++)
                {
                    if(p[i].need[j]>work[j])
                        break;
                }
                if(j==nr)
                {
                    found=1;
                    finish[i]=1;
                    safeSeq[count]=i;
                    for(j=0;j<nr;j++)
                        work[j]+=p[i].allocated[j];
                    break;
                }
            }   
        }
        if(found==0)
        {
            printf("Unsafe State!\n");
            return;
        }
    }
    printf("SAFE STATE\nSafe Sequence: ");
    for(i=0;i<np;i++)
        printf("P[%d] ",safeSeq[i]);

}
int main()
{
    int i,j,available[10],availablecp[10],newid,request[10];
    printf("Enter the number of processes: ");
    scanf("%d",&np);
    printf("Enter the no. of resources: ");
    scanf("%d",&nr);

    //info about each process
    for(i=0;i<np;i++)
    {
        printf("Max need for P[%d]: ",i);
        for(j=0;j<nr;j++)
            scanf("%d",&p[i].max[j]);
        printf("No. of Resources allocated for P[%d]: ",i);
        for(j=0;j<nr;j++)
            scanf("%d",&p[i].allocated[j]);
        for(j=0;j<nr;j++)
            p[i].need[j]=p[i].max[j]-p[i].allocated[j];
    }

    printf("No.of available resources: ");
    for(i=0;i<nr;i++)
    {
        scanf("%d",&available[i]);
        availablecp[i]=available[i];
    }

    //print info about each process
    printf("\nProcess\tMAX\tALLOCATED\tNEED\n");
    for(i=0;i<np;i++)
    {
        printf("P[%d]\t",i);
        for(j=0;j<nr;j++)
            printf("%d ",p[i].max[j]);
        printf("\t");
        for(j=0;j<nr;j++)
            printf("%d ",p[i].allocated[j]);
        printf("\t\t");
        for(j=0;j<nr;j++)
            printf("%d ",p[i].need[j]);
        printf("\n");
    }

    isSafeState(available);

    printf("\nNEW REQUEST!");
    printf("Enter the process ID: ");
    scanf("%d",&newid);
    printf("P[%d] request: ",newid);
    for(i=0;i<nr;i++)
        scanf("%d",&request[i]);
    for(i=0;i<nr;i++)
    {
        if(request[i]>p[newid].need[i])
        {
            printf("Request exceeds the max need of the process");
            break;
        }
        available[i]-=request[i];
        p[newid].need[i]-=request[i];
        p[newid].allocated[i]+=request[i];
      
    }
    isSafeState(available);
    return 0;
}
