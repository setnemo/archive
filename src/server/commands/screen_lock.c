#include <stdlib.h>
#include <string.h>

#ifdef __linux__
static const char			*g_command = "dm-tool lock";
#else
#endif

char				*screen_lock_callback(void *arg)
{
	(void)arg;
	if (system(g_command))
		return (strdup("Failed to lock screen"));
	return (strdup("Screen locked successfully"));
}
