#include "client/client.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int		main(void)
{
	char	*responce;
	char	*input;

	while (1)
	{
		input = readline("please enter command >");
		if (!input || strlen(input) == 0)
		{
			puts("No input detected!");
			continue ;
		}
		responce = send_text_command(input);
		free(input);
		if (responce)
		{
			puts(responce);
		}
		free(responce);
	}
	return (0);
}
