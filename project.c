#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<locale.h>
#include<time.h>
/*********************************structures ***********************************************/
typedef struct {
    int jour;
    int mois;
    int anne;
} date;
typedef struct {
    int idhistorique;
    int montant;
    date doperation;
    char *typeoperation;
}historique;
typedef struct {
int solde;
int Ncompte;
historique h;
int password;
date dcreation;
char typecompte[20];
}compte;
typedef struct {
    int idclient;
    char CIN[20];
    char nom[20];
    char prenom[20];
    char sexe;
    char adress[100];
    char phone[20];
    date d;
    compte c;
    char lieudenaissa[20];
} client;
/*************************************************fonctions****************************************************** */
void clear_screen() {
    system("cls");
}
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}
/**********************************************function de deplacement ********************************************* */
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
/**********************************************finction de horlage ***************************************************** */
void tim_function(){
    time_t t ; 
    struct tm *tm_info ; 
    time(&t) ; 
    tm_info = localtime(&t) ; 

    // afichage du temp ==> heur et date : 
    printf("Heur : %02d : %02d : %02d \n",tm_info->tm_hour , tm_info->tm_min , tm_info->tm_sec); 
    printf("data d'ajourduit : %02d / %02d / %04d \n",tm_info->tm_mday , tm_info->tm_mon +1 ,tm_info->tm_year +1900) ; 
    
    
}
/***********************************************function de box ************************************************************ */
void print_box(int width, int height) {
    
    for (int i = 0; i < width; i++) {
        printf("▓");
    }
    printf("\n");

    for (int i = 0; i < height - 2; i++) {
        printf("▓");
        for (int j = 0; j < width - 2; j++) {
            printf(" ");
        }
        printf("▓\n");
    }
    for (int i = 0; i < width; i++) {
        printf("▓");
    }
    printf("\n");
}
void secBox(char a[]){

    int i, j;

    for(i = 1; i <= 21; i++){
        if(i == 1){
            for(j = 0; j < 81; j++){
                if(j <= 30 || j >= 49){
                    printf("\xB2");
                }else{
                    printf("%c", a[j - 30]);
                }
            }
        }else if(i == 21){
             for(j = 0; j < 81; j++){
                printf("\xB2");
            }
        }else{
            for(j = 1; j <= 81; j++){
                if(j == 1 || j == 81){
                    printf("\xB2");
                }else{
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}
void delay(unsigned int x){

    int i, j;
    x *= 10000;
    for(i = 0; i <= x; i++){
        j = i;
    }
}
void loadingPage(){
    int a, i;
    clear_screen();
    gotoxy(45,7);
    puts("*********** NOW LOADING ***********");
   /* gotoxy(15, 9);
    box(50, 3, 15, 9);
    gotoxy(16,10);*/

    a= 16;
    for(i = 1; i < 50; i++){
        printf("\xB1");
        delay(100);
        gotoxy(a++, 10);
    }
}
/********************************************la premier intrface ********************************************** */
void interface1(){
    system("color 0A");
    
    // Affichage de la bordure et du texte avec gotoxy pour ajuster la position du curseur
    gotoxy(4, 9);
    printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 9)
    printf("┌────────────────────────────────────────────────────────────────────────────┐");

    gotoxy(4, 10); printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 10)
    printf("│          D  I  G  I  T  A  L           C  A  P  I  T  A  L                 │");

    gotoxy(4, 11);printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 11)
    printf("│                             B  A  N  K                                     │");

    gotoxy(4, 12);printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 12)
    printf("│                                                                            │");

    gotoxy(4, 13);printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 13)
    printf("│                       INFORMATIQUES ET SERVICES                            │");

    gotoxy(4, 14);printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 14)
    printf("│                                                                            │");

    gotoxy(4, 15);printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 15)
    printf("│ Digital Capital Bank (DCB) Une banque est une institution financière qui   │");

    gotoxy(4, 16);printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 16)
    printf("│ offre des services tels que la gestion des dépôts, l'octroi de crédits,    │");

    gotoxy(4, 17);printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 17)
    printf("│ la gestion des paiements et l'investissement des fonds...                  │");

    gotoxy(4, 18);printf("\t\t");  // Positionnement du curseur à (colonne 1, ligne 18)
    printf("└────────────────────────────────────────────────────────────────────────────┘");


    printf("\n") ; 
    printf("\n") ; 
    printf("\n") ; 
    printf("****************************************************************************************************************\n");
    printf("                                     **S O Y E Z  L A  B I E N V E N U E**\n ");
    printf("****************************************************************************************************************\n\n\n\n\n");
    printf("                                   pour plus d'information cliquez sur entrer :");
    getch();
    printf("\n") ; 
    tim_function() ; 
}
/*******************************************function de ecriture dans les fichiers ******************************** */
void ECRIRELESCLIENTS(FILE *fich, client cl) {
    fich = fopen("clients.txt", "a+");
    if (fich == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }


   fprintf(fich, "%-10d | %-10s | %-10s  | %02d/%02d/%04d  | %-17s | %-8s | %-30s | +212 %-10s |  %c   | %5d \n",
            cl.idclient, cl.nom, cl.prenom, cl.d.jour, cl.d.mois, cl.d.anne,
            cl.lieudenaissa, cl.CIN, cl.adress, cl.phone,
            cl.sexe,cl.c.Ncompte);

    fclose(fich);

}
void ECRIRELESCOMPTES(FILE *fich,compte c,client cl) {
    fich = fopen("comptes.txt", "a+");
    if (fich == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }


   fprintf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n",
            cl.c.Ncompte, cl.nom, cl.prenom, c.dcreation.jour, c.dcreation.mois, c.dcreation.anne,c.typecompte, c.solde,c.password,c.h.idhistorique);
    fclose(fich);

}
void ECRIRELESHISTORIQUE(FILE *fich,compte c) {
    fich = fopen("historique.txt", "a+");
    if (fich == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }  

   fprintf(fich, "%-12d |        %-11s      | %-12d |    %02d/%02d/%04d    | %d \n",
            c.h.idhistorique,c.h.typeoperation,c.h.montant,c.h.doperation.jour,c.h.doperation.mois,c.h.doperation.anne,c.solde);    

    fclose(fich); 
}
int getLastClientId(FILE *fich) {
    int lastId = 100000;
    int tempId;

    fich = fopen("clients.txt", "r");
    if (fich == NULL) {
        printf("Fichier non trouve.");
        return lastId;
    }

    char line[200];
    while (fgets(line, sizeof(line), fich) != NULL) {
        if (sscanf(line, "%d", &tempId) == 1) {
            if (tempId > lastId) {
                lastId = tempId;
            }
        }
    }

    fclose(fich);
    return lastId;
}
int getLastIdHistorique(FILE *fich) {
    int lastIdHis = 1;
    int tempIdHis;
    
    fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        printf("Fichier non trouve.", lastIdHis);
        return lastIdHis;
    }
    char line[200];
    while (fgets(line, sizeof(line), fich) != NULL) {
        if (sscanf(line, "%*d %*s %*s %*d/%*d/%*d %*s %*d %*d %d", &tempIdHis) == 1) {
            if (tempIdHis >= lastIdHis) {
                lastIdHis = tempIdHis + 1; 
            }
        }
    }

    fclose(fich);
    return lastIdHis;
}

