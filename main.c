#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct{
    int day;
    int month;
    int year;
}Date;

typedef struct{
    int id;
    char titre[50];
    char description[400];
    Date deadline;
    char statut[100];
}Task;

Task tasks[500];
int counter = 0;

void ajouter(){
    printf("Entrer l'Identifiant : \n-");
    scanf("%d", &tasks[counter].id);
    getchar();
    printf("Entrer le titre : \n-");
    gets(tasks[counter].titre);
    printf("Entrer le description : \n-");
    gets(tasks[counter].description);
    printf("Entrer le jour de deadline : \n-");
    scanf("%d" ,&tasks[counter].deadline.day);
    printf("Entrer le mois de deadline : \n-");
    scanf("%d" ,&tasks[counter].deadline.month);
    printf("Entrer l'annee de deadline : \n-");
    scanf("%d" ,&tasks[counter].deadline.year);
    getchar();
    while(1){
        printf("Entrer le status : \n-");
        gets(tasks[counter].statut);
        
        if(strcmp(tasks[counter].statut, "a realiser") == 0 || strcmp(tasks[counter].statut, "finalisee") == 0 || strcmp(tasks[counter].statut, "en cours de realisation") == 0){
            printf("Tache cree avec success\n");
            counter++;
            break;
        }else{
            printf("--------------------Entrer un statut valid !--------------------\n\n");
        }
    }
}

void ajouterMulti(){
    int nombre;
    printf("Entrer le nombre des taches :\n-");
    scanf("%d", &nombre);

    for(int i=0; i<nombre; i++){
        ajouter();
    }
}

void afficher(char sort[]){
    Task ordered[500];

    for(int i=0; i<counter; i++){
        ordered[i] = tasks[i];    
    }

    for(int i=0; i<counter-1; i++){
        for(int j=0; j<counter-i-1; j++){
            if(strcmp(sort, "alpha") == 0){
                if((ordered[j].titre, ordered[j+1].titre) > 0){
                    Task tmp = ordered[j];
                    ordered[j] = ordered[j+1];
                    ordered[j+1] = tmp;
                }
            }else if(strcmp(sort, "deadline") == 0){
                struct tm date1 = { 0 };
                struct tm date2 = { 0 };

                date1.tm_year = ordered[j].deadline.year - 1900;
                date1.tm_mon = ordered[j].deadline.month - 1;
                date1.tm_mday = ordered[j].deadline.day;

                date2.tm_year = ordered[j+1].deadline.year - 1900;
                date2.tm_mon = ordered[j+1].deadline.month - 1;
                date2.tm_mday = ordered[j+1].deadline.day;

                time_t time1 = mktime(&date1);
                time_t time2 = mktime(&date2);

                double diff = difftime(time1, time2);

                if(diff > 0){
                    Task tmp = ordered[j];
                    ordered[j] = ordered[j+1];
                    ordered[j+1] = tmp;
                }
            }
        }
    }


    for(int i=0; i<counter; i++){
        printf("Id : %d | Titre : %s | Description : %s | Deadline : %d/%d/%d | Statut : %s\n", ordered[i].id, ordered[i].titre, ordered[i].description, ordered[i].deadline.day, ordered[i].deadline.month, ordered[i].deadline.year, ordered[i].statut);
    }

}

int diff(Date date){
    time_t t = time(NULL);

    struct tm date1 = {0};
    date1.tm_year = date.year - 1900;
    date1.tm_mon = date.month - 1;
    date1.tm_mday = date.day;  

    time_t time1 = mktime(&date1);

    double diff = difftime(t, time1) / (60 * 60 * 24);

    return (int)diff;
}

void afficher3days(){
    for(int i=0; i<counter; i++){
        if(diff(tasks[i].deadline) <= 3 && diff(tasks[i].deadline) >= 0){
            printf("Id : %d | Titre : %s | Description : %s | Deadline : %d/%d/%d | Statut : %s\n", tasks[i].id, tasks[i].titre, tasks[i].description, tasks[i].deadline.day, tasks[i].deadline.month, tasks[i].deadline.year, tasks[i].statut);
        }
    }
}

