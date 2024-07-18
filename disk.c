#include<stdio.h>
#include<stdlib.h>
int size;
void fcfs(int req[],int n,int head_pos)
{
    printf("\nFCFS");
    int tot_head_mov=0,i,order[n];
    for(i=0;i<n;i++)
    {
        order[i]=req[i];
        tot_head_mov+=abs(req[i]-head_pos);
        head_pos=req[i];
    }
    printf("\nSeek Sequence: ");
    for(i=0;i<n;i++)
        printf("%d ",order[i]);
    printf("\nTotal Head Movement: %d",tot_head_mov);
}
void scan(int req[],int n,int head_pos)
{
    printf("\nSCAN");
    int tot_head_mov=0,i,j,order[n],temp,move,index,k=0;
    
    //sorting the requests
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(req[j]>req[j+1])
            {
                temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
    
    printf("\nSorted Requests: ");
    for(i=0;i<n;i++)
        printf("%d ",req[i]);
    
    printf("Enter 1 to move to higher end and 0 to move to lower end: ");
    scanf("%d",&move);
    if(move==1)
    {
        //finding the starting index
        for(i=0;i<n;i++)
        {
            if(head_pos<=req[i])//the smallest req thats greater than or equal to initial head position
            {
                index=i;
                break;
            }
        }
        //move upward
        for(i=index;i<n;i++)
        {
            tot_head_mov+=abs(req[i]-head_pos);
            order[k]=req[i];
            k++;
            head_pos=req[i];
        }
        //move to upper end
        tot_head_mov+=abs(size-1-head_pos);
        head_pos=size-1;
        //move reverse
        for(i=index-1;i>=0;i--)
        {
            tot_head_mov+=abs(req[i]-head_pos);
            order[k]=req[i];
            k++;
            head_pos=req[i];
        }
        
    }
    if(move==0)
    {
        //finding the starting index
        for(i=n-1;i>=0;i--)
        {
            if(head_pos>=req[i])//the largets req thats smaller than or equal to initial head position
            {
                index=i;
                break;
            }
        }
        //move downward
        for(i=index;i>=0;i--)
        {
            tot_head_mov+=abs(req[i]-head_pos);
            order[k]=req[i];
            k++;
            head_pos=req[i];
        }
        //move to lower end
        tot_head_mov+=req[0];
        head_pos=0;
        //move reverse
        for(i=index+1;i<n;i++)
        {
            tot_head_mov+=abs(req[i]-head_pos);
            order[k]=req[i];
            k++;
            head_pos=req[i];
        }
    }
    printf("\nSeek Sequence: ");
    for(i=0;i<k;i++)
        printf("%d ",order[i]);
    printf("\nTotal Head Movement: %d",tot_head_mov);
}
void cscan(int req[],int n,int head_pos)
{
    printf("\nCSCAN");
    int tot_head_mov=0,i,j,order[n],temp,move,index,k=0;
    
    //sorting the requests
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(req[j]>req[j+1])
            {
                temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
    
    printf("\nSorted Requests: ");
    for(i=0;i<n;i++)
        printf("%d ",req[i]);
    
    printf("Enter 1 to move to higher end and 0 to move to lower end: ");
    scanf("%d",&move);
    if(move==1)
    {
        //finding the starting index
        for(i=0;i<n;i++)
        {
            if(head_pos<=req[i])//the smallest req thats greater than or equal to initial head position
            {
                index=i;
                break;
            }
        }
        //move upward
        for(i=index;i<n;i++)
        {
            tot_head_mov+=abs(req[i]-head_pos);
            order[k]=req[i];
            k++;
            head_pos=req[i];
        }
        //move to upper end
        tot_head_mov+=abs(size-1-head_pos);
        head_pos=size-1;
        //movetolowerend
        tot_head_mov+=size-1;
        head_pos=0;
        //move until index-1
        for(i=0;i<index;i++)
        {
            tot_head_mov+=abs(req[i]-head_pos);
            order[k]=req[i];
            k++;
            head_pos=req[i];
        }
        
    }
    if(move==0)
    {
        //finding the starting index
        for(i=n-1;i>=0;i--)
        {
            if(head_pos>=req[i])//the largets req thats smaller than or equal to initial head position
            {
                index=i;
                break;
            }
        }
        //move left
        for(i=index;i>=0;i--)
        {
            tot_head_mov+=abs(req[i]-head_pos);
            order[k]=req[i];
            k++;
            head_pos=req[i];
        }
        //move to lower end
        tot_head_mov+=req[0];
        head_pos=0;
        //move to upper end
        tot_head_mov+=size-1;
        head_pos=size-1;
        //move until index+1
        for(i=n-1;i>index;i--)
        {
            tot_head_mov+=abs(req[i]-head_pos);
            order[k]=req[i];
            k++;
            head_pos=req[i];
        }
    }
    printf("\nSeek Sequence: ");
    for(i=0;i<k;i++)
        printf("%d ",order[i]);
    printf("\nTotal Head Movement: %d",tot_head_mov);
}
void main()
{
    int i,n,temp[100],req[100],c=1,choice,head_pos;
    printf("Enter total disk size: ");
    scanf("%d",&size);
    printf("No.of requests: ");
    scanf("%d",&n);
    printf("Enter the request sequence: ");
    for(i=0;i<n;i++)
        scanf("%d",&temp[i]);
    printf("Enter the initial head position: ");
    scanf("%d",&head_pos);
    while(c)
    {
        for(i=0;i<n;i++)
            req[i]=temp[i];
        printf("\nChoose a scheduling algorithm:\n1.FCFS\n2.SCAN\n3.C-SCAN\n0.Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            
            case 1:
                fcfs(req,n,head_pos);
                break;
            case 2:
                scan(req,n,head_pos);
                break;
            case 3:
                cscan(req,n,head_pos);
                break;
            case 0:
                c=0;
                break;
        }
    }
}
