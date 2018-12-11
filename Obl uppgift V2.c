#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menu() {
	
	int option, retry, sort = 0;

	printf("1. Lista Innehall\n\n");
    printf("\n2. Lagg till ny vara\n\n");
    printf("\n3. Sok bland varor\n\n");
    printf("\n4. Spara vara till fil\n\n");
    printf("\n5. Avsluta\n\n");    
    
    printf("Please enter your choice: ");
    scanf("%d", &option);

    switch (option) {
        case 1:    
			printf("\nPress 1 to sort by serialnumber or 2 to sort by name\n");
			scanf("%d", &sort);
			switch (sort) {
				case 1: 
					sort_content_serialnumber(beer_list);
					break;			
				case 2:
					sort_content_name(beer_list);	
					break;
			}	
        case 2:
            add_product(beer_list);
            break;
        case 3:
            search_list(beer_list);
            break;
        case 4:
            save_file(beer_list);
			menu();
            break;
        case 5:
            save_file(beer_list);
            exit(-1);
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
    
    if ((fp = fopen("varortest.csv", "r")) == NULL) {
        fprintf(stderr, "Filen varor.csv gick inte att öppna\n");
        exit(-1);
    }
    
    while (fgets(envara, 256, fp) != NULL) {
    envara[strlen(envara) - 1] = '\0'; // Ta bort radslutstecknet
    
    oneline = strdup(envara);

    tok = strtok(oneline, delim);
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

	get_beer(beer_list);
	int varunummer, i = 0;
	int EXIT;
    int TRUE = 1;
	
    printf("Enter the 5 digit serialnumber of the product you're searching for: ");
    scanf("%d", &varunummer);
		while (TRUE) {
			if (varunummer == beer_list[i].varunummer) {
				printf("\nYour searched product is displayed below: \n");
				printf("\nSerialnumber: %d\nName: %s\nPrice: %f\nVolym: %f\nType: %s\nStyle: %s\nPackaging: %s\nCountry: %s\nProducer: %s\nAlcohol content: %f\n", 
					beer_list[i].varunummer,
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
	
	get_beer(beer_list);
	int varunummer, j;
	int TRUE;
	for (j = 0; j < 100; j++) {
		if (beer_list[j].varunummer == '\0') {
			break;
		} 
		if (j == 99) {
			printf("\nWe've reached the limit of products you can add to our store. Please remove a few products from the file varor.csv to continue\n\n");
			menu();
		}
	}
	
	printf("Enter the five digit serialnumber of your product you'd like to add: ");
	scanf("%d", &varunummer);
		for (int i = 0; i < 100; i++) {
			if (varunummer == beer_list[i].varunummer) {
				printf("\nA product with that serialnumber already exists, try again.\n\n");
				add_product(beer_list);
			}
		}
	
		printf("Enter the following to add your product into our assortment\n");
			beer_list[j].varunummer = varunummer;
		printf("Name: ");
			scanf(" %s", beer_list[j].namn);													///beer_list[i].varunummer != '\0' använd detta i if sats för att se om char som blev inskriven hade ett tecken eller inte.
		printf("Price: ");
			scanf(" %f", &beer_list[j].pris);
		printf("Volume: ");
			scanf(" %f", &beer_list[j].volym);
		printf("Type: ");
			scanf(" %s", beer_list[j].typ);														//FELHANTERA MÅSTE VARA INT/FLOAT OSV TILL RÄTT STÄLLEN SÅ MAN INTE KAN SKRIVA IN VAD SOM HELST.
		printf("Style: ");	
			scanf(" %s", beer_list[j].stil);
		printf("Packaging: ");
			scanf(" %s", beer_list[j].forpackning);
		printf("Country: ");
			scanf(" %s", beer_list[j].land);
		printf("Producer: ");
			scanf(" %s", beer_list[j].producent);
		printf("Alcohol percentage: ");
			scanf(" %f", &beer_list[j].alkoholhalt);
				printf("\nEnter 1 to add another product or 0 to return to the menu: \n");
				scanf("%d", &TRUE);
					if (TRUE) {
						add_product(beer_list);
					} else {
						menu();
					}
}
	
void save_file(struct product beer_list[]) {
	 
	int i = 0;
	FILE *fp = fopen("varortest.csv", "w");
		if (fp == NULL) {
			fprintf(stderr, "There was an error trying to open the file\n");
			exit(-1);
		} 
		
		do {
		fprintf(fp, "%d,%s,%f,%f,%s,%s,%s,%s,%s,%f\n",	beer_list[i].varunummer,	
														beer_list[i].namn,
														beer_list[i].pris,
														beer_list[i].volym,
														beer_list[i].typ,
														beer_list[i].stil,
														beer_list[i].forpackning,
														beer_list[i].land,
														beer_list[i].producent,
														beer_list[i].alkoholhalt);																																		
		i++;
		}
		while (beer_list[i].varunummer != '\0');                      
		fclose(fp);
			printf("\nThe current assortment has been updated\n\n");		
}

void sort_content_serialnumber(struct product beer_list[]) {

		get_beer(beer_list);
		struct product temp;
		int n;
		
            for (n = 0; n < 100; n++) {
                if (beer_list[n].varunummer == '\0') {
                    break;
				}
			}
		
		for(int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (beer_list[j].varunummer > beer_list[j+1].varunummer) {
					temp = beer_list[j];
					beer_list[j] = beer_list[j+1];
					beer_list[j+1] = temp;
				}
			}
		}
	for(int p = 0; p < n; p++) {
		printf("\n%d %s %f %f %s %s %s %s %s %f",	beer_list[p].varunummer,       
													beer_list[p].namn,
													beer_list[p].pris,
													beer_list[p].volym,
													beer_list[p].typ,
													beer_list[p].stil,
													beer_list[p].forpackning,
													beer_list[p].land,
													beer_list[p].producent,
													beer_list[p].alkoholhalt);
			if (p == n-1) {
				printf("\n");
			}
	}
	menu();
}

void sort_content_name(struct product beer_list[]) {

		get_beer(beer_list);
		struct product temp;
		int n;
		
			for (n = 0; n < 100; n++) {
                if (beer_list[n].varunummer == '\0') {
                    break;
				}
			}
			
        for(int i = 0; i < n - 1; i++) {																		
            for (int j = 0; j < n - i - 1; j++) {
				if (strcmp(beer_list[j].namn, beer_list[j+1].namn) > 0) {
					temp = beer_list[j];
					beer_list[j] = beer_list[j+1];
					beer_list[j+1] =  temp;
                }
            }
        }
        
        for(int p = 0; p < n; p++) {
            printf("\n%d %s %f %f %s %s %s %s %s %f", beer_list[p].varunummer,
                                                      beer_list[p].namn,
                                                      beer_list[p].pris,
                                                      beer_list[p].volym,
                                                      beer_list[p].typ,
                                                      beer_list[p].stil,
                                                      beer_list[p].forpackning,
                                                      beer_list[p].land,
                                                      beer_list[p].producent,
                                                      beer_list[p].alkoholhalt);
                if (p == n-1) {    
                    printf("\n");
                }
        }    
        menu();
}
