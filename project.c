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
typedef struct 
{
    char Nomentreprise[20] ; 
    int Code_iDentifant ; 
    char adresentreprise[20] ; 
    char type_entreprise[20]; 
}Entreprise ; 
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

        // If Enter is pressed, exit the loop
        if (ch == 13) {
            break;
        }
        // If Backspace is pressed, remove the last digit and erase the character
        else if (ch == 8) {
            if (i > 0) {
                i--;
                *passwordadmin /= 10;  // Remove the last digit
                printf("\b \b");  // Erase last character (asterisk)
            }
        }
        // If a digit is entered, add it to the password
        else if (ch >= '0' && ch <= '9') {
            *passwordadmin = *passwordadmin * 10 + (ch - '0');  // Add digit to password
            i++;
            printf("*");  // Mask the character by printing an asterisk
        }

        // If more than 4 digits are entered, show a message and reject the input
        if (i > 4) {
            gotoxy(10, 15);  // Adjust the position of the message
            printf("Le mot de passe doit contenir exactement 4 chiffres.\n");
            *passwordadmin = 0;  // Reset the password
            i = 0;  // Reset the digit count
            printf("\n");
            printf("Entrez à nouveau le mot de passe (4 chiffres): ");
        }
    }
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


// Function to print a box with "██" borders and centered title
void print_box_with_title(int x, int y, int width, int height, const char *title) {
    int title_length = strlen(title);
    int title_padding = (width - title_length - 4) / 2; // Adjust for centering

    setConsoleColor(15, 1); // White text on blue background

    // Top Border with Title
    gotoxy(x, y);
    printf("██"); // Top-left corner (double)
    for (int i = 0; i < width - 4; i++) { // Adjust width for corners
        if (i == title_padding) { 
            printf(" %s ", title); // Title with spaces around it
            i += title_length + 1;
        } else {
            printf("█");
        }
    }
    printf("██"); // Top-right corner (double)

    // Middle Part of the Box
    for (int i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("██"); // Left border (double)
        for (int j = 0; j < width - 4; j++) {
            printf(" "); // Empty space inside
        }
        printf("██"); // Right border (double)
    }

    // Bottom Border
    gotoxy(x, y + height - 1);
    printf("██"); // Bottom-left corner (double)
    for (int i = 0; i < width - 4; i++) { // Adjust width for corners
        printf("█");
    }
    printf("██"); // Bottom-right corner (double)

    setConsoleColor(15, 0); // Reset to white text on black background
}

// Function to print a box with "██" borders and centered title
void setConsoleColor(int textColor, int backgroundColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor * 16 + textColor);
}

