#include <stdio.h>
#include "external/sam.h"
#include "client/client.h"

int		main(void)
{
	char	*responce;
	char	*input;
	// char	*line_end;
	// size_t	len;

	while (1)
	{
		// len = 0;
		input = NULL;
		input = get_user_speech();
		// printf("please enter command > ");
		// if (getline(&input, &len, stdin) == -1)
		// {
		// 	puts("Error reading stdin");
		// 	continue ;
		// }
		// if ((line_end = strchr(input, '\n')))
		// 	line_end[0] = 0;
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
			sam_say(responce);
			free(responce);
		}
	}
	return (0);
}
