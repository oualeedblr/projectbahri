#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include<locale.h>
typedef struct {
    int jour;
    int mois;
    int anne;
} date;

typedef struct {
    int idclient;
    char CIN[20];
    char nom[20];
    char prenom[20];
    char sexe;
    char adress[100];
    char phone[20];
    date d;
    char lieudenaissa[20];
} client;
typedef struct {
int solde;
int Ncompte;
int idhistorique;
int password;
date dcreation;
char typecompte[20];
}compte;

void clear_screen() {
    system("cls");
}

void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void ECRIRELESCLIENTS(FILE *fich, client c) {
    fich = fopen("clients.txt", "a+");
    if (fich == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }


   fprintf(fich, "%-10d | %-10s | %-10s | %02d/%02d/%04d  | %-17s | %-8s | %-30s | +212 %-10s | %c \n",
            c.idclient, c.nom, c.prenom, c.d.jour, c.d.mois, c.d.anne,
            c.lieudenaissa, c.CIN, c.adress, c.phone,
            c.sexe);

    fclose(fich);

}
void ECRIRELESCOMPTES(FILE *fich,compte c,client cl) {
    fich = fopen("comptes.txt", "a+");
    if (fich == NULL) {
        perror("Error opening file for writing");
        exit(1);
    }


   fprintf(fich, "%-10d | %-10s | %-10s |     %02d/%02d/%04d    | %-15s | %-9d  |   %-4d   | %-5d\n",
            c.Ncompte, cl.nom, cl.prenom, c.dcreation.jour, c.dcreation.mois, c.dcreation.anne,
            c.typecompte, c.solde,c.password,c.idhistorique);

    fclose(fich);

}

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
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
        if (sscanf(line, "%*d | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %d", &tempIdHis) == 1) {
            if (tempIdHis >= lastIdHis) {
                lastIdHis = tempIdHis + 1; 
            }
        }
    }

    fclose(fich);
    return lastIdHis;
}

void NOTIFICATION(char *std){
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
            exit(0);
                  
}
void afficher_menu() {
    int choix=0;
    int x = 50;
    int y = 2;  
    client c;
    FILE* fich;
    date d;
    system("cls");
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
            loadingPage();
            SIGNIN(fich);
            break;
        case 2:
            system("cls");
            loadingPage();
            break;
        case 3:
        clear_screen();
        loadingPage();
        NOTIFICATION(" MERCI POUR VOTRE VISITE .....\n");
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
int SIGNIN(FILE* fich) {
    system("Cls");
    client c1;
    compte c;
    char choix = 'N';
    int lastId = getLastClientId(fich);
    c1.idclient = lastId + 1;
    c.idhistorique= getLastIdHistorique(fich);
    

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
        scanf("%d", c.solde);
        while (getchar() != '\n'); 
        gotoxy(x, y++);
        printf("TU PEUX SAUVEGARDER VOTRE INFORMATIONS O/N : \n");
        scanf(" %c", &choix);
        while (getchar() != '\n'); 
    } while (choix == 'N' || choix =='n');

    gotoxy(x, y++);
    
    printf("TU peux donner le mot de passe (4 chiffres) : ");
    scanf("%d", &c.password);
    system("cls");
    gotoxy(x, y++);
    printf("Ton compte a ete enregistre avec succes. ");
    ECRIRELESCLIENTS(fich,c1);
    ECRIRELESCOMPTES(fich,c,c1);
    return 0;
}
void LIRECLIENTS(FILE *fich) {
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
        compte c;
        
        if (sscanf(line, "%*d | %19[^|] | %19[^|] | %d/%d/%d | %19[^|] | %19[^|] | %99[^|] | %19[^|] | %d | %*d",
                   &client.idclient, client.nom, client.prenom,
                   &client.d.jour, &client.d.mois, &client.d.anne,
                   client.lieudenaissa, client.CIN, client.adress, client.phone,
                   &client.sexe) == 9) {
           
            printf(" Nom: %s, Prenom: %s, date de naissance: %d/%d/%d, lieu de naissance: %s, CIN: %s, Address: %s, Phone: +212 %s, Sexe : %s\n",
                   client.idclient, client.nom, client.prenom, 
                   client.d.jour, client.d.mois, client.d.anne,
                   client.lieudenaissa, client.CIN, client.adress, client.phone,
                   client.sexe);
        } else {
            printf("erreur de lire les clients\n");
        }
    }

    fclose(fich);
}

/*

    char line[200];
    while (fgets(line, sizeof(line), fich) != NULL) {
        if (sscanf(line, "%*d %*s %*s %*d/%*d/%*d %*s %*s %*s %*s %*d %d", &tempIdHis) == 1) {
            if (tempIdHis >= lastIdHis) {
                lastIdHis = tempIdHis + 1; 
            }
        }
    }*/
int PAGEPROFIL(FILE* fich){
     int choix=0;
     system("Cls");
    client c1;
    int x = 45;
    int y = 5;  
  
    date d;
    
 do
    {
    gotoxy(x,y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓ PAGE DE PROFIL  ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 1-AFFICHER  VOTRE INFORMATIONS PERSONNELES .\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 2-AFFICHER VOTRE SOLDE .\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 3-AFFICHER VOTRE HISTORIQUES.\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 4-MODIFIER VOTRE INFORMATIONS .\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 5-CHANGER VOTRE MOT DE PASS  .\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓░ 6-RETURNER AU MENU PRINCIPALE.\n");

    gotoxy(x, y++);
    printf("▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓\n");
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
           
            break;
        case 3:
         
            break;
        case 4:
           
            break;
        case 5:
            
            break;
        case 6:
            afficher_menu();
            break;
        default:
            NOTIFICATION("erreur de saisir...  \n");
            break;
        }
    } while (choix != 6);
    
}
int main() {
    setlocale(LC_ALL, "fr_FR.UTF-8");  
    SetConsoleOutputCP(65001);
    system("COLOR 0A");
    loadingPage();
    afficher_menu();    
    return 0;
}

void box(int x, int y, int X, int Y){

  int i,j;
  system("color 0A");

  for(i = 1; i <= y; i++){
	  
	  gotoxy(X, Y++);
	  
      if(i == 1 || i == y){
          for(j = 0; j < x; j++){
              printf("\xB2");
          }
      }else{
          for(j = 1; j <= x; j++){
              if(j == 1 || j == x){
                  printf("\xB2");
              }else{
                  printf(" ");
              }
          }
      }
  }
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
        delay(1000);
        gotoxy(a++, 10);
    }
}
void delay(unsigned int x){

    int i, j;
    x *= 10000;
    for(i = 0; i <= x; i++){
        j = i;
    }
}