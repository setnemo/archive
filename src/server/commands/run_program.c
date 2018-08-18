#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "server/config.h"

static const char	*g_args[] = {
	"editor",
	"browser",
	"terminal",
	"file manager",
	NULL
};

static const char	*g_system_args[] = {
#ifdef __linux__
	"xbacklight + 10",
	"xbacklight + 10",
	"xbacklight + 10",
	"xbacklight + 10",
#else
	"open -a \"" PROGRAM_EDITOR "\"",
	"open -a \"" PROGRAM_BROWSER"\"",
	"open -a \"" PROGRAM_TERMINAL"\"",
	"open -a \"" PROGRAM_FILEMANAGER"\"",
#endif
	NULL
};

char				*run_program(void *arg)
{
	char		*str;
	const char	*modifier;
	int			i;

	str = (char*)arg;
	modifier = NULL;
	i = -1;
	while (g_args[++i])
	{
		if (strstr(str, g_args[i]))
		{
			modifier = g_system_args[i];
			break ;
		}
	}
	if (!modifier)
		return (strdup("I don't understand this run program operation"));
	if (system(modifier))
		return (strdup("Fail run program operation"));
	return (strdup("Success run program operation"));
}