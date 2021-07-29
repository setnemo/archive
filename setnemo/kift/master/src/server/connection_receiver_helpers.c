/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_receiver_helpers.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 21:20:55 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 21:22:43 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/server.h"

char		*insert_length(const char *command, int *command_len)
{
	char		*tmp;
	int			len;

	len = strlen(command);
	tmp = strdup(command);
	tmp = realloc(tmp, len + 4);
	memmove((void*)(tmp + 4), (void*)tmp, len);
	printf("response len: %d\n", len);
	tmp = memcpy((void*)tmp, (void*)&len, sizeof(int));
	*command_len = len + 4;
	return (tmp);
}

void		respond_and_clean(char *responce, void *thread_data,
				int client_socket, int len)
{
	printf("Responded: %s\n", responce);
	responce = insert_length(responce, &len);
	write(client_socket, responce, len);
	close(client_socket);
	free(thread_data);
	free(responce);
}
