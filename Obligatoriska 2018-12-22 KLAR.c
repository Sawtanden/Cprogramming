::::::MAIN::::::

#include "product.h"
#include "get_beer.c"
#include "check_integer.c"
#include "continuation.c"
#include "menu.c"
#include "sort_functions.c"
#include "add_function.c"
#include "search_function.c"
#include "save_file.c"

int main(input) {
	menu(input);
	return 0;
}

::::::MAIN::::::

::::::HEADER FILE::::::

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct product {
    int varunummer;
    char namn[100];
    float pris;
    float volym;
    char typ[100];
    char stil[100];
    char forpackning[50];
    char land[50];
    char producent[100];
    float alkoholhalt;
};

void menu(int input);
void get_beer();
void continuation_check(int input, int check);
void search_list(struct product [], int input);
int add_product(struct product [], int input);
void save_file(struct product []);
void sort_content_serialnumber(struct product [], int input);
void sort_content_name(struct product [], int input);
void check_add(struct product [], int nr_of_products);
int check_integer();

struct product beer_list[100];


::::::HEADER FILE::::::

::::::GET_BEER_FUNCTION::::::

void get_beer() {

	int i = 0;
    char *oneline, *tok;
    char envara[256];
    char delim[] = ",";
    
    FILE *fp; 
    
    if ((fp = fopen("varor.csv", "r")) == NULL) {
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

::::::GET_BEER_FUNCTION::::::

::::::MENU_FUNCTION::::::

void menu(int input) {
	
	printf("******************************\n\n");
	printf("   1. List content\n\n");
	printf("   2. Add new product\n\n");
	printf("   3. Search for product\n\n");
	printf("   4. Save changes to file\n\n");
	printf("   5. Exit and save\n\n");    
	printf("******************************\n");
	
	printf("Please enter your choice (1-5): ");

    int menu_choice = check_integer(input);
    switch (menu_choice) {
        case 1:    
			while(1) {
				printf("\nPress 1 to sort by serial number or 2 to sort by name\n");
				int sort_choice = check_integer(input);
				switch (sort_choice) {
					case 1: 
						sort_content_serialnumber(beer_list, input);
						break;			
					case 2:
						sort_content_name(beer_list, input);	
						break;
				}
			}	
        case 2:
            add_product(beer_list, input);
            break;
        case 3:
            search_list(beer_list, input);
            break;
        case 4:
            save_file(beer_list);
			menu(input);
            break;
        case 5:
            save_file(beer_list);
            exit(-1);
        default:  
			menu(input);
			break;
	}
}

::::::MENU_FUNCTION::::::

::::::SORT_FUNCTIONS::::::
void sort_content_serialnumber(struct product beer_list[], int input) {

	struct product temp;
	int n;
	save_file(beer_list);
		
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
		
	printf("    Number:             Name:                       	       Price:   Volume:             Type:  			    Style:    	          Packaging:   Country:        	    	   Producer:   	     Alcohol percentage:\n");
	for(int antal_varor = 0; antal_varor < n; antal_varor++) {	
		printf("\n%-4d %-8d %-48s %-8.2f %-8.2f %-30s %-27s %-10s %-23s %-29s %.2f", antal_varor+1,
		 beer_list[antal_varor].varunummer,       
		 beer_list[antal_varor].namn,
		 beer_list[antal_varor].pris,
		 beer_list[antal_varor].volym,
		 beer_list[antal_varor].typ,
		 beer_list[antal_varor].stil,
		 beer_list[antal_varor].forpackning,
		 beer_list[antal_varor].land,
		 beer_list[antal_varor].producent,
		 beer_list[antal_varor].alkoholhalt);
		if (antal_varor == n-1) {
			printf("\n\n");
		}
	}
	printf("Press 1 to sort by name or 0 to return to main menu\n");
	continuation_check(input, 4);
}

void sort_content_name(struct product beer_list[], int input) {

	struct product temp;
	int n;
	save_file(beer_list);
		
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
	
	printf("    Number:             Name:                       	       Price:   Volume:             Type:  			    Style:    	          Packaging:   Country:        	    	  Producer:   	     Alcohol percentage:\n");
	for(int antal_varor = 0; antal_varor < n; antal_varor++) {	
		printf("\n%-4d %-8d %-48s %-8.2f %-8.2f %-30s %-27s %-10s %-23s %-29s %.2f", antal_varor+1,
		 beer_list[antal_varor].varunummer,       
		 beer_list[antal_varor].namn,
		 beer_list[antal_varor].pris,
		 beer_list[antal_varor].volym,
		 beer_list[antal_varor].typ,
		 beer_list[antal_varor].stil,
		 beer_list[antal_varor].forpackning,
		 beer_list[antal_varor].land,
		 beer_list[antal_varor].producent,
		 beer_list[antal_varor].alkoholhalt);
		if (antal_varor == n-1) {
			printf("\n\n");
		}
	}
	printf("Press 1 to sort by number or 0 to return to main menu\n");
	continuation_check(input, 3);
}

::::::SORT_FUNCTIONS::::::

::::::ADD_FUNCTION::::::

int add_product(struct product beer_list[], int input) {
	
	int nr_of_products;
	char length_check_add[30];
	
	for (nr_of_products = 0; nr_of_products < 100; nr_of_products++) {
		if (beer_list[nr_of_products].varunummer == '\0') {
			break;
		} 
		if (nr_of_products == 99) {
			printf("\nWe've reached the limit of products you can add to our store.\n");
			printf("Please remove a few products from the file varor.csv to continue\n\n");
			menu(input);
		}
	}	
	
    printf("Enter the 5 digit serial number of the product you'd like to add: ");
	while(1) {
		int varunummer = check_integer(input);
			sprintf(length_check_add, "%d", varunummer);
				int length = strlen(length_check_add);       
				if(length != 5) {
					printf("Enter a 5 digit serial number: ");
				} else {
					break;
				}
	}
	
	int varunummer = atoi(length_check_add);																	
	for (int i = 0; i < 100; i++) {																
		if (varunummer == beer_list[i].varunummer) {						             
			printf("\nA product with that serial number already exists, try again.\n\n");
			printf("Press 1 to search again or 0 to return to main menu\n");
			continuation_check(input, 2);
		}
	}		
	beer_list[nr_of_products].varunummer = varunummer;
		
	printf("Enter the following to add your product into our assortment\n");
	fflush(stdin);
	printf("Name: ");
		check_add(beer_list, nr_of_products);
	
	printf("Press 1 to add another product or 0 to return to main menu\n");
		continuation_check(input, 2);
		
		return(nr_of_products);	
}



void check_add(struct product beer_list[], int nr_of_products) {
	
	int check = 1;
	int switch_option = 0, comma_counter = 0, letter_counter = 0;
	char struct_option[50];
	char float_check[40];
	
	while(check) {
		fflush(stdin);
		fgets(struct_option, sizeof(struct_option), stdin);
			if(struct_option[0] == '\n') {
				printf("An error was found, try again: ");
			} else {
				int length = strlen(struct_option);
					if (struct_option[length-1] == '\n') {
						struct_option[length-1] = '\0';
					}
					switch(switch_option) {
						case 0:
							strcpy(beer_list[nr_of_products].namn, struct_option);
							switch_option++;
							printf("Type: ");
							break;
						case 1:
							strcpy(beer_list[nr_of_products].typ, struct_option);
							switch_option++;
							printf("Style: ");
							break;
						case 2:
							strcpy(beer_list[nr_of_products].stil, struct_option);
							switch_option++;
							printf("Packaging: ");
							break;
						case 3:
							strcpy(beer_list[nr_of_products].forpackning, struct_option);
							switch_option++;
							printf("Country: ");
							break;
						case 4:
							strcpy(beer_list[nr_of_products].land, struct_option);
							switch_option++;
							printf("Producer: ");
							break;
						case 5:
							strcpy(beer_list[nr_of_products].producent, struct_option);
							check = 0;
							break;
					}
			}
	}
	
	check = 1;
	printf("Price: ");
		while(check) {
			fflush(stdin);
			fgets(float_check, 40, stdin);   
			int length_comma = strlen(float_check);
				for(int k = 0; k < length_comma; k++) {
					if(float_check[k] == '.') {
						comma_counter++;
					}
					if(isalpha(float_check[k])) {
						letter_counter++;
					}
				}
				
				if(comma_counter == 1 && letter_counter == 0 && float_check[0] != '.') {
					switch(switch_option) {
						case 5: 
							beer_list[nr_of_products].pris = atof(float_check);
							printf("Volume: ");
							comma_counter = 0;
							switch_option++;
							break;
						case 6:
							beer_list[nr_of_products].volym = atof(float_check);
							printf("Alkohol percentage: ");
							comma_counter = 0;
							switch_option++;
							break;
						case 7:
							beer_list[nr_of_products].alkoholhalt = atof(float_check);
							check = 0;
							break;
					}
				} else {
					printf("Please enter a float value, try again: ");
					comma_counter = 0;
					letter_counter = 0;
			}
			
		}
}

::::::ADD_FUNCTIONS::::::

::::::SEARCH_FUNCTIONS::::::

void search_list(struct product beer_list[], int input) {

	int i = 0;
	int search_loop = 1;
	char length_check_search[30];
	
    printf("Enter the 5 digit serial number of the product you're searching for: ");
	while(1) {
		int varunummer = check_integer(input);
			sprintf(length_check_search, "%d", varunummer);
				int length = strlen(length_check_search);
				if(length != 5) {
					printf("Enter a 5 digit serial number: ");
				} else {
					break;
				}
	}
	
	int varunummer = atoi(length_check_search);
		while (search_loop) {
			if(varunummer == beer_list[i].varunummer) {
				printf("\nYour searched products information is displayed below: \n");
				printf("\nSerial number: %d\nName: %s\nPrice: %.2f\nVolym: %.2f\nType: %s\nStyle: %s\nPackaging: %s\nCountry: %s\nProducer: %s\nAlcohol: %.2f\n\n", 
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
				
	printf("Press 1 to search again or 0 to return to main menu\n");			
	continuation_check(input, 1);
				
			} else {
				i++;
				if(i > 100) {
					printf("\nYour product isn't in our assortment, Press 1 to try again or 0 to return to main menu\n");
					continuation_check(input, 1);
				}
			}
		}
}

::::::SEARCH_FUNCTIONS::::::

::::::SAVE_FILE_FUNCTIONS::::::

void save_file(struct product beer_list[]) {
	 
	int i = 0;
	FILE *fp = fopen("varor.csv", "w");
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

::::::SAVE_FILE_FUNCTIONS::::::

::::::CHECK_INTEGER_FUNCTIONS::::::

int check_integer(int check) {    

	char int_check[30];
	
	while(1) {
        scanf("%s", int_check);  
            int length = strlen(int_check);
            for(int i = 0; i < length; i++) {
                if (!isdigit(int_check[i])) {
                    printf("\nEntered input isnt an integer, try again: \n\n"); 
					int input = atoi(int_check);
					menu(input);
				}
			}
		break;
	}
	int input = atoi(int_check);
	return(input);
}
	
::::::CHECK_INTEGER_FUNCTIONS::::::

::::::CONTINUATION_FUNCTIONS::::::

void continuation_check(int input, int check) {	
	
	while(1) {
		int search_check = check_integer(input);
			switch(search_check) {
				case 0: 
					menu(input);
				case 1:
					switch(check) {
						case 1:
							search_list(beer_list, input);
						case 2: 
							add_product(beer_list, input);
					    case 3:
							sort_content_serialnumber(beer_list, input);
						case 4:
							sort_content_name(beer_list, input);
					}
				default: 
					printf("Press 1 to try again or 0 to go to main menu\n");
			}
	}
}

::::::CONTINUATION_FUNCTIONS::::::
