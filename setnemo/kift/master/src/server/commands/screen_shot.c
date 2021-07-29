/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:51:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 21:08:55 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "server/config.h"

#ifdef __linux__

static const char			*g_command = SCREENSHOT_CMD;
static const char			*g_show_command = FILE_MANAGER_CMD " "
SCREENSHOT_FOLDER " &";
#else

static const char			*g_command = SCREENSHOT_CMD"$(date +%Y%m%d%H%M%S)"
".png";
static const char			*g_show_command = " open -a Preview.app "
SCREENSHOT_FOLDER;
#endif

char						*screen_shot_callback(void *arg)
{
	(void)arg;
	if (system("mkdir -p " SCREENSHOT_FOLDER))
		return (strdup("Failed to create screen shot folder"));
	if (system(g_command))
		return (strdup("Failed to take screen shot"));
	return (strdup("Screen shot have been taken"));
}

char						*show_screen_shots_callback(void *arg)
{
	(void)arg;
	if (system(g_show_command))
		return (strdup("Failed to screen shot folder"));
	return (strdup("Here is your screen shots"));
}
