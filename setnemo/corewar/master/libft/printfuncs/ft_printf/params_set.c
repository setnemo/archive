/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:31:29 by nkolosov          #+#    #+#             */
/*   Updated: 2017/12/03 15:31:29 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
** % [param] [flags] [width]  [precision] [length]    [type]
** % [n$]    [ #0+-] [n || *] [.n||.*]    [hlhhlljzLt][sSpdDioOuUxXcCeEfFgGaAn]
*/

size_t		get_n(char *str, int *p)
{
	int		i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '$')
	{
		*p = *p + 1;
		return (printf_atoi(str, p));
	}
	return (0);
}

void		get_flags(char *str, int *p, t_flags *f)
{
	int		i;

	i = 0;
	while (1)
	{
		if (str[i] == '+')
			f->plus = 1;
		else if (str[i] == '-')
			f->minus = 1;
		else if (str[i] == '0')
			f->zero = 1;
		else if (str[i] == '#')
			f->hash = 1;
		else if (str[i] == ' ')
			f->space = 1;
		else if (str[i] == '\'')
			f->apostrophe = 1;
		else
			break ;
		i++;
	}
	*p = *p + i;
}

int			get_width(char *str, int *p, va_list *ap, _Bool *b)
{
	if (str[0] >= '0' && str[0] <= '9')
		return (printf_atoi(str, p));
	if (str[0] == '*')
	{
		*p = *p + 1;
		if (str[1] > '0' && str[1] <= '9')
		{
			*p = *p + 1;
			*b = 1;
			return (printf_atoi(&str[1], p));
		}
		return (va_arg(*ap, int));
	}
	return (0);
}

int			get_precision(char *str, int *p, va_list *ap, _Bool *b)
{
	if (str[0] != '.')
		return (-1);
	*p = *p + 1;
	if (str[1] == '*')
	{
		*p = *p + 1;
		if (str[2] > '0' && str[2] <= '9')
		{
			*p = *p + 1;
			*b = 1;
			return (printf_atoi(&str[2], p));
		}
		return (va_arg(*ap, int));
	}
	return (printf_atoi(&str[1], p));
}

t_length	get_length(char *str, int *i)
{
	t_length	l;
	size_t		c;

	l = EMPTY;
	while ((c = get_next_length(str, &l)))
	{
		str += c;
		*i = *i + c;
	}
	return (l);
}
