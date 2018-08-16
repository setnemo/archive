#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include "server/command_callbacks.h"

static const char		*g_commands[] = {
	"hello test",
	"sound",
	"lock screen",
	"run",
	"screen shot",
	"show screen shots",
	"weather",
	"backlight",
	NULL
};

static char		*(*g_command_callbacks[])(void *) = {
	hello_test_callback,
	sound_callback,
	screen_lock_callback,
	run_program,
	screen_shot_callback,
	show_screen_shots_callback,
	weather_callback,
	backlight_callback,
	NULL
};

static void				write_log(const char *received, const char *responded)
{
	int		fd;

	fd = open("command_log.csv", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Unable to open command_log.csv");
		return ;
	}
	dprintf(fd, "\"%d\",\"%s\",\"%s\"\n", (int)time(NULL), received, responded);
	close(fd);
}

char					*command_handler(char *command)
{
	int			i;
	char		*responce;

	i = -1;
	responce = NULL;
	while (g_commands[++i])
	{
		if (strncmp(command, g_commands[i], strlen(g_commands[i])) == 0)
		{
			responce = g_command_callbacks[i](command);
			break ;
		}
	}
	if (responce == NULL)
		responce = strdup("Command not found!");
	write_log(command, responce);
	return (responce);
}
