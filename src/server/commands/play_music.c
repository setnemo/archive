#include <stdlib.h>
#include <string.h>
#include "server/config.h"

static const char	*g_command = OPEN_CMD" https://amitness.com/shuffle/ &";

char				*play_music_callback(void *arg)
{
	(void)arg;
	if (system(g_command))
		return (strdup("Failed to play music"));
	return (strdup("Here is you music"));
}
