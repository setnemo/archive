#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <arpa/inet.h>

char			*get_user_speech(void);
char			*send_text_command(const char *command);

#endif
