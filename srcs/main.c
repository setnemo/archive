/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oantonen <oantonen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:03:47 by apakhomo          #+#    #+#             */
/*   Updated: 2018/04/28 11:49:33 by oantonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core_asm.h"
#include "error_asm.h"
#include "op.h"

static void		cleaning_asm(t_asm *data)
{
	if (data->dotsname)
		ft_strdel(&data->dotsname);
	if (data->dotcorname)
		ft_strdel(&data->dotcorname);
	if (data->dotsstr)
		ft_strdel(&data->dotsstr);
	if (data->dotsstrtemp)
		ft_strdel(&data->dotsstrtemp);
}

static void		init_data(t_asm *data, char *argv)
{
	ft_bzero(data, sizeof(t_asm));
	data->dotsname = NULL;
	data->dotsstr = NULL;
	data->dotsstrtemp = NULL;
	data->dotcorname = NULL;
	data->fd = -1;
	data->len = ft_strlen(argv);
	data->filename = NULL;
	data->filecomment = NULL;
	data->next = NULL;
}

static int		checkdotcor(t_asm *data, char *argv)
{
	data->dotcorname = ft_strdup(argv);
	data->dotsname = ft_strnew(data->len - 2);
	ft_strncpy(data->dotsname, data->dotcorname, data->len - 3);
	ft_strcpy(ft_strchr(data->dotsname, '.') + 1, "s");
	if ((data->fd = open(data->dotsname, O_RDONLY)) < 0)
		return (1);
	if (ft_strrchr(data->dotsname, '/'))
	{
		argv = ft_strdup(ft_strrchr(data->dotsname, '/') + 1);
		ft_strdel(&data->dotsname);
		data->dotsname = ft_strdup(argv);
		ft_strdel(&argv);
	}
	data->dotsname = ft_strjoin_free(ft_strdup("disasm_"), data->dotsname);
	ft_printf(DDC, data->dotcorname, data->dotsname);
	return (0);
}

static int		checkdots(t_asm *data, char *argv)
{
	t_list		*fl_lst;
	t_list		*fl_err;

	fl_lst = NULL;
	fl_err = NULL;
	data->dotsname = ft_strdup(argv);
	data->dotcorname = ft_strnew(data->len + 2);
	ft_strncpy(data->dotcorname, data->dotsname, data->len - 1);
	ft_strcpy(ft_strchr(data->dotcorname, '.') + 1, "cor");
	if ((data->fd = open(data->dotsname, O_RDONLY)) < 0)
		return (1);
	if (ft_strrchr(data->dotcorname, '/'))
	{
		argv = ft_strdup(ft_strrchr(data->dotcorname, '/') + 1);
		ft_strdel(&data->dotcorname);
		data->dotcorname = ft_strdup(argv);
		ft_strdel(&argv);
	}
	if (save_file(&fl_lst, &fl_err, data->fd))
		if (to_file(&fl_lst, data))
			ft_printf(DDS, data->dotsname, data->dotcorname);
	cleaning_asm_lst(&fl_lst, &fl_err, data);
	return (0);
}

int				main(int argc, char **argv)
{
	t_asm		data;
	int			i;
	int			ret;

	i = 0;
	if ((argc == 2 && ft_strequ(argv[1], "-h")) || argc == 1)
	{
		ft_printf("%s%s%s%s", USAGE);
		exit(42);
	}
	while (++i < argc && *(argv)++)
	{
		init_data(&data, *argv);
		if (data.len > 2 && AR1 == 's' && AR2 == '.')
			ret = checkdots(&data, *argv);
		else if (data.len > 4 && AR)
			ret = checkdotcor(&data, *argv);
		else
			ft_printf("[!] Error! '%s' - invalid filename\n", *argv);
		if (ret)
			ft_printf("[!] Error! '%s' - file not found\n", *argv);
		cleaning_asm(&data);
	}
	system("leaks -quiet asm");
	return (0);
}
