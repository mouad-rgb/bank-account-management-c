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
    printf("Erreur d'allocation\n");
    return;
	}
        printf("donner le numero du compte :");
        scanf("%d",&ne->num);
        getchar();
        printf("donner le nom du titulaire du compte :");
        fgets(ne->nom,sizeof(ne->nom),stdin);
        ne->nom[strcspn(ne->nom, "\n")] = '\0';
        printf("donner le solde du compte :");
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
        printf("La liste est vide \n");
        printf("---------------------------------------\n");
        return;
    }
    compte *temp=debut;
    while(temp!=NULL){
        printf("Le numero du compte : %d\nLe nom du titulaire : %s\nLe Solde : %0.2f\n",temp->num,temp->nom,temp->solde);
        printf("---------------------------------------\n");
        temp=temp->suivant;
    }
    printf("FIN\n");
    printf("---------------------------------------\n");
}

void rechercheCompte (int n){
    
    compte *temp=debut;
        while(temp!=NULL){
            if(n==temp->num){
            printf("---------------------------------------\n");
            printf("Le numero du compte : %d\nLe nom du titulaire : %s\nLe Solde : %0.2f\n",temp->num,temp->nom,temp->solde);
            printf("---------------------------------------\n");
            return;
            }
            temp=temp->suivant;
        }
    printf("Le compte n'existe pas.\n");
}

void suprimerCompte (int n){
    if(debut==NULL){
        printf("La liste est vide \n");
        return;
    }
    compte *temp=debut;
    if (temp->num == n) {
        debut = temp->suivant;
        free(temp);
        printf("Compte supprime.\n");
        return;
    }
        while(temp->suivant!=NULL){
            if(n==temp->suivant->num){
                compte *sup=temp->suivant;
                temp->suivant=sup->suivant;
                free(sup);
                printf("Compte supprime.\n");
                return;
            }
            temp=temp->suivant;
        }
    printf("Le compte n'existe pas.\n");
}

int effectuerTransaction(int type, float montant, int num) {//une solution pour eviter le cas ou lutilisateur done un compte inexistant
    compte *temp = debut;

    while (temp != NULL) {
        if (temp->num == num) {
            if (type == 1) {  
                temp->solde += montant;
            } else if (type == 0) { 
                if (montant > temp->solde) {
                    printf("Transaction impossible (solde insuffisant).\n");
                } else {
                    temp->solde -= montant;
                }
            }
            return 1; //succes compte exist 
        }
        temp = temp->suivant;
    }

    return 0;  //compte nesixte pas
}

int main (){
    int sw,rech,sup,dr,num,g=0;
	float montant;
	compte *temp;
    do{
    	printf("---------------------------------------\n");
		printf("1. Ajouter un compte\n2. Afficher tous les comptes\n3. Rechercher un compte\n4. Supprimer un compte\n5. Effectuer une transaction (depot/retrait)\n0. Quitter\nVotre choix : ");
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
            	if(debut==NULL){//si la liste est vide
			        printf("La liste est vide \n");
			        printf("---------------------------------------\n");
			        break;
			    }
                printf("donner le numero du compte a chercher : ");
                scanf("%d",&rech);
                rechercheCompte(rech);
                break;
            case 4:
            	if(debut==NULL){//si la liste est vide
			        printf("La liste est vide \n");
			        printf("---------------------------------------\n");
			        break;
			    }
                printf("donner le numero du compte a supprimer :");
                scanf("%d",&sup);
                suprimerCompte(sup);
                break;
            case 5:
            	if (debut==NULL){
    				printf("La liste est vide \n");
    				printf("---------------------------------------\n");
       				 break;
				}
				
            	printf("numero du compte :");
               	scanf("%d",&num);
               	if (!effectuerTransaction(2, 0, num)) {  //test de l existance du compte
      			  printf("Le compte n'existe pas.\n");
      			  break;
    			}
                do{
                printf("---------------------------------------\n");
                printf("0.pour un retrait\n1.pour un depot\n2.pour quitter\n=>");
                scanf("%d",&dr);            
                    switch(dr){
                        case 1:
                        
                            printf("donner le montant: ");
                            scanf("%f",&montant);
                            effectuerTransaction(1,montant,num);
                            break;
                        case 0:
        
                            printf("donner le montant:\n");
                            scanf("%f",&montant);
                            effectuerTransaction(0,montant,num);
                            break;
                        case 2:
                        	printf("Fin de transaction\n");
                        	break;
                        default:
                            printf("error");
                            break;
                    }
                    printf("---------------------------------------\n");
                }while(dr!=2);
                break;
            case 0:
                printf("Au revoir");
                break;
            default:
                printf("error\n");
                break;
        }

    }while(sw!=0);

}
