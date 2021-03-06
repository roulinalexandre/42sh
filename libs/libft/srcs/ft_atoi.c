/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <aroulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by aroulin           #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	check_pass(char c)
{
	if (c == 32 || c == 11 || c == 9 || c == '\r' || c == '\n' || c == '\f')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int		sign;
	long	number;

	if (!str)
		return (0);
	while (check_pass((unsigned char)(*str)))
		str++;
	sign = *(str) == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	number = 0;
	while (*str && ft_isdigit(*str))
	{
		number = number * 10 + (unsigned char)*str - '0';
		str++;
	}
	return ((int)(number * sign));
}
