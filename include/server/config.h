#ifndef CONFIG_H
# define CONFIG_H

# ifdef __linux__
# define LOCKSCREEN_CMD "dm-tool lock"
# define SCREENSHOT_FOLDER "/tmp/screenshots/"
# define SCREENSHOT_CMD "scrot '" SCREENSHOT_FOLDER "%Y-%m-%d_$wx$h.png'"
# define FILE_MANAGER_CMD "thunar"
# else
# endif

#endif
