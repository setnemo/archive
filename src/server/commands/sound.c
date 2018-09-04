/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:51:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 20:57:23 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static const char	*g_args[] = {
	"up",
	"down",
	"increase",
	"decrease",
	"mute",
	"disable",
	"enable",
	"min",
	"max",
	NULL
};

static const char	*g_system_args[] = {
#ifdef __linux__

	"amixer -D pulse sset Master 5%+",
	"amixer -D pulse sset Master 5%-",
	"amixer -D pulse sset Master 5%+",
	"amixer -D pulse sset Master 5%-",
	"amixer -D pulse sset Master mute",
	"amixer -D pulse sset Master mute",
	"amixer -D pulse sset Master unmute",
	"amixer -D pulse sset Master 40%",
	"amixer -D pulse sset Master 100%",
#else

	"osascript -e \"set volume output volume (output volume of "
	"(get volume settings) + 5) --100%\"",
	"osascript -e \"set volume output volume (output volume of "
	"(get volume settings) - 5) --100%\"",
	"osascript -e \"set volume output volume (output volume of "
	"(get volume settings) + 5) --100%\"",
	"osascript -e \"set volume output volume (output volume of "
	"(get volume settings) - 5) --100%\"",
	"osascript -e \"set volume with output muted\"",
	"osascript -e \"set volume with output muted\"",
	"osascript -e \"set volume without output muted\"",
	"osascript -e \"set volume 4\"",
	"osascript -e \"set volume 10\"",
#endif

	NULL
};

char				*sound_callback(void *arg)
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
		return (strdup("I don't understand this sound operation"));
	if (system(modifier))
		return (strdup("Fail sound operation"));
	return (strdup("Success sound operation"));
}