int searchBy(char by[]){
    char titre[100];
    int id;
    if(strcmp(by, "id") == 0){
        printf("Entrer l'id de tache : \n-");
        scanf("%d", &id);
    }else{
        printf("Entrer le titre de tache : \n-");
        scanf("%d", &titre);
    }

    for(int i=0; i<counter; i++){
        if(strcmp(by, "id") == 0){
            if(id == tasks[i].id){
                return i;
            }
        }else{
            if(strcmp(tasks[i].titre, titre) == 0){
                return i;
            }
        }
    }

    return -1;
}

void update(char property[100]){
    int index = searchBy("id");
    if(index == -1){
        printf("La tache n'existe pas !\n");
        return;
    }
    getchar();
    if(strcmp(property, "description") == 0){
        char desc[100];
        printf("Entrer le nouveau description :\n-");
        gets(desc);
        strcpy(tasks[index].description, desc);
        printf("Tache modifiee avec success !\n");
    }else if(strcmp(property, "statut") == 0){
        char statut[100];
        while(1){
            printf("Entrer le nouveau statut : \n-");
            gets(statut);
            
            if(strcmp(statut, "a realiser") == 0 || strcmp(statut, "finalisee") == 0 || strcmp(statut, "en cours de realisation") == 0){
                break;
            }else{
                printf("--------------------Entrer un statut valid !--------------------\n\n");
            }
        }

        strcpy(tasks[index].statut, statut);
        printf("Tache modifiee avec success !\n");
    }else{
        //deadline
        Date date;
        printf("Entrer le jour de deadline : \n-");
        scanf("%d" ,&date.day);
        printf("Entrer le mois de deadline : \n-");
        scanf("%d" ,&date.month);
        printf("Entrer l'annee de deadline : \n-");
        scanf("%d" ,&date.year);

        tasks[index].deadline = date;
        printf("Tache modifiee avec success !\n");
    }
}

void supprimer(){
    int index = searchBy("id");
    if(index == -1){
        printf("Tache n'existe pas !\n");
        return;
    }

    char sure = 'n';
    printf("Es-tu sur ? tapez 'o' pour oui et 'n' pour non\n-");
    scanf("%c", &sure);

    if(sure == 'n'){
        return;
    }

    for(int i=index; i<counter-1; i++){
        tasks[i] = tasks[i+1];
    }

    counter--;
    printf("Tache supprime avec success !\n");
}

void recherche(char by[]){
    int i = searchBy(by);
    if(i == -1){
        printf("Tache n'exist pas !\n");
        return;
    }

    printf("Id : %d | Titre : %s | Description : %s | Deadline : %d/%d/%d | Statut : %s\n", tasks[i].id, tasks[i].titre, tasks[i].description, tasks[i].deadline.day, tasks[i].deadline.month, tasks[i].deadline.year, tasks[i].statut);
}

//statistiques
void daysbeforedelay(){
    for(int i=0; i<counter; i++){ 
        if(diff(tasks[i].deadline) >= 0)
            printf("Titre : %s | delay : %d jours\n", tasks[i].titre, diff(tasks[i].deadline));
    }
}

void nombreTotal(){
    printf("Nombre total des taches : %d", counter);
}

void nombreTacheCI(){
    int complete = 0;
    int incomplete = 0;
    for(int i=0; i<counter; i++){
        if(strcmp(tasks[i].statut, "finalisee") == 0){
            complete++;
        }else{
            incomplete++;
        }
    }

    printf("Nombre des taches completes : %d\n", complete);
    printf("Nombre des taches incompletes : %d\n", incomplete);
}

