#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Definir les structure des données

typedef struct {

 char nom[20];
 char prenom[20];
 char CIN[10];

}personne;

typedef struct {

 char matricule[20];
 char marque[20];
 float prix_jour;
 int dure_loc ;

}voiture;

typedef struct lc{

 int id_loc,N;
 personne client ;
 voiture voiture_loue[100];
 struct lc *next;

}location;

//Fonction d'ajouter une nouvelle location 

location *ajout_location(location *l,personne p,voiture v[],int n,int id){

     location *l1 = (location*)malloc(sizeof(location));

  l1->id_loc=id;
  l1->N=n;

  strcpy(l1->client.nom,p.nom);
  strcpy(l1->client.prenom,p.prenom);
  strcpy(l1->client.CIN,p.CIN);

  for(int i=0;i<n;i++){

     strcpy(l1->voiture_loue[i].matricule,v[i].matricule);
     strcpy(l1->voiture_loue[i].marque,v[i].marque);
     l1->voiture_loue[i].prix_jour=v[i].prix_jour;
     l1->voiture_loue[i].dure_loc=v[i].dure_loc;

  }

  if(l==NULL) {l1->next=l1 ; return (l1);}
  else {
       l1->next=l->next;
       l->next=l1;
       return(l);
  }

}


//Fonction de calcule le prix total de location

float calculer_prix_total(location *l){

     float total=0;
     for(int i=0;i<(l->N);i++){

         total=total+((l->voiture_loue[i].prix_jour)*(l->voiture_loue[i].dure_loc));

     }

     return total;
}


//Fonction d'enregistrer une location comme une facture à imprimer

void *enregistrer_location(location *l, char fichier[]){

  FILE *F=NULL;

  F=fopen(fichier, "a");
  if (F!=NULL) {

      fprintf(F,"Identificateur de la location :  %d\n\n\n",l->id_loc);
      fputs("Informations sur le client\n",F);
      fprintf(F,"CIN du client : %s\n",l->client.CIN);
      fprintf(F,"Nom du client : %s\n",l->client.nom);
      fprintf(F,"Prenom du client : %s\n\n\n",l->client.prenom);

      fputs("Informations sur les voitures louees\n\n",F);

      fputs(" Matricule de la voiture \t Marque de la voiture  \tPrix par jour  \t Duree de la location\n",F);

      for(int i=0; i<(l->N) ; i++){

        fprintf(F,"   %s\t\t\t",l->voiture_loue[i].matricule);
        fprintf(F,"     %s\t\t",l->voiture_loue[i].marque);
        fprintf(F,"  %f DH\t\t  ",l->voiture_loue[i].prix_jour);
        fprintf(F," %d Jour(s)\t\t\n",l->voiture_loue[i].dure_loc);
  }

  fprintf(F, "\nPrix total a payer par le client : %f DH\n\n\n", calculer_prix_total(l));
  printf("\n  Enregistrement fait avec succes :)\n");
  
  }
  else {   
    printf("\nimpossible d'ouvrir le fichier :(\n");
  }

  fclose(F);
}


//Fonction d'affichage les factures des locations

void *afficher_liste_locations(location *l){

   location *tmp;

   if (l!=NULL){
     
     tmp=l;
     
     if (calculer_prix_total(tmp)>0){
        do {
           printf("=======================================================================================================");
           printf("\nIdentificateur de la location :  %d\n\n\n",tmp->id_loc);
           printf("Informations sur le client\n");
           printf("CIN du client : %s\n",tmp->client.CIN);
           printf("Nom du client : %s\n",tmp->client.nom);
           printf("Prenom du client : %s\n\n\n",tmp->client.prenom);
           printf("Informations sur les voitures louees\n\n");
           printf(" Matricule de la voiture \t Marque de la voiture \tPrix par jour   \t Duree de la location\n");

           for(int i=0; i<(tmp->N) ; i++){
                 printf("    %s\t\t\t",tmp->voiture_loue[i].matricule);
                 printf("    %s\t\t",tmp->voiture_loue[i].marque);
                 printf("%f DH\t\t ",tmp->voiture_loue[i].prix_jour);
                 printf("%d jour(s)\t\t\n",tmp->voiture_loue[i].dure_loc);
           }

          printf( "\nPrix total � payer par le client : %f DH\n", calculer_prix_total(tmp));
          printf("=======================================================================================================\n\n");

          tmp=tmp->next;
      
         }while(tmp!=l);

    }else {
      printf("  \nLa liste des locations est vide\n\n");
    }
  }else {
    printf("  \nLa liste des locations est vide\n\n");
  }
}

//Fonction pour chercher une location

  location *find_location(location *l,char cin[]){

    location *tmp=l;
    if (l==NULL) 
       return NULL;
    else{
      do{
        if(strcmp(tmp->client.CIN,cin)==0) {return tmp;}
        tmp=tmp->next;
        } while(tmp!=l);
    }
   return NULL;
  }


//Supprimer une location

 void *del_location(location *l,char cin[]){

    location *tmp=find_location(l,cin);

       if(l!=NULL){

        tmp=l->next;

        l->next=tmp->next;

        if (l==tmp) {
           l=NULL;
        }

        if(calculer_prix_total(tmp)==0) {
           tmp=NULL;
        }

        free(tmp);
    }
 }

//Menu de choix :

