void menu() {
	
	int option, retry, sort = 0;

	printf("1. List content\n\n");
    printf("\n2. Add new product\n\n");
    printf("\n3. Search for product\n\n");
    printf("\n4. Save changes to file\n\n");
    printf("\n5. Exit and save\n\n");    
    
    printf("Please enter your choice: ");
    scanf("%d", &option);

    switch (option) {
        case 1:    
			printf("\nPress 1 to sort by serial number or 2 to sort by name\n");
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
				exit(1);
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
        fprintf(stderr, "File varor.csv couldn't be opened\n");
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
	int search_loop = 1;
	
    printf("Enter the 5 digit serial number of the product you're searching for: ");
	scanf("%d", &varunummer);
		while (search_loop) {
			if (varunummer == beer_list[i].varunummer) {
				printf("\nYour searched products information is displayed below: \n");
				printf("\nSerial number: %d\nName: %s\nPrice: %.2f\nVolym: %.2f\nType: %s\nStyle: %s\nPackaging: %s\nCountry: %s\nProducer: %s\nAlcohol: %.2f\n", 
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
					
				search_loop = 0;
				printf("\nEnter 1 to search for a new product or 0 to go back to the main menu: ");  
				check_integer(beer_list);
				search_list(beer_list);
			} else {
				i++;
				if (i > 99) {
					printf("\nYour product isn't in our assortment, Try again with a different serial number\n");
					search_list(beer_list);
				}
			}
		}
} 

int add_product(struct product beer_list[]) {
	
	get_beer(beer_list);
	int varunummer, j;
	
	for (j = 0; j < 100; j++) {
		if (beer_list[j].varunummer == '\0') {
			break;
		} 
		if (j == 100) {
			printf("\nWe've reached the limit of products you can add to our store. Please remove a few products from the file varor.csv to continue\n\n");
			menu();
		}
	}
	
	printf("Enter the five digit serial number of your product you'd like to add: ");
	while (1) {
    scanf("%d", &varunummer);
		if(varunummer >= 10000 && varunummer <= 99999) {  
			break;
		} else {
			printf("Please enter a five digit serial number to proceed: ");
		}
	}
	
		for (int i = 0; i < 100; i++) {
			if (varunummer == beer_list[i].varunummer) {						             
				printf("\nA product with that serial number already exists, try again.\n\n");
				add_product(beer_list);
			}
		}		
		beer_list[j].varunummer = varunummer;
		
	printf("Enter the following to add your product into our assortment\n");
	fflush(stdin);
	printf("Name: ");
		check_string_float(beer_list, j);
		
	printf("\nEnter 1 to add another product or 0 to return to the menu: ");
	check_integer(beer_list);
	add_product(beer_list);
	
	return(j);	
}

	
void save_file(struct product beer_list[]) {
	 
	int i = 0;
	FILE *fp = fopen("varortest.csv", "w");
		if (fp == NULL) {
			fprintf(stderr, "There was an error trying to open the file\n");
			exit(-1);
		} 
		
		do {
		fprintf(fp, "%d,%s,%2f,%2f,%s,%s,%s,%s,%s,%2f\n",	beer_list[i].varunummer,	
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
		printf("\n%d %s %.2f %.2f %s %s %s %s %s %.2f",	beer_list[p].varunummer,       
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
		printf("\n%d %s %.2f %.2f %s %s %s %s %s %.2f", beer_list[p].varunummer,
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

void check_string_float(struct product beer_list[], int j) {
	
	int check = 1;
	int i = 0;
	char struct_option[50];
	float check_float;
	
	while(check) {
		fflush(stdin);
		fgets(struct_option, sizeof(struct_option), stdin);
			if(struct_option[0]=='\n') {
				printf("An error was found, try again: ");
			} else {
				int len = strlen(struct_option);
					if (struct_option[len-1]=='\n') {
						struct_option[len-1]='\0';
					}
					switch(i) {
						case 0:
							strcpy(beer_list[j].namn, struct_option);
							i++;
							printf("Type: ");
							break;
						case 1:
							strcpy(beer_list[j].typ, struct_option);
							i++;
							printf("Style: ");
							break;
						case 2:
							strcpy(beer_list[j].stil, struct_option);
							i++;
							printf("Packaging: ");
							break;
						case 3:
							strcpy(beer_list[j].forpackning, struct_option);
							i++;
							printf("Country: ");
							break;
						case 4:
							strcpy(beer_list[j].land, struct_option);
							i++;
							printf("Producer: ");
							break;
						case 5:
							strcpy(beer_list[j].producent, struct_option);
							check = 0;
							break;
					}
			}
	}
	
	check = 1;
	printf("Price: ");
		while(check) {
			fflush(stdin);
			if (scanf("%f", &check_float) == 1) {
				switch(i) {
					case 5: 
						beer_list[j].pris = check_float;
						printf("Volume: ");
						i++;
						break;
					case 6:
						beer_list[j].volym = check_float;
						printf("Alkoholhalt: ");
						i++;
						break;
					case 7:
						beer_list[j].alkoholhalt = check_float;
						check = 0;
						break;
				}
			} else {
				printf("Please enter in a float value for the price: ");
				fflush(stdin);
			}
		}
}

void check_integer(struct product beer_list[]) {
	
	int check = 1;
	float check_float;
	
	while(check) {
		fflush(stdin);
		if (scanf("%f", &check_float) == 1) {
			if (check_float == 1) {
				check = 0;
			} else {
				menu();
			}
		} else {
			printf("\nYou've entered a character please enter 1 to try again or 0 to return to the main menu: ");
		}
	}
}

