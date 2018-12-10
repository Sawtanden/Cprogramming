#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

int main() {	
	menu();
}

void menu() {
	
    int option, retry = 0;

    printf("1. Lista Innehall\n\n");
    printf("\n2. Lagg till ny vara\n\n");
    printf("\n3. Sok bland varor\n\n");
    printf("\n4. Spara vara till fil\n\n");
    printf("\n5. Avsluta\n\n");    
    
    printf("Please enter your choice: ");
    scanf("%d", &option);

    switch (option) {
        case 1:                                                             //Switch som tar användaren till den funktionen innehåller det användaren vill gå till.
            printf("\nFunktion for: lista innehall\n");
            break;
        case 2:
            add_product(beer_list);
            break;
        case 3:
            search_list(beer_list);
            break;
        case 4:
            printf("\nFunktion for: Spara vara till fil\n");
            break;
        case 5:
            printf("\nFunktion for: Spara fil sedan break\n");
            break;
        default:     
            printf("\nInvalid entry, press 1 to go back to the menu or 0 to exit the program\n");
			scanf("%d", &retry);
			if (retry) {
				menu();
			} else {
				break;
			}
    }
}

void get_beer() {
	
	int i = 0;
    char *oneline, *tok;
    char envara[256];
    char delim[] = ",";
    
    FILE *fp; 
    
    if ((fp = fopen("varor.csv", "r")) == NULL) {
        fprintf(stderr, "Filen varor.csv gick inte att öppna\n");
        exit(-1);
    }
    
    while (fgets(envara, 256, fp) != NULL) {
    envara[strlen(envara) - 1] = '\0'; // Ta bort radslutstecknet
    
    oneline = strdup(envara);

    tok = strtok(oneline, delim); //// ta bort???! dubbelkolla
        while (tok != NULL) {
            beer_list[i].varunummer = atoi(tok);
            tok = strtok(NULL, delim);
			strcpy(beer_list[i].namn, tok);
			tok = strtok(NULL, delim);
			beer_list[i].pris = atof(tok);
			tok = strtok(NULL, delim);
			beer_list[i].volym = atof(tok);
			tok = strtok(NULL, delim);
			strcpy(beer_list[i].typ, tok);
			tok = strtok(NULL, delim);
			strcpy(beer_list[i].stil, tok);
			tok = strtok(NULL, delim);
			strcpy(beer_list[i].forpackning, tok);
			tok = strtok(NULL, delim);
			strcpy(beer_list[i].land, tok);
			tok = strtok(NULL, delim);
			strcpy(beer_list[i].producent, tok);
			tok = strtok(NULL, delim);
			beer_list[i].alkoholhalt = atof(tok);
			tok = strtok(NULL, delim);
			i++;
        }    
    }
	
    free(oneline); free(tok);
    fclose(fp);	
}

void search_list(struct product beer_list[]) {
	
	int varunummer, i = 0;
	int EXIT;
    int TRUE = 1;
	
    printf("Enter the 5 digit serialnumber of the product you're searching for: ");
    scanf("%d", &varunummer);
	while (TRUE) {
		if (varunummer == beer_list[i].varunummer) {
			printf("\nYour searched product is displayed below: \n");
			printf("\n%d\n%s\n%f\n%f\n%s\n%s\n%s\n%s\n%s\n%f\n",  beer_list[i].varunummer,
									      beer_list[i].namn,
									      beer_list[i].pris,
									      beer_list[i].volym,
								              beer_list[i].typ,
								              beer_list[i].stil,
									      beer_list[i].forpackning,
									      beer_list[i].land,
									      beer_list[i].producent,
									      beer_list[i].alkoholhalt);
			TRUE = 0;
			printf("\nPress 1 to search for a new product or 0 to go back to the main menu\n");
			scanf("%d", &EXIT);
				if (EXIT == 0) {
					menu();
				} else {
					search_list(beer_list);
				}
					
		} else {
	 		i++;
				if (i > 100) {
					printf("\nYour product isn't in our assortment, press 1 to try again or press 0 to return to menu\n");
					scanf("%d", &EXIT);
				if (EXIT == 0) {
					menu();
				} else {
					search_list(beer_list);
				}
			}
		}
	} 
}

void add_product(struct product beer_list[]) {
	
	get_beer();
	int varunummer, k = 55;
	int TRUE;
	
	printf("Enter the five digit serialnumber of your product you'd like to add: ");
	scanf("%d", &varunummer);
		for (int i = 0; i < 100; i++) {
			if (varunummer == beer_list[i].varunummer) {
				printf("\nA product with that serialnumber already exists, try again.\n\n");
				add_product(beer_list);
			}
		}
	
		// Kolla så att vi inte har över 100 element i struct array. Ifall över 100 skriv error meddelande. annars skippa och skriv in ny struct i array nedan
		// beer_list[99] == ..... 
	
		printf("Enter the following to add your product into our assortment\n");
			beer_list[k].varunummer = varunummer;
		printf("Name: ");
			scanf(" %s", beer_list[k].namn);
		printf("Price: ");
			scanf(" %f", &beer_list[k].pris);
		printf("Volume: ");
			scanf(" %f", &beer_list[k].volym);
		printf("Type: ");
			scanf(" %s", beer_list[k].typ);														//FELHANTERA MÅSTE VARA INT/FLOAT OSV TILL RÄTT STÄLLEN SÅ MAN INTE KAN SKRIVA IN VAD SOM HELST.
		printf("Style: ");
			scanf(" %s", beer_list[k].stil);
		printf("Packaging: ");
			scanf(" %s", beer_list[k].forpackning);
		printf("Country: ");
			scanf(" %s", beer_list[k].land);
		printf("Producer: ");
			scanf(" %s", beer_list[k].producent);
		printf("Alcohol percentage: ");
			scanf(" %f", &beer_list[k].alkoholhalt);
				k++;
					printf("\nEnter 1 to add another product or 0 to return to the menu: \n");
					scanf("%d", &TRUE);
						if (TRUE) {
							add_product(beer_list);
						} else {
							menu();
						}
}
	
