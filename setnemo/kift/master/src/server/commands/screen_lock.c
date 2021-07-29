/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_lock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 20:51:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 20:55:46 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "server/config.h"

#ifdef __linux__

static const char			*g_command = LOCKSCREEN_CMD;
#else

static const char			*g_command = LOCKSCREEN_CMD;
#endif

char				*screen_lock_callback(void *arg)
{
	(void)arg;
	if (system(g_command))
		return (strdup("Failed to lock screen"));
	return (strdup("Screen locked successfully"));
}
