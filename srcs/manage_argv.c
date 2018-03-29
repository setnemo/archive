/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int					manage_argv(t_asm *data, char **argv)
{
	// проверить другие компиляторы, как они себя ведут если приходит файл по абсолютному пути ~/../../ и куда они его сохраняют
	// и если да - сохранить имена в дату
	// считать файл
	// распарсить файл
	char	*str;
	int		len;

	str = argv[0];
	len = ft_strlen(str);
	// проверяю длину имени файла (не меньше трех) и что заканчивается нужным мне расширением
	if (len < 3 || *(str + len - 1) != 's' || *(str + len - 2) != '.') 
		return (1);
	data->dotsname = ft_strdup(str);
	data->dotcorname = ft_strnew(len + 2);
	ft_strncpy(data->dotcorname, data->dotsname, len - 1);
	ft_strcpy(ft_strchr(data->dotcorname, '.') + 1, "cor");
	// проверяю полученное имя для сравнения с аргументом
	// ft_printf("%s\n", data->dotcorname);
	if((data->dotsfd = open(data->dotsname, O_RDONLY)) < 0)
		manage_error(data, 1);
	return (0);
}