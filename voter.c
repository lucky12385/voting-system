#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct voter
{
    int id;
    char name[100];
    int voted;
};

int main(){

    FILE *vfile = fopen("voting.txt","w");

    printf("\n -----voter ditles-----\n");

    int n;
    printf("entr no. of voter:  ");
    scanf("%d",&n);

    struct voter v[n];

    for(int i=0;i<n;i++){

        printf("enter voter id:   ");
        scanf("%d",&v[i].id);
        getchar();

        printf("enter voter name:  ");
        fgets(v[i].name,sizeof(v[i].name),stdin);
        v[i].name[strcspn(v[i].name,"\n")]=0;

        printf("enter voter votes:  ");
        scanf("%d",&v[i].voted);

    }

    for(int i=0;i<n;i++){

        fprintf(vfile,"%d %s %d\n",v[i].id,v[i].name,v[i].voted);

    }

    fclose(vfile);

    printf("voter ditles successfully:");

    return 0;
}

