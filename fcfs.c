#include<stdio.h>
struct process
{
    int pid;
    int arrival;
    int burst;
    int wait;
    int turn;
    int completion;
};
void calculate_time(struct process *p,int n)
{
    int current_time=p[0].arrival,i;
    for(i=0;i<n;i++)
    {
        if(current_time<p[i].arrival)
            current_time=p[i].arrival;
        current_time+=p[i].burst;
        p[i].completion=current_time;
        p[i].turn=p[i].completion-p[i].arrival;
        p[i].wait=p[i].turn-p[i].burst;
    }
}
void gantt(struct process* p,int n)
{
    int i,j;
    printf("\nGANTT CHART\n---------------\n\n");
    printf("+");
    for(j=0;j<p[n-1].completion;j++)
        printf("--");
    printf("+");

    printf("\n");

    printf("|");

    for(i=0;i<n;i++)
    {
        for(j=0;j<p[i].burst-1;j++)
            printf(" ");
        printf("P%d",p[i].pid);
        for(j=0;j<p[i].burst-1;j++)
            printf(" ");
        printf("|");
    }
    printf("\n+");
    for(j=0;j<p[n-1].completion;j++)
        printf("--");
    printf("+");

    printf("\n0");

    for(i=0;i<n;i++)
    {
        for(j=0;j<p[i].burst;j++)
            printf("  ");
        printf("%d",p[i].completion);
    }
}
void main()
{
    int n,i,j;
    printf("Enter the number of processes:");
    scanf("%d",&n);
    struct process p[n],temp;
    //reading all the n processes
    for(i=0;i<n;i++)
    {
        printf("Process Id:");
        scanf("%d",&p[i].pid);
        printf("Arrival Time:");
        scanf("%d",&p[i].arrival);
        printf("Burst Time:");
        scanf("%d",&p[i].burst);
        printf("\n");
    }
    //sorting the process based on their arrival time
    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].arrival>p[j].arrival)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    //calculating times
    calculate_time(p,n);
    //displaying the processes in tabular form
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting");
    for(i=0;i<n;i++)
    {
       printf("\n%d\t%d\t%d\t%d\t\t%d\t\t%d",p[i].pid,p[i].arrival,p[i].burst,p[i].completion,p[i].turn,p[i].wait);
    }
    //gantt chart
    gantt(p,n);
    //avg waiting and turnaround time
    int totwait=0,totturn=0;
    for(i=0;i<n;i++)
    {
        totwait+=p[i].wait;
        totturn+=p[i].turn;
    }
    float avgwait=(totwait+0.0)/n;
    float avgturn=(totturn+0.0)/n;

    printf("\nAverage Waiting Time:%.2f",avgwait);
    printf("\nAverage Turnaround Time:%.2f",avgturn);
}
