#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int comparison(char matchresult[], char rattrad[]);

int main(void)  {

    srand(time(NULL));
    char filename[2024];												// Sätter upp variabel och fält för att skriva in filer till fälten samt skriva ut från fälten vid rättningen i funktionen.
    char correct_row[200];
	char match_result[200];
    const char txt[4] = ".txt";
    
    printf("Enter in the name of your file and it will be solved: ");
    scanf("%s", filename);
    
    strcat(filename, txt);												// Använder strcat för att sätta ihop filnamnet från användaren 																	
																		// och .txt för att alltid få ut en text fil.
    FILE *out_file = fopen(filename, "w");									
        if(out_file == NULL)  {											// Skapar en text fil med namnet från användaren.
            printf("There was an error creating your file.\n");   
            exit(-1);             
        }
	
	printf("\nDin stryktipskupong: \n");
	
    for (int i=1; i<14; i++) {											// Forloop för att skriva ut slumpmässiga tal genom rand() modulo 3.
        int j = rand() % 3;												// samtidigt som ett tecken per varv skrivs in i textfilen som användaren skapar.
            if (j == 1) {
                printf("Match %2d: 1\n",i);
                fprintf(out_file,"%d",1);
            } else if (j == 0) {
                printf("Match %2d:   X\n",i);
				fprintf(out_file,"%c",'X');
            } else {
                printf("Match %2d:     2\n",i);
				fprintf(out_file,"%d",2);
            }
            if (i < 13) {
                 fprintf(out_file, ",");									// Sätter in kommatecken mellan varje inskrivet tecken från forloopen.
            }
    }
	
	fclose(out_file);
	
	FILE *in_file = fopen(filename, "r");								 
        if(in_file == NULL)  {										   	// Skriver in innehållet från text filen användaren skapade
            printf("Couldn't open file file.\n");   					// och lägger det i fältet matchresult.
            exit(-1);             
        }
		
			fgets(match_result, 200, in_file);							// Skriver in rad för rad från strömmen. Eftersom filen bara har en rad 
			fclose(in_file);												// som ska skrivas ut görs detta utan en whileloop.
	
    FILE *comparison_row = fopen("C:\\Users\\Sawball\\Documents\\C programmering\\C\\Debug\\RattRad.csv", "r");
        if (comparison_row == NULL) {
            printf("Couldn't open file\n");
            exit(-1);
        }

			fgets(correct_row, 200, comparison_row);
			fclose(comparison_row);
		
	printf("\nAntal ratt: %d\n", comparison(match_result, correct_row));	
	
}

int comparison(char match_result[], char correct_row[]) {				// Funktion som tar in de två fälten vi skrivit in tidigare
    int right_answers = 0;												// och kontrollerar för varje element om de två fälten är lika.
    for (int i = 0; i < 26; i++) {										// Vid lika ökas variabeln right_answers som sedan skrivs ut till main.
        if (match_result[i] == correct_row[i]) {
            right_answers++;
        }
    i++;																// i++ för att hoppa över och undvika kommatecknen i text filerna  
    }																 	// då vi bara är intresserade av resultatet.
    return(right_answers);
}
