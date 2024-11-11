#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h> 
#include<windows.h>
#include <locale.h> 
#include <time.h>


//fonction temp : 
void tim_function(){
    time_t t ; 
    struct tm *tm_info ; 
    time(&t) ; 
    tm_info = localtime(&t) ; 

    // afichage du temp ==> heur et date : 
    printf("Heur : %02d : %02d : %02d \n",tm_info->tm_hour , tm_info->tm_min , tm_info->tm_sec); 
    printf("data d'ajourduit : %02d / %02d / %04d \n",tm_info->tm_mday , tm_info->tm_mon +1 ,tm_info->tm_year +1900) ; 
    
    
}


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



    typedef struct {
        int jour ;
        int mois;
        int anne;
    }date;

    typedef struct{
    int idclient;
    char CIN[20];
    char nom[20];
    char prenom[20];
    char adress[100] ; 
    char phone[20];
    date d;
    char lieudenaissa[20];
    float sold_total ; 
    } client;

    //fonction position : 
    


    #define tail_char 20 


    FILE *fichies_historique ; 
    FILE *fichie_client ; 
    FILE *fichies_supresion ; 

    //==> fonction qui fait afichage d'historique : 
void affichage_data_client(){
        fichie_client = fopen("client.txt " , "rt+"); 
        if(fichie_client == NULL){
            printf("problemme dans fichies \n"); 
            exit(1); 
        }
        char nom_client [20] ; 
        int id_client ; 
        client data_clinet ; 
        printf("cette permet d'aficher les donnes du client : \n ");
        printf("entrer le nnom du client : "); scanf("%s",nom_client); 
        printf("entrer id client : "); scanf("%d",&id_client);
        // ==> lecture des donnes dans fichies client : 
        while (!feof(fichie_client))
        {
            fscanf(fichie_client , "%-10d | %-10s | %-10s | %02d/%02d/%04d     | %-17s | %-8s | %-30s | +212 %-10s | %-7d | %-15d\n",
                &data_clinet.idclient ,
                data_clinet.nom ,
                data_clinet.prenom ,
                data_clinet.adress ,
                &data_clinet.sold_total
            ) ; 
            if(strcmp(data_clinet.nom, nom_client) == 0 && data_clinet.idclient == id_client){
                // afichage des donnes de client : 

            }
            else{
                printf("le client n'exite pas \n"); 
            }
        }
        
}

    // ==> fonction afichage des historique : 
void Afichage_historique_client(){
        printf("afichage historique");
        /*
            dans afichage des historique : 
            on fait afichage des operation ==> requit et depot 
            * sold de chaque operation 
            *date de chaque operation 

        */
}







    //==> fonction supresion de client ==> fermeture de compt : 
void Supresion_compt() {
    fichie_client = fopen("client.txt", "rt");
    if (fichie_client == NULL) {
        printf("Problème d'ouverture de fichier.\n");
        exit(1);
    }

    char nom_client[tail_char];
    int id_client;
    client data_client;
    printf("Entrer le nom du client : ");
    scanf("%s", nom_client);
    printf("Entrer l'id du client : ");
    scanf("%d", &id_client);

    // Ouvrir le fichier de suppression en mode écriture
    fichies_supresion = fopen("client_nv.txt", "wt");
    if (fichies_supresion == NULL) {
        printf("Problème d'ouverture de fichier.\n");
        fclose(fichie_client); // Ferme le fichier ouvert
        exit(1);
    }

    int client_found = 0; // Flag pour savoir si le client a été trouvé
    while (fscanf(fichie_client, "%-10d | %-10s | %-10s | %02d/%02d/%04d     | %-17s | %-8s | %-30s | +212 %-10s | %-7d | %-15d\n",
                  &data_client.idclient, data_client.nom,
                  data_client.prenom, data_client.adress,
                  &data_client.sold_total) != EOF) {
        if (strcmp(data_client.nom, nom_client) != 0 || data_client.idclient != id_client) {
            fprintf(fichies_supresion, "%d\n%s\n%s\n%s\n%f\n",
                    data_client.idclient, data_client.nom,
                    data_client.prenom, data_client.adress,
                    data_client.sold_total);
        } else {
            client_found = 1; // Client trouvé
        }
    }

    fclose(fichie_client);
    fclose(fichies_supresion);

    if (client_found) {
        printf("La fermeture de compte s'est effectuée avec succès.\n");
    } else {
        printf("Le client n'existe pas.\n");
    }
}





    void Data_base(){
        int choix =0  ; 
        
        do
        {
            printf("\n") ; 
            printf("\t\t------ MENUE ------ \n") ;
            printf("\t\t 1_afichage_historique du client \n") ; 
            printf("\t\t 2_affichage_information du clinet \n") ; 
            printf("\n") ; 
            printf("**** Entrer votre choix : \n"); 
            scanf("%d",&choix) ; 
            switch (choix)
            {
            case 1:
                // rapelle au fonction qui affiche l'historique : 
                Afichage_historique_client();
                break;
            case 2 : 
                
                // rapelle du fonction qui affiche compt : 
                affichage_data_client();
                break;
            default:
                printf("se service est n'existe pas (EREUR_SYSTEME) \n") ; 
                break;
            }




        } while (choix != 3);
        
        
    
        

}

    // fonction supresion : 
    void Supresion_data(){
        int choix = 0 ; 
        do
        {
            
            printf("\t\tSERVEC  \n") ; 
            printf("\t\t suprimer_compt(fermeture de compt )\n") ; 
            printf("\t\t suprimer_historique_compt \n") ; 
            printf("Entrer votre choix : ") ; scanf("%d",&choix) ; 
            switch (choix)
            {
            case 1:
                // rapelle au fonction qui suprimer le compt : 
                Supresion_compt() ; 
                break;
            case 2 : 
                // rapelle au fonction  qui suprimer l'historique : 
                printf("helow wold") ; 
                break;
            
            default:
                printf("se service n'existe pas \n") ; 
                break;
            }
        } while (choix != 3);
        
}

    // ==> fonction menu aplication : 
    void FONCTION_PRINCIPALE(){
        int x = 30 ; 
        int y = 2 ; 
        int choix = 0  ; 

        printf("\n\n") ; 
        gotoxy(x,y++) ; 
        printf("\t\t▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓SERVICE▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓ \n") ; 
        gotoxy(x,y++) ; 
        printf("\t\t▓▓▓▓▓▓▓▓▓▓▓1_afichage_data \n") ; 

        gotoxy(x,y++) ; 
        printf("\t\t▓▓▓▓▓▓▓▓▓▓▓2_Supresion_data \n") ; 
        printf("\n") ; 
        printf("\n\n") ; 
        gotoxy(x++ , y++) ; 
        printf("\t\t▓▓▓▓▓▓▓▓▓▓▓ entrer votre choix de service : "); printf("\t") ; scanf("%d",&choix) ; 
        switch (choix)
        {
        case 1 :
            // rappele fonction d'afichage :
            system("cls") ; 
            Data_base() ;
            break;
        case 2 : 
            // rappelle au fonction supresion : 
            system("cls") ; 
            Supresion_data() ; 
            break ; 

        
        default:
            printf("se service n'existe pas \t") ; 
            break;
        }
    

}





int main(){

    // ==> test des fonction : 
    setlocale(LC_ALL, "fr_FR.UTF-8");  
    SetConsoleOutputCP(65001);
    system("color 0A") ; 
    FONCTION_PRINCIPALE() ; 

    return 0 ; 
}