// Loading Screen Function
void loadingScreen() {
    setConsoleColor(15, 1); // White text on Blue background

    int barLength = 35;     // Length of the loading bar
    char block = 219;       // Block character "█"

    // Display the loading text
    gotoxy(40, 11);
    printf(".......EN COURS.......");

    // Draw the empty progress bar
    gotoxy(40, 12);
    for (int i = 0; i < barLength; i++) {
        printf(" "); // Spaces with blue background
    }

    // Fill the progress bar
    for (int j = 0; j <= barLength; j++) {
        // Draw the progress bar
        gotoxy(40 + j, 12);
        printf("%c", block);

        // Display the percentage at the end of the bar
        gotoxy(40 + barLength + 2, 12);
        printf("%d%%", (j * 100) / barLength);

        Sleep(50); // Adjust the speed of loading
    }

    // Final Message
    setConsoleColor(15, 1); // Maintain theme
    gotoxy(40, 14);
    printf("Chargement termine avec succes!");

    // Reset console to default settings
    setConsoleColor(15, 0); // White text on black background
    gotoxy(0, 20); // Reset cursor position
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


void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15 | (1 << 4)); // 15 = White text, 1 << 4 = Blue background
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
    movingBanner("DIGITAL BANK");
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
    fich = fopen("data/clients.txt", "a+");
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
    fich = fopen("data/comptes.txt", "a+");
    if (fich == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }


   fprintf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n",
            cl.c.Ncompte, cl.nom, cl.prenom, c.dcreation.jour, c.dcreation.mois, c.dcreation.anne,c.typecompte, c.solde,c.password,c.h.idhistorique);
    fclose(fich);

}
void ECRIRELESHISTORIQUE(FILE *fich,compte c) {
    fich = fopen("data/historique.txt", "a+");
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

    fich = fopen("data/clients.txt", "r");
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
    
    fich = fopen("data/comptes.txt", "r");
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
    setConsoleColor(15,1);
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
            SesionAdmin(idCompt_search,"Login");
        NOTIFICATION("CONNEXION RÉUSSIE",0);
        getch();
        PAGEPROFIL(fich,idCompt_search);
    } else {
        // Connexion échouée
        int choix = 0;
        system("cls");        
        NOTIFICATION("❌Erreur système ❌",0);
        getch();
        system("cls");
        NOTIFICATION(" Numéro de compte ou mot de passe incorrect ",0);
        print_box(10,5,100,20);
        gotoxy(35,11);printf("1-CONNEXION .");
        gotoxy(35,15);printf("2-Retourner  au menu ");
        gotoxy(35,17);printf("Donner votre choix : ");
        gotoxy(35+strlen("Donner votre choix : "), 17);
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

    fich = fopen("data/comptes.txt", "r");
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

int verification(int numcompte) {

 FILE *fich = fopen("data/comptes.txt", "r");
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
//*****************************************************************************creation de compte *********************************************************************************** */
void interfece2() {
    clear_screen();
    
   FILE*fich;
         print_box_with_title(10, 5, 100, 20, "*** Offres de la Banque ***");
    int x = 12, y = 5;
    setConsoleColor(15, 1);

    // Professionnel and Individuel on the same line
    gotoxy(x + 8, y + 3);
    printf("*** Offres Pro *** ");

    // Professionnel offers
    gotoxy(x + 2, y + 4); 
    printf("1. Comptes Pro: Adapté à votre entreprise.\n");
    gotoxy(x + 2, y + 5);
    printf("2. Épargne Pro: Taux compétitifs.\n");
    gotoxy(x + 2, y + 6);
    printf("3. Prêts Pro: Financement flexible.\n");
    gotoxy(x + 2, y + 7);
    printf("4. Services Marchands: Solutions de paiement.\n");
    gotoxy(x + 2, y + 8);
    printf("5. Paie Pro: Automatisée.\n");
    gotoxy(x + 2, y + 9);
    printf("6. Plan Financier: Stratégie pour entreprises.\n");

    // Individuel offers
    gotoxy(x + 55, y + 3);printf("*** Offres Indivi *** ");
    gotoxy(x + 50, y + 4); // Move to the right for Individual offers
    printf("1. Comptes Perso: Frais réduits.\n");
    gotoxy(x + 50, y + 5);
    printf("2. Épargne Perso: Taux élevés.\n");
    gotoxy(x + 50, y + 6);
    printf("3. Prêts Perso: Taux compétitifs.\n");
    gotoxy(x + 50, y + 7);
    printf("4. Cartes de Crédit: Cashback, récompenses.\n");
    gotoxy(x + 50, y + 8);
    printf("5. Investissements: Plans personnalisés.\n");
    gotoxy(x + 50, y + 9);
    printf("6. Prêts Auto & Immo: Financement flexible.\n");

     // Bottom box for choice: Continue or Back
    int box_x = 10, box_y = 17;
    print_box_with_title(box_x, box_y, 100, 7, "*** Choisissez une option ***");
    gotoxy(box_x + 32, box_y + 2);
    setConsoleColor(15,1);
    printf("1. Continuer\n");
    gotoxy(box_x + 32, box_y + 3);
    printf("2. Retour\n");

    int choice;
    do {
        gotoxy(box_x + 2, box_y + 4);  // Move the cursor to the prompt position
        choice = getch(); // Wait for user input

        if (choice == '1') {
            SIGNIN(fich);
            break;  // Exit the loop and continue
        } else if (choice == '2') {
           afficher_menu();
            break;  // Exit the loop and go back
        } else {
            // Handle invalid input
            printf("\nChoix invalide, veuillez entrer 1 pour continuer ou 2 pour revenir.\n");
        }
    } while (choice != '1' && choice != '2');
    
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
        setConsoleColor(15,1);
        //printf("\033[0;34;40m");
         x+=3;y+=2;
        gotoxy(x+4, y++);
        printf(" ATTENTION : VOUS ÊTES RESPONSABLE DE CHAQUE ERREUR DANS VOS INFORMATIONS.");
        getch();
        gotoxy(x, y++);
        printf("Donner votre nom:  \t ");
        fgets(c1.nom, sizeof(c1.nom), stdin);
        remove_newline(c1.nom);
        
        gotoxy(x, y++);
        printf("Donner votre prenom: \t");
        fgets(c1.prenom, sizeof(c1.prenom), stdin);
        remove_newline(c1.prenom);
       
       
 do {
        gotoxy(x, y++);
        printf("Donner votre sexe ( Homme:H / Femme:F): \t");
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
    } 

        gotoxy(x, y++);
        printf("Donner votre lieu de naissance :\t");
        fgets(c1.lieudenaissa, sizeof(c1.lieudenaissa), stdin);
        remove_newline(c1.lieudenaissa);
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
        printf("Donner le type de compte (professionel(P)/individuel(I)): \t");
        fgets(c.typecompte, sizeof(c.typecompte), stdin);
        remove_newline(c.typecompte); 

         if (c.typecompte[0] != 'P' && c.typecompte[0] != 'I') {
        gotoxy(x, y++);
        printf("Entrée invalide. Veuillez entrer 'P' pour professionnel ou 'I' pour individuel.\n");
         }



        } while (c.typecompte[0] != 'P' && c.typecompte[0] != 'I');
        while (getchar() != '\n'); 
          do {
        gotoxy(x, y++);
        printf("Entrer le dépôt initial: \t ");
        scanf("%d", &c.h.montant);
        if (c.h.montant <= 100) {
        gotoxy(x, y++);
        printf("Le montant doit être supérieur à 100. Veuillez entrer un montant valide: \t ");
    }   
    } while (c.h.montant <= 100);
        gotoxy(x,y++ );
         printf("TU PEUX SAUVEGARDER VOTRE INFORMATIONS O/N :  \t");
        scanf(" %c", &choix);
    while (getchar() != '\n'); // Clear input buffer

    // Convert input to uppercase for consistent comparison
    choix = toupper(choix);

    if (choix != 'O' && choix != 'N') {
        printf("Choix invalide. Veuillez entrer 'O' pour Oui ou 'N' pour Non.\n");
    }   
    } while (choix != 'O' && choix != 'N');
    
    if(c.typecompte[0] == 'P'){
        sizezProfesionelle(c1);

    }     
    clear_box_content(10,5,100,20);
    print_box_with_title(10,5,100,20,"***sign in***");
    int w=17,z=12;
    do
    {
        gotoxy(w,z++ );
        setConsoleColor(15,1);
    printf("TU peux donner le numero de compte  (5 chiffres) :  ");
    scanf("%5d", &c1.c.Ncompte);
    if(verification(c1.c.Ncompte)==1){
        gotoxy(w,z++);
        printf("NUMERO DE COMPTE DEJA EXISITE .\n");
    }
   

    } while (verification(c1.c.Ncompte)==1);
    do {
        gotoxy(w, z++);
        printf("Tu peux donner le mot de passe (4 chiffres max): ");
        saisirMotDePasseMasque(&c.password);  // Masked password input
        printf("\n");

        // Check if password is 4 digits long
        if (c.password < 1000 || c.password > 9999) {  // Check if password is not 4 digits
            gotoxy(w, z++);
            printf("Le mot de passe doit contenir exactement 4 chiffres.\n");
        }
    } while (c.password < 1000 || c.password > 9999);  
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
    c.h.typeoperation="d.initial";
    ECRIRELESCLIENTSbin(fich,c1);
    ECRIRELESCLIENTStxt(fich,c1);
    ECRIRELESCOMPTES(fich,c,c1);
    ECRIRELESHISTORIQUE(fich,c);
    setConsoleColor(15,10);
    NOTIFICATION("  Ton compte a ete enregistre avec succes.  ",0);
    getch();
    resetColor();
    afficher_menu();
}

