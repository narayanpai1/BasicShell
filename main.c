#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// flag=1 when exit statement is encountered
int flag = 0;

/*
parses the string into many array of strings seperated by either
   1) NULL pointer to indicate semicolans.
   2) NULL pointer followed by an array with null character as the first element,to indicate end of line
eg:
  cat file ; ls -l
	 will be parsed into [ ['c','a','t'], ['f', 'i', 'l', 'e'], NULL, ['l', 's'], ['-','l'],  NULL,['\0'] ]
*/
char **parse(char *line)
{
	unsigned int BUFFER_SIZE = 10;
	unsigned int arr_size = BUFFER_SIZE, curr_arr_size = 0, next_index_of_line = 0;
	char **rv = (char **)malloc(arr_size * (sizeof(char *)));

	if (!rv)
	{
		printf("\nDynammic allocation failed");
	}
	while (line[next_index_of_line] != 10)
	{
		if (curr_arr_size == (arr_size - 1))
		{
			arr_size += BUFFER_SIZE;
			rv = (char **)realloc(rv, arr_size * (sizeof(char *)));
			if (!rv)
			{
				printf("\nDynammic allocation failed");
			}
		}

		// if it is a semicolon, next pointer is NULL
		if (line[next_index_of_line] == ';')
		{
			rv[curr_arr_size] = NULL;
			next_index_of_line++;
			curr_arr_size++;
			continue;
		}

		//if a word
		int curr_word_index = 0;
		if ((line[next_index_of_line] != ' ') && (line[next_index_of_line] != 10))
		{
			rv[curr_arr_size] = (char *)malloc(20 * sizeof(char)); //assuming each word doesnt exceed 20 chars
			while (line[next_index_of_line] != ';' && line[next_index_of_line] != ' ' && line[next_index_of_line] != 10)
			{
				rv[curr_arr_size][curr_word_index] = line[next_index_of_line];
				curr_word_index++;
				next_index_of_line++;
			}
			rv[curr_arr_size][curr_word_index] = '\0';
			curr_arr_size++;
		}

		//if a space
		if (line[next_index_of_line] == ' ')
			while (line[++next_index_of_line] == ' ')
				;
	}
	rv[curr_arr_size] = NULL;
	curr_arr_size++;
	rv[curr_arr_size] = (char *)malloc(1 * sizeof(char));
	rv[curr_arr_size][0] = '\0';
	return rv;
}

void execute(char **pointer_to_str_arr)
{
	int i = 0;
	do
	{
		// each block is of the form [NULLs, a command, NULLs]

		//for NULLs
		if (pointer_to_str_arr[i] == NULL)
			while (pointer_to_str_arr[++i] == NULL)
				;

		// for commands
		if (strcmp(pointer_to_str_arr[i], "exit") == 0)
		{
			if (pointer_to_str_arr[i + 1] != NULL)
			{
				while (pointer_to_str_arr[++i] != NULL)
					;
				printf("\nexit statement doesnt have parameters");
			}
			else
			{
				flag = 1;
			}
		}
		else if (pointer_to_str_arr[i][0] != '\0')
		{
			// execvp(pointer_to_str_arr[i], &(pointer_to_str_arr[i]))
			while (pointer_to_str_arr[++i] != NULL)
				;
		}

		// for NULLs
		if (pointer_to_str_arr[i] == NULL)
			while (pointer_to_str_arr[++i] == NULL)
				;
	} while (pointer_to_str_arr[i][0] != '\0');
}

void loop()
{
	char *line;
	char **pointer_to_str_arr;
	int bytes_read;
	while (flag == 0)
	{
		printf("\nxD>>");

		long unsigned int LINE_BUFFER_SIZE = 10;
		line = (char *)malloc(LINE_BUFFER_SIZE * sizeof(char));
		bytes_read = getline(&line, &LINE_BUFFER_SIZE, stdin);
		// 'line' will now be pointing to the first character of the string

		// if there was some error in malloc
		if (bytes_read == -1)
		{
			printf("Error");
			continue;
		}
		// if there was nothing in the input
		else if (bytes_read == 1)
		{
			continue;
		}
		int i = 0;

		// pointer_to_str_arr points to an array where each element points to the start of a word
		pointer_to_str_arr = parse(line);
		while (i < 12)
		{
			if (pointer_to_str_arr[i] == NULL)
				printf("NULL\n");
			else
			{
				printf("%s\n", pointer_to_str_arr[i]);
			}
			i++;
		}
		execute(pointer_to_str_arr);
	}
}
int main()
{
	printf("Entering Shell !!!\n");
	loop();
	printf("\nTerminating...");
	return 0;
}