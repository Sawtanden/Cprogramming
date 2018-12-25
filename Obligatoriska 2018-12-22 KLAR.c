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
	
	/* Efter ett varv i loopen skrivs en vara från filen varor.csv in till
	 * ett element av strukt fältet. Detta pågår sålänge det finns varor som
	 * inte har blivit hämtade ur varor.csv. Alltså sålänge token inte == NULL
	 */
	 
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

	printf("\n******************************\n\n");
	printf("   1. List content\n\n");
	printf("   2. Add new product\n\n");
	printf("   3. Search for product\n\n");
	printf("   4. Save changes to file\n\n");
	printf("   5. Exit and save\n\n");    
	printf("******************************\n");
	
	printf("Please enter your choice (1-5): ");
	
	/* Här skriver användaren in ett heltal mellan 1-5 för att gå vidare i programmet.
	 * Om det inte är ett tal mellan 1-5 utan t.ex. 6 skickas man tillbaka till menyn.
	 * Det som användaren skriver in kollas i funktionen check_integer som ser till att
	 * det är en integer och inte en char eller en float som skrevs in till programmet.
	 */
	 
    int menu_choice = check_integer(input);
    switch (menu_choice) {
        case 1:    
			while(1) {
				printf("\nPress 1 to sort by serial number or 2 to sort by name: ");
				int sort_choice = check_integer(input);
				switch (sort_choice) {														//Switch sats i Switch sats för att kunna välja vilket alternative
					case 1: 																//man vill utföra. Sortera genom varunummer eller namn i detta fallet.
						sort_by_serialnumber(beer_list, input);								//Samtidigt som en ny kontroll av användarens inmatning inte är en char eller float.
						break;			
					case 2:
						sort_by_name(beer_list, input);	
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

void swap(product *xp, product *yp) { 								//swap funktion för bubblesort.
  product temp = *xp;
  *xp = *yp;
  *yp = temp;
}

void sort_by_serialnumber(product beer_list[], int input) {

	int n;
	
	/* Loopen tar reda på hur många element som finns i 
	 * struct fältet vid tillfället som man anropar denna funktionen
	 */
	 
	for (n = 0; n < 100; n++) {
		if (beer_list[n].varunummer == '\0') {
			break;
		}
	}
	
	/* Bubblesort för att sortera alla element i structfältet
	 * Här används informationen som togs fram och lades i variabeln n.
	 */
	
	for(int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (beer_list[j].varunummer > beer_list[j+1].varunummer) {
				swap(&beer_list[j], &beer_list[j+1]);
			}
		}
	}
		
	/* Skriver ut alla element i struct fältet med passande 
	 * rubriker ovanför dem. Samtidigt som avståndet mellan de olika
	 * elementen har sats till olika värden för att få det att skrivas 
	 * ut på ett snyggt sätt
	 */
	 
	printf("\n    Number:             Name:                       	      Price:   Volume:              Type:  			    Style:    	         Packaging:  Country:        	    	   Producer:   	     Alcohol percentage:\n");
	for(int antal_varor = 0; antal_varor < n; antal_varor++) {	
		printf("\n%-4d%-8d %-48s %-8.2f %-8.2f %-30s %-27s %-10s %-23s %-29s %.2f", 
			antal_varor+1,
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
	
	/* Här låter man användaren välja om man vill sortera genom namn eller gå tillbaka
	 * till menyn efter att sorteringen av varunummer har gjorts. Istället för att
	 * skicka användaren till menyn automatiskt efter operationen ger man här användaren ett val.
	 * 4an bestämmer vart funktionen continuation_check ska skicka användaren genom en switch sats
	 * när den anropas just från denna funktionen.
	 */
	 
	printf("Press 1 to sort by name or 0 to return to main menu: ");
	continuation_check(input, 4);										
}

void sort_by_name(product beer_list[], int input) {

	/* Denna funktionen fungerar på exakt samma sätt som funktionen sort_by_serialnumber förrutom
	 * att när man anropar funktionen continuation_check så skickas en 3a istället. Vilket kommer
	 * ändra vart i programmet man skickas efter att man gjort sitt val*/
	 
	int n;
	
	for (n = 0; n < 100; n++) {
		if (beer_list[n].varunummer == '\0') {
			break;
		}
	}
			
	for(int i = 0; i < n - 1; i++) {																		
		for (int j = 0; j < n - i - 1; j++) {
			if (strcmp(beer_list[j].namn, beer_list[j+1].namn) > 0) {
				swap(&beer_list[j], &beer_list[j + 1]);
			}
		}
	}
	
	printf("\n    Number:             Name:                       	       Price:   Volume:             Type:  			    Style:    	         Packaging:  Country:        	    	  Producer:   	     Alcohol percentage:\n");
	for(int antal_varor = 0; antal_varor < n; antal_varor++) {	
		printf("\n%-4d%-8d %-48s %-8.2f %-8.2f %-30s %-27s %-10s %-23s %-29s %.2f",
			antal_varor+1,
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
	printf("Press 1 to sort by number or 0 to return to main menu: ");
	continuation_check(input, 3);
}


::::::SORT_FUNCTIONS::::::

::::::ADD_FUNCTION::::::

int add_product(product beer_list[], int input) {
	
	int nr_of_products;
	char length_check_add[30];
	


	for (nr_of_products = 0; nr_of_products < 100; nr_of_products++) {						//Loop för att ta fram antal varor som förnärvarande finns i struct fältet
		if (beer_list[nr_of_products].varunummer == '\0') {									//som läggs i variablen nr_of_products.
			break;
		} 
		if (nr_of_products == 99) {															//En kontroll som kollar att antal varor inte överstiger 100st. 
			printf("\nWe've reached the limit of products you can add to our store.\n");	//Skulle antal varor nå 100 kommer ett passande meddelande skrivas ut.
			printf("Please remove a few products from the file varor.csv to continue\n\n");
			menu(input);
		}
	}	
	
	/* Här görs en kontroll att varunummret som skrivs in är 5 siffror långt.
	 * Detta är inte nödvändigt då det inte hade förändrat något om man kunde välja
	 * ett tal under 5 siffror eller över. Detta görs enbart för att det ser bättre ut.
	 */
	
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
	
	/* En kontroll att varunummret som användare skriver in inte
	 * finns i sortimentet redan. Är detta fallet skriver programmet ut
	 * ett passande meddelande och så får användaren anvälja om den vill
	 * testa igen med ett annat varunummer eller gå tillbaka till huvudmenyn.
	 */
	
	int varunummer = atoi(length_check_add);																	
	for (int i = 0; i < 100; i++) {																
		if (varunummer == beer_list[i].varunummer) {						             
			printf("\nA product with that serial number already exists, try again.\n\n");
			printf("Press 1 to search again or 0 to return to main menu: ");
			continuation_check(input, 2);
		}
	}
	
	/* Varunummret användaren skrev in läggs in i struct fältet därefter
	 * körs användaren igenom lägg till produkt processen där man skickas till
	 * en funktion som utför alla kontroller av användarens inmatning.*/
	 
	beer_list[nr_of_products].varunummer = varunummer;
		
	printf("Enter the following to add your product into our assortment\n");
	fflush(stdin);
	printf("Name: ");
		check_space_and_float(beer_list, nr_of_products);
	printf("Press 1 to add another product or 0 to return to main menu: ");
		continuation_check(input, 2);
		
		return(nr_of_products);							
}

void check_space_and_float(product beer_list[], int nr_of_products) {
	
	int check = 1;
    int switch_option = 0, comma_counter = 0, letter_counter = 0;
    char struct_option[50];
    char float_check[40];
    
	/* Varje gång användaren matar in något så kontrolleras det att
	 * det inte är några tomma fält som skrivs in till char fältet.
	 * Efter kontrollerna läggs användarens inmatningar i element hos en ny struct
	 * som sedan läggs i struct fältet.
	 */
	 
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
					
	/* Switch satsen är till för att föra användaren genom alla kategorier som ska skrivas in.
	 * Efter varje kategori ökar switch_option med 1 och nästa gång man går igenom loopen har man gått
	 * ned ett steg i switch satsen. Tills alla char fält fått indata från användaren.
	 */
	 
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
	
	/* Här testas användarens inmatning om det är en float. Är det inte en float
	 * d.v.s ett heltal med bara EN decimalpunkt kommer programmet att varna och användaren
	 * Får försöka igen. Samtidigt som switch_option variabeln fortsätter att ta användaren ner 
	 * i switch satsen.
	 */
	 
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

void search_list(product beer_list[], int input) {

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
	
	/* Whileloop som testar användarens inmatade värde på varunummer med alla 
	 * varunummer element i struct fältet med hjälp av variabeln i. Om varunummret
	 * användaren matar in finns i struct fältet hos en produkt kommer all information
	 * om den produkten att skrivas ut på skrämen. Om produkten inte finns i sortimentet d.v.s
	 * om i är större än 100 kommer ett meddelande att skrivas ut med denna informationen.
	 * Samtidigt som användaren får sin återkommande check med funktionen continuation_check.
	 */
	 
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
				
	printf("Press 1 to search again or 0 to return to main menu: ");			
	continuation_check(input, 1);
				
			} else {
				i++;
				if(i > 100) {
					printf("\nYour product isn't in our assortment, Press 1 to try again or 0 to return to main menu: ");
					continuation_check(input, 1);
				}
			}
		}
}



::::::SEARCH_FUNCTIONS::::::

::::::SAVE_FILE_FUNCTIONS::::::

void save_file(product beer_list[]) {
	
	/* Öppnar ström för fp och gör programmet redo att skriva ut information till
	 * varor.csv filen. Loopen kör igenom struct fältet tills att varunummer platsen
	 * är tom. Alltså när första elementet i det fältet är \0.
	 */
	int i = 0;
	FILE *fp = fopen("varor.csv", "w");
		if (fp == NULL) {
			fprintf(stderr, "There was an error trying to open the file\n");
			exit(-1);
		} 
		
		while (beer_list[i].varunummer != '\0') {
			fprintf(fp, "%d,%s,%f,%f,%s,%s,%s,%s,%s,%f\n",	
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
				i++;
		}
	fclose(fp);
	printf("\nThe current assortment has been updated\n\n");
}


::::::SAVE_FILE_FUNCTIONS::::::

::::::CHECK_INTEGER_FUNCTIONS::::::

int check_integer() {    

	char int_check[30];
	
	/*Integer kontroll, tar fram längden på strängen som skrivs in av 
	 * användaren och sätter upp en forloop som kör genom hela strängen.
	 * Samtidigt som varje element kontrolleras. Är det något annat än ett heltal
	 * som skrivs in till int_check skrivs en felmeddelande ut. Är det istället
	 * ett heltal som skrivs in kommer detta att retuneras tillbaka dit funktionen
	 * anropades från med värdet som skrevs in.
	 */
	 
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
	
	/* Användarens inmatning kontrolleras så att det är heltalen 1 eller 0. 
	 * Första switchen kollar om talet är 1 går man vidare in till den andra switchen.
	 * Den andra switch satsen beror på variabeln check som
	 * får sitt värde från nummret i parametern därifrån den anropades.
	 * T.ex. i funktionen add_product är 2 det värde som kommer att 
	 * läggas i variabeln check. Detta kommer göra att antingen får användaren
	 * lägga till en till product eller så skickas man tillbaka till menyn.
	 */
	 
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
							sort_by_serialnumber(beer_list, input);
						case 4:
							sort_by_name(beer_list, input);
					}
				default: 
					printf("Press 1 to try again or 0 to go to main menu: ");
			}
	}
}



::::::CONTINUATION_FUNCTIONS::::::
