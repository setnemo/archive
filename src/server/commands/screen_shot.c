#include <stdlib.h>
#include <string.h>
#include "server/config.h"

#ifdef __linux__
static const char			*g_command = SCREENSHOT_CMD;
static const char			*g_show_command = FILE_MANAGER_CMD " "\
											  SCREENSHOT_FOLDER " &";
#else
#endif

char				*screen_shot_callback(void *arg)
{
	(void)arg;
#ifdef __linux__
	if (system("mkdir -p " SCREENSHOT_FOLDER))
		return (strdup("Failed to create screen shot folder"));
#endif
	if (system(g_command))
		return (strdup("Failed to take screen shot"));
	return (strdup("Screen shot have been taken"));
}

char				*show_screen_shots_callback(void *arg)
{
	(void)arg;
	if (system(g_show_command))
		return (strdup("Failed to screen shot folder"));
	return (strdup("Here is your screen shots"));
}