void main(){
    printf("\a");
    // int choix = 0;
    // char subchoix;
    // system("cls");
    // do{
    //     printf("--------------------------------------------------------------------------------\n");
    //     printf("----------------------------- Welcome to main menu -----------------------------\n");
    //     printf("--------------------------------------------------------------------------------\n\n");
    //     printf("0- Exit\n");
    //     printf("1- Ajouter tache :\n");
    //     printf("   a- Ajouter une nouvelle tache\n");
    //     printf("   b- Ajouter plusieurs nouvelles taches\n");
    //     printf("2- Afficher la liste de toutes les taches :\n");
    //     printf("   a- Trier les taches par ordre alphabetique\n");
    //     printf("   b- Trier les taches par deadline\n");
    //     printf("   c- Afficher les tâches dont le deadline est dans 3 jours ou moins\n");
    //     printf("3- Modifier une tache :\n");
    //     printf("   a- Modifier la description d'une tache\n");
    //     printf("   b- Modifier le statut d'une tache\n");
    //     printf("   c- Modifier le deadline d'une tache\n");
    //     printf("4- Supprimer une tache par identifiant\n");
    //     printf("5- Rechercher les Taches :\n");
    //     printf("   a- Rechercher une tache par son Identifiant\n");
    //     printf("   b- Rechercher une tache par son Titre\n");
    //     printf("6- Statistiques :\n");
    //     printf("   a- Afficher le nombre total des taches\n");
    //     printf("   b- Afficher le nombre de taches completes et incompletes\n");
    //     printf("   c- Afficher le nombre de jours restants jusqu'au delai de chaque tache\n");

    //     printf("Entrez votre choix : \n");
    //     scanf("%d", &choix);

    //     switch(choix){
    //         case 1:
    //             system("color 2");
    //             printf("Entrez votre sous choix : \n");
    //             scanf(" %c", &subchoix);

    //             switch(subchoix){
    //                 case 'a':
    //                     ajouter();
    //                 break;
    //                 case 'b':
    //                     ajouterMulti();
    //                 break;
    //                 default:
    //                     printf("sous choix  est pas valid !\n");
    //                 break;
    //             }
    //         break;
    //         case 2:
    //             system("color 3");
    //             printf("Entrez votre sous choix : \n");
    //             scanf(" %c", &subchoix);
    //             switch(subchoix){
    //                 case 'a':
    //                     afficher("alpha");
    //                 break;
    //                 case 'b':
    //                     afficher("deadline");
    //                 break;
    //                 case 'c':
    //                     afficher3days();
    //                 break;
    //                 default:
    //                     printf("sous choix  est pas valid !\n");
    //                 break;
    //             }                
    //         break;
    //         case 3:
    //             system("color 4");
    //             printf("Entrez votre sous choix : \n");
    //             scanf(" %c", &subchoix);
    //             switch(subchoix){
    //                 case 'a':
    //                     update("description");
    //                 break;
    //                 case 'b':
    //                     update("statut");
    //                 break;
    //                 case 'c':
    //                     update("deadline");
    //                 break;
    //                 default:
    //                     printf("sous choix  est pas valid !\n");
    //                 break;
    //             } 
    //         break;
    //         case 4:
    //             system("color 5");
    //             supprimer();
    //         break;
    //         case 5:
    //             system("color 6");
    //             printf("Entrez votre sous choix : \n");
    //             scanf(" %c", &subchoix);
    //             switch(subchoix){
    //                 case 'a':
    //                     recherche("id");
    //                 break;
    //                 case 'b':
    //                     recherche("titre");
    //                 break;
    //                 default:
    //                     printf("sous choix  est pas valid !\n");
    //                 break;
    //             }  
    //         break;
    //         case 6:
    //             system("color 7");
    //             printf("Entrez votre sous choix : \n");
    //             scanf(" %c", &subchoix);
    //             switch(subchoix){
    //                 case 'a':
    //                     nombreTotal();
    //                 break;
    //                 case 'b':
    //                     nombreTacheCI();
    //                 break;
    //                 case 'c':
    //                     daysbeforedelay();
    //                 break;
    //                 default:
    //                     printf("sous choix  est pas valid !\n");
    //                 break;
    //             } 
    //         break; 
    //         default:
    //             if(choix != 0){
    //                 printf("votre choix n'existe pas !\n");
    //             }
    //         break;
    //     }
    //     system("pause");
    //     system("cls");
    // }while(choix != 0);
}
