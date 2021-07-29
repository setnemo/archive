/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connection_receiver_private.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 21:23:03 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 21:23:05 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_RECEIVER_PRIVATE_H
# define CONNECTION_RECEIVER_PRIVATE_H

void		respond_and_clean(char *responce, void *thread_data,
				int client_socket, int len);
char		*insert_length(const char *command, int *command_len);

#endif
