#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO:exceed buffer limit
char **parse(char *line)
{
	int BUFFER_SIZE = 10;
	char **rv = (char **)malloc(BUFFER_SIZE * (sizeof(char *)));
	int arr_size = 10, curr_arr_size = 0, next_index_of_line = 0;
	while (line[next_index_of_line] != '\0')
	{
		rv[curr_arr_size] = (char *)malloc(20 * sizeof(char)); //assuming each word doesnt exceed 20 chars
		int curr_word_index = 0;
		while (line[next_index_of_line] != ' ' && line[next_index_of_line] != '\0')
		{
			rv[curr_arr_size][curr_word_index] = line[next_index_of_line];
			curr_word_index++;
			next_index_of_line++;
		}
		rv[curr_arr_size][curr_word_index] = '\0';
		if (line[next_index_of_line] == ' ')
			while (line[++next_index_of_line] == ' ')
				;
		curr_arr_size++;
	}
	rv[curr_arr_size] = (char *)malloc(1);
	rv[curr_arr_size][0] = '\0';
	return rv;
}

void loop()
{
	char *line;
	char **pointer_to_str_arr;
	int bytes_read;
	while (1)
	{
		printf("\nxD>>");

		unsigned int LINE_BUFFER_SIZE = 10;
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

		while (pointer_to_str_arr[i][0] != '\0')
		{
			printf("%s\n", pointer_to_str_arr[i]);
			i++;
		}
		// execute(str_arr[0], str_arr[1]);
	}
}
int main()
{
	printf("Entering Shell !!!\n");
	loop();
	return 0;
}