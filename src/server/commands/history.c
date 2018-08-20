#include <stdlib.h>
#include <string.h>
#include "server/config.h"

static const char	*g_command = OPEN_CMD" http://127.0.0.1:8888 &";

char				*history_callback(void *arg)
{
	(void)arg;
	if (system(g_command))
		return (strdup("Failed to open history"));
	return (strdup("History opened"));
}
