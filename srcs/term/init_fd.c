/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 00:42:35 by aroulin           #+#    #+#             */
/*   Updated: 2017/08/10 01:07:42 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int		init_fd(void)
{
	static int fd;

	if (!(fd) && (fd = open(ttyname(STDIN_FILENO), O_WRONLY)) == -1)
		STR_FD("Failed to open a tty\n", 2);
	return (fd);
}