#include<stdio.h>
#include<stdlib.h>
typedef struct{
	int data;
	int diff;
	int visit;
}disk;

int sort(disk arr[],int curr,int n){
	int i,j,k;
	disk brr;
	for(i=0;i<n;i++){
		if(arr[i].visit==0){
            arr[i].diff=abs(curr-arr[i].data);
		}
		else{
			arr[i].diff=100000;
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n-i-1;j++){
			if(arr[j].diff>arr[j+1].diff){
				brr=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=brr;
			}
		}
	}
	arr[0].visit=1;
	return arr[0].data;
}
void shortest(disk arr[],int head,int n){
	int i,curr,k=0;
	int curr1,hmov=0,diff=0;
	int seek[n];
	curr=head;
	for(i=0;i<n;i++){
		int small=sort(arr,curr,n);
		seek[k++]=small;
		curr=small;
	}
	printf("\nSEEK SEQUENCE\n");
	for(i=0;i<k;i++){
		printf("%d\t",seek[i]);
	}
	printf("\n");
	for(int j=0;j<k;j++){
		curr1=seek[j];
		diff=abs(head-curr1);
		hmov+=diff;
		head=curr1;
	}
	printf("\nTotal head movement=%d\n",hmov);
}
void main(){
	printf("Enter the no.of requests:");
	int n;
	scanf("%d",&n);
	disk arr[n];
	printf("Enter the requests:\n");
	int i;
	for(i=0;i<n;i++){
		scanf("%d",&arr[i].data);
		arr[i].visit=0;
		arr[i].diff=0;
	}
	printf("Enter the current head position:");
	int head;
	scanf("%d",&head);
	shortest(arr,head,n);
}
