/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:48:53 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 20:51:39 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "external/sam.h"
#include "client/client.h"

int		main(void)
{
	char	*responce;
	char	*input;

	while (1)
	{
		input = NULL;
		input = get_user_speech();
		if (!input || strlen(input) == 0)
		{
			puts("No input detected!");
			continue ;
		}
		responce = send_text_command(input);
		free(input);
		if (responce)
		{
			puts(responce);
			sam_say(responce);
			free(responce);
		}
	}
	return (0);
}