int Menu_general(){

   int ch;
   printf("===============================================Menu general============================================\n");
   printf("+ 1. ________________________________________Ajouter Location_________________________________________+\n");
   printf("+ 2. _______________________________________Afficher Locations________________________________________+\n");
   printf("+ 3. ______________________________________Rechercher Location________________________________________+\n");
   printf("+ 4. _______________________________________Supprimer Location________________________________________+\n");
   printf("+ 5. ______________________________________Enregistrer Location_______________________________________+\n");
   printf("+ 0. _____________________________________________Quitter_____________________________________________+\n");
   printf("=======================================================================================================\n");

   printf("\nVeuillez entrer votre choix :  ");
   fflush(stdin);
   scanf("%d",&ch);
   return (ch);

}

//Fonction principal

  int main(){

    location *l1=NULL , *tmp=NULL, *Loc_chercher;
    personne p ;
    int choix,N=1,id=1023433232;
    char cin[20],fichier[10];

    printf("\nListe Simplement chainee : Systeme de Gestion Agence de location - SGAL - Cree par Mohcine Boudenjal - FST Tanger\n\n");

   do{
        choix=Menu_general();
        switch (choix){

    case 1 :   {

                printf("========================================Informations du client=========================================\n\n");

                printf("    Nom : ") ; scanf("%s",p.nom);
                printf("    Prenom : ") ; scanf("%s",p.prenom);
                printf("    CIN : ") ; scanf("%s",p.CIN);
                printf("    combien de voiture vous voulez louer ? : "); scanf("%d",&N);



                printf("\n====================================Informations de voiture(s)=========================================\n\n");
                voiture v[N];

                for(int i=0; i<N ; i++){

                   printf("    Matricule de la voiture(10 symboles) %d: ",i+1);scanf("%s",v[i].matricule);
                   printf("    Marque de la voiture (sans espace) %d: ",i+1) ; scanf("%s",v[i].marque);
                   printf("    Prix/jour de la voiture %d: ",i+1) ; scanf("%f",&v[i].prix_jour);
                   printf("    Duree de location %d: ",i+1) ; scanf("%d",&v[i].dure_loc);

                printf("=======================================================================================================\n");
                }
                printf("\n\nl'ajoute est termine avec succes\n\n");
                l1=ajout_location(l1,p,v,N,id);
                id--;
                break;
                }

   case 2 :    {

                 afficher_liste_locations(l1);
                 break;
                }

   case 3 :     {
                printf(" \nEntrer le CIN du client que vous voulez : ");
                scanf("%s",cin);
                printf("=======================================================================================================\n");
                Loc_chercher=find_location(l1,cin);


                if (Loc_chercher==NULL) {
                printf("\n  le client avec CIN : %s n'existe pas dans la liste des locations !!!!\n\n",cin);

                }else{
                  if(calculer_prix_total(Loc_chercher)!=0){
                printf("\nvoila les information du client que vous voulez !!! \n\n") ;
                printf("=======================================================================================================");

                printf("\nIdentificateur de la location :  %d\n\n\n",Loc_chercher->id_loc);
                printf("Informations sur le client\n");

                printf("CIN du client : %s\n",Loc_chercher->client.CIN);
                printf("Nom du client : %s\n",Loc_chercher->client.nom);
                printf("Prenom du client : %s\n\n\n",Loc_chercher->client.prenom);

                printf("Informations sur les voitures louees\n\n");

                printf(" Matricule de la voiture \t Marque de la voiture \tPrix par jour   \t Duree de la location\n");

                for(int i=0; i<(Loc_chercher->N) ; i++){

                 printf("    %s\t\t\t",Loc_chercher->voiture_loue[i].matricule);
                 printf("    %s\t\t",Loc_chercher->voiture_loue[i].marque);
                 printf("%f DH\t\t ",Loc_chercher->voiture_loue[i].prix_jour);
                 printf("%d jour(s)\t\t\n",Loc_chercher->voiture_loue[i].dure_loc);
                }

                printf( "\nPrix total � payer par le client : %f DH\n", calculer_prix_total(Loc_chercher));

                printf("=======================================================================================================\n\n");
                }else{  printf("\n  le client avec CIN : %s n'existe pas dans la liste des locations !!!!\n\n",cin);
                }}
                break;

               }

  case 4 :     {

                printf("Entrer le CIN du client que vous voulez supprimer : ");
                scanf("%s",cin);
                tmp=find_location(l1,cin);
                printf("=======================================================================================================\n");
                if (tmp==NULL){
                printf(" \nle client n'existe pas dans la liste des locations \n\n");
                }
                else {
                   del_location(l1,cin);
                   printf("\nla suppression faite avec succes \n\n");
                }
                break;
                }
  case 5 :     {
               printf("\n  Saisie le CIN du client que vous voulez enregistrer : ");
               scanf("%s",cin);
               tmp=find_location(l1,cin);
               if(tmp!=NULL){
               printf("\n  Entrer un nom pour le fichier : ");
               scanf("%s", fichier);
               enregistrer_location(tmp,fichier);
               }else{ printf("\n  le client n'existe pas dans la liste des locations\n");
               }
               break;
               }

  case 0 :     {
               break;  
               }

  default :    {

               printf("\nVerifier votre choix !!! \n");
               break;
               }

     }

   }while(choix!=0);

    return 0;
}

