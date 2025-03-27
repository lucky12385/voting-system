#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct voter
{
    int id;
    char name[100];
    int voted;
};

struct condidate
{
    int id;
    char name[100];
    int votes;
};

void addvoter();
void registervoter();
void addcondidate();
void castvote();
void viewresults();
void removevoter();

int main(){

    int n;

    while(1){

        printf("\n---voting system---\n");

        printf("1. Add Voters:\n");
        printf("2. Register Voter:\n");
        printf("3. Add Condidate:\n");
        printf("4. Cast Voter:\n");
        printf("5. Viwe Results:\n");
        printf("6. Remove Voter:\n");
        printf("7. Exit Program:\n");

        printf("Enter Your Choise:   ");
        scanf("%d",&n);


        switch(n){

            case 1:
            addvoter();
            break;

            case 2:
            registervoter();
            break;

            case 3:
            addcondidate();
            break;

            case 4:
            castvote();
            break;

            case 5:
            viewresults();
            break;

            case 6:
            removevoter();
            break;

            case 7:
            printf("Exit Program:");
            break;

            default:
            printf("Please Viled No. You Choise:");
            break;

        }

        if(n==7){
            break;
        }
    }

    return 0;

}

void addvoter() {

    FILE *vfile = fopen("voting.txt","a");

    int n;
    printf("Enter No. Of New Voter:   ");
    scanf("%d",&n);

    struct voter v[n];

    for(int i=0;i<n;i++){

        printf("Enter Voter Id:  ");
        scanf("%d",&v[i].id);
        getchar();

        printf("Enter Voter Name:  ");
        fgets(v[i].name,sizeof(v[i].name),stdin);
        v[i].name[strcspn(v[i].name,"\n")]=0;

        printf("Enter voted:  ");
        scanf("%d",&v[i].voted);

        fprintf(vfile,"%d %s %d",v[i].id,v[i].name,v[i].voted);

    }
    fclose(vfile);
    printf("Add Voter Successfully...\n");
}

void registervoter(){

    FILE *vfile = fopen("voting.txt","a");

    struct voter v;

    printf("Enter Voter Id:\n");
    scanf("%d",&v.id);
    getchar();

    printf("Enter Voter Name:");
    fgets(v.name,sizeof(v.name),stdin);
    v.name[strcspn(v.name,"\n")]=0;

    v.voted=0;

    fprintf(vfile,"%d %s",v.id,v.name);

    fclose(vfile);


    printf("Register Voter Successfully...\n");
}

void addcondidate(){

    FILE *cfile = fopen("candidate.txt","a");

    int n;
    printf("Enter No. Of New Condidate:  ");
    scanf("%d",&n);

    struct condidate c[n];
    
    for(int i=0;i<n;i++){

        printf("Enter Condidate Id:  ");
        scanf("%d",&c[i].id);
        getchar();

        printf("Enter Condidate Name:  ");
        fgets(c[i].name,sizeof(c[i].name),stdin);
        c[i].name[strcspn(c[i].name,"\n")]=0;

        printf("Enter Condidate Votes:  ");
        scanf("%d",&c[i].votes);

        fprintf(cfile,"%d %s %d",c[i].id,c[i].name,c[i].votes);

    }

    fclose(cfile);
    printf("Add Condidate Successfully...\n");
}

void castvote(){

    FILE *vfile = fopen("voting.txt","r");
    FILE *temp =fopen("temp.txt","w");

    struct voter v;

    int n;
    printf("Enter Voter Id: ");
    scanf("%d",&n);

    int found;

    while(fscanf(vfile,"%d %s %d",&v.id,v.name,&v.voted) != EOF){

        if(v.id == n){
            found =1;

            if(v.voted == 1){

                printf("You Have Already voted:\n");
                
                fclose(vfile);
                fclose(temp);
            }

            FILE *cfile = fopen("candidate.txt","r");

            struct condidate c;

            printf("\n--Candidate--\n");

            while(fscanf(cfile,"%d %s %d",&c.id,c.name,&c.votes) != EOF){

                printf("%d %s %d\n",c.id,c.name,c.votes);
            }

            fclose(cfile);

            int a;
            printf("Enter Your Vote:  ");
            scanf("%d",&a);

            while(fscanf(cfile,"%d %s %d",&c.id,c.name,&c.votes) != EOF){

                if(c.id==a){

                    c.votes++;

                    fprintf(cfile,"%d %s %d\n",v.id,v.name,v.voted);
                    break;
                }
            }

            fclose(cfile);
            v.voted=1;
            printf("vote cast successfiully:\n");

        }

        fprintf(temp,"%d %s %d",v.id,v.name,v.voted);
    }

    fclose(vfile);
    fclose(temp);

    remove("voting.txt");
    rename("temp.txt","voting.txt");

    if(!found){

        printf("voter not fonud:\n");
    }
}

void viewresults(){

    FILE *cfile = fopen("candidate.txt", "r");
    
    struct condidate c;

    int totalvote=0;
    
    while(fscanf(cfile,"%d %s %d",&c.id,c.name,&c.votes) != EOF){

        printf("%d %s %d\n", c.id, c.name,c.votes);

        totalvote = totalvote + c.votes;
    }
    
    fclose(cfile);
    
    printf("Total Votes: %d\n", totalvote);
    printf("View Results Successfully...\n");
}


void removevoter(){


        char r[200];

        int found = 0;
        printf("Enter Voter ID to delete: ");
        scanf("%s", r);

        FILE *file = fopen("voting.txt", "r");
        FILE *temp = fopen("temp.txt", "w");

        struct voter v;

        char id[200];
        char voted[200];

        while(fscanf(file,"%s%s%s",id,v.name,voted) !=EOF) {
            if(strcmp(id,r) == 0) {
                found = 1;
                printf("Voter removed successfully!\n");
            }else{
            
            fprintf(temp,"%s %s %s\n",id,v.name,voted);
            }
        }
        fclose(file);
        fclose(temp);

        remove("voting.txt");
        rename("temp.txt", "voting.txt");

        if(!found) {
            printf("Voter ID not found!\n");
        }

    printf("Remove Voter Successfully...\n");

}