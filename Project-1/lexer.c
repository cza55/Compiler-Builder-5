#include <stdio.h>
#include <string.h>
#include <ctype.h>

void PrintLines(int input);
void PrintTokens(FILE *ifp);

typedef enum token {nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6, slashsym = 7, oddsym = 8,
eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12,
gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19,      
becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, 
		    constsym = 28, varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33} token_type;

int main(int argc, char* argv[]){
	FILE *ifp = fopen(argv[1],"r");
	//char temp[13];
	char current;
	int i, counter=0, comment, halt=0;
	
	//memset(temp, '\0', 12);

	PrintTokens(ifp);
    // Close the file from reading
    fclose(ifp);

    return 0;
}


// Prints output if --source or --clean are given as command arguments
//if commentsIncluded = 1, print comments. If 0, don't.
void PrintLines(int commentsIncluded){

}


// Reads in each token and prints the values
// Should consist of an obnoxiously large switch statement to handle the tokens
void PrintTokens(FILE *ifp)
{
    char current; // stores fgetc returned char
    int found = 0; // used for finding end of comment
    
    while(!feof(ifp)){

	current = fgetc(ifp);

	// filters out white space from the rest of the if-statements
	if(!isspace(current))
	{
	    // Check to see if the current character is a character other than a letter or number
	    if(!isalpha(current) && !isdigit(current))
	    {
		switch(current)
	        {
		    // possible comment case
		    case '/':
		    {
			current = fgetc(ifp);

			// if comment loops until the end of the comment
			if(current == '*')
			{			
			    while(found == 0)
			    {
			        current = fgetc(ifp);
				// possible end of comment
				if(current == '*')
				{
				    current = fgetc(ifp);
				    // if "/", end of comment found
				    if(current == '/')
					found = 1;
				 }
			     }
			     // reinitialize found to 0
			     found = 0;
			}
		    
			// else print slashsym
			else
			    printf("/\t%d\n", slashsym);
			break;
		    }
		    // various single char operator and special symbol cases
		    case '*':
			printf("*\t%d\n", slashsym);
			break;
		    case '+':
		        printf("+\t%d\n", plussym);
			break;
		    case '-':
			printf("-\t%d\n", minussym);
			break;
		    case '(':
			printf("(\t%d\n", lparentsym);
			break;
		    case ')':
			printf(")\t%d\n", rparentsym);
			break;
		    case ',':
			printf(",\t%d\n", commasym);
			break;
		    case '.':
		        printf(".\t%d\n", periodsym);
			break;
		    case ';':
			printf(";\t%d\n", semicolonsym);
			break;
		    
		    
		    // possible becomessym case
		    case ':':
		    {
			// scan for next char
		        current = fgetc(ifp);
		       
			// check for becomessym case, print symbol and associated int if found
			if(current == '=')
			    printf(":=\t%d\n", becomessym);
			break;
		    }
		}
	    }
	}
    }

}
