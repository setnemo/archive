#include <string.h>
#include <stdlib.h>

char		*hello_test_callback(void *arg)
{
	(void)arg;
	return strdup("test success!");
}

static char		*g_commands[] = {
	"hello test",
	NULL
};

static char		*(*g_command_callbacks[])(void *) = {
	hello_test_callback
};

char	*command_handler(char *command)
{
	int			i;

	i = -1;
	while (g_commands[++i])
	{
		if (strncmp(command, g_commands[i], strlen(g_commands[i])) == 0)
			return g_command_callbacks[i](command);
	}
	return (strdup("Command not found!"));
}
