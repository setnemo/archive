#!/bin/bash

source .env
if [[ ! ${WEATHER_API_KEY:+x} ]]; then echo "Please, provide WEATHER_API_KEY! in .env file"; fi
if [[ ! ${WEATHER_GEO_LOCATION:+x} ]]; then
	echo "Getting geolocation";
	my_ip=$(curl 'https://api.ipgeolocation.io/getip' | grep -oE "[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+")
	geo_location_array=$(curl "https://api.hackertarget.com/geoip/?q="$my_ip | grep -oE "[0-9]+\.[0-9]{6}\$"| tr "\n" " ")
	WEATHER_GEO_LOCATION=$(echo ${geo_location_array%% } | tr " " ",")
	echo "WEATHER_GEO_LOCATION=$WEATHER_GEO_LOCATION"
fi
cat <<EOF > config.h
#ifndef CONFIG_H
# define CONFIG_H

# ifdef __linux__
#  define LOCKSCREEN_CMD "dm-tool lock"
#  define SCREENSHOT_FOLDER "/tmp/screenshots/"
#  define SCREENSHOT_CMD "scrot '" SCREENSHOT_FOLDER "%Y-%m-%d_\$wx\$h.png'"
#  define FILE_MANAGER_CMD "thunar"
#  define PROGRAM_EDITOR "atom"
#  define PROGRAM_BROWSER "firefox"
#  define PROGRAM_TERMINAL "terminator"
#  define PROGRAM_FILEMANAGER "thunar"
#  define OPEN_CMD "xdg-open"
# else
#  define L1 "osascript -e 'tell application \"System Events\" to "
#  define L2 "keystroke \"q\" using {control down,  command down}'"
#  define LOCKSCREEN_CMD L1 L2
#  define SCREENSHOT_FOLDER "$HOME/screenshots/"
#  define SCREENSHOT_CMD "screencapture $HOME/screenshots/"
#  define PROGRAM_EDITOR "Sublime Text"
#  define PROGRAM_BROWSER "Google Chrome"
#  define PROGRAM_TERMINAL "iterm"
#  define PROGRAM_FILEMANAGER "Finder"
#  define OPEN_CMD "open"
# endif
# define WEATHER_GEO_LOCATION "$WEATHER_GEO_LOCATION"
# define WEATHER_API_KEY "$WEATHER_API_KEY"

#endif
EOF
vim +Stdheader +wq config.h
