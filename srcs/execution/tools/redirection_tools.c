/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 08:01:56 by jle-quel          #+#    #+#             */
/*   Updated: 2017/11/19 08:02:22 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/*
*************** PRIVATE ********************************************************
*/

/*
*************** PUBLIC *********************************************************
*/

int				check_fd(int fildes)
{
	if (fildes == init_fd())
		fildes = STDOUT_FILENO;
	return (fildes);
}
