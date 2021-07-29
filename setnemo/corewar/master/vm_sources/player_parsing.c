/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:27:01 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/16 15:27:01 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include <fcntl.h>
#include <unistd.h>

extern t_global	g_g;

static void	parse_magic_number(char *name, int fd)
{
	int				ret;
	long			magic_number;
	unsigned char	buf[4];

	if ((ret = read(fd, buf, 4)) < 4)
		not_a_champion(name);
	magic_number = buf[3] +
				(buf[2] << 8) +
				(buf[1] << 16) +
				(buf[0] << 24);
	if (magic_number != COREWAR_EXEC_MAGIC)
		not_a_champion(name);
}

static void	read_viravn(char *name, int fd)
{
	char	temp[6];
	int		ret;
	int		i;

	if ((ret = read(fd, temp, 6)) < 6)
		invalid_champion(name);
	i = -1;
	while (++i < 6)
		if (temp[i] != 0)
			invalid_champion(name);
}

static void	read_declared_player_size(char *name, int fd, t_champ *player)
{
	unsigned char	temp[2];
	int				ret;

	if ((ret = read(fd, temp, 2)) < 2)
		invalid_champion(name);
	player->declared_player_size = (temp[0] << 8) + temp[1];
}

void		parse_player(char *name, t_champ *player)
{
	int		fd;
	int		ret;
	char	temp[1];

	if ((fd = open(name, O_RDONLY)) < 0)
		file_error(name);
	parse_magic_number(name, fd);
	if ((ret = read(fd, player->name, PROG_NAME_LENGTH)) <
		PROG_NAME_LENGTH)
		invalid_champion(name);
	read_viravn(name, fd);
	read_declared_player_size(name, fd, player);
	if ((ret = read(fd, player->comment, COMMENT_LENGTH - 2)) <
		COMMENT_LENGTH - 2)
		invalid_champion(name);
	read_viravn(name, fd);
	if ((ret = read(fd, player->field, CHAMP_MAX_SIZE)) < 0)
		invalid_champion(name);
	player->field_size = ret;
	if ((ret = read(fd, temp, 1)) > 0)
		invalid_champion(name);
	if (player->field_size != player->declared_player_size)
		invalid_champ_length(name);
	close(fd);
}
