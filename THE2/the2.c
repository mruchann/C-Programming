#include <stdio.h> 
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
char *String; char *CurrentPosition; char Alphabet[26]; char **matrix;

int evaluatechar(char *p) 
{
	int i;
	for (i = 0; matrix[0][i] != 'R'; i++)
	{
		if (*CurrentPosition == matrix[0][i])
		{
			CurrentPosition++;
			return p[i];
		}
	}
	return -1; 
}

int evaluate(char *p)
{
	int left, right; char operator;

	if (*CurrentPosition == '(')
	{
		CurrentPosition++;
		left = evaluate(p);
		operator = *CurrentPosition++;
		right = evaluate(p);
		CurrentPosition++;

		switch(operator)
		{
			case '&': return (left & right);
			case '|': return (left | right);
			case '>': return (!left | right);
			case '=': return (left == right);
		}
	}
	else if (islower(*CurrentPosition)) return evaluatechar(p);
	else if (*CurrentPosition == '-') 
	{
		CurrentPosition++;
		return !evaluate(p);
	}
	return -1;
}

int main()
{
	int i = 0; int j = 0; int k = 0; int x = 0; int length = 0; int lettercount = 0; 
	int numberofcharpointers = 0; int numberofchar = 0; 
	String = (char*) malloc(1*sizeof(char));

	while ( (x = getchar()) != EOF )
	{
		if (isspace(x)) continue;
		else 
		{
			String[i++] = x;
			String = (char *) realloc(String, (i+1)* sizeof(char));
		}
	}	

	String[i] = 0; 
	CurrentPosition = String; 
	length = strlen(String);

	for (i = 0; i < 26; i++) 
	{
		for (j = 0; j < length; j++)
		{
			if(String[j] == (i+97))
			{
				Alphabet[i] = i+97;
				lettercount++;
				break;
			}		
		}
	}

	numberofcharpointers = pow(2,lettercount)+1;
	numberofchar = lettercount + 1;
	matrix = (char**) calloc(numberofcharpointers,sizeof(char*)); 

	for (i = 0; i < numberofcharpointers; i++)
	{
		matrix[i] = (char*) calloc(numberofchar,sizeof(char));
	}

	for(i = 0, j = 0; i < 26; i++)
	{
		if (Alphabet[i] && (j < lettercount)) matrix[0][j++] = Alphabet[i];
		else if(!Alphabet[i]) continue;
	}

	matrix[0][lettercount] = 'R';

	for (i = 0; i < lettercount; i++)
	{	
		for(j = 1; j < numberofcharpointers;j++)
		{
			if (!((j-1) % (int)pow(2,lettercount-i-1)))
			{
				k = !k;
			}
			matrix[j][i] = k; 
		}	
	}	

	for (i = 1; i < numberofcharpointers; i++)
	{
		matrix[i][lettercount] = evaluate(matrix[i]);
		CurrentPosition = String;
	}

	for (i = 0; i < 26; i++)
	{
		if (Alphabet[i] != 0) printf("%c ",Alphabet[i]);
	}

	printf("R\n");

	for (i = 1; i < numberofcharpointers; i++)
	{
		for (j = 0; j < lettercount; j++)
		{
			if (matrix[i][j] == 1) printf("T ");
			else if (matrix[i][j] == 0) printf("F ");
		}

		if (matrix[i][j] == 1) printf("T\n");
		else if (matrix[i][j] == 0) printf("F\n");
	}

	return 0;
}


