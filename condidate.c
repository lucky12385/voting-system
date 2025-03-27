#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct condidate
{
    int id;
    char name[100];
    int votes;
};

int main(){

    FILE *cfile = fopen("candidate.txt","w");

    printf("\n -----condidate ditles-----\n");

    int n;
    printf("enter no. of candidate:  ");
    scanf("%d",&n);

    struct condidate c[n];
    
    for(int i=0;i<n;i++){

        printf("enter voter id:   ");
        scanf("%d",&c[i].id);
        getchar();

        printf("enter voter name:  ");
        fgets(c[i].name,sizeof(c[i].name),stdin);
        c[i].name[strcspn(c[i].name,"\n")]=0;

        printf("enter voter votes:  ");
        scanf("%d",&c[i].votes);

    }

    for(int i=0;i<n;i++){

        fprintf(cfile,"%d %s %d\n",c[i].id,c[i].name,c[i].votes);
        
    }

    fclose(cfile);

    printf("condidate ditles successfully:");
}