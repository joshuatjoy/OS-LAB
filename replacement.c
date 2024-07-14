#include<stdio.h>

void FIFO(int* rs,int n,int* frames,int nf)
{
    int i,j,fcount=0,k=0,avail;
    printf("\nFIFO\n===============================================\n");
    printf("PageRef\t");
    for(i=0;i<nf;i++)
        printf("F%d\t",i);
    printf("Hit/Fault");
    for(i=0;i<n;i++)
    {
        avail=0;
        for(j=0;j<nf;j++)
        {
            if(rs[i]==frames[j])
            {
                avail=1;
                printf("\n%d",rs[i]);
                for(j=0;j<nf;j++)
                    printf("\t%d",frames[j]);
                printf("\tH");
                break;
            }
        }
        if(avail==0)
        {
            fcount++;
            frames[k]=rs[i];
            k=(k+1)%nf;
            printf("\n%d",rs[i]);
            for(j=0;j<nf;j++)
                printf("\t%d",frames[j]);
            printf("\tF");
        }
    }
    printf("\nPage Faults: %d\n",fcount);
}
void LRU(int* rs,int n,int* frames,int nf)
{
    int i,j,fcount=0,avail,k=0,lr[nf],x,lastused;
    printf("\nLRU\n===============================================\n");
    printf("PageRef\t");
    for(i=0;i<nf;i++)
        printf("F%d\t",i);
    printf("Hit/Fault");
    for(i=0;i<n;i++)
    {
        avail=0;
        for(j=0;j<nf;j++)
        {
            if(rs[i]==frames[j])
            {
                avail=1;
                printf("\n%d",rs[i]);
                for(j=0;j<nf;j++)
                    printf("\t%d",frames[j]);
                printf("\tH");
                break;
            }
        }
        if(avail==0)
        {
            fcount++;
            //if there are free frames i.e k<nf,k denotes the no. of full frames
            if(k<nf)
            {
                frames[k]=rs[i];
                k++;
                printf("\n%d",rs[i]);
                for(j=0;j<nf;j++)
                    printf("\t%d",frames[j]);
                printf("\tF");
            }
            else
            {
                //page replacement algorithm-find the last recently used page in the frame
                for(j=0;j<nf;j++)
                {
                    lr[j]=0;
                    for(x=i-1;x>=0;x--)
                    {
                        if(rs[x]==frames[j])
                            break;
                        lr[j]=lr[j]+1;
                    }
                }
                lastused=0;
                for(j=1;j<nf;j++)
                {
                    if(lr[j]>lr[lastused])
                        lastused=j;
                }
                frames[lastused]=rs[i];
                printf("\n%d",rs[i]);
                for(j=0;j<nf;j++)
                    printf("\t%d",frames[j]);
                printf("\tF");
            }
        }
    }
    printf("\nPage Fault: %d\n",fcount);
}
void LFU(int* rs,int n,int* frames,int nf)
{
    int i,j,fcount=0,avail,k=0,freq[nf],x,leastfreq;
    printf("\nLFU\n===============================================\n");
    printf("PageRef\t");
    for(i=0;i<nf;i++)
        printf("F%d\t",i);
    printf("Hit/Fault");
    for(i=0;i<n;i++)
    {
        avail=0;
        for(j=0;j<nf;j++)
        {
            if(frames[j]==rs[i])
            {
                avail=1;
                printf("\n%d",rs[i]);
                for(j=0;j<nf;j++)
                    printf("\t%d",frames[j]);
                printf("\tH");
                break;
            }
        }
        if(avail==0)
        {
            fcount++;
            //check for free frames
            if(k<nf)
            {
                frames[k]=rs[i];
                k++;
                printf("\n%d",rs[i]);
                for(j=0;j<nf;j++)
                    printf("\t%d",frames[j]);
                printf("\tF");
            }
            else
            {
                //replacement algorithm-replace the frame with the least frequently used page
                for(j=0;j<nf;j++)
                {
                    freq[j]=0;
                    for(x=i-1;x>=0;x--)
                    {
                        if(rs[x]==frames[j])
                            freq[j]++;
                    }
                }
                leastfreq=0;
                for(j=1;j<nf;j++)
                {
                    if(freq[j]<freq[leastfreq])
                        leastfreq=j;
                }
                frames[leastfreq]=rs[i];
                printf("\n%d",rs[i]);
                for(j=0;j<nf;j++)
                    printf("\t%d",frames[j]);
                printf("\tF");
            }
        }
    }
    printf("\nPage Faults: %d\n",fcount);
}
void main()
{
    int i,rs[30],n,frames[30],nf,choice,c=1;
    printf("Enter the no. of pages: ");
    scanf("%d",&n);
    printf("Enter the reference string: ");
    for(i=0;i<n;i++)
        scanf("%d",&rs[i]);
    printf("Enter the no. of frames:");
    scanf("%d",&nf);
    
    while(c)
    {
        for(i=0;i<nf;i++)
            frames[i]=-1;
        printf("Choose a replacement strategy:\n0.Exit\n1.FIFO\n2.LRU\n3.LFU\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                FIFO(rs,n,frames,nf);
                break;
            case 2:
                LRU(rs,n,frames,nf);
                break;
            case 3:
                LFU(rs,n,frames,nf);
                break;
            case 4:
                c=0;
                break;
        }
    }
}
