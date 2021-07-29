/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:51:39 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 21:45:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include "server/command_callbacks.h"
#include "server/small_talk.h"

static const char		*g_commands[] = {
	"hello",
	"sound",
	"lock screen",
	"run",
	"screen shot",
	"show screen shots",
	"weather",
	"backlight",
	"play music",
	"history",
	"flip coin",
	"crystal ball",
	"roll dice",
	"sing song",
	"tell something",
	"tell joke",
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
	play_music_callback,
	history_callback,
	flip_a_coin,
	crystal_ball,
	roll_the_dice,
	sing_song,
	tell_me_something,
	tell_a_joke,
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