void NOTIFICATION(char *std,int trv){
            system("cls");
            gotoxy(32,5);
            printf("--------------------------------------------");
            for(int i =0 ;i<5 ;i++){   
                printf("|");
            }
            printf("--------------------------------------------");
            
            gotoxy(67,10);
            printf("%s",std);
            gotoxy(32,15);
            printf("--------------------------------------------");
            for(int i =0 ;i<5 ;i++){   
                printf("|");
            }
            printf("--------------------------------------------");
            if (trv==1)
            {
                exit(0);
            }                 
}

void login() {
    int idCompt_search, password_search;
    int x = 15, y = 5;
    FILE* fich;
    system("color 0A");

    // Affichage du cadre de login
    gotoxy(x, y++);
    printf("╔══════════════════════════════════════════════════════════════════════════╗");

    gotoxy(x, y++);
    printf("║                 ******** LOGIN : *******                                 ║");

    gotoxy(x, y++);
    printf("║                                                                          ║");

    gotoxy(x, y++);
    printf("║  NUM_COMPT:                                                              ║");

    gotoxy(x, y++);
    printf("║  Mot de passe:                                                           ║");

    gotoxy(x, y++);
    printf("╚══════════════════════════════════════════════════════════════════════════╝");

    gotoxy(x, y++);
    printf("\n\n");

    tim_function(); // Fonction pour gérer le temps si nécessaire

    // Saisie des informations de connexion
    gotoxy(35, 8);  // Placer le curseur juste après "NUM_COMPT:"
    scanf("%d", &idCompt_search);

    gotoxy(32, 9);  // Placer le curseur juste après "Mot de passe:"
    scanf("%d", &password_search);

    // Authentification
    int trouver = authentification(idCompt_search, password_search);
    
    if (trouver == 1) {
        // Connexion réussie
        system("cls");
        printf("✅ CONNEXION RÉUSSIE");
        PAGEPROFIL(fich);
    } else {
        // Connexion échouée
        int choix = 0;
        system("cls");

        gotoxy(2, 5);
        printf("┌────────────────────────────────────────────────────────────────────────────────────┐");

        gotoxy(2, 6);
        printf("│                             ❌Erreur système ❌                                  │");

        gotoxy(2, 7);
        printf("└────────────────────────────────────────────────────────────────────────────────────┘");

        getch();
        system("cls");

        gotoxy(2, 5);
        printf("\t⚠️ Numéro de compte ou mot de passe incorrect ⚠️\n");
        getch();

        gotoxy(2, 5);
        printf("┌────────────────────────────────────────────────────────────────────────────┐");

        gotoxy(2, 6);
        printf("│   1_Connexion                                                             │");

        gotoxy(2, 7);
        printf("│   2_Retour                                                                │");

        gotoxy(2, 8);
        printf("│    ✰ Choix :                                                             │");

        gotoxy(2, 10);
        printf("└────────────────────────────────────────────────────────────────────────────┘");

        gotoxy(21, 8);
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                system("cls");
                login(); // Re-essayer la connexion
                break;
            case 2:
                system("cls");
                afficher_menu(); // Retourner au menu
                break;
            default:
                system("cls");
                exit(1); // Sortir en cas de mauvaise entrée
                break;
        }
    }
}

int AFFICHERSOLDE(){
    FILE *fich;
    compte c ; 
    fich = fopen("comptes.txt" , "r") ; 
    if(fich == NULL){
        printf("problemme de lire  du fichies \n") ; 
        exit(1) ; 
    }
    
    char line[200];
     fgets(line, sizeof(line), fich);
     fgets(line, sizeof(line), fich);

    while (fgets(line, sizeof(line), fich) != NULL) {
        if (sscanf(line, "%d | %*[^|] | %*[^|] | %d/%d/%d | %*[^|] | %d | %*d | %*d", 
                &c.Ncompte, &c.solde) == 2) {
                return c.solde ;
        }
    }
}
int authentification(int ncompte_saisie, int pswd_saisie) {
    FILE *fich;
    compte c;
    client cl;
    char line[200];

    fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    while (fgets(line, sizeof(line), fich) != NULL) {
        if (sscanf(line, "%d %*s %*s %*s %*s %*d %d %*d %*d", 
                   &c.Ncompte, &c.password) == 2) {
            if (c.Ncompte == ncompte_saisie && c.password == pswd_saisie) {
                fclose(fich);
                return 1; // Succès
            }
        }
    }

    fclose(fich);
    return 0; 
}

int SIGNIN(FILE* fich) {
    system("Cls");
    client c1;
    compte c;
    char choix = 'N';
    int lastId = getLastClientId(fich);
    c1.idclient = lastId + 1;
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    int x = 30, y = 2;

    do {
        gotoxy(x, y++);
        printf("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓ CREATION DE COMPTE ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");

        gotoxy(x, y++);
        printf("ATTENTION : VOUS ÊTES RESPONSABLE DE CHAQUE ERREUR DANS VOS INFORMATIONS.\n");
        getchar();
        gotoxy(x, y++);
        printf("Donner votre nom:  \t ");
        fgets(c1.nom, sizeof(c1.nom), stdin);
        remove_newline(c1.nom);
        
        gotoxy(x, y++);
        printf(" Donner votre prenom: \t");
        fgets(c1.prenom, sizeof(c1.prenom), stdin);
        remove_newline(c1.prenom);
       
        gotoxy(x, y++);
        printf(" Donner votre sexe ( Homme:H / Femme:F): \t");
        scanf("%c",&c1.sexe);
        while(getchar() != '\n');
        do {
            gotoxy(x, y++);
            printf("Donner votre date de naissance (JJ MM AAAA): ");
            scanf("%d %d %d", &c1.d.jour, &c1.d.mois, &c1.d.anne);
            while (getchar() != '\n'); 

            if (c1.d.jour > 31 || c1.d.mois > 12 || c1.d.anne < 1900 || c1.d.anne > 9999) {
                gotoxy(x,y++);
                printf("Date incorrecte ! Veuillez entrer une date valide.\n");
            }
        } while (c1.d.jour > 31 || c1.d.mois > 12 || c1.d.anne < 1900 || c1.d.anne > 9999);

        gotoxy(x, y++);
        printf("Donner votre lieu de naissance :\t");
        fgets(c1.lieudenaissa, sizeof(c1.lieudenaissa), stdin);
        remove_newline(c1.lieudenaissa);
        gotoxy(x,y++);
        printf("Donner le type de compte (professionel/individuel): \t");
        fgets(c.typecompte, sizeof(c.typecompte), stdin);
        remove_newline(c.typecompte);
        gotoxy(x, y++);
        printf("Donner votre numero de carte national (CIN): \t");
        fgets(c1.CIN, sizeof(c1.CIN), stdin);
        remove_newline(c1.CIN);
        
        gotoxy(x, y++);
        printf("Donner votre adresse : \t ");
        fgets(c1.adress, sizeof(c1.adress), stdin);
        remove_newline(c1.adress);

        do {
            gotoxy(x, y++);
            printf("Donner votre numero de telephone : +212 ");
            scanf("%9s", c1.phone);
            while (getchar() != '\n'); 

            if (strlen(c1.phone) != 9) {
                gotoxy(x,y++);
                printf("Le numero est incorrect ! Il doit contenir exactement 9 chiffres.\n");
            }
        } while (strlen(c1.phone) != 9);
        gotoxy(x, y++);
        printf("Entrer le dépôt initial: \t ");
        scanf("%d",&c.h.montant);
        while (getchar() != '\n'); 
        gotoxy(x, y++);
        printf("TU PEUX SAUVEGARDER VOTRE INFORMATIONS O/N : \n");
        gotoxy(x,y++);
        scanf(" %c", &choix);
        while (getchar() != '\n'); 
    } while (choix == 'N' || choix =='n');

    gotoxy(x, y++);
    printf("TU peux donner le numero de compte  (5 chiffres) :  ");
    scanf("%d", &c1.c.Ncompte);
    gotoxy(x,y++);
    printf("TU peux donner le mot de passe (4 chiffres) : ");
    scanf("%d", &c.password);
    system("cls");
    c.dcreation.jour=local_time->tm_mday;
    c.dcreation.mois=local_time->tm_mon+1;
    c.dcreation.anne=local_time->tm_year + 1900;
    // la partie depend de l'hiatorique 
    c.solde=c.h.montant;
    c.h.doperation.jour=local_time->tm_mday;
    c.h.doperation.mois=local_time->tm_mon+1;
    c.h.doperation.anne=local_time->tm_year + 1900;
    c.h.idhistorique=getLastIdHistorique(fich);
    c.h.typeoperation="depot";
    ECRIRELESCLIENTS(fich,c1);
    ECRIRELESCOMPTES(fich,c,c1);
    ECRIRELESHISTORIQUE(fich,c);
    gotoxy(x, y++);
    NOTIFICATION(" ✅ Ton compte a ete enregistre avec succes. ✅ ",0);
}
void LIRECLIENTS(FILE *fich) {
    clear_screen();
    fich = fopen("clients.txt", "r");
    if (fich == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }

    char line[200];
    

    fgets(line, sizeof(line), fich);
    fgets(line, sizeof(line), fich);

    printf("Liste des clients :\n");
    while (fgets(line, sizeof(line), fich) != NULL) {
        client client;
        
        if (sscanf(line, "%d | %19[^|] | %19[^|] | %d/%d/%d | %19[^|] | %9[^|] | %99[^|] | +212 %9[^|] | %c",
                   &client.idclient, client.nom, client.prenom,
                   &client.d.jour, &client.d.mois, &client.d.anne,
                   client.lieudenaissa, client.CIN, client.adress, client.phone,
                   &client.sexe) == 11) { 
            printf("Nom: %s \n Prenom: %s \n Date de naissance: %d/%d/%d \n Lieu de naissance: %s \n CIN: %s \n Address: %s \n Phone: +212 %s \n Sexe: %c\n",
                   client.nom, client.prenom, 
                   client.d.jour, client.d.mois, client.d.anne,
                   client.lieudenaissa, client.CIN, client.adress, client.phone,
                   client.sexe);
        } else {
            printf("Erreur de lecture pour la ligne : %s\n", line);
        }
    }

    fclose(fich);
}