void afficher_compte(int numcompte, int trv) {
    FILE *fich = fopen("data/comptes.txt", "r");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier.\n");
        return;
    }
    client cl;
    
    int trvw=0;
    while (fscanf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n", &cl.c.Ncompte, cl.nom, cl.prenom, 
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne, cl.c.typecompte, 
                  &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) {
        if (cl.c.Ncompte == numcompte) {
            if(trv==0){
            setConsoleColor(15,1);
            gotoxy(20,7); 
            printf("╔═════════════════════════════════╗");
            gotoxy(20 , 8); 
            printf("║                                 ║ ");
            gotoxy(20 , 9);  
            printf("╚═════════════════════════════════╝");
            gotoxy(21 , 8);printf("Compte : %d\n", cl.c.Ncompte);
            gotoxy(20,10); 
            printf("╔═════════════════════════════════╗");
            gotoxy(20 , 11); 
            printf("║                                 ║ ");
            gotoxy(20 , 12);  
            printf("╚═════════════════════════════════╝");
            gotoxy(21 , 11);printf("Nom : %s\n", cl.nom);
             gotoxy(20,13); 
            printf("╔═════════════════════════════════╗");
            gotoxy(20 , 14); 
            printf("║                                 ║ ");
            gotoxy(20 , 15);  
            printf("╚═════════════════════════════════╝");
            gotoxy(21 , 14); printf("Prénom : %s\n", cl.prenom);
              gotoxy(20,16); 
            printf("╔═════════════════════════════════╗");
            gotoxy(20 , 17); 
            printf("║                                 ║ ");
            gotoxy(20 , 18);  
            printf("╚═════════════════════════════════╝");
            gotoxy(21 , 17); printf("Type de compte : %s\n", cl.c.typecompte);
               gotoxy(20,19); 
            printf("╔═════════════════════════════════╗");
            gotoxy(20 , 20); 
            printf("║                                 ║ ");
            gotoxy(20 , 21);  
            printf("╚═════════════════════════════════╝");
            gotoxy(21 , 20);printf("Solde : %d DH\n", cl.c.solde);
            trvw=1;
            break; 
            }else if (trv==1){
                 gotoxy(35, 7);
                printf("╔════════════════════════════════════════════════════════╗");
                gotoxy(35, 8);
                printf("║                                                        ║");gotoxy(42, 8);printf("Compte : %d\n", cl.c.Ncompte);
                gotoxy(35, 9);
                printf("║                                                        ║");gotoxy(42, 9);printf("Nom : %s\n", cl.nom);
                gotoxy(35, 10);
                printf("║                                                        ║"); gotoxy(42, 10);printf("Prénom : %s\n", cl.prenom);
                gotoxy(35, 11);
                printf("║                                                        ║"); gotoxy(42, 11);printf("Type de compte : %s\n", cl.c.typecompte);
                gotoxy(35, 12);
                printf("║                                                        ║"); gotoxy(42, 12);printf("Solde : %d\n", cl.c.solde);
                gotoxy(35, 13);
                printf("║                                                        ║");gotoxy(42,13);printf("Date de creation : %d/%d/%d",cl.c.dcreation.jour, cl.c.dcreation.mois, cl.c.dcreation.anne);
                gotoxy(35, 14);
                printf("║                                                        ║");gotoxy(42, 14);printf("Solde : %d DH\n", cl.c.solde);
                gotoxy(35, 15);
                printf("╚════════════════════════════════════════════════════════╝");
                 trvw=1;
                int box_x = 10, box_y = 17;
                print_box_with_title(box_x, box_y, 100, 7, "*** Choisissez une option ***");
                gotoxy(box_x + 32, box_y + 2);
                setConsoleColor(15,1);
                printf("1. Supprimer le compte \n");
                gotoxy(box_x + 32, box_y + 3);
                printf("2. Retour\n");

                int choice;
                do {
                    gotoxy(box_x + 2, box_y + 4);  // Move the cursor to the prompt position
                    choice = getch(); // Wait for user input

                    if (choice == '1') {
                        fermer_comptes(numcompte);
                        break;  // Exit the loop and continue
                    } else if (choice == '2') {
                         MENUE_ADMIN();
                        break;  // Exit the loop and go back
                    } else {
                        // Handle invalid input
                        printf("\nChoix invalide, veuillez entrer 1 pour continuer ou 2 pour revenir.\n");
                    }
                } while (choice != '1' && choice != '2');
                 trvw=1;
            }
          
        }
    }

    if (!trvw) {
        printf("Compte avec le numéro %d non trouvé.\n", numcompte);
    }
    fclose(fich);
}
void affichageclient(int id_compte){
      // Display all client information
    FILE *fich = fopen("data/clients.bin", "rb");
    if (fich == NULL) {
        perror("Error opening clients.bin for reading");
        exit(1);
    }
     client cl;
    while (fread(&cl, sizeof(client), 1, fich)) {
       
       if(cl.c.Ncompte==id_compte){

            gotoxy(22,8);
             setConsoleColor(15,1);
            printf("Nom complet: %s %s\n", cl.nom, cl.prenom);        
            gotoxy(22,14);
            printf("La date de naissance : %02d/%02d/%04d  A %s \n", cl.d.jour, cl.d.mois, cl.d.anne,cl.lieudenaissa);
            gotoxy(22,16);
            printf("L'address: %s\n", cl.adress);
            gotoxy(22,18);
            printf("Phone: +212 %s\n", cl.phone);
       }
    }
    fclose(fich);
}
/********************************************************  */
void modifier_adress_client(FILE* fich, client cl,int id_compte) {
    char nouvelle_adresse_saisie[100];
    int mdp_saisie;
    int trouve = 0;
    print_box_with_title(10,5,100,20,"modification adresse");
    setConsoleColor(15,1);
    gotoxy(35,12);
    printf("Donner la nouvelle adresse : ");
    scanf(" %[^\n]%*c", nouvelle_adresse_saisie);
    gotoxy(35,14);
    printf("donner le mot de passe pour la confirmation : \t");
    saisirMotDePasseMasque(&mdp_saisie);
    if (authentification(id_compte,mdp_saisie)==1){
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

    }

    if (!trouve) {
        
        printf("Client non trouvé.\n");
    } else {
         setConsoleColor(15,10);
        SesionAdmin(id_compte,"modifier l'adresse");
        NOTIFICATION("Adresse modifiée avec succès.",0);
        resetColor();
        getch();
        clear_screen();
    }
    
    MODIFIERCLIENT(fich,cl,id_compte);
}
void modifier_client_telephone(FILE* fich, client cl,int id_compte) {
    char nouvelle_telephone_saisie[20];
    int mdp_saisie;
    int trouve = 0;
    print_box_with_title(10,5,100,20,"modification telephone ");
    gotoxy(35,12);
            setConsoleColor(15,1);
    printf("Donner le nouveau numéro de téléphone : ");
    scanf("%s", nouvelle_telephone_saisie);
    gotoxy(35,14);
    printf("donner le mot de passe pour la confirmation : \t");
    saisirMotDePasseMasque(&mdp_saisie);
    if (authentification(id_compte,mdp_saisie)==1){
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

    }

  
    if (!trouve) {
        printf("Client non trouvé.\n");
    } else {
        setConsoleColor(7,2);
         SesionAdmin(id_compte,"modifier le telephone");
         setConsoleColor(15,10);
        NOTIFICATION("Téléphone modifié avec succès.",0);
        getch();
    }
    clear_screen();
   
    MODIFIERCLIENT(fich,cl,id_compte);
}
void MODIFIERCLIENT(FILE *fich, client cl, int id_compte) {

  
    int choix = 0;

    do {
        // Display modification options
        print_box_with_title(10, 5, 100, 20, "MODIFICATION CLIENT ");
        gotoxy(35,11);
        affichageclient(id_compte);
        setConsoleColor(15,1);
        gotoxy(68, 11); printf("1- Modifier l'adresse .\n");
        gotoxy(68, 13); printf("2- Modifier le numero .\n");
        gotoxy(68, 15); printf("3- Retourner .\n");
        gotoxy(68, 17); printf("Donner votre choix : \t");
        scanf("%d", &choix);

        // Handle user choice
        switch (choix) {
            case 1:
                system("cls");
                modifier_adress_client(fich, cl, id_compte); // Modify client address
                break;
            case 2:
                system("cls");
                modifier_client_telephone(fich, cl, id_compte); // Modify client phone
                break;
            case 3:
                system("cls");
                PAGEPROFIL(fich, id_compte); // Return to profile page
                break;
            default:
                gotoxy(60, 16); printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choix != 3); // Loop until the user chooses to return
}

//

void CHANGER_MOTDEPASSE(int numcompte) {
    int nouveau_mdp_saisie, nouveau_mdp_saisie1;
    int trouve = 0;
    int mdp_actuel_saisie;
    print_box_with_title(10,5,100,20,"***CHANGEMENT DE MDP***");
do
    {
         setConsoleColor(15,1);
    gotoxy(31,10); printf("Pour la confirmation : \n");
    gotoxy(31,11);printf("Donner le mot de passe actuelle   (4 chiffres) : ");
    gotoxy(31+strlen("Donner le mot de passe actuelle   (4 chiffres) : "),11);
    scanf("%d", &mdp_actuel_saisie);
    } while (authentification(numcompte,mdp_actuel_saisie)==0);

    trouve=authentification(numcompte,mdp_actuel_saisie);
    if(trouve==1){
   do {
        gotoxy(31, 13);
        printf("Donner le nouveau mot de passe (4 chiffres) : ");
        scanf("%d",&nouveau_mdp_saisie);
        gotoxy(31, 15);
        printf("\nDonner le mot de passe pour verification : ");
        saisirMotDePasseMasque(&nouveau_mdp_saisie1);

        // If passwords don't match, display an error message
        if (nouveau_mdp_saisie1 != nouveau_mdp_saisie) {
            gotoxy(31,16);
            setConsoleColor(4,1);
            printf("\nLe mot de passe n'est pas exact. Veuillez reessayer.\n");
        }
    } while (nouveau_mdp_saisie1 != nouveau_mdp_saisie);
    }
     FILE *fichier = fopen("data/comptes.txt", "r+"); // Open file for reading and writing
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
        setConsoleColor(15,10);
        NOTIFICATION("Mot de passe modifié avec succès.\n",0);
        SesionAdmin(numcompte,"modification mdp");
        resetColor();
        getch();
    }
    PAGEPROFIL(fichier,numcompte);
}
///lsite des operation 
void operation_liste(int numcompte){
    int choix = 0;
    system("cls");
    FILE*fich;
     do {
        
        
        print_box_with_title(10, 5, 100, 20, "*****LES OPERATIONS*****");
        setConsoleColor(15,1);
        gotoxy(35, 11); printf("1-Dépôt\n");
        gotoxy(35, 13); printf("2-RETRAIT.\n");
        gotoxy(35, 15); printf("3-VIREMENTS.\n");
        gotoxy(35, 17); printf("4-retourner au menu principale.\n");

        gotoxy(35, 19); printf("Donner votre choix : \t");
        gotoxy(10, 25);
        tim_function();
        gotoxy(35+strlen("Donner votre choix : "),19);
        scanf("%d",&choix);
      switch (choix)
    {
    case 1:
    system("cls");
        depot(numcompte);
        break;
    case 2:
        retrait(numcompte);
        break;
    case 3 : 
        function_verment(numcompte);
        break;
       case 4 : 
        PAGEPROFIL(fich,numcompte);
        break;
    default:
        setConsoleColor(15,4);
        NOTIFICATION("INVALID CHOIX .REESAYER",0);
        getch();
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
    afficher_compte(id_compte,0);
        setConsoleColor(15,1);

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
           Supresion_compt(id_compte,0);
            break;
        case 6:
            afficher_menu();
            break;
        default:
                setConsoleColor(15,4);

            NOTIFICATION("erreur de saisir...  ",0);
            break;
        }
        printf("\033[0m");
    } while (choix == 0);
    
}
/*******************************************************************affiche menu ***************************** */
void move_cursor_to_top() {
    printf("\033[H");  // Move the cursor to the top-left corner
}

