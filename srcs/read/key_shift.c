/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:34:02 by aroulin           #+#    #+#             */
/*   Updated: 2017/08/20 19:54:53 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int		shift_up_key(t_read **read_std)
{
	int		co;

	co = tgetnum("co");
	if (co)
		while (co-- && (*read_std)->cmd->prev)
		{
			if (!(*read_std)->history && (*read_std)->cmd->prev->c == 10)
				break ;
			(*read_std)->cmd = (*read_std)->cmd->prev;
		}
	return (1);
}

int		shift_down_key(t_read **read_std)
{
	int		co;

	co = tgetnum("co");
	if (co)
		while (co-- && (*read_std)->cmd->next)
			(*read_std)->cmd = (*read_std)->cmd->next;
	return (1);
}

int		shift_left_key(t_read **read_std)
{
	while ((*read_std)->cmd->prev && (*read_std)->cmd->prev->c == 32)
		(*read_std)->cmd = (*read_std)->cmd->prev;
	while ((*read_std)->cmd->prev)
	{
		if ((*read_std)->cmd->prev->c == 32)
			break;
		(*read_std)->cmd = (*read_std)->cmd->prev;
	}
	return (1);
}

int		shift_right_key(t_read **read_std)
{

	while ((*read_std)->cmd)
	{
		if ((*read_std)->cmd->c == 32)
			break;
		(*read_std)->cmd = (*read_std)->cmd->next;
	}
	while ((*read_std)->cmd && (*read_std)->cmd->c == 32)
		(*read_std)->cmd = (*read_std)->cmd->next;
	return (1);
}

