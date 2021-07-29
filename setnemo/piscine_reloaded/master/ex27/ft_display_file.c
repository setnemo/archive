/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 10:00:01 by apakhomo          #+#    #+#             */
/*   Updated: 2017/10/25 10:00:02 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 10

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_putchar('\n');
}

int		ft_check(int argc, char **argv)
{
	int	fd;
	int stop;

	stop = 0;
	if (argc == 1)
	{
		ft_putstr("File name missing.");
		stop = 1;
	}
	if (argc > 2)
	{
		ft_putstr("Too many arguments.");
		stop = 1;
	}
	return (stop);
}

int		main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	buf[BUFSIZE + 1];

	if (ft_check(argc, argv) == 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("open() error");
		return (1);
	}
	while ((ret = read(fd, buf, BUFSIZE)))
	{
		buf[ret] = '\0';
		write(1, buf, ret);
	}
	if (close(fd) == -1)
	{
		ft_putstr("close() error");
		return (1);
	}
	return (0);
	close(fd);
}
