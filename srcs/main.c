/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 09:07:27 by apakhomo          #+#    #+#             */
/*   Updated: 2018/02/03 09:07:28 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

ssize_t	allocsize(char **file)
{
	char	buf;
	int		fd;
	int		ret;
	ssize_t	size;
	if ((fd = open(*file, O_RDONLY)) == -1)
		return (-1);
	size = 0;
	while ((ret = read(fd, &buf, 1)) == 1)
		size++;
	close(fd);
	if (ret == 0)
		return (size);
	else
		return (-1);
}

void	readoutfile(t_ssl *data) 
{
	ssize_t			ret;
	int				fd;

	if ((int)(data->size = allocsize(&data->inp)) == -1)
		exit_error(errno, NULL);
	if ((data->income = ft_memalloc(data->size + 1)) == NULL)
		exit_error(errno, NULL);
	if ((fd = open(data->inp, O_RDONLY)))
	{
		ret = read(fd, data->income, data->size);
		close(fd);
		if (ret == (ssize_t)data->size)
			return ;
	}
	free(data->income);
	exit_error(errno, NULL);
}

void	printinfile(t_ssl *data)
{
	int		fd;

	if ((fd = open(data->out, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		exit_error(errno, data->outcome);
	if ((write(fd, data->outcome, data->size)) == -1)
	{
		close(fd);
		exit_error(errno, data->outcome);
	}
	close(fd);
}

int		main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("usage: %s command [command opts] [command args]\n", argv[0]);
		return (1);
	}
	flag_parser(argc, argv);
	return (0);
}
