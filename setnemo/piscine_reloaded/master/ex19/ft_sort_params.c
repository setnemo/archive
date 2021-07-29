/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apakhomo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 09:41:55 by apakhomo          #+#    #+#             */
/*   Updated: 2017/10/25 09:41:55 by apakhomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		++i;
	}
}

void	ft_sort_argv(int argc, char **argv)
{
	int		i;
	int		j;
	int		arg;
	char	*tmp;

	arg = argc - 1;
	i = 1;
	while (i < arg)
	{
		j = 0;
		while (argv[i][j] == argv[i + 1][j])
			j++;
		if (argv[i][j] > argv[i + 1][j])
		{
			tmp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = tmp;
			i = 0;
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	int i;

	ft_sort_argv(argc, argv);
	i = 1;
	while (argv[i] != '\0')
	{
		ft_putstr(argv[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}
