#include <string.h>
#include <stdlib.h>

static const char	*g_args[] = {
	"up",
	"down",
	"increase",
	"decrease",
	"min",
	"max",
	NULL
};

static const char	*g_system_args[] = {
#ifdef __linux__
	"xbacklight + 10",
	"xbacklight - 10",
	"xbacklight + 10",
	"xbacklight - 10",
	"xbacklight = 100",
	"xbacklight = 10",
#else
#endif
	NULL
};

char				*backlight_callback(void *arg)
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
