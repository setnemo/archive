/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weather_private.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 21:11:00 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 21:14:07 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEATHER_PRIVATE_H
# define WEATHER_PRIVATE_H

# include <stddef.h>
# include <curl/curl.h>

typedef struct		s_memory_chunk
{
	char			*memory;
	size_t			size;
}					t_memory_chunk;

typedef CURL		t_curl;

#endif
