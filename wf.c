#include<stdio.h>
struct block
{
    int id;
    int size;
    int alloc;
};

#define MAX 30

void display(struct block *p,int pn)
{
    int i;
    printf("\n========================================\n");
    printf("ProcessID\tSize\tBlock No.");
    printf("\n========================================\n");
    for(i=0;i<pn;i++)
    {
        printf("\n\t%d\t%d\t%d",i+1,p[i].size,p[i].alloc);
    }
}

void desc(struct block* m,int mn)
{
    int i,j;
    struct block temp;
    for(i=0;i<mn;i++)
    {
        for(j=0;j<mn-i-1;j++)
        {
            if(m[j].size<m[j+1].size)
            {
                temp=m[j];
                m[j]=m[j+1];
                m[j+1]=temp;
            }
        }
    }
}
void worstfit(struct block *p,int pn,struct block *m,int mn)
{
    int i,j;
    for(i=0;i<pn;i++)
    {
        desc(m,mn);
        for(j=0;j<mn;j++)
        {
            if(p[i].size<=m[j].size)
            {
                p[i].alloc=m[j].id;
                m[j].size-=p[i].size;
                break;
            }
        }
    }
    display(p,pn);
}

void main()
{
    struct block p[MAX],m[MAX];
    int mn,pn,i,c;

    printf("Enter the number of blocks:");
    scanf("%d",&mn);
    for(i=0;i<mn;i++)
    {
        m[i].id=i+1;
        printf("Size of Block %d: ",i+1);
        scanf("%d",&m[i].size);
    }
    printf("Enter the number of processes:");
    scanf("%d",&pn);
    for(i=0;i<pn;i++)
    {
        printf("Size of Process %d: ",i+1);
        scanf("%d",&p[i].size);
        p[i].alloc=-1;
    }
    worstfit(p,pn,m,mn);

}