void LIRECOMPTES(FILE *fich) {
    fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }

    char line[200];

    // Ignore les deux premières lignes (header et séparation)
    fgets(line, sizeof(line), fich);
    fgets(line, sizeof(line), fich);

    printf("Liste des comptes :\n");
    while (fgets(line, sizeof(line), fich) != NULL) {
        compte c;
        client cl;  // Nom et prénom lus temporairement

        // Lecture et validation des champs
        if (sscanf(
                line,
                "%llu | %19[^|] | %19[^|] | %d/%d/%d | %19[^|] | %d | %d | %d",
                &c.Ncompte,cl.nom,cl.prenom,&c.dcreation.jour,
                &c.dcreation.mois,&c.dcreation.anne,c.typecompte,
                &c.solde,&c.password,&c.h.idhistorique
            ) == 10) {
            
            // Affichage des informations du compte
            printf("Compte : %d\n", c.Ncompte);
            printf("Nom : %s\n", cl.nom);
            printf("Prénom : %s\n", cl.prenom);
            printf("Date de création : %02d/%02d/%04d\n", c.dcreation.jour, c.dcreation.mois, c.dcreation.anne);
            printf("Type de compte : %s\n", c.typecompte);
            printf("Solde : %d\n", c.solde);
            printf("Password : %d\n", c.password);
            printf("ID Historique : %d\n", c.h.idhistorique);
            printf("--------------------------\n");
        } else {
            printf("Erreur : impossible de lire la ligne suivante :\n%s\n", line);
        }
    }

    fclose(fich);
}
void AFFICHERHSITORIQUE(compte c){
  FILE*fich;
  fich = fopen("historique.txt", "r");
    if (fich == NULL) {
        perror("erreur de lire de fichier");
        exit(1);
    }

    char line[200]; 
    fgets(line, sizeof(line), fich)   ;
    fgets(line, sizeof(line), fich);    
    while (fgets(line, sizeof(line), fich) != NULL) {
        if (sscanf(line, "%d | %[^|] | %d |  %2d/%2d/%4d   |  %d", 
                &c.h.idhistorique,c.h.typeoperation, &c.h.montant, &c.h.doperation.jour, &c.h.doperation.mois, &c.h.doperation.anne) == 5)
        {
            printf("%d | %s | %d |  %d/%d/%d   |  %d\n",c.h.idhistorique,c.h.typeoperation,c.h.montant,c.h.doperation.jour,c.h.doperation.mois,c.h.doperation.anne);
        }
        
    }
}
void modifier_adress_client(FILE* fich, client cl, compte c) {
    char nouvelle_adresse_saisie[100];  
    int N_compte_saisie;
    int N_compte_cher;
    int trouve = 0;

    printf("Donner la nouvelle adresse: \n");
    scanf(" %[^\n]%*c", nouvelle_adresse_saisie);  

    printf("Donner votre numero de compte : \t");
    scanf("%d", &N_compte_saisie);

    fich = fopen("clients.txt", "r+");
    if (fich == NULL) {
        printf("Problème de lire le fichier\n");
        exit(1);
    }

    char ligne[200];
    FILE* temp_fich=fopen("temp.txt","w+");
     if ((temp_fich) == NULL) {
        printf("Problème de ecrire dans  le fichier\n");
        exit(1);
    }
    while (fgets(ligne, sizeof(ligne), fich) != NULL) {
        if (sscanf(ligne, "%*d | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %*[^|] |  %*[^|]  | %*[^|] | %d", &N_compte_cher) == 1) {
            if (N_compte_cher == N_compte_saisie) {
                trouve = 1;
                sprintf(ligne, "%d | %s | %s | %d/%d/%d | %s | %s | %s | %s | %c | %s\n", 
                        cl.idclient, cl.nom, cl.prenom, cl.d.jour, cl.d.mois, cl.d.anne, 
                        cl.phone, cl.adress, cl.sexe, nouvelle_adresse_saisie);
            }
        }
        fputs(ligne,temp_fich);
    }

    fclose(fich);
    fclose(temp_fich);
    remove("clients.txt");
    rename("temp.txt", "clients.txt");
    if (!trouve) {
        printf("Client non trouvé\n");
    } else {
        printf("Info du client modifiée avec succès\n");
    }
}
void modifier_client_telephone(FILE* fich,client cl,compte c) {
    char *nouvelle_telephone_saisie;
    int N_compte_saisie;
    printf("Donner la nouvelle numero de telephone: \n");
    scanf("%s",nouvelle_telephone_saisie);
    printf("Pour la confirmation : \n");
    printf("donner votre numero de compte : \t");
    scanf("%d",&N_compte_saisie);
        char ligne[200];
        int trouve = 0;
        int N_compte_cher;
    

    fich = fopen("clients.txt", "r+");
    if (fich == NULL) {
        printf("Problème de lire le fichier\n");
        exit(1);
    }
    FILE* temp_fich=fopen("temp.txt","w+");
     if ((temp_fich) == NULL) {
        printf("Problème de ecrire dans  le fichier\n");
        exit(1);
    }
    while (fgets(ligne, sizeof(ligne), fich) != NULL) {
        if (sscanf(ligne, "%*d | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %*[^|] |  %*[^|]  | %*[^|] | %d", &N_compte_cher) == 1) {
            if (N_compte_cher == N_compte_saisie) {
                trouve = 1;
                sprintf(ligne, "%d | %s | %s | %d/%d/%d | %s | %s | %s | %s | %c | %s\n", 
                        cl.idclient, cl.nom, cl.prenom, cl.d.jour, cl.d.mois, cl.d.anne, 
                        cl.phone, cl.adress, cl.sexe, nouvelle_telephone_saisie);
            }
        }
        fputs(ligne,temp_fich);
    }

    fclose(fich);
    fclose(temp_fich);
    remove("clients.txt");
    rename("temp.txt", "clients.txt");
    if (!trouve) {
        printf("Client non trouvé\n");
    } else {
        printf("Info du client modifiée avec succès\n");
    }
}
void MODIFIERCLIENT(FILE* fich,client cl,compte c){
    fich = fopen("clients.txt", "r");
    if (fich == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }
int choix=0;
LIRECLIENTS(fich);
do{

printf("MODIFIER CLIENT\n");
printf("1- modifier l'adresse .\n");
printf("2- modifier le numero .\n");
printf("3-modifier les deux .\n");
printf("donner votre choix : ");
scanf("%d",&choix);
switch (choix)
{
case 1:
system("cls");
    modifier_adress_client(fich,cl,c);
    break;
case 2 :
system("cls");
modifier_client_telephone(fich,cl,c);
break;
case 3: 
system("cls");
modifier_info_client(fich,cl,c);
break;
default:
    break;
}
}while(choix==0);
   
fclose(fich);

}
void modifier_info_client(FILE* fich,client cl,compte c) {
modifier_adress_client(fich,cl,c);
modifier_client_telephone(fich,cl,c);
}
void CHANGER_MOTDEPASSE(FILE* fich, client cl, compte c) {
    int nouveau_mdp_saisie, mdp_actuel_saisie, mdp_cherch;
    int N_compte_saisie;
    int trouve = 0;
    printf("Donner le nouveau mot de passe (4 chiffres) : \t");
    scanf("%4d", &nouveau_mdp_saisie);
    printf("Pour la confirmation : \n");
    printf("Donner votre numero de compte : \t");
    scanf("%d", &N_compte_saisie);
    printf("Donner le mot de passe actuel : \t");
    scanf("%d", &mdp_actuel_saisie);

    fich = fopen("comptes.txt", "r+");
    if (fich == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    char ligne[200];
    FILE* temp_fich = fopen("temp.txt", "w+");
    if (temp_fich == NULL) {
        printf("Impossible de créer un fichier temporaire.\n");
        fclose(fich);
        return;
    }

    while (fgets(ligne, sizeof(ligne), fich) != NULL) {
        if (sscanf(ligne, "%*d %*s %*s %*d/%*d/%*d %*s %*d %d %*d", &mdp_cherch) == 1) {
            if (mdp_cherch == mdp_actuel_saisie) {
                trouve = 1;
                sprintf(ligne, "%d %s %s %d/%d/%d %s %d %d %d\n",
                        cl.c.Ncompte, cl.nom, cl.prenom, c.dcreation.jour, 
                        c.dcreation.mois, c.dcreation.anne, c.typecompte, 
                        c.solde, nouveau_mdp_saisie, c.h.idhistorique);
        }
        }
        fputs(ligne, temp_fich);
    }

    fclose(fich);
    fclose(temp_fich);

    remove("comptes.txt");
    rename("temp.txt", "comptes.txt");

    if (!trouve) {
        printf("Client non trouvé.\n");
    } else {
        printf("Mot de passe modifié avec succès.\n");
    }
}

/// fonction de page de profil 
int PAGEPROFIL(FILE* fich){
     int choix=0;
     system("Cls");
    int x = 45;
    int y = 5;  
    client cl;
    compte c;
    date d;
    
 do
    {
    gotoxy(x,y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓ PAGE DE PROFIL  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 1-AFFICHER  VOTRE INFORMATIONS PERSONNELES .\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 2-AFFICHER VOTRE HISTORIQUES.\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 3-MODIFIER VOTRE INFORMATIONS .\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 4-CHANGER VOTRE MOT DE PASS  .\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 5-RETURNER AU MENU PRINCIPALE.\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");
    gotoxy(x, y++);
    printf("\n\n"); 
    tim_function() ;

    gotoxy(x,y++);
    printf("donner votre choix : ");
    scanf("\t%d",&choix);
    

        switch (choix)
        {
        case 1:
       system("cls");
        LIRECLIENTS(fich);
            
            break;
        case 2:
        clear_screen();
        AFFICHERHSITORIQUE(c);
            break;
        case 3:
         clear_screen();    
            MODIFIERCLIENT(fich,cl,c);
           break;
        case 4:
           
            break;
        case 5:
            
            break;
        case 6:
            afficher_menu();
            break;
        default:
            NOTIFICATION("erreur de saisir...  \n",0);
            break;
        }
    } while (choix == 0);
    
}
// menu funcrion 
void afficher_menu() {
    int choix=0;
    int x = 50;
    int y = 2;  
    client c;
    FILE* fich;
    date d;
    system("cls");
    /*
    printbox(180,20);*/
 do
    {
    gotoxy(x,y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓ MAIN MENU ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 1-SIGN IN  .\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 2-LOGIN  .\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 3-QUITTER L'APPLICATION.\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");
    gotoxy(x,y++);
    printf("donner votre choix : ");
    scanf("%d",&choix);
        switch (choix)
        {
        case 1:
            system("cls");
            
            SIGNIN(fich);
            break;
        case 2:
            system("cls"); 
         
           login();
            break;
        case 3:
        clear_screen();
        loadingPage();
        NOTIFICATION(" MERCI POUR VOTRE VISITE .....\n",1);
            break;
        default:
        clear_screen();
        loadingPage();
        printf("erruer de sasair \n");
        afficher_menu();
            break;
        }
    } while (choix != 3);
    
}
int main() {
    setlocale(LC_ALL, "fr_FR.UTF-8");  
    SetConsoleOutputCP(65001);
    system("COLOR 0A");
    loadingPage();
    afficher_menu();    
   
}