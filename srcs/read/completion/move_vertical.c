/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_or_down.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 14:15:25 by aroulin           #+#    #+#             */
/*   Updated: 2017/08/23 17:34:23 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static inline void		change_page(t_read **read_std)
{
	place_cursor(read_std, 1);
	print_tab(read_std);
	place_cursor(read_std, 0);
}

static inline void		change_element(t_read **read_std, t_file *tmp)
{
	SAVE;
	MV_BOT;
	print_element(tmp, 1);
	tmp = (*read_std)->tab_->file;
	while (tmp->index != (*read_std)->tab_->index)
		tmp = tmp->next;
	print_element(tmp, 0);
	RESTORE;
}

void					move_vertical(t_read **read_std, int pos)
{
	t_file	*tmp;

	tmp = (*read_std)->tab_->file;
	while (tmp->index != (*read_std)->tab_->index)
		tmp = tmp->next;
	update_index(read_std, (*read_std)->tab_->nbr * pos);
	if (((*read_std)->tab_->index / (*read_std)->tab_->elem_page) != (*read_std)->tab_->page)
		change_page(read_std);
	else
		change_element(read_std, tmp);
}