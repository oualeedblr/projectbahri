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
/*****************************************************creation de fichier bin************************************ */
void create_files() {
    // Check if the "data" directory exists
    if (access("data", F_OK) == -1) {
        printf("Le dossier 'data' n'existe pas. Creation du dossier...\n");
        if (mkdir("data") == -1) {
            perror("Erreur lors de la creation du dossier 'data'");
            exit(1); // Exit the program if the directory cannot be created
        }
    }

    // Create clients.bin if it does not exist
    FILE *clients_file = fopen("data/clients.bin", "ab");
    if (clients_file == NULL) {
        perror("Erreur lors de la creation du fichier clients.bin");
        exit(1); // Exit the program if the file cannot be created
    }
    fclose(clients_file);
    printf("Fichiers crees avec succes.\n");
}
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
void saisirMotDePasseMasque(int *passwordadmin) {
    char ch;
    int i = 0;
    *passwordadmin = 0;  // Reset the password to 0

    while (1) {
        ch = _getch();  // Get a character from user input without echoing

        if (ch == 13) {  // Enter key
            break;
        } else if (ch == 8) {  // Backspace key
            if (i > 0) {
                i--;
                *passwordadmin /= 10;  // Remove the last digit
                printf("\b \b");  // Erase last character (asterisk)
            }
        } else if (ch >= '0' && ch <= '9') {  // If the character is a digit
            *passwordadmin = *passwordadmin * 10 + (ch - '0');  // Add digit to password
            i++;
            printf("*");  // Mask the character by printing an asterisk
        }
    }

    printf("\n");  // Newline after input is finished
}
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = 0; // Set to 0 to hide
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}
void progressBar() {
    printf("\033[1;36m"); // Cyan text
    movingBanner("Welcome to the Dynamic Terminal!");
    printf("\033[0m");
    for (int i = 0; i < 50; i++) {
        printf("#");
        fflush(stdout);
        usleep(50000); // 50ms delay
    }
    printf("] Done!\n");
}
/***********************************************function de box ************************************************************ */
void print_box(int x, int y, int width, int height) {
    gotoxy(x, y);
    for (int i = 0; i < width; i++) {
        printf("█");
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
        printf("█");
    }


    printf("\n");
}
void print_box_with_title(int x, int y, int width, int height, const char *title) {
    int title_length = strlen(title);
    int padding = (width - title_length) / 2;
    printf("\033[0;34;40m"); 
    gotoxy(x, y);
    for (int i = 0; i < padding; i++) {
        printf("█");
    }
    printf("%s", title);
    for (int i = padding + title_length; i < width; i++) {
        printf("█");
    }

    // Middle part of the box
    for (int i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("█");
        for (int j = 1; j < width - 1; j++) {
            printf(" ");
        }
        printf("█");
    }

    // Bottom border
    gotoxy(x, y + height - 1);
    for (int i = 0; i < width; i++) {
        printf("█");
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
void interface1() {
    // Define color codes
    #define RESET   "\033[0m"
    #define BORDER  "\033[44m\033[37m" // Blue background, white text
    #define TITLE   "\033[1;37m"       // Bold white text
    #define SUBTEXT "\033[1;36m"       // Bold cyan text
    #define DESC    "\033[37m"         // White text
    #define WELCOME "\033[1;33m"       // Bold yellow text
    #define BYELLOW "\033[1;33m"       // Bold yellow text

    system("color 01"); // Set console color to blue on black
    system("cls"); // Clear the screen

    // Top thicker border
    gotoxy(3, 8);
    printf("%s%s%s\n", BORDER, "██████████████████████████████████████████████████████████████████████", RESET);

    // Inner top border
    gotoxy(4, 9);
    printf("%s╔═════════════════════════════════════════════════════════════════════════════╗%s\n", BORDER, RESET);

    // Title
    gotoxy(10, 10);
    printf("%s                  DIGITAL CAPITAL BANK                                       %s\n", TITLE, RESET);

    // Subheader
    gotoxy(15, 11);
    printf("%s                            INFORMATIQUES ET SERVICES                         %s\n", SUBTEXT, RESET);

    // Inner empty line
    gotoxy(4, 12);
    printf("%s║                                                                             ║%s\n", BORDER, RESET);

    // Description lines
    gotoxy(6, 13);
    printf("%s Digital Capital Bank (DCB) is a financial institution offering a range      %s\n", DESC, RESET);
    gotoxy(6, 14);
    printf("%s of services such as deposit management, credit issuance, payment handling,  %s\n", DESC, RESET);
    gotoxy(6, 15);
    printf("%s and investment of funds...                                                  %s\n", DESC, RESET);

    // Inner bottom border
    gotoxy(4, 16);
    printf("%s╚═════════════════════════════════════════════════════════════════════════════╝%s\n", BORDER, RESET);

    // Bottom thicker border
    gotoxy(3, 17);
    printf("%s%s%s\n", BORDER, "██████████████████████████████████████████████████████████████████████", RESET);

    // Welcome message with star border in yellow
    gotoxy(5, 19);
    printf("%s****************************************************************************************%s\n", BYELLOW, RESET);
    gotoxy(5, 20);
    printf("%s*                             **S O Y E Z  L A  B I E N V E N U E**                      *%s\n", BYELLOW, RESET);
    gotoxy(5, 21);
    printf("%s****************************************************************************************%s\n", BYELLOW, RESET);

    // Prompt
    gotoxy(15, 23);
    printf("%sPress Enter for more information:%s", WELCOME, RESET);

    // Wait for user input
    getch();
}

/*******************************************function de ecriture dans les fichiers ******************************** */
void ECRIRELESCLIENTSbin(FILE *fich, client cl) {
    fich = fopen("data/clients.bin", "ab");
    if (fich == NULL) {
        perror("Error opening clients.bin for writing");
        exit(1);
    }

    fwrite(&cl, sizeof(client), 1, fich);
    fclose(fich);
}
void ECRIRELESCLIENTStxt(FILE *fich, client cl) {
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
void ECRIRELESHISTORIQUE_retrait(int idhisto,int montant,int solde ) {
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
   fprintf(fich, "%-12d |        %-11s      | %-12d |    %02d/%02d/%04d    | %d \n",
            idhisto,c.h.typeoperation,c.h.montant,c.h.doperation.jour,c.h.doperation.mois,c.h.doperation.anne,c.solde);    

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
c.h.typeoperation="depot";
c.h.montant=montant;
c.h.doperation.jour=local_time->tm_mday;
c.h.doperation.mois=local_time->tm_mon+1;
c.h.doperation.anne=local_time->tm_year + 1900;
c.solde=solde;
   fprintf(fich, "%-12d |        %-11s      | %-12d |    %02d/%02d/%04d    | %d \n",
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
    printf("\033[0;34;40m");
    gotoxy(35,11);printf("Donner le numero de compte (5 chiffres) : ");
    gotoxy(35,15);printf("Donner le mot de passe  (4 chiffres) : ");
    gotoxy(10, 25);tim_function();

    // Saisie des informations de connexion
    gotoxy(35 + strlen("Donner le numero de compte (5 chiffres) : "),11);  // Placer le curseur juste apres Donner le numero de compte (5 chiffres) :
    scanf("%d", &idCompt_search);

    gotoxy(35 + strlen("Donner le mot de passe (4 chiffres) : "), 15);  // Placer le curseur juste apres Donner le mot de passe (4 chiffres) : 
    saisirMotDePasseMasque(&password_search);
    //scanf("%d",&password_search);

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
        gotoxy(35,11);printf("1-connexion .");
        gotoxy(35,15);printf("2-retourner  au menu ");
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
    saisirMotDePasseMasque(&mdp_actuel_saisie);
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
        int currentDay = local_time->tm_mday;
        int currentMonth = local_time->tm_mon + 1;
    int currentYear = local_time->tm_year + 1900;

    int x = 10, y = 5;

    do {
        print_box_with_title(x,y,100,20," CREATION DE COMPTE ");
printf("\033[0;34;40m");
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
       
       
 do {
        gotoxy(x, y++);
        printf(" Donner votre sexe ( Homme:H / Femme:F): \t");
        scanf(" %c", &c1.sexe); 
        if (c1.sexe != 'H' && c1.sexe != 'h' && c1.sexe != 'F' && c1.sexe != 'f') {
            gotoxy(x,y++);
            printf("Entrée invalide. Veuillez entrer 'H' pour Homme ou 'F' pour Femme: \t");
        }
    } while (c1.sexe != 'H' && c1.sexe != 'h' && c1.sexe != 'F' && c1.sexe != 'f'); 

        while(getchar() != '\n');


    do {
        gotoxy(x, y++);
        printf("Donner votre date de naissance (JJ MM AAAA): ");
        scanf("%d %d %d", &c1.d.jour, &c1.d.mois, &c1.d.anne);
        while (getchar() != '\n');

        if (c1.d.mois < 1 || c1.d.mois > 12 || c1.d.jour < 1 || (c1.d.mois == 1 || c1.d.mois == 3 || c1.d.mois == 5 || c1.d.mois == 7 || c1.d.mois == 8 || c1.d.mois == 10 || c1.d.mois == 12) && c1.d.jour > 31 || (c1.d.mois == 4 || c1.d.mois == 6 || c1.d.mois == 9 || c1.d.mois == 11) && c1.d.jour > 30 || (c1.d.mois == 2 && (c1.d.anne % 4 == 0 && (c1.d.anne % 100 != 0 || c1.d.anne % 400 == 0)) && c1.d.jour > 29) || (c1.d.mois == 2 && c1.d.jour > 28) || c1.d.anne < 1900 || c1.d.anne > 9999) {
            gotoxy(x, y++);
            printf("Date incorrecte ! Veuillez entrer une date valide.\n");
        }
    } while (c1.d.mois < 1 || c1.d.mois > 12 || c1.d.jour < 1 || (c1.d.mois == 1 || c1.d.mois == 3 || c1.d.mois == 5 || c1.d.mois == 7 || c1.d.mois == 8 || c1.d.mois == 10 || c1.d.mois == 12) && c1.d.jour > 31 || (c1.d.mois == 4 || c1.d.mois == 6 || c1.d.mois == 9 || c1.d.mois == 11) && c1.d.jour > 30 || (c1.d.mois == 2 && (c1.d.anne % 4 == 0 && (c1.d.anne % 100 != 0 || c1.d.anne % 400 == 0)) && c1.d.jour > 29) || (c1.d.mois == 2 && c1.d.jour > 28) || c1.d.anne < 1900 || c1.d.anne > 9999);

    int age = currentYear - c1.d.anne;
    if (currentMonth < c1.d.mois || (currentMonth == c1.d.mois && currentDay < c1.d.jour)) {
        age--;
    }

    if (age < 18) {
        gotoxy(x, y++);
        printf("Vous devez avoir 18 ans ou plus.\n");
    } else {
        gotoxy(x, y++);
        printf("Vous avez %d ans.\n", age);
    }

        gotoxy(x, y++);
        printf("Donner votre lieu de naissance :\t");
        fgets(c1.lieudenaissa, sizeof(c1.lieudenaissa), stdin);
        remove_newline(c1.lieudenaissa);
      do {
    gotoxy(x, y++);
    printf("Donner le type de compte (professionel(P)/individuel(I)): \t");
    fgets(c.typecompte, sizeof(c.typecompte), stdin);
    remove_newline(c.typecompte);  // Remove the newline character if it exists

    if (c.typecompte[0] != 'P' && c.typecompte[0] != 'I') {
        gotoxy(x, y++);
        printf("Entrée invalide. Veuillez entrer 'P' pour professionnel ou 'I' pour individuel.\n");
    }
    } while (c.typecompte[0] != 'P' && c.typecompte[0] != 'I');
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
       do {
        gotoxy(x, y++);
        printf("Entrer le dépôt initial: \t ");
        scanf("%d", &c.h.montant);
        if (c.h.montant <= 100) {
        gotoxy(x, y++);
        printf("Le montant doit être supérieur à 100. Veuillez entrer un montant valide: \t ");
    }
} while (c.h.montant <= 100);

        while (getchar() != '\n'); 
        gotoxy(x,y++ );
        printf("TU PEUX SAUVEGARDER VOTRE INFORMATIONS O/N :  \t");
        scanf(" %c", &choix);
        while (getchar() != '\n');
        printf("\033[0m");
        
    } while (choix == 'N' || choix =='n');
    clear_box_content(10,5,100,20);
    int w=17,z=12;
printf("\033[0;34;40m");
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
    saisirMotDePasseMasque(&c.password);
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
    ECRIRELESCLIENTSbin(fich,c1);
    ECRIRELESCLIENTStxt(fich,c1);
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
void AFFICHAGECLIENT() {
    FILE *fich = fopen("data/clients.bin", "rb");
    if (fich == NULL) {
        perror("Error opening clients.bin for reading");
        exit(1);
    }

    client cl;
    int trv = 0;

    while (fread(&cl, sizeof(client), 1, fich)) {
       
            printf("\033[0;34;40m");
            gotoxy(22,8);
            printf("Nom complet: %s %s\n", cl.nom, cl.prenom);        
            gotoxy(22,14);
            printf("La date de naissance : %02d/%02d/%04d  A %s \n", cl.d.jour, cl.d.mois, cl.d.anne,cl.lieudenaissa);
            gotoxy(22,16);
            printf("L'address: %s\n", cl.adress);
            gotoxy(22,18);
            printf("Phone: +212 %s\n", cl.phone);
            printf("\033[0m");
  
    }

    fclose(fich);

}
void function_verment() {
    int id_transfert, id_destinataire;
    float sold_verement;
    client client_client;
    client client_destinataire;
    date date_verment;
    date date_Actuelle;

    system("color 10");
    gotoxy(2, 2);
    printf("\t");
    printf("**********************\n");
    gotoxy(2, 3);
    printf("\t");
    printf("   information : Transfert entre deux comptes de la même banque  \n");
    gotoxy(2, 4);
    printf("\t");
    printf("**********************\n");
    printf("\n");
    gotoxy(2, 5);
    printf("\t");
    printf("┌────────────────────────────────────────────────────────────────────────────┐");

    gotoxy(2, 6);
    printf("\t");
    printf("│                       ** ✉️ Vérment  **                               │");

    gotoxy(2, 7);
    printf("\t");
    printf("│                                                                            │");

    gotoxy(2, 8);
    printf("\t");
    printf("│  ▓▓▓ Entrer votre identifiant :                                            │");

    gotoxy(2, 9);
    printf("\t");
    printf("│  ▓▓▓ Entrer identifiant de destinataire  :                                 │");
    printf("\n");
    gotoxy(2, 10);
    printf("\t");
    printf("|  ▓▓▓ Entrer sold de verement :                                             |");
    printf("\n");
    gotoxy(2, 11);
    printf("\t");
    gotoxy(2, 12);
    printf("\t");
    printf("└────────────────────────────────────────────────────────────────────────────┘");
    gotoxy(5, 14);
    printf("\t");
    tim_function();

    gotoxy(48, 8);
    scanf("%d", &id_transfert);
    gotoxy(55, 9);
    scanf("%d", &id_destinataire);
    gotoxy(45, 10);
    scanf("%f", &sold_verement);

    // Ouverture des fichiers
    FILE *fichies_compt = fopen("fichiescompt.txt", "rt");
    if (fichies_compt == NULL) {
        printf("Problème dans le fichier \n");
        exit(1);
    }
    FILE *modVerment = fopen("FILEmodever.txt", "at+");
    if (modVerment == NULL) {
        printf("Problème serveur ! ");
        exit(1);
    }

    int Compt1Trouver = 0;
    int Compt3Trouver = 0;
    int soldDispo = 0;

    // Test sur le solde (est-il positif ?)
    if (sold_verement <= 0) {
        system("cls");
        gotoxy(2, 5);
        printf("┌────────────────────────────────────────────────────────────────────────────┐");

        gotoxy(2, 6);
        printf("│                     ⚠️ Le montant n'est pas convenable ⚠️                   │");

        gotoxy(2, 7);
        printf("└────────────────────────────────────────────────────────────────────────────┘");
        getch();
        system("cls");
        interface1();
    }

    // Requête des données du fichier
    while (fscanf(fichies_compt, "%d\n%s\n%f\n%d\n%d\n", &client_client.c.Ncompte, client_client.c.typecompte, &client_client.c.solde, &client_client.c.password, &client_client.idclient) == 5) {
        // Test sur les données du client (existe et solde disponible) :
        if (client_client.c.Ncompte == id_transfert) {
            Compt1Trouver++;
            if (client_client.c.solde >= sold_verement) {
                soldDispo++;
            }
        }
    }

    // Chercher le client destinataire si les conditions sont vérifiées
    if (Compt1Trouver != 0 && soldDispo != 0) {
        // Chercher le destinataire :
        while (fscanf(fichies_compt, "%d\n%s\n%f\n%d\n%d\n", &client_destinataire.c.Ncompte, client_destinataire.c.typecompte, &client_destinataire.c.solde, &client_destinataire.c.password, &client_destinataire.idclient) == 5) {
            if (client_destinataire.c.Ncompte == id_destinataire) {
                // Effectuer l'opération sur le compte : solde = solde + solde envoyé
                client_destinataire.c.solde += sold_verement;
                Compt3Trouver++;
            }
            // Modifier le solde :
            fprintf(modVerment, "%d\n%s\n%f\n%d\n%d\n", client_destinataire.c.Ncompte, client_destinataire.c.typecompte, client_destinataire.c.solde, client_destinataire.c.password, client_destinataire.idclient);
        }
    }

    fclose(modVerment);
    fclose(fichies_compt);

    // Traitement sur les fichiers pour mettre à jour les soldes
    modVerment = fopen("FILEmodever.txt", "rt");
    if (modVerment == NULL) {
        printf("Problème fichier : ");
        exit(1);
    }
    fichies_compt = fopen("fichiesNvtest.txt", "at+");
    if (fichies_compt == NULL) {
        printf("Problème d'ouverture du fichier \n");
        exit(1);
    }

    while (fscanf(modVerment, "%d\n%s\n%f\n%d\n%d\n", &client_client.c.Ncompte, client_client.c.typecompte, &client_client.c.solde, &client_client.c.password, &client_client.idclient) == 5) {
        if (client_client.c.Ncompte == id_transfert) {
            client_client.c.solde -= sold_verement;
        }
        fprintf(fichies_compt, "%d\n%s\n%f\n%d\n%d\n", client_client.c.Ncompte, client_client.c.typecompte, client_client.c.solde, client_client.c.password, client_client.idclient);
    }

    fclose(fichies_compt);

    // Si le virement a été effectué avec succès
    if (Compt1Trouver != 0 && Compt3Trouver != 0 && soldDispo != 0) {
        system("cls");
        gotoxy(2, 5);
        printf("┌────────────────────────────────────────────────────────────────────────────┐");

        gotoxy(2, 6);
        printf("│                                                                            │");

        gotoxy(2, 7);
        printf("│                ✅  VIREMENT EFFECTUÉ AVEC SUCCÈS  ✅                      │");

        gotoxy(2, 8);
        printf("│    Le montant a été transféré avec succès vers le compte destinataire      │");

        gotoxy(2, 9);
        printf("└────────────────────────────────────────────────────────────────────────────┘");

        // Si le virement est effectué, on copie les données dans l'historique
        FILE *fichies_historique = fopen("fichieshistorique.text", "at+");
        if (fichies_historique == NULL) {
            printf("L'ouverture du fichier contient des erreurs ");
            exit(1);
        }
        // Copie des données du virement dans le fichier historique
        fprintf(fichies_historique, "%d\n%d\n%d%d%d\n%s\n", id_transfert, id_destinataire, date_verment.jour, date_verment.mois, date_verment.anne, sold_verement);
    } else {
        // Gestion des erreurs si le virement n'a pas pu être effectué
        system("cls");
        gotoxy(2, 13);
        printf("* Le virement n'a pas pu être effectué. Vérifiez les données et réessayez. *\n");
        function_verment();
    }
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
            printf("\033[0;34;40m");
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
/********************************************************  */
void modifier_adress_client(FILE* fich, client cl,int id_compte) {
    char nouvelle_adresse_saisie[100];
    int N_compte_saisie;
    int trouve = 0;

    printf("Donner la nouvelle adresse : ");
    scanf(" %[^\n]%*c", nouvelle_adresse_saisie);

    fich = fopen("data/clients.bin", "rb+");
    if (fich == NULL) {
        perror("Erreur lors de l'ouverture du fichier clients.bin");
        exit(1);
    }

    while (fread(&cl, sizeof(client), 1, fich)) {
        if (cl.c.Ncompte == id_compte) {
            trouve = 1;
            strcpy(cl.adress, nouvelle_adresse_saisie);
            fseek(fich, -sizeof(client), SEEK_CUR); // Revenir en arrière pour remplacer
            fwrite(&cl, sizeof(client), 1, fich);
            break;
        }
    }

    fclose(fich);

    if (!trouve) {
        printf("Client non trouvé.\n");
    } else {
        NOTIFICATION("Adresse modifiée avec succès.",0);
        getch();
    }
    MODIFIERCLIENT(fich,cl,id_compte);
}
void modifier_client_telephone(FILE* fich, client cl,int id_compte) {
    char nouvelle_telephone_saisie[20];
    int N_compte_saisie;
    int trouve = 0;

    printf("Donner le nouveau numéro de téléphone : ");
    scanf("%s", nouvelle_telephone_saisie);

    fich = fopen("data/clients.bin", "rb+");
    if (fich == NULL) {
        perror("Erreur lors de l'ouverture du fichier clients.bin");
        exit(1);
    }

    while (fread(&cl, sizeof(client), 1, fich)) {
        if (cl.c.Ncompte == id_compte) {
            trouve = 1;
            strcpy(cl.phone, nouvelle_telephone_saisie);
            fseek(fich, -sizeof(client), SEEK_CUR); // Revenir en arrière pour remplacer
            fwrite(&cl, sizeof(client), 1, fich);
            break;
        }
    }

    fclose(fich);

    if (!trouve) {
        printf("Client non trouvé.\n");
    } else {
        NOTIFICATION("Téléphone modifié avec succès.",0);
getch();
    }
    MODIFIERCLIENT(fich,cl,id_compte);
}
void MODIFIERCLIENT(FILE* fich,client cl,int id_compte){
    fich = fopen("clients.txt", "r");
    if (fich == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }
int choix=0;
AFFICHAGECLIENT();
do{

printf("MODIFIER CLIENT\n");
printf("1- modifier l'adresse .\n");
printf("2- modifier le numero .\n");
printf("3-retourner  .\n");
printf("donner votre choix : ");
scanf("%d",&choix);
switch (choix)
{
case 1:
    system("cls");
    modifier_adress_client(fich,cl,id_compte);
    break;
case 2 :
system("cls");
modifier_client_telephone(fich,cl,id_compte);
break;
case 3: 
system("cls");
PAGEPROFIL(fich,id_compte);
break;
default:
    break;
}
}while(choix==0);
   
fclose(fich);

}
//

void CHANGER_MOTDEPASSE(int numcompte) {
    int nouveau_mdp_saisie;
    int trouve = 0;
    trouve=verification_mdp();
    if(trouve==1){
    printf("Donner le nouveau mot de passe (4 chiffres) : \t");
    scanf("%4d", &nouveau_mdp_saisie);
    }
     FILE *fichier = fopen("comptes.txt", "r+"); // Open file for reading and writing
    client cl;
    trouve = 0;

    if (!fichier) {
        perror("Erreur d'ouverture du fichier");
        return 0; // Failure
    }

    long position = 0; // To track the position in the file
    char buffer[256]; // Buffer to store the new line

    while (fscanf(fichier, "%d%s%s%d/%d/%d%s%d%d%d\n",
                  &cl.c.Ncompte, cl.nom, cl.prenom,
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne,
                  cl.c.typecompte, &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) {
        if (cl.c.Ncompte == numcompte) {
            // Update password
            cl.c.password= nouveau_mdp_saisie;
            trouve = 1;

            // Move file pointer back to overwrite the current line
            fseek(fichier, position, SEEK_SET);

            // Format the new record into a buffer
            int newLength = snprintf(buffer, sizeof(buffer), "%d %s %s %d/%d/%d %s %d %d %d\n",
                                      cl.c.Ncompte, cl.nom, cl.prenom,
                                      cl.c.dcreation.jour, cl.c.dcreation.mois, cl.c.dcreation.anne,
                                      cl.c.typecompte, cl.c.solde, cl.c.password, cl.c.h.idhistorique);

            // Get the length of the original line
            int oldLength = ftell(fichier) - position;

            // Ensure the new line is exactly the same length as the old line
            if (newLength < oldLength) {
                memset(buffer + newLength, ' ', oldLength - newLength); // Pad with spaces
                buffer[oldLength] = '\0'; // Null-terminate the padded line
            }

            // Write the new record
            fprintf(fichier, "%s", buffer);

            break; // Exit loop after finding and updating the account
        }
        // Update position to the start of the next record
        position = ftell(fichier);
    }


    fclose(fichier);
    if (!trouve) {
        printf("Client non trouvé.\n");
    } else {
        printf("Mot de passe modifié avec succès.\n");
    }
    PAGEPROFIL(fichier,numcompte);
}
///lsite des operation 
void operation_liste(int numcompte){
    int choix = 0;
    FILE*fich;
        system("cls");
    
     do {
        system("cls");
        print_box_with_title(10, 5, 100, 20, "*****LES OPERATIONS*****");
        printf("\033[0;34;40m");
        gotoxy(35, 11); printf("1-le depot ..\n");
        gotoxy(35, 13); printf("2-RETRAIT.\n");
        gotoxy(35, 15); printf("3-VIREMENTS.\n");
        gotoxy(35, 17); printf("4-QUITTER L'APPLICATION.\n");

        gotoxy(35, 19); printf("Donner votre choix : \t");
        gotoxy(10, 25);
        tim_function();
        gotoxy(35+strlen("Donner votre choix : "),19);
        scanf("%d",&choix);
      switch (choix)
    {
    case 1:
    system("cls");
        depot();
        break;
    case 2:
        retrait();
        break;
    case 3 : 
        function_verment();
        break;
       case 4 : 
        PAGEPROFIL(fich,numcompte);
        break;
    default:
        break;
    }
        printf("\033[0m");
    } while (choix != 3);      
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
    printf("\033[0;34;40m");

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
        MODIFIERCLIENT(fich,cl,id_compte);
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
        printf("\033[0;34;40m");
        gotoxy(35, 11); printf("1-SIGN IN.\n");
        gotoxy(35, 13); printf("2-LOGIN.\n");
        gotoxy(35, 15); printf("3-ADMIN.\n");
        gotoxy(35, 17); printf("4-QUITTER L'APPLICATION.\n");

        gotoxy(35, 19); printf("Donner votre choix : \t");
        gotoxy(10, 25);
        tim_function();
        gotoxy(35+strlen("Donner votre choix : "),19);
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
                LOGINADMIN();
                break;
            case 4:
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

    system("color 01");
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

    system("color 01");
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
// calculer le solde 
int calculer_solde(int numcompte, int montant, int numop) {
    FILE *fich = fopen("comptes.txt", "r");
    if (!fich) {
        printf("Erreur d'ouverture du fichier.\n");
        return -1; // Indicate an error
    }

    client cl;
    while (fscanf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n", 
                  &cl.c.Ncompte, cl.nom, cl.prenom, &cl.c.dcreation.jour, 
                  &cl.c.dcreation.mois, &cl.c.dcreation.anne, cl.c.typecompte, 
                  &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) {
        
        if (cl.c.Ncompte == numcompte) {
            fclose(fich);
            if (numop == 1) return cl.c.solde - montant; // Retrait
            if (numop == 0) return cl.c.solde + montant; // Dépôt
        }
    }

    fclose(fich);
    printf("Compte avec le numéro %d non trouvé.\n", numcompte);
    return -1; // Indicate that the account was not found
}
int modifierSolde(int idCompte, int nouveauSolde) {
    FILE *fichier = fopen("comptes.txt", "r+"); // Open file for reading and writing
    client cl;
    int trouve = 0;

    if (!fichier) {
        perror("Erreur d'ouverture du fichier");
        return 0; // Failure
    }

    long position = 0; // To track the position in the file
    char buffer[256]; // Buffer to store the new line

    while (fscanf(fichier, "%d%s%s%d/%d/%d%s%d%d%d\n",
                  &cl.c.Ncompte, cl.nom, cl.prenom,
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne,
                  cl.c.typecompte, &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) {
        if (cl.c.Ncompte == idCompte) {
            // Update solde
            cl.c.solde = nouveauSolde;
            trouve = 1;

            // Move file pointer back to overwrite the current line
            fseek(fichier, position, SEEK_SET);

            // Format the new record into a buffer
            int newLength = snprintf(buffer, sizeof(buffer), "%d %s %s %d/%d/%d %s %d %d %d\n",
                                      cl.c.Ncompte, cl.nom, cl.prenom,
                                      cl.c.dcreation.jour, cl.c.dcreation.mois, cl.c.dcreation.anne,
                                      cl.c.typecompte, cl.c.solde, cl.c.password, cl.c.h.idhistorique);

            // Get the length of the original line
            int oldLength = ftell(fichier) - position;

            // Ensure the new line is exactly the same length as the old line
            if (newLength < oldLength) {
                memset(buffer + newLength, ' ', oldLength - newLength); // Pad with spaces
                buffer[oldLength] = '\0'; // Null-terminate the padded line
            }

            // Write the new record
            fprintf(fichier, "%s", buffer);

            break; // Exit loop after finding and updating the account
        }
        // Update position to the start of the next record
        position = ftell(fichier);
    }

    fclose(fichier);

    if (trouve) {
        printf("Mise à jour réussie.\n");
        return 1; // Success
    } else {
        printf("Compte non trouvé.\n");
        return 0; // Account not found
    }
}

void depot() {
    int idEntrer, soldEAjouter, solde;

    printf("Enter Account ID: ");
    scanf("%d", &idEntrer);

    if (verification(idEntrer) == 0) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Amount to Deposit: ");
    scanf("%d", &soldEAjouter);

    if (soldEAjouter <= 0) {
        printf("Error: Deposit amount must be positive.\n");
        return;
    }

    solde = calculer_solde(idEntrer, soldEAjouter, 0);
    if (solde == -1) {
        printf("Error: Account not found or calculation error.\n");
        return;
    }

    if (!modifierSolde(idEntrer, solde)) {
        printf("Error updating the account file.\n");
        return;
    }

    // Record in history
    FILE *fichier_historique = fopen("historique.txt", "a+");
    if (!fichier_historique) {
        printf("Error opening history file.\n");
        return;
    }

    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    fprintf(fichier_historique, "%-12d | %-11s | %-12d | %02d/%02d/%04d | %d\n",
            retourner_idhistori(idEntrer), "deposit", soldEAjouter,
            local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900, solde);
    fclose(fichier_historique);

    printf("✅ Deposit successful. New balance: %d\n", solde);
}
 void retrait() {
    int idEntrer, montantRetirer, solde;

    printf("Enter Account ID: ");
    scanf("%d", &idEntrer);

    if (verification(idEntrer) == 0) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter Amount to Withdraw: ");
    scanf("%d", &montantRetirer);

    if (montantRetirer <= 0) {
        printf("Error: Withdrawal amount must be positive.\n");
        return;
    }

    solde = calculer_solde(idEntrer, montantRetirer, 1);
    if (solde == -1) {
        printf("Error: Insufficient balance or account not found.\n");
        return;
    }

    if (!modifierSolde(idEntrer, solde)) {
        printf("Error updating the account file.\n");
        return;
    }

    // Record in history
    FILE *fichier_historique = fopen("historique.txt", "a+");
    if (!fichier_historique) {
        printf("Error opening history file.\n");
        return;
    }

    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    fprintf(fichier_historique, "%-12d | %-11s | %-12d | %02d/%02d/%04d | %d\n",
            retourner_idhistori(idEntrer), "withdraw", montantRetirer,
            local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900, solde);
    fclose(fichier_historique);

    printf("✅ Withdrawal successful. New balance: %d\n", solde);
}


/******* AUTONTIFICATION ADMIN *********/
int authentificationAdmin( int pswd_saisie) {
    FILE *fich;
    int password_Admin ; 
    int variable_trouver = 0 ; 
    fich = fopen("data/admin/Fadmin.txt" , "r"); 
    if(fich == NULL){
        printf("fichies contient une problemme d'ouverture "); 
        exit(1); 
    }

    // comparer les element // ==> si le password trouver donc la fonction return 1 sinon return 0 . 
    while (fscanf(fich , "%d\n" ,&password_Admin) ==1)
    {
        if(pswd_saisie == password_Admin){
            variable_trouver ++ ; 
        }
    }
    fclose(fich); 
    
    if(variable_trouver != 0){
        return variable_trouver ; 
    }
    else{
        return 0 ; 
    }
}
void LOGINADMIN(){
    int  passwordadmin;
    FILE* fich;
    print_box_with_title(10,5,100,20,"**LOGIN-ADMIIN**");
    printf("\033[0;34;40m");
    gotoxy(35,15);
    printf("Donner le mot de passe  (4 chiffres) : ");
    gotoxy(10, 25);
    tim_function();

    gotoxy(35 + strlen("Donner le mot de passe (4 chiffres) : "), 15);  // Placer le curseur juste apres Donner le mot de passe (4 chiffres) : 
    saisirMotDePasseMasque(&passwordadmin);  

    // Authentification
    // autofication pour fihcies admin : 
    int trouver =authentificationAdmin(passwordadmin); 
    
    if (trouver != 0 ) {
        // Connexion réussie
        
        NOTIFICATION("✅ CONNEXION RÉUSSIE",0);
        getch();
        // fonction menu admin pour les operation admin . 
        MENUE_ADMIN(); 
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
                LOGINADMIN(); 
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
void MENUE_ADMIN(){

    int choix = 0 ; 

    print_box_with_title(10,5,100,20,"**MENUE_ADMIN**");
   printf("\033[0;34;40m");
    gotoxy(35,11);
    printf("1-affichage de compte  ");
    gotoxy(35,15);
    printf("2-affichage de client ");
    gotoxy(35 , 17); 
    printf("3-affichage historique .  "); // choix pour entrer :
    gotoxy(35 , 19); 
    printf("4_Activite Et transaction : "); 
    gotoxy(35 , 21); 
    printf("Choix : "); 
    gotoxy(10, 25);
    tim_function();

    // Saisie des informations de connexion
    gotoxy(45,21); 
    scanf("%d",&choix); 
    getch(); 

    // switch : 
    switch (choix)
    {
    case 1 : 
        system("cls"); 
        // fonction AFichage information sur compt compt  . 
        AFichageCOMPt(); 

        break;
    case 2 : 
        system("cls"); 
        // Afichage client :  
        AFICHaclient(); 
        break; 
    case 3: 
        system("cls"); 
        // afichage historique : 
        break; 
     case 4 : 
        system("cls"); 
        // fonction activite : 
        break; 
    default:
        // retour au page initiale . 
        exit(1) ; // exite aplication . 
        break;
    }
}
void AFichageCOMPt() {
    FILE *fich;
    client cl; // Une variable pour stocker les informations de chaque compte

    // Ouvrir le fichier en mode lecture
    fich = fopen("comptes.txt", "r");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier Comp.text\n");
        exit(1); // Arrêter l'exécution en cas d'erreur
    }

    // backgroud d'afichage est en blan 
    system("color 01"); 

    // Titre de l'affichage
    printf("\n");
    printf("┌────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                        Liste des Comptes                               │\n");
    printf("└────────────────────────────────────────────────────────────────────────┘\n");
    printf("\n");

    // Affichage de l'entête
    printf("ID Compte   | Type Compte    | Solde      | Mot de Passe | ID Historique | DATE DE CREATION\n");
    printf("-----------------------------------------------------------------------------------------\n");


    // Lecture et affichage des données de chaque compte
      while (fscanf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n", &cl.c.Ncompte, cl.nom, cl.prenom, 
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne, cl.c.typecompte,
                  &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) { // ID historique associé au compte
    
        // Affichage des informations du compte avec une mise en forme verticale
        printf("%-12d| %-13s | %-8d | %-12d | %-15d | %d/%d/%d\n",cl.c.Ncompte,cl.c.typecompte,cl.c.solde,cl.c.password, cl.c.h.idhistorique,cl.c.dcreation.jour, cl.c.dcreation.mois, cl.c.dcreation.anne);
    }

    // Fermer le fichier
    fclose(fich);
    getchar();
    MENUE_ADMIN();
}
void AFICHaclient(){
    FILE *fich ; 
    client c ; 
    // afichage des information du client : 
    fich = fopen("data/clients.bin","r"); 
    if(fich == NULL){
        printf("problemme dans le fichies "); 
        exit(1); 
    }
    
    system("color 01");
    while (fscanf(fich, "%d %s %s %s %c %s %s %s %d-%d-%d", 
                &c.idclient, c.CIN, c.nom, c.prenom, &c.sexe, c.adress, c.phone, c.lieudenaissa, 
                &c.d.jour, &c.d.mois, &c.d.anne) == 11) {
        
        printf("\n");
        printf("┌────────────────────────────────────────────────────────────────────────┐\n");
        printf("│                         Détails du Client                              │\n");
        printf("└────────────────────────────────────────────────────────────────────────┘\n");
        printf("\n");

        // Affichage des informations du client avec mise en forme
        printf("ID Client        : %-20d\n", c.idclient);
        printf("CIN              : %-20s\n", c.CIN);
        printf("Nom              : %-20s\n", c.nom);
        printf("Prénom           : %-20s\n", c.prenom);
        printf("Sexe             : %-20c\n", c.sexe);
        printf("Adresse          : %-20s\n", c.adress);
        printf("Téléphone        : %-20s\n", c.phone);
        printf("Lieu de Naissance: %-20s\n", c.lieudenaissa);
        printf("Date de Naissance: %02d-%02d-%04d\n", c.d.jour, c.d.mois, c.d.anne);
        printf("\033[0m");
    }
    getchar();
    MENUE_ADMIN();
}
void movingBanner(const char *text) {
    if (!text) {
        fprintf(stderr, "Invalid input to movingBanner.\n");
        return;
    }

    int textLen = strlen(text);
    if (textLen == 0) {
        fprintf(stderr, "Text length must be greater than zero.\n");
        return;
    }

    char display[81] = {0}; // Assume terminal width is 80 characters + null terminator

    // Animate the text across the terminal width
    for (int pos = 0; pos < textLen + 80; pos++) {
        memset(display, ' ', 80); // Clear the display array with spaces

        // Fill the display array dynamically based on position
        for (int i = 0; i < 80; i++) {
            int index = (pos + i) % textLen; // Circular indexing
            display[i] = text[index]; // Use the original text
        }

        printf("\r\033[1;33m%s\033[0m", display); // Bright yellow text
        fflush(stdout);
        usleep(100000); // Delay for smooth animation
    }

    // Add a symbol at the end of the line
    printf("\r\033[1;33m%s █\033[0m\n", display);
}
void drawLetterD(int x, int y) {
    gotoxy(x, y);     printf("█████  ");
    gotoxy(x, y + 1); printf("█    █ ");
    gotoxy(x, y + 2); printf("█     █");
    gotoxy(x, y + 3); printf("█    █ ");
    gotoxy(x, y + 4); printf("█████  ");
}

void drawLetterI(int x, int y) {
    gotoxy(x, y);     printf(" ███ ");
    gotoxy(x, y + 1); printf("  █  ");
    gotoxy(x, y + 2); printf("  █  ");
    gotoxy(x, y + 3); printf("  █  ");
    gotoxy(x, y + 4); printf(" ███ ");
}

void drawLetterG(int x, int y) {
    gotoxy(x, y);     printf(" █████");
    gotoxy(x, y + 1); printf("█     ");
    gotoxy(x, y + 2); printf("█  ███");
    gotoxy(x, y + 3); printf("█    █");
    gotoxy(x, y + 4); printf(" █████");
}

void drawLetterT(int x, int y) {
    gotoxy(x, y);     printf("███████");
    gotoxy(x, y + 1); printf("   █   ");
    gotoxy(x, y + 2); printf("   █   ");
    gotoxy(x, y + 3); printf("   █   ");
    gotoxy(x, y + 4); printf("   █   ");
}

void drawLetterA(int x, int y) {
    gotoxy(x, y);     printf("   █   ");
    gotoxy(x, y + 1); printf("  █ █  ");
    gotoxy(x, y + 2); printf(" █   █ ");
    gotoxy(x, y + 3); printf("███████");
    gotoxy(x, y + 4); printf("█     █");
}

void drawLetterL(int x, int y) {
    gotoxy(x, y);     printf("█      ");
    gotoxy(x, y + 1); printf("█      ");
    gotoxy(x, y + 2); printf("█      ");
    gotoxy(x, y + 3); printf("█      ");
    gotoxy(x, y + 4); printf("██████ ");
}

void drawLetterB(int x, int y) {
    gotoxy(x, y);     printf("█████  ");
    gotoxy(x, y + 1); printf("█    █ ");
    gotoxy(x, y + 2); printf("█████  ");
    gotoxy(x, y + 3); printf("█    █ ");
    gotoxy(x, y + 4); printf("█████  ");
}

void drawLetterN(int x, int y) {
    gotoxy(x, y);     printf("█    █ ");
    gotoxy(x, y + 1); printf("██   █ ");
    gotoxy(x, y + 2); printf("█ █  █ ");
    gotoxy(x, y + 3); printf("█  █ █ ");
    gotoxy(x, y + 4); printf("█   ██ ");
}

void drawLetterK(int x, int y) {
    gotoxy(x, y);     printf("█   █ ");
    gotoxy(x, y + 1); printf("█  █  ");
    gotoxy(x, y + 2); printf("████  ");
    gotoxy(x, y + 3); printf("█  █  ");
    gotoxy(x, y + 4); printf("█   █ ");
}

void drawText() {
    int x = 2, y = 2;

    drawLetterD(x, y);
    drawLetterI(x + 8, y);
    drawLetterG(x + 14, y);
    drawLetterI(x + 22, y);
    drawLetterT(x + 28, y);
    drawLetterA(x + 36, y);
    drawLetterL(x + 44, y);

    drawLetterB(x, y + 6);
    drawLetterA(x + 8, y + 6);
    drawLetterN(x + 16, y + 6);
    drawLetterK(x + 24, y + 6);
}
int main() {
    setlocale(LC_ALL, "fr_FR.UTF-8");  
    SetConsoleOutputCP(65001);
    system("COLOR 01");
    system("cls");
   /*int data[] = {5, 10, 7, 12, 8};
    displayBarGraph(data, 5);
    progressBar();
   */

    hideCursor();
    movingBanner("BANK DIGITAL ");
    drawText();
    sleep(5000);
    interface1();
    

    afficher_menu();    
}