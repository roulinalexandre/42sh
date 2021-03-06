/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 14:42:34 by jle-quel          #+#    #+#             */
/*   Updated: 2017/12/20 14:42:39 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void				op_string(t_parsing *node)
{
	int			std;
	int			std_in;

	std_in = STDIN_FILENO;
	if (ft_isdigit(node->command[0][0]))
		std_in = ft_atoi(node->command[0]);
	if ((std = open(node->heredoc, O_RDWR)) == -1)
		check_path(node->heredoc);
	if (dup2(std, std_in) == -1)
		exit(error_msg(S42H, BAD_FD, NULL));
	close(std);
}
