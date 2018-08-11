#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

char		*run_program(void *arg)
{
	char	*command;
	char	*str;
	int		i;

	str = (char*)arg;
	i = 0;
	while (isalpha(str[i]))
		i++;
	while (isspace(str[i]))
		i++;
	str += i;
	command = malloc(strlen(str) + 3);
	strncpy(command, str, strlen(str) + 3);
	strncat(command, " &", strlen(str) + 3);
	puts(command);
	if (system(command))
		return (strdup("Fail running command"));
	return (strdup("Success running command"));
}
