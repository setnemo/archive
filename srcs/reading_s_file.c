/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_s_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error_asm.h"

void				start_reading_s(t_asm *data)
{
	data->dotsstr = ft_strnew(0);
	while (get_next_line(data->dotsfd, &data->dotsstrtemp))
	{
		data->dotsstr = ft_strjoin_free(data->dotsstr, data->dotsstrtemp);
		data->dotsstr = ft_strjoin_free(data->dotsstr, ft_strdup("\n"));
	}
}
