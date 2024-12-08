#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<locale.h>
#include<time.h>
#include <unistd.h>
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
    printf("%02d : %02d  \t\t \t\t \t\t \t\t ",tm_info->tm_hour , tm_info->tm_min ); 
    printf("%02d / %02d / %04d \n",tm_info->tm_mday , tm_info->tm_mon +1 ,tm_info->tm_year +1900) ;  
}
void obtenir_date_actuelle(date *d) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    d->jour = tm.tm_mday;
    d->mois = tm.tm_mon + 1; // Les mois commencent à 0
    d->anne = tm.tm_year + 1900; // Les années commencent à 1900
}
/***********************************************masque le mdp ***************************************************** */
void saisie_masquee(char* buffer, int taille_max) {
    char c;
    int index = 0;

    while ((c = getch()) != '\r') { 
        if (c == '\b') { 
            if (index > 0) {
                index--; 
                printf("\b \b"); 
            }
        } else if (index < taille_max - 1) {
            buffer[index++] = c;
            printf("*"); // Afficher une étoile
        }
    }
    buffer[index] = '\0'; // Terminer la chaîne
}

/***********************************************function de box ************************************************************ */
void print_box(int x, int y, int width, int height) {
    gotoxy(x, y);
    for (int i = 0; i < width; i++) {
        printf("▓");
    }

    for (int i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("▓");
        for (int j = 1; j < width - 1; j++) {
            printf(" ");
        }
        printf("▓");
    }
    gotoxy(x, y + height - 1);
    for (int i = 0; i < width; i++) {
        printf("▓");
    }
    printf("\n");
}
void print_box_with_title(int x, int y, int width, int height, const char *title) {
    int title_length = strlen(title);
    int padding = (width - title_length) / 2;
    printf("\033[1;32m");  
    gotoxy(x, y);
    for (int i = 0; i < padding; i++) {
        printf("▓");
    }
    printf("%s", title);
    for (int i = padding + title_length; i < width; i++) {
        printf("▓");
    }

    // Middle part of the box
    for (int i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("▓");
        for (int j = 1; j < width - 1; j++) {
            printf(" ");
        }
        printf("▓");
    }

    // Bottom border
    gotoxy(x, y + height - 1);
    for (int i = 0; i < width; i++) {
        printf("▓");
    }
    printf("\n");
    printf("\033[0m");
}
void clear_box_content(int x_start, int y_start, int width, int height) {
    for (int i = 1; i < height - 1; i++) { 
        gotoxy(x_start + 1, y_start + i);
        for (int j = 0; j < width - 2; j++) {
            printf(" ");
        }
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
/**********************************************notification fonction ************************************************** */ 
void NOTIFICATION(char *std, int trv) {
    clear_screen();                
            gotoxy(17,5);
            printf("--------------------------------------------");
            for(int i =0 ;i<5 ;i++){   
                printf("|");
            }
            printf("--------------------------------------------");
            
            gotoxy(52,10);
            printf("%s",std);
            gotoxy(17,15);
            printf("--------------------------------------------");
            for(int i =0 ;i<5 ;i++){   
                printf("|");
            }
            printf("--------------------------------------------");
            Sleep(5);
      if (trv == 1) {
        getchar(); 
        exit(0);
    } else {
        getchar(); 
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
void ECRIRELESHISTORIQUE_depot(int idhisto,int montant,int solde ) {
    FILE* fich = fopen("historique.txt", "a+");
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    if (fich == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }
    compte c;  
c.h.typeoperation="Retrait";
c.h.montant=montant;
c.h.doperation.jour=local_time->tm_mday;
c.h.doperation.mois=local_time->tm_mon+1;
c.h.doperation.anne=local_time->tm_year + 1900;
c.solde=solde;
   fprintf(fich, "%-12d |        %-11s      | -%-11d |    %02d/%02d/%04d    | %d \n",
            idhisto,c.h.typeoperation,c.h.montant,c.h.doperation.jour,c.h.doperation.mois,c.h.doperation.anne,c.solde);    

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
void login() {
    int idCompt_search, password_search;
    FILE* fich;
    print_box_with_title(10,5,100,20,"*******LOGIN*******");
    printf("\033[1;32m");
    gotoxy(35,11);
    printf("Donner le numero de compte (5 chiffres) : ");
    gotoxy(35,15);
    printf("Donner le mot de passe  (4 chiffres) : ");
    gotoxy(10, 25);
    tim_function();

    // Saisie des informations de connexion
    gotoxy(35 + strlen("Donner le numero de compte (5 chiffres) : "),11);  // Placer le curseur juste apres Donner le numero de compte (5 chiffres) :
    scanf("%d", &idCompt_search);

    gotoxy(35 + strlen("Donner le mot de passe (4 chiffres) : "), 15);  // Placer le curseur juste apres Donner le mot de passe (4 chiffres) : 
    scanf("%d",&password_search);

    // Authentification
    int trouver = authentification(idCompt_search, password_search);
    
    if (trouver == 1) {
        // Connexion réussie
        
        NOTIFICATION("✅ CONNEXION RÉUSSIE",0);
        getch();
        PAGEPROFIL(fich,idCompt_search);
    } else {
        // Connexion échouée
        int choix = 0;
        system("cls");        
        NOTIFICATION("❌Erreur système ❌",0);

        getch();
        system("cls");
        NOTIFICATION("⚠️ Numéro de compte ou mot de passe incorrect ⚠️",0);
        print_box(10,5,100,20);
        gotoxy(35,11);
        printf("1-connexion .");
        gotoxy(35,13);
        printf("2-retourner  au menu ");
        gotoxy(36+strlen("2-retourner  au menu "), 8);
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
                exit(0); 
                break;
        }
    }
    printf("\033[0m"); 
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
int verification_mdp() {
    int N_compte_saisie, mdp_actuel_saisie;

do
    {
    printf("Pour la confirmation : \n");
    printf("Donner votre numero de compte : \t");
    scanf("%d", &N_compte_saisie);
    printf("Donner le mot de passe actuel : \t");
    scanf("%d", &mdp_actuel_saisie);
    } while (authentification(N_compte_saisie,mdp_actuel_saisie)==0);
    return authentification(N_compte_saisie,mdp_actuel_saisie);
}
int verification(int numcompte) {

 FILE *fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    client cl;
    int trv = 0;
    
    while (fscanf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n", &cl.c.Ncompte, cl.nom, cl.prenom, 
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne, cl.c.typecompte, 
                  &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) {
        
        if (cl.c.Ncompte == numcompte) {
        return 1;
        break; 
        }
    }

    if (!trv) {
        printf("Compte avec le numéro %d non trouvé.\n", numcompte);
    }
    fclose(fich);
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

    int x = 10, y = 5;

    do {
        print_box_with_title(x,y,100,20," CREATION DE COMPTE ");
        printf("\033[1;32m");  
         x+=2;y+=2;
        gotoxy(x, y++);
        printf(" ⚠️ ATTENTION ⚠️: VOUS ÊTES RESPONSABLE DE CHAQUE ERREUR DANS VOS INFORMATIONS.\n");
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
        gotoxy(x,y++ );
        printf("TU PEUX SAUVEGARDER VOTRE INFORMATIONS O/N :  \t");
        scanf(" %c", &choix);
        while (getchar() != '\n');
        printf("\033[0m");
        
    } while (choix == 'N' || choix =='n');
    clear_box_content(10,5,100,20);
    int w=17,z=12;
    printf("\033[1;32m"); 
    gotoxy(w,z++ );
    do
    {
    printf("TU peux donner le numero de compte  (5 chiffres) :  ");
    scanf("%d", &c1.c.Ncompte);
    if(verification(c1.c.Ncompte)==1){
        gotoxy(w,z++);
        printf("NUMERO DE COMPTE DEJA EXISITE .\n");
    }
   

    } while (verification(c1.c.Ncompte)==1);
    gotoxy(w,z++ );
    printf("TU peux donner le mot de passe (4 chiffres) : ");
    scanf("%d", &c.password);
    printf("\033[0m");
    
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
    NOTIFICATION(" ✅ Ton compte a ete enregistre avec succes. ✅ ",0);
    return 0; 
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
void afficher_compte(int numcompte) {
    FILE *fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    client cl;
    int trv = 0;
    
    while (fscanf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n", &cl.c.Ncompte, cl.nom, cl.prenom, 
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne, cl.c.typecompte, 
                  &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) {
        
        if (cl.c.Ncompte == numcompte) {
            printf("\033[1;32m");
            gotoxy(22,8);
            printf("Compte : %d\n", cl.c.Ncompte);
            gotoxy(22,10);
            printf("Nom : %s\n", cl.nom);
            gotoxy(22,12);
            printf("Prénom : %s\n", cl.prenom);
            gotoxy(22,14);
            printf("Date de création : %02d/%02d/%04d\n", cl.c.dcreation.jour, cl.c.dcreation.mois, cl.c.dcreation.anne);
            gotoxy(22,16);
            printf("Type de compte : %s\n", cl.c.typecompte);
            gotoxy(22,18);
            printf("Solde : %d\n", cl.c.solde);
            printf("\033[0m");
            trv = 1;
            break; 
        }
    }

    if (!trv) {
        printf("Compte avec le numéro %d non trouvé.\n", numcompte);
    }
    fclose(fich);
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
void CHANGER_MOTDEPASSE(numcompte) {
    int nouveau_mdp_saisie;
    int trouve = 0;
    trouve=verification_mdp();
    if(trouve==1){
    printf("Donner le nouveau mot de passe (4 chiffres) : \t");
    scanf("%4d", &nouveau_mdp_saisie);
    }
    FILE *fich = fopen("comptes.txt", "r+");
    if (fich == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        exit(0);
    }

    char ligne[256];
    long position;
    trouve = 0;
    client cl;
    compte c;
    while (fgets(ligne, sizeof(ligne), fich)) {
        // Extraire les informations depuis la ligne
        if (sscanf(ligne, "%d %s %s %d/%d/%d %s %d %d %d", 
                  &cl.c.Ncompte, cl.nom, cl.prenom, 
                  &c.dcreation.jour, &c.dcreation.mois, &c.dcreation.anne, c.typecompte, 
                  &c.solde, &c.password, &c.h.idhistorique) == 10) {
            // Vérifier si c'est le bon numéro de compte
            if (cl.c.Ncompte== numcompte) {
                trouve = 1;
                position = ftell(fich) - strlen(ligne);  
                fseek(fich, position, SEEK_SET);  
                fprintf(fich, "%d %s %s %02d/%02d/%04d %s %d %d %d\n", 
                        cl.c.Ncompte, cl.nom, cl.prenom, c.dcreation.jour, c.dcreation.mois, c.dcreation.anne,c.typecompte,c.solde,nouveau_mdp_saisie,c.h.idhistorique);
                break;
            }
        }
    }

    fclose(fich);
    if (!trouve) {
        printf("Client non trouvé.\n");
    } else {
        printf("Mot de passe modifié avec succès.\n");
    }
    sleep(5);
}
///lsite des operation 
void operation_liste(int numcompte){
    int choix = 0;
    printf("1-le depot .\n");
    printf("2-retrait .\n");
    scanf("%d",&choix);
    switch (choix)
    {
    case 1:
    system("cls");
        depot();
        break;
    case 2:
        faire_retrait(numcompte);
        break;
    default:
        break;
    }
}
/// fonction de page de profil 
int PAGEPROFIL(FILE* fich,int id_compte){
     int choix=0;
     system("Cls");
    client cl;
    compte c;
    date d;
    int x=60,y=7;
 do
    {
    print_box_with_title(10,5,100,20,"*******PAGE PROFIL********");
    
    
    gotoxy(35,11);
    afficher_compte(id_compte);
    printf("\033[1;32m");

    gotoxy(60, 8);
    printf("1-FAIRE DES OPPERATIONS .\n");

    gotoxy(60, 10);
    printf("2-AFFICHER VOTRE HISTORIQUES.\n");

    gotoxy(60, 12);
    printf("3-MODIFIER VOTRE INFORMATIONS .\n");

    gotoxy(60, 14);
    printf("4-CHANGER VOTRE MOT DE PASS  .\n");

    gotoxy(60, 16);
    printf("5-SUPPRIMER VOTRE  COMPTE .\n");   
    gotoxy(60, 18);
    printf("6-RETURNER AU MENU PRINCIPALE.\n");   
    gotoxy(10, 25);
    tim_function();

    gotoxy(60, 20);
    printf("Donner votre choix : ");
    scanf("\t%d",&choix);
    

        switch (choix)
        {
        case 1:
        system("cls");
        operation_liste(id_compte);
            
            break;
        case 2:
            clear_screen();
            
            break;
        case 3:
         clear_screen();    
            MODIFIERCLIENT(fich,cl,c);
           break;
        case 4:
           clear_screen();
           CHANGER_MOTDEPASSE(id_compte);
            break;
        case 5:
            clear_screen();
           Supresion_compt();
            break;
        case 6:
            afficher_menu();
            break;
        default:
            NOTIFICATION("erreur de saisir...  ",0);
            break;
        }
        printf("\033[0m");
    } while (choix == 0);
    
}
// menu funcTion 
void afficher_menu() {
    int choix=0;
    client c;
    FILE* fich;
    date d;
    system("cls");
    
     do {
        system("cls");
        print_box_with_title(10, 5, 100, 20, "ACCUEIL");
        printf("\033[1;32m");
        gotoxy(35, 11); printf("1-SIGN IN.\n");
        gotoxy(35, 13); printf("2-LOGIN.\n");
        gotoxy(35, 15); printf("3-QUITTER L'APPLICATION.\n");
        gotoxy(35, 17); printf("Donner votre choix : \t");
        gotoxy(10, 25);
        tim_function();
        gotoxy(35+strlen("Donner votre choix : "),17);
        scanf("%d",&choix);
        switch (choix) {
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
                NOTIFICATION("MERCI POUR VOTRE VISITE .....", 1);
                break;
            default:
                clear_screen();
                
                NOTIFICATION("Erreur de saisie. Réessayez.", 0);
                break;
        }
        printf("\033[0m");
    } while (choix != 3);      
    
 
}
void FermetCompt() {
    FILE *fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        printf("Problème d'ouverture du fichier original.\n");
        exit(1);
    }

    FILE *fichancien = fopen("temp.txt", "w");
    if (fichancien == NULL) {
        printf("Problème d'ouverture du fichier temporaire.\n");
        fclose(fich);
        exit(1);
    }

    client cl;
    int id_search, password;
    int compt_trouver = 0;

    system("color 0A");
    printf("\n⚠️ Note bien que la suppression s'effectue définitivement !\n");
    printf("\nEntrer le numéro de votre compte : ");
    scanf("%d", &id_search);
    printf("Entrer le mot de passe : ");
    scanf("%d", &password);

    while (fscanf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n",
                  &cl.c.Ncompte, cl.nom, cl.prenom,
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne,
                  cl.c.typecompte, &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) == 10) {
        if (cl.c.Ncompte == id_search && cl.c.password == password) {
            compt_trouver = 1; 
        } else {
            fprintf(fichancien, "%d %s %s %d/%d/%d %s %d %d %d\n",
                    cl.c.Ncompte, cl.nom, cl.prenom,
                    cl.c.dcreation.jour, cl.c.dcreation.mois, cl.c.dcreation.anne,
                    cl.c.typecompte, cl.c.solde, cl.c.password, cl.c.h.idhistorique);
        }
    }

    fclose(fich);
    fclose(fichancien);

    if (compt_trouver) {
        rename("comptes.txt","datacompte.txt");         
        rename("temp.txt", "comptes.txt"); // Renomme le fichier temporaire

        system("cls");
        printf("\n✅ La suppression du compte s'est effectuée avec succès ✅\n");
        Sleep(3);
    } else {
        remove("temp.txt"); // Supprime le fichier temporaire inutile
        system("cls");
        printf("\n❌ Erreur : Compte introuvable ou mot de passe incorrect ❌\n");
        Sleep(3);
    }
}
void Supresion_compt() {
    int choix;

    system("color 0A");
    printf("\n**** FERMETURE DE COMPTE ****\n");
    printf("1. Fermer un compte\n");
    printf("2. Retourner au menu principal\n");
    printf("Entrer votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            system("cls");
            FermetCompt();
            break;
        case 2:
            system("cls");
            printf("\nRetour au menu principal...\n");
            break;
        default:
            system("cls");
            printf("\n⚠️ Choix invalide, retour au menu principal.\n");
            Sleep(2000);
            break;
    }
}
/// retourn  id histo
int retourner_idhistori(int numcompte) {
    FILE *fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    client cl;
    int trv = 0;
    
    while (fscanf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n", &cl.c.Ncompte, cl.nom, cl.prenom, 
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne, cl.c.typecompte, 
                  &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) {
        
        if (cl.c.Ncompte == numcompte) {
            return cl.c.h.idhistorique;
            trv = 1;
            break; 
        }
    }

    if (!trv) {
        printf("Compte avec le numéro %d non trouvé.\n", numcompte);
    }
    fclose(fich);
}
int modifierSolde(int numeroCompte, int nvsolde) {
    FILE *fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    FILE *fichTemp = fopen("temp.txt", "w");
    if (fichTemp == NULL) {
        printf("Erreur : impossible de créer le fichier temporaire.\n");
        fclose(fich);
        return 0; 
    }

    char ligne[256];
    int trouve = 0;
    client cl;
    compte c;

    // Read each line from the original file
    while (fgets(ligne, sizeof(ligne), fich)) {
        // Extract data from the line
        if (sscanf(ligne, "%d %s %s %d/%d/%d %s %d %d %d", 
                  &cl.c.Ncompte, cl.nom, cl.prenom, 
                  &c.dcreation.jour, &c.dcreation.mois, &c.dcreation.anne, c.typecompte, 
                  &c.solde, &c.password, &c.h.idhistorique) == 10) {

            // If account number matches, update the balance
            if (cl.c.Ncompte == numeroCompte) {
                c.solde = nvsolde;  // Set the new balance
                trouve = 1;
            }

            // Write the updated data to the temporary file
            fprintf(fichTemp, "%d %s %s %02d/%02d/%04d %s %d %d %d\n", 
                    cl.c.Ncompte, cl.nom, cl.prenom, c.dcreation.jour, c.dcreation.mois, c.dcreation.anne, 
                    c.typecompte, c.solde, c.password, c.h.idhistorique);
        }
    }

    fclose(fich);
    fclose(fichTemp);

    // If an account was found and modified, replace the original file with the temporary file
    if (trouve) {
        remove("comptes.txt");  // Delete the original file
        rename("temp.txt", "comptes.txt");  // Rename temp file to the original file
        printf("Le solde a été mis à jour avec succès.\n");
    } else {
        remove("temp.txt");  // Delete the temp file if account not found
        printf("Compte non trouvé.\n");
    }
    return trouve ; 
}


// calculer le solde 
int calculer_solde(int numcompte,int montant,int numop){
     FILE *fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        exit(1);
    }
    client cl;
    int trv = 0;
    int soldecalcu;
    while (fscanf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n", &cl.c.Ncompte, cl.nom, cl.prenom, 
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne, cl.c.typecompte, 
                  &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) {
        
        if (cl.c.Ncompte == numcompte) {
            if(numop==1){
            soldecalcu=cl.c.solde-montant;/// retrait 
            }else if(numop==0){
            soldecalcu=cl.c.solde+montant;
            }
            return soldecalcu;
            }
            trv = 1;
            break; 
        }
    

    if (!trv) {
        printf("Compte avec le numéro %d non trouvé.\n", numcompte);
    }
    fclose(fich);
}
// depot fonction 
void faire_retrait(int numcompte){
    /*     print_box_with_title(10,5,100,20,"*******retrait********"); */
    int mdp_saisie;
    do{
    printf("Donner le mot de passe  (4 chiffres) : \n");
    scanf("%d",&mdp_saisie);
    if(authentification(numcompte,mdp_saisie)==0){
        printf("le mot de pass est incorrect\n" );
    }
}while (authentification(numcompte,mdp_saisie)==0);
   
    
    // retourner le num de id historique 
    int id_histo=retourner_idhistori(numcompte);
    int solde,montant_saisie;
    do {
        printf("donner le montant : \n");
        scanf("%d",&montant_saisie);
        solde=calculer_solde(numcompte,montant_saisie,1);
        if(solde<0){
            printf("le montant est plus grand \n");
        }
    }while(solde<0);
    ECRIRELESHISTORIQUE_depot(id_histo,montant_saisie,solde);
    modifierSolde(numcompte,solde);
}
void depot() {
    int idEntrer; 
    int soldEAjouter; 
    compte c;
    client cl; 
    do{
 system("color 0A"); 
    gotoxy(2, 2);
    printf("\t************************\n");
    gotoxy(2, 3);
    printf("\t                               Dépot                              \n"); 
    gotoxy(2, 4);
    printf("\t************************\n"); 
    printf("\n");
    gotoxy(2, 5);
    printf("\t┌────────────────────────────────────────────────────────────────────────────┐");
    gotoxy(2, 6);
    printf("\t│                       ** ✉️ Vérment  **                               │");
    gotoxy(2, 7);
    printf("\t│                                                                            │");
    gotoxy(2, 8);
    printf("\t│  ▓▓▓ Entrer  identifiant :                                                 │");
    gotoxy(2, 9); 
    printf("\n"); 
    gotoxy(2, 10);
    printf("\t|  ▓▓▓ Entrer sold de verement :                                             |");
    printf("\n");
    gotoxy(2, 11);
    printf("\t└────────────────────────────────────────────────────────────────────────────┘");
    gotoxy(5, 14); 
    tim_function(); 

    gotoxy(48, 8); 
    scanf("%d", &idEntrer);
    ;
    gotoxy(55, 10);
    scanf("%d", &soldEAjouter); 
    } while (verification(idEntrer)==0);
    
   

    if (soldEAjouter <= 0) {
        system("cls"); 
        printf("Problème dans les données entrées : le montant doit être positif.\n");
        return;
    }
    int vartrouver = 0 ;
    
    
    
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    c.h.doperation.jour=local_time->tm_mday;
    c.h.doperation.mois=local_time->tm_mon+1;
    c.h.doperation.anne=local_time->tm_year + 1900;

    FILE *fichies_historique = fopen("historique.txt", "a+"); 
    if (fichies_historique == NULL) {
        printf("Problème d'ouverture du fichier historique.\n");
        exit(1);
    }
    int solde=calculer_solde(idEntrer,soldEAjouter,0);
    vartrouver =    modifierSolde(idEntrer,solde);
    
    
    int id_hist=retourner_idhistori(idEntrer);
    if (vartrouver != 0) {
           fprintf(fichies_historique, "%-12d |        %-11s      | %-12d |    %02d/%02d/%04d    | %d \n",
            id_hist,"depot",soldEAjouter,c.h.doperation.jour,c.h.doperation.mois,c.h.doperation.anne,solde); 
        fclose(fichies_historique); 

        system("cls"); 
        gotoxy(2, 5);
        printf("┌────────────────────────────────────────────────────────────────────────────┐");
        gotoxy(2, 6);
        printf("│                             ✅ le dépôt a été effectué                   │");
        gotoxy(2, 7);
        printf("└────────────────────────────────────────────────────────────────────────────┘");
        getch(); 
    } else {
        system("cls"); 
        gotoxy(2, 5);
        printf("┌────────────────────────────────────────────────────────────────────────────┐");
        gotoxy(2, 6);
        printf("│                             ⚠️ Problème système                         │");
        gotoxy(2, 7);
        printf("└────────────────────────────────────────────────────────────────────────────┘");
        getch(); 
    }
}
int main() {
    setlocale(LC_ALL, "fr_FR.UTF-8");  
    SetConsoleOutputCP(65001);
    system("COLOR 0A");
    afficher_menu();    
}