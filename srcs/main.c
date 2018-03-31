/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 08:28:46 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/15 08:28:47 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "error_asm.h"
#define AR1 *(*argv + (len - 1))
#define AR2 *(*argv + (len - 2))
#define AR3 *(*argv + (len - 3))
#define AR4 *(*argv + (len - 4))

static void			cleaning_asm(t_asm *data)
{
	if (data->dotsname)
		ft_strdel(&data->dotsname);
	if (data->dotcorname)
		ft_strdel(&data->dotcorname);
}

void				manage_error(t_asm *data, char error)
{
	if (error == 0 || error == 1)
		(error == 0) ? ft_printf(ER00) : ft_printf(ER01);
	if (error == 2 || error == 3)
		(error == 2) ? ft_printf(ER02) : ft_printf(ER03);
	if (error == 4 || error == 5)
		(error == 4) ? ft_printf(ER04) : ft_printf(ER05);
	if (error == 6 || error == 7)
		(error == 6) ? ft_printf(ER06) : ft_printf(ER07);
	if (error == 8 || error == 9)
		(error == 8) ? ft_printf(ER08) : ft_printf(ER09);
	cleaning_asm(data);
	system("leaks -quiet asm");
	exit(-42);
}

static void			init_data(t_asm *data)
{
	data->dotsname = NULL;
	data->dotcorname = NULL;
	data->dotsfd = -1;
	data->dotcorfd = -1;
}

static int			checkdotcor(t_asm *data, char *argv)
{
	ft_printf("[*] Done! '%s' compiled to '%s'\n", argv, data->dotsname);
	return (0);
}

static int			checkdots(t_asm *data, char *argv, size_t len)
{
	// проверяю длину имени файла (не меньше трех) и что заканчивается нужным мне расширением
	data->dotsname = ft_strdup(argv);
	data->dotcorname = ft_strnew(len + 2);
	ft_strncpy(data->dotcorname, data->dotsname, len - 1);
	ft_strcpy(ft_strchr(data->dotcorname, '.') + 1, "cor");
	// проверяю полученное имя для сравнения с аргументом
	// ft_printf("data->dotcorname:%s\n", data->dotcorname);
	// если имя с папками - обрезать лишнее
	if (ft_strrchr(data->dotcorname, '/'))
	{
		argv = ft_strdup(ft_strrchr(data->dotcorname, '/') + 1);
		ft_strdel(&data->dotcorname);
		data->dotcorname = ft_strdup(argv);
		ft_strdel(&argv);
	}
	// ft_printf("data->dotcorname:%s\n", data->dotcorname);
	// проверяю чтение файла и сохраняю его фд
	if((data->dotsfd = open(data->dotsname, O_RDONLY)) < 0)
		return (1);
	// ft_printf("FD{%i}:%s\n", data->dotsfd, data->dotsname);
	ft_printf("[*] Done! '%s' compiled to '%s'\n", data->dotsname, data->dotcorname);
	return (0);
}

static void			print_error(int ret, char *argv)
{
	if (ret == 1)
		ft_printf("[!] Error! '%s' - file not found\n", argv);
	else
		ft_printf("[!] Error! '%s' - invalid filename\n", argv);
}

int					main(int argc, char **argv)
{
	t_asm		data;
	int			i;
	int			ret;
	size_t		len;

	i = 1;
	while (i < argc && *(argv)++)
	{
		// ft_printf(":1:\n");
		init_data(&data);
		len = ft_strlen(*argv);
		if (len > 2 && AR1 == 's' && AR2 == '.')
			ret = checkdots(&data, *argv, len);
		else if (len > 4 && AR1 == 'r' && AR2 == 'o' && AR3 == 'c' && AR4 == '.')
			ret = checkdotcor(&data, *argv);
		else
			print_error(ret, *argv);
		if (ret > 0)
			print_error(ret, *argv);
		cleaning_asm(&data);
		i++;
	}
	system("leaks -quiet asm");
	return (42);
}
