#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct compte {
    int num;
    char nom[50];
    float solde;
    struct compte *suivant;
}compte;

compte *debut=NULL;

void ajt_Compte (compte **debut ){
	printf("---------------------------------------\n");
    compte *ne=(compte*)malloc(sizeof(compte));
    if(ne==NULL){
    printf("Allocation error\n");
    return;
	}
        printf("Enter account number: ");
        scanf("%d",&ne->num);
        getchar();
        printf("Enter account holder name: ");
        fgets(ne->nom,sizeof(ne->nom),stdin);
        ne->nom[strcspn(ne->nom, "\n")] = '\0';
        printf("Enter account balance: ");
        scanf("%f",&ne->solde);
    ne->suivant=NULL;

    if (*debut==NULL){               
        *debut=ne;
        printf("---------------------------------------\n");
        return;
    }
    compte *temp=*debut;
    while (temp->suivant!=NULL){
        temp=temp->suivant;
    }
    temp->suivant=ne;
    printf("---------------------------------------\n");
}

void afficheCompte(compte *debut){
	printf("---------------------------------------\n");
    if(debut==NULL){
        printf("The list is empty\n");
        printf("---------------------------------------\n");
        return;
    }
    compte *temp=debut;
    while(temp!=NULL){
        printf("Account number: %d\nAccount holder: %s\nBalance: %0.2f\n",temp->num,temp->nom,temp->solde);
        printf("---------------------------------------\n");
        temp=temp->suivant;
    }
    printf("END\n");
    printf("---------------------------------------\n");
}

void rechercheCompte (int n){
    
    compte *temp=debut;
        while(temp!=NULL){
            if(n==temp->num){
            printf("---------------------------------------\n");
            printf("Account number: %d\nAccount holder: %s\nBalance: %0.2f\n",temp->num,temp->nom,temp->solde);
            printf("---------------------------------------\n");
            return;
            }
            temp=temp->suivant;
        }
    printf("Account not found.\n");
}

void suprimerCompte (int n){
    if(debut==NULL){
        printf("The list is empty\n");
        return;
    }
    compte *temp=debut;
    if (temp->num == n) {
        debut = temp->suivant;
        free(temp);
        printf("Account deleted.\n");
        return;
    }
        while(temp->suivant!=NULL){
            if(n==temp->suivant->num){
                compte *sup=temp->suivant;
                temp->suivant=sup->suivant;
                free(sup);
                printf("Account deleted.\n");
                return;
            }
            temp=temp->suivant;
        }
    printf("Account not found.\n");
}

int effectuerTransaction(int type, float montant, int num) { // solution to avoid the case where the user enters a non-existent account
    compte *temp = debut;

    while (temp != NULL) {
        if (temp->num == num) {
            if (type == 1) {  
                temp->solde += montant;
            } else if (type == 0) { 
                if (montant > temp->solde) {
                    printf("Transaction failed (insufficient balance).\n");
                } else {
                    temp->solde -= montant;
                }
            }
            return 1; // success: account exists
        }
        temp = temp->suivant;
    }

    return 0; // account does not exist
}

int main (){
    int sw,rech,sup,dr,num,g=0;
	float montant;
	compte *temp;
    do{
    	printf("---------------------------------------\n");
		printf("1. Add an account\n2. Display all accounts\n3. Search for an account\n4. Delete an account\n5. Perform a transaction (deposit/withdrawal)\n0. Quit\nYour choice: ");
		scanf("%d",&sw);
		printf("---------------------------------------\n");
		switch (sw){
            case 1:
                ajt_Compte(&debut);
                break;
            case 2:
                afficheCompte(debut);
                break;
            case 3:
            	if(debut==NULL){ // if the list is empty
			        printf("The list is empty\n");
			        printf("---------------------------------------\n");
			        break;
			    }
                printf("Enter account number to search: ");
                scanf("%d",&rech);
                rechercheCompte(rech);
                break;
            case 4:
            	if(debut==NULL){ // if the list is empty
			        printf("The list is empty\n");
			        printf("---------------------------------------\n");
			        break;
			    }
                printf("Enter account number to delete: ");
                scanf("%d",&sup);
                suprimerCompte(sup);
                break;
            case 5:
            	if (debut==NULL){
    				printf("The list is empty\n");
    				printf("---------------------------------------\n");
       				 break;
				}
				
            	printf("Account number: ");
               	scanf("%d",&num);
               	if (!effectuerTransaction(2, 0, num)) { // check if account exists
      			  printf("Account not found.\n");
      			  break;
    			}
                do{
                printf("---------------------------------------\n");
                printf("0. Withdrawal\n1. Deposit\n2. Quit\n=>");
                scanf("%d",&dr);            
                    switch(dr){
                        case 1:
                            printf("Enter amount: ");
                            scanf("%f",&montant);
                            effectuerTransaction(1,montant,num);
                            break;
                        case 0:
                            printf("Enter amount:\n");
                            scanf("%f",&montant);
                            effectuerTransaction(0,montant,num);
                            break;
                        case 2:
                        	printf("End of transaction\n");
                        	break;
                        default:
                            printf("error");
                            break;
                    }
                    printf("---------------------------------------\n");
                }while(dr!=2);
                break;
            case 0:
                printf("Goodbye");
                break;
            default:
                printf("error\n");
                break;
        }

    }while(sw!=0);

}
