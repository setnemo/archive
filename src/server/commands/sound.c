#include <string.h>
#include <stdlib.h>

static char		*g_args[] = {
	"up",
	"down",
	"mute",
	"disable",
	"enable",
	"min",
	"max",
	NULL
};

static char		*g_system_args[] = {
	"amixer -D pulse sset Master 5%+",
	"amixer -D pulse sset Master 5%-",
	"amixer -D pulse sset Master mute",
	"amixer -D pulse sset Master mute",
	"amixer -D pulse sset Master unmute",
	"amixer -D pulse sset Master 40%",
	"amixer -D pulse sset Master 100%",
	NULL
};

char			*sound_callback(void *arg)
{
	char		*str;
	char		*modifier;
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