void move_cursor_to_bottom() {
    printf("\033[999B");  // Move the cursor to the bottom of the terminal screen
}

void movingBanner(const char *text) {
    int textLen = strlen(text);
    char display[81] = {0}; // Assume terminal width is 80 characters + null terminator

    while (1) {
        for (int pos = 0; pos < textLen + 80; pos++) {
            memset(display, ' ', 80); // Clear the display array with spaces

            // Fill the display array dynamically based on position
            for (int i = 0; i < 80; i++) {
                int index = (pos + i) % textLen; // Circular indexing
                display[i] = text[index]; // Use the original text
            }

            // Print at the top
            move_cursor_to_top();
            printf("\033[1;33m%s\033[0m", display);  // Bright yellow text

            // Print at the bottom
            move_cursor_to_bottom();
            printf("\033[1;33m%s\033[0m", display);  // Bright yellow text

            fflush(stdout);
            usleep(100000); // Delay for smooth animation

            // Check if menu is closed, and break the loop if it is
            if (_kbhit()) break;  // This breaks if the user is interacting with the menu
        }
    }
}

void afficher_menu() {
    FILE *fich;
    // Define menu items and title
    char *menu_items[] = {
        "SIGN IN",
        "LOGIN",
        "ADMIN",
        "QUIT APPLICATION",
        NULL // Null-terminated list
    };
    char *menu_title = "ACCEUIL";

    const int box_x = 10;
    const int box_y = 5;
    const int box_width = 100;
    const int box_height = 20;

    while (1) {
        system("cls");

        // Draw the box with the title
        print_box_with_title(box_x, box_y, box_width, box_height, menu_title);

        // Calculate the starting position to center the menu items inside the box
        int menu_start_y = box_y + (box_height / 2) - 2; // Center vertically
        int menu_start_x = box_x + (box_width / 2) - 10; // Approx center horizontally (adjust padding as needed)

        // Display the menu and get the user's choice
        int selected_option = 0;
        int key;
        int item_count = 0;

        // Count menu items
        while (menu_items[item_count] != NULL) {
            item_count++;
        }

        while (1) {
            // Display menu options inside the box
            for (int i = 0; i < item_count; i++) {
                gotoxy(menu_start_x, menu_start_y + i * 2); // Space out options vertically
                if (i == selected_option) {
                    setConsoleColor(2, 1); // Green for selected option with black background
                    printf("> %s", menu_items[i]);
                } else {
                    setConsoleColor(15, 1); // White text with black background for unselected options
                    printf("  %s", menu_items[i]);
                }
            }

            // Get user input for navigation
            key = _getch();
            if (key == 224) { // Arrow key prefix
                key = _getch();
                if (key == 72 && selected_option > 0) { // Up arrow
                    selected_option--;
                } else if (key == 80 && selected_option < item_count - 1) { // Down arrow
                    selected_option++;
                }
            } else if (key == 13) { // Enter key
                break;
            }

            // Clear the menu area (without clearing the box)
            for (int i = 0; i < item_count; i++) {
                gotoxy(menu_start_x, menu_start_y + i * 2);
                printf("                    "); // Clear line with spaces
            }
        }

        // Act based on the selected choice
        switch (selected_option) {
            case 0:
                system("cls");
                interfece2();
                break;
            case 1:
                system("cls");
                login();
                break;
            case 2:
                system("cls");
                LOGINADMIN();
                break;
            case 3:
                system("cls");
                        setConsoleColor(15,10);
                NOTIFICATION("THANK YOU FOR YOUR VISIT .....", 1);
                return; // Exit the menu loop

            default:
                system("cls");
                        setConsoleColor(15,4);

                NOTIFICATION("Invalid input. Please try again.", 0);
             
                break;
        }
    }
}

        
/*
// Function to display the menu
void afficher_menu() {
    char *menu_items[] = {"SIGN IN", "LOGIN", "ADMIN", "QUIT APPLICATION", NULL};
    char *menu_title = "ACCEUIL";

    const int box_x = 10;
    const int box_y = 5;
    const int box_width = 100;
    const int box_height = 20;

    int selected_option = 0;

    while (1) {
        clear_screen();
        print_box_with_title(box_x, box_y, box_width, box_height, menu_title);

        int menu_start_y = box_y + (box_height / 2) - 2;
        int menu_start_x = box_x + (box_width / 2) - 10;

        // Display menu options
        for (int i = 0; menu_items[i] != NULL; i++) {
            gotoxy(menu_start_x, menu_start_y + i * 2);
            if (i == selected_option) {
                setConsoleColor(2, 15); // Highlight selected option
                printf("> %s", menu_items[i]);
            } else {
                setConsoleColor(15, 0); // Normal text
                printf("  %s", menu_items[i]);
            }
        }

        // Input handling
        int key = _getch();
        if (key == 224) { // Arrow key prefix
            key = _getch();
            if (key == 72 && selected_option > 0) { // Up arrow
                selected_option--;
            } else if (key == 80 && selected_option < 3) { // Down arrow
                selected_option++;
            }
        } else if (key == 13) { // Enter key
            // Handle actions for selected menu item
            switch (selected_option) {
                case 0:
                    clear_screen();
                    printf("SIGN IN selected.\n");
                    system("pause");
                    break;
                case 1:
                    clear_screen();
                    printf("LOGIN selected.\n");
                    system("pause");
                    break;
                case 2:
                    clear_screen();
                    printf("ADMIN selected.\n");
                    system("pause");
                    break;
                case 3:
                    clear_screen();
                    printf("QUIT APPLICATION selected.\n");
                    return; // Exit the loop
            }
        }
    }
}*/

/*void afficher_menu() {
    int choix = 1;  // Start with the first option selected
    client c;
    FILE *fich;
    date d;

    // Initialize variables for banner animation
    const char *bannerText = "BANK DIGITAL";
    
    // Start the moving banner in a separate thread or use a non-blocking approach
    // (Assuming your terminal supports threading for non-blocking behavior)
  //  _beginthread(movingBanner, 0, (void *)bannerText); // Windows threading or use pthreads for Linux

    // Loop to keep the menu active
    do {
        // Save the current cursor position before clearing the screen
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int savedX = csbi.dwCursorPosition.X;
        int savedY = csbi.dwCursorPosition.Y;
        hideCursor();
        system("cls");  // Clear screen at the start
        print_box_with_title(10, 5, 100, 20, "ACCUEIL");
        printf("\033[0;34;40m");

        // Display menu options without numbers
        gotoxy(35, 11);setConsoleColor(10,0); printf(choix == 1 ? "> SIGN IN.\n" : "  SIGN IN.\n");
        gotoxy(35, 13);setConsoleColor(10,0); printf(choix == 2 ? "> LOGIN.\n" : "  LOGIN.\n");
        gotoxy(35, 15); setConsoleColor(10,0);printf(choix == 3 ? "> ADMIN.\n" : "  ADMIN.\n");
        gotoxy(35, 17); setConsoleColor(10,0);printf(choix == 4 ? "> QUIT APPLICATION.\n" : "  QUIT APPLICATION.\n");
        gotoxy(35, 19);setConsoleColor(10,0); printf("Please use arrow keys to navigate or press 'q' to quit.");

        gotoxy(35, 21); printf("Press Enter to select an option.");

        // Variable to capture user input
        char key;

        while (1) {
            // Call `gestion_touche_fonctions` for navigation and input
            key = _getch();

            if (key == 0 || key == 224) { // Special keys (arrow keys)
                key = _getch();
                switch (key) {
                    case 72: // Up arrow
                        if (choix > 1) choix--;
                        break;
                    case 80: // Down arrow
                        if (choix < 4) choix++;
                        break;
                }
            } else if (key == '\r') { // Enter key
                break; // Proceed to selected option
            } else if (key == 'q') { // Quit
                choix = 4;
                break;
            }

            // Update the menu display with the selected option
            gotoxy(35, 11); printf(choix == 1 ? "> SIGN IN.\n" : "  SIGN IN.\n");
            gotoxy(35, 13); printf(choix == 2 ? "> LOGIN.\n" : "  LOGIN.\n");
            gotoxy(35, 15); printf(choix == 3 ? "> ADMIN.\n" : "  ADMIN.\n");
            gotoxy(35, 17); printf(choix == 4 ? "> QUIT APPLICATION.\n" : "  QUIT APPLICATION.\n");
        }

        // Perform action based on the selected choice
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
                NOTIFICATION("THANK YOU FOR YOUR VISIT .....", 1);
                break;
            default:
                clear_screen();
                NOTIFICATION("Invalid input. Please try again.", 0);
                break;
        }

        // Restore the cursor to the previous position
        gotoxy(savedX, savedY);

        printf("\033[0m"); // Reset text color
    } while (choix != 4);
}*/


void fermer_comptes(int numcompte){
    FILE *file = fopen("data/comptes.txt", "r");
    FILE *temp = fopen("data/temp.txt", "w");

    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }

    client cl;
    int found = 0;

    while (fscanf(fich, "%d %s %s %d/%d/%d %s %d %d %d\n", &cl.c.Ncompte, cl.nom, cl.prenom, 
                  &cl.c.dcreation.jour, &cl.c.dcreation.mois, &cl.c.dcreation.anne, cl.c.typecompte, 
                  &cl.c.solde, &cl.c.password, &cl.c.h.idhistorique) != EOF) {
        if (cl.c.Ncompte == numcompte) {
            found = 1;
        } else {
           fprintf(temp, "%d %s %s %d/%d/%d %s %d %d %d\n",
            cl.c.Ncompte, cl.nom, cl.prenom, cl.c.dcreation.jour, cl.c.dcreation.mois, cl.c.dcreation.anne,cl.c.typecompte, cl.c.solde,cl.c.password,cl.c.h.idhistorique);
        }
    }

    fclose(file);
    fclose(temp);

    remove("data/comptes.txt");
    rename("data/temp.txt", "data/comptes.txt");

    if (found) {
        setConsoleColor(15,4);
        NOTIFICATION("Compte supprimé avec succès!\n",0);
        resetColor();
    } else {
        printf("Account with ID %d not found!\n", id);
    }
}

void Supresion_compt(int numcompte) {
    int choix;
    int mdp_saisie;
    print_box_with_title(10,5,100,20,"**** FERMETURE DE COMPTE ****");
    gotoxy(35,12);
            setConsoleColor(15,1);
    printf("1. Fermer un compte\n");
    gotoxy(35,14);
    printf("2. Retourner au menu principal\n");
    gotoxy(35,16);
    printf("Entrer votre choix : \t ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            system("cls");
            print_box_with_title(10,5,100,20,"Supprimer Compte");
            setConsoleColor(15,1);
            gotoxy(35,15);printf("Donner le mot de passe  (4 chiffres) : ");
            saisirMotDePasseMasque(&mdp_saisie);
            if(authentification(numcompte,mdp_saisie)==1){
                fermer_comptes(numcompte);
            }else{
                NOTIFICATION("mot de passe est incorrecte",0);
            }
            
            break;
        case 2:
            system("cls");
            printf("\nRetour au menu principal...\n");
            break;
        default:
            system("cls");
            setConsoleColor(15,4);

            NOTIFICATION("\nChoix invalide, retour au menu principal.\n",0);
            break;
    }
}
/// retourn  id histo
int retourner_idhistori(int numcompte) {
    FILE *fich = fopen("data/comptes.txt", "r");
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
    FILE *fich = fopen("data/comptes.txt", "r");
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
    FILE *fichier = fopen("data/comptes.txt", "r+"); // Open file for reading and writing
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

void depot(int idEntrer) {
    int  mdp_saisie,soldEAjouter, solde;
    print_box_with_title(10,5,100,20,"***DEPOT***");
        setConsoleColor(15,1);

       do {
    gotoxy(35, 11);
    printf("Donner le montant ( >100dh): ");
    gotoxy(35 + strlen("Donner le montant ( >100dh): "), 13);
    scanf("%d", &soldEAjouter);

    if (soldEAjouter < 100) {
        gotoxy(35, 12);
        printf("Erreur: le montant doit etre >= 10dh. Veuillez reessayer.");
    } else {
        int solde = calculer_solde(idEntrer,soldEAjouter, 1);
        if (solde < 0) {
            gotoxy(35, 13);
            setConsoleColor(4,1);
            printf("SOLDE INSUFFISANT. VEUILLEZ ENTRER UN MONTANT VALIDE.");
            soldEAjouter= -1; // Force re-entry of amount
        } else {
            break; // Valid amount and sufficient balance
        }
    }
} while (1);
   int auth_result;
    do {
        gotoxy(35, 15);
        printf("Donner le mot de passe : ");
        gotoxy(35 + strlen("Donner le mot de passe :"), 15);
        saisirMotDePasseMasque(&mdp_saisie);

        auth_result = authentification(idEntrer, mdp_saisie);
        if (auth_result == 0) {
            gotoxy(35, 16);
            setConsoleColor(4,1);
            printf("Mot de passe incorrect. Veuillez reessayer.");
        }
    } while (auth_result == 0);
    if (soldEAjouter <= 0) {
        setConsoleColor(15,4);
        NOTIFICATION("Erreur : le montant du dépôt doit être positif.\n",0);
                resetColor();

        return;
    }
    solde=calculer_solde(idEntrer,soldEAjouter,0);
    if (!modifierSolde(idEntrer, solde)) {
        printf("Error updating the account file.\n");
        return;
    }
    FILE *fichier_historique = fopen("data/historique.txt", "a+");
    if (!fichier_historique) {
        printf("Error opening history file.\n");
        return;
    }
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    fprintf(fichier_historique,"%-12d |        %-11s        | %-13d|    %02d/%02d/%04d    | %d \n",
            retourner_idhistori(idEntrer), "dépôt", soldEAjouter,
            local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900, solde);
    fclose(fichier_historique);
    SesionAdmin(idEntrer,"faire un dépôt");
    setConsoleColor(15,10);
    NOTIFICATION(" Deposit successful", 0);
    getch();
    resetColor();
    operation_liste(idEntrer);

}
 void retrait(int idEntrer) {
    int mdp_saisie, montantRetirer, solde;
    print_box_with_title(10,5,100,20,"***Retrait***");
setConsoleColor(15,1);   
    do {
    gotoxy(35, 11);
    printf("Entrez le montant à retirer :");
    gotoxy(35 + strlen("Entrez le montant à retirer : "), 11);
    scanf("%d", &montantRetirer);

    if (montantRetirer <= 0) {
        gotoxy(35, 12);
        printf("\033[0;31mErreur : Le montant doit être supérieur à 0. Veuillez réessayer.\033[0m");
    } else {
        solde = calculer_solde(idEntrer, montantRetirer, 1);
        if (solde < 0) {
            gotoxy(35, 12);
            setConsoleColor(4,1);
            printf("\033[0;31mErreur : Solde insuffisant ou compte non trouvé. Veuillez réessayer.\033[0m");
                    resetColor();
            montantRetirer = -1; // Force re-entry of amount
        } else {
            break; // Valid amount and sufficient balance
        }
    }
} while (1);

    int auth_result;
    do {
        gotoxy(35, 15);
        printf("Donner le mot de passe : ");
        gotoxy(35 + strlen("Donner le mot de passe :"), 15);
        scanf("%d", &mdp_saisie);

        auth_result = authentification(idEntrer, mdp_saisie);
        if (auth_result == 0) {
            gotoxy(35, 16);
            printf("Mot de passe incorrect. Veuillez reessayer.");
        }
    } while (auth_result == 0);
    if (!modifierSolde(idEntrer, solde)) {
        printf("Error updating the account file.\n");
        return;
    }

    // Record in history
    FILE *fichier_historique = fopen("data/historique.txt", "a+");
    if (!fichier_historique) {
        printf("Error opening history file.\n");
        return;
    }
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    fprintf(fichier_historique,"%-12d |        %-11s      | -%-12d|    %02d/%02d/%04d    | %d \n",
            retourner_idhistori(idEntrer), "Retrait", montantRetirer,
            local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900, solde);
    fclose(fichier_historique);
    SesionAdmin(idEntrer,"fait un Retrait");
    setConsoleColor(15,10);
    NOTIFICATION("Withdrawal successful.", 0);
    getch();
    resetColor();
    operation_liste(idEntrer);


}
void function_verment(int id_transfert) {
    int id_destinataire;
    int montant, mdp_saisie;

    print_box_with_title(10, 5, 100, 20, "***Virement***");
    gotoxy(12, 7);
    setConsoleColor(15,1);
    printf(" ⚠ INFORMATION ⚠ : Transfert entre deux comptes de la même banque ");
   do {
    gotoxy(35, 11);
    printf("Donner le numero de compte destinataire : ");
    gotoxy(35 + strlen("Donner le numero de compte destinataire : "), 11);
    scanf("%d", &id_destinataire);

    if (id_destinataire == id_transfert) {
        gotoxy(35,12);
        printf("Erreur : Vous ne pouvez pas transférer de l'argent à votre propre compte.");
        getch();
    } else if (verification(id_destinataire) == 0) {
        setConsoleColor(4,1);
        NOTIFICATION("LE COMPTE DESTINATAIRE N'EXISTE PAS. VEUILLEZ RÉESSAYER.", 0);
        getch();
        resetColor();
        operation_liste(id_transfert);
    } else {
        break; // Exit the loop if the account exists and it's not the user's own account
    }
} while (1);
int solde_trans;

   do {
    gotoxy(35, 13);
    printf("Donner le montant ( >10dh): ");
    gotoxy(35 + strlen("Donner le montant ( >10dh): "), 13);
    scanf("%d", &montant);

    if (montant < 10) {
        gotoxy(35, 14);
        printf("Erreur: le montant doit etre >= 10dh. Veuillez reessayer.");
    } else {
         solde_trans = calculer_solde(id_transfert, montant, 1);
        if (solde_trans < 0) {
            gotoxy(35, 14);
            setConsoleColor(4,1);
            printf("SOLDE INSUFFISANT. VEUILLEZ ENTRER UN MONTANT VALIDE.");
            montant = -1; // Force re-entry of amount
        } else {
            break; // Valid amount and sufficient balance
        }
    }
} while (1); 

int solde_desti = calculer_solde(id_destinataire, montant, 0);
    int auth_result;
    do {
        gotoxy(35, 15);
        setConsoleColor(15,1);
        printf("Donner le mot de passe : ");
        gotoxy(35 + strlen("Donner le mot de passe :"), 15);
        saisirMotDePasseMasque(&mdp_saisie);

        auth_result = authentification(id_transfert, mdp_saisie);
        if (auth_result == 0) {
            gotoxy(35, 16);
            printf("Mot de passe incorrect. Veuillez reessayer.");
        }
    } while (auth_result == 0);

    if (!modifierSolde(id_transfert, solde_trans)) {
        printf("Error updating the account file.\n");
        return;
    }
    if (!modifierSolde(id_destinataire, solde_desti)) {
        printf("Error updating the account file.\n");
        return;
    }

    gotoxy(10, 25);
    tim_function();

    // Record in history
    FILE *fichier_historique = fopen("data/historique.txt", "a+");
    if (!fichier_historique) {
        printf("Error opening history file.\n");
        return;
    }
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    fprintf(fichier_historique, "%-12d |        %-11s      | -%-11d |    %02d/%02d/%04d    | %d \n",
            retourner_idhistori(id_transfert), "Virement", montant,
            local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900, solde_trans);
    fprintf(fichier_historique, "%-12d |        %-11s      | +%-11d |    %02d/%02d/%04d    | %d \n",
            retourner_idhistori(id_destinataire), "Virement", montant,
            local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900, solde_desti);
    fclose(fichier_historique);
    FILE *fich=fopen("data/virements.txt","a+");
    if (!fich) {
        printf("erreur de ecrire sue le fichier de virements .\n");
        return;
    }
    fprintf(fich, "%-8d     |       %-8d      |       %-10d | %02d/%02d/%04d\n", id_transfert, id_destinataire, montant, local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);
    fclose(fich);
    SesionAdmin(id_transfert,"effectuer un virment");
            setConsoleColor(15,10);
    NOTIFICATION("✅  VIREMENT EFFECTUÉ AVEC SUCCÈS  ✅", 0);
    getch();
   

    resetColor();
    operation_liste(id_transfert);
}


void sizezProfesionelle(client cl){
    Entreprise dataEntreprise ; 
    FILE *entreprise = fopen("data/entreprise.txt", "a"); 
    if(entreprise == NULL){
        printf("problemme d'ouverture de fichies : ");
        exit(1); 
    }
    // entrer les information sur l'entreprise : 
    print_box_with_title(10,5,100,20,"**Entreprise**");
    setConsoleColor(15,1);   
    gotoxy(35,11);
    printf("Nom Entreprise : ");
    gotoxy(35,13);
    printf(" Code ICE : ");
    gotoxy(35 ,15); 
    printf("Type d'entreprise : "); 
    gotoxy(35 , 17); 
    printf("Adresse ; "); 
    gotoxy(10, 25);
    tim_function();

    // Saisie des informations de connexion
    gotoxy(35 + strlen("Nom Entreprise : "),11);
    scanf("%s",dataEntreprise.Nomentreprise); 
    while(getchar() != '\n');
    gotoxy(35 + strlen(" Code ICE : "), 13);  
    scanf("%d",&dataEntreprise.Code_iDentifant); 
    while(getchar() != '\n');
    gotoxy(35 + strlen("Type d'entreprise : "),15); 
    scanf("%s", &dataEntreprise.type_entreprise); 
    while(getchar() != '\n');
    gotoxy(35 + strlen("Adresse ; "),17); 
    scanf("%s", &dataEntreprise.adresentreprise); 
    while(getchar() != '\n');

    fprintf(entreprise, "Nom Entreprise     : %s\n", dataEntreprise.Nomentreprise);
    fprintf(entreprise, "Code ICE           : %d\n", dataEntreprise.Code_iDentifant);
    fprintf(entreprise, "Type d'Entreprise  : %s\n", dataEntreprise.type_entreprise);
    fprintf(entreprise, "Adresse            : %s\n", dataEntreprise.adresentreprise);
    fprintf(entreprise, "Maitre d'ouverage  : %s %s\n", cl.nom,cl.prenom);
    fprintf(entreprise, "---------------------------------------------\n");
    fclose(entreprise); 

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
    setConsoleColor(15,1);  
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
    clear_screen();
    print_box_with_title(10,5,100,20,"**MENUE_ADMIN**");
    setConsoleColor(15,1);
    gotoxy(35,11);
    printf("1-affichage de compte  ");
    gotoxy(35,13);
    printf("2-affichage de client ");
    gotoxy(35,15);
    printf("3-cherche un compte  ");
    gotoxy(35 , 17); 
    printf("4-affichage historique .  "); // choix pour entrer :
    gotoxy(35 , 19); 
    printf("5-affichage d'activite . "); 
    gotoxy(35 , 21); 
    printf("Choix : "); 
    gotoxy(10, 25);
    tim_function();

    // Saisie des informations de connexion
    gotoxy(35+strlen("choix : "),21); 
    scanf("%d",&choix); 
    getch(); 

    // switch : 
    switch (choix)
    {
    case 1 : 
        system("cls"); 
        // fonction AFichage information sur compt compt  . 
        affichagecompteadmin(); 

        break;
    case 2 : 
        system("cls"); 
       AFICHAGECLIENTADMIN();
        break; 
    case 3: 
        system("cls"); 
        SearchClientADmin();
        break; 
 
    case 4: 
        system("cls"); 
        AFICHAGEHISTORIQUEAdmin();
        break; 
     case 5 : 
        system("cls"); 
        SesionAdmin(); 
        break; 
    default:
        // retour au page initiale . 
        exit(1) ; // exite aplication . 
        break;
    }
}
void affichagecompteadmin() {
    FILE *fich;
    client cl; // Une variable pour stocker les informations de chaque compte

    // Ouvrir le fichier en mode lecture
    fich = fopen("data/comptes.txt", "r");
    if (fich == NULL) {
        printf("Erreur d'ouverture du fichier Comp.text\n");
        exit(1); // Arrêter l'exécution en cas d'erreur
    }

    // backgroud d'afichage est en blan 
    system("color 01"); 

    // Titre de l'affichage
    printf("\n");
    printf("┌──────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                    Liste des Comptes                                     │\n");
    printf("└──────────────────────────────────────────────────────────────────────────────────────────┘\n");
    printf("\n");

    // Affichage de l'entête
    printf("ID Compte   | Type Compte   | Solde    | Mot de Passe | ID Historique   | DATE DE CREATION\n");
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
    getch();
    resetColor();
    MENUE_ADMIN();
}

void AFICHAGEHISTORIQUEAdmin() {
    FILE *fich;
    historique historique_operation; // Une variable pour stocker les informations de chaque compte
    int id_compt;

    // Ouvrir le fichier en mode lecture
    fich = fopen("data/historique.txt", "r");
    if (fich == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier 'historique.txt'.\n");
        return; 
    }

    system("color F0");

    printf("\n");
    printf("┌───────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                         Historique                                    │\n");
    printf("└───────────────────────────────────────────────────────────────────────────────────────┘\n");
    printf("\n");
    char line[256];
    fgets(line, sizeof(line),fich);
    fgets(line, sizeof(line),fich);

    // Affichage de l'entête
    printf("ID HISTORIQUE|    TYPE D'OPERATION     | MONTANT      | DATE D'OPERATION |   SOLDE\n");
    printf("--------------------------------------------------------------------------------------\n");
    // lecture du donnes dans le fichies historique 
    while (fgets(line, sizeof(line), fich) != NULL){
        printf("%s\n", line);
    }

   

    fclose(fich); 
    /*printf("\n\n");
    gotoxy(30, 20);
    system("color 04"); // Fond noir, texte rouge
    printf("┌────────────┐\n");
    printf("│ [ Retour ] │\n");
    printf("└────────────┘\n");*/
    getch(); 
    resetColor();
    MENUE_ADMIN();

}

void AFICHAGECLIENTADMIN() {
    client client_data;
    FILE *fich;
    fich = fopen("data/clients.bin", "rb");

    if (fich == NULL) {
        printf("Problème dans l'ouverture du fichier.\n");
        exit(1);
    }

    system("color F0");
      // Top Border
    printf("┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                                               CLIENTS                                                            │\n");
    printf("└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");

    // Table Header
    printf("ID CLIENT │ NOM        │ PRENOM     │ ADRESSE                       │ TELEPHONE    │ ID COMPTE │ DATE NAISSANCE │ LIEU DE NAISSANCE\n");
    printf("──────────┼────────────┼────────────┼───────────────────────────────┼──────────────┼───────────┼────────────────┼──────────────────\n");

    // Reading and displaying client information
    while (fread(&client_data, sizeof(client_data), 1, fich) == 1) {
        printf("%-10d│ %-11s│ %-11s│ %-30s│ +212%-9s │ %-9d │ %02d/%02d/%04d     │ %-17s\n",
               client_data.idclient,
               client_data.nom,
               client_data.prenom,
               client_data.adress,
               client_data.phone,
               client_data.c.Ncompte,
               client_data.d.jour,
               client_data.d.mois,
               client_data.d.anne,
               client_data.lieudenaissa);
    }

    // Bottom Border
    printf("─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────-────\n");


    fclose(fich); 
    gotoxy(10,25); 
    printf("<rotour "); 
    getch();           
    // rappele au fonction menue admiin au depart
    system("cls");
      resetColor();
    MENUE_ADMIN(); 
}
void SesionAdmin(int id_ompt , char nom_service[20]){
    // fonction qui permet de remplir les donnes des activites qui realiser les clients : 
    FILE *fich_admin; 
    fich_admin = fopen("data/session.txt", "a"); 
    if(fich_admin == NULL){
        printf("problemme dans l'ouverture de fichies "); 
    }
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);
    // remplir le fichies seison . 
    fprintf(fich_admin , "%-15d | %-16s | %02d/%02d/%04d %02d:%02d:%02d\n",
                                    id_ompt ,
                                    nom_service , 
                                    local_time->tm_mday, 
                                    local_time->tm_mon + 1 ,
                                    local_time->tm_year + 1900,
                                    local_time->tm_hour , 
                                    local_time->tm_min,
                                    local_time->tm_sec);
    
    fclose(fich_admin);
}
/*void move_cursor_to_top() {
    printf("\033[H");  // Move the cursor to the top-left corner
}

void move_cursor_to_bottom() {
    printf("\033[999B");  // Move the cursor to the bottom of the terminal screen
}

void movingBanner() {
    char *text = "DIGITAL BANK ";
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

    while (1) {
        // Animate the text across the terminal width
        for (int pos = 0; pos < textLen + 80; pos++) {
            memset(display, ' ', 80); // Clear the display array with spaces

            // Fill the display array dynamically based on position
            for (int i = 0; i < 80; i++) {
                int index = (pos + i) % textLen; // Circular indexing
                display[i] = text[index]; // Use the original text
            }

            // Print at the top
            move_cursor_to_top();
            printf("\033[1;33m%s\033[0m", display);  // Bright yellow text

            // Print at the bottom
            move_cursor_to_bottom();
            printf("\033[1;33m%s\033[0m", display);  // Bright yellow text

            fflush(stdout);
            usleep(100000); // Delay for smooth animation
        }
    }
}
*/
void SearchClientADmin(){    
    FILE *fichCompt; 
    client compt_search; 
    int idCompt_serach; 
    int var_trouver = 0;

    // Titre de la recherche
    print_box_with_title(10, 5, 100, 20, "**Search**");
    setConsoleColor(15,1);
    gotoxy(35, 11);  // Déplacer le curseur à une position spécifique (nécessite conio.h sous Windows)
    printf("Donner le numero de compte (5 chiffres) : ");
    gotoxy(35 , 12); 
    printf("╔═══════════════════════════════════════════╗");
    gotoxy(35 , 13); 
    printf("║                                           ║ ");
    gotoxy(35 , 14); 
    printf("╚═══════════════════════════════════════════╝");

    
    // Saisie des informations de recherche
    gotoxy(38, 13); 
    scanf("%d", &idCompt_serach);
    clear_box_content(10,5,100,20); 
    afficher_compte(idCompt_serach,1);
    getch();

}
void AfichageSesionAdmin(){
    FILE *fichsesion ; 
    fichsesion = fopen("data/sesion.txt" , "r"); 
    if(fichsesion == NULL){
        printf(" problemme dans l'ouverture de fiches "); 
        exit(1) ; 
    }
    system("color F0");
    printf("NUMERO_COMPTE   | TYPE_Service        |  Date \n");
    printf("------------------------------------------------\n");
    char line[256];
    fgets(line, sizeof(line), fichsesion); //pour ignorer les deux premiere ligne .  
    fgets(line, sizeof(line), fichsesion); 
    while (fgets(line, sizeof(line), fichsesion) != NULL) {
    printf("%s\n", line);
    }
    fclose(fichsesion); 

    gotoxy(20 , 35);
    printf("<< Retou >>\n");
    getch(); 
    resetColor();
    MENUE_ADMIN();
    // rappelle au fonction menue admin pour routour au meni : 
}
int main() {
    setlocale(LC_ALL, "fr_FR.UTF-8");  
    SetConsoleOutputCP(65001);
    system("cls");
    setConsoleColor(15, 1); 
    //interface1();    
    afficher_menu();
    return 0;
}
 
