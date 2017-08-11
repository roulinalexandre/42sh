/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 00:26:38 by aroulin           #+#    #+#             */
/*   Updated: 2017/08/11 06:29:26 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int		init_our_term(struct termios *term)
{
	(*term).c_lflag &= ~(ICANON);
	(*term).c_lflag &= ~(ECHO);
	(*term).c_cc[VMIN] = 1;
	(*term).c_cc[VTIME] = 0;
	return (1);
}

int		init_term(void)
{
	static struct termios old_term;
	static struct termios our_term;

	if ((init_fd() == -1))
		return (1);
	if (my_getenv("TERM") && tgetent(NULL, my_getenv("TERM")))
	{
		NBR(tcgetattr(STDIN_FILENO, &old_term));
		keep_term_struct(SAVE_OLD, &old_term);
	}
	else if (!tgetent(NULL, my_getenv("TERM")))
	{
		add_list_env("TERM", "xterm");
		tcgetattr(STDIN_FILENO, &old_term);
		keep_term_struct(SAVE_OLD, &old_term);
	}
	if (!(tcgetattr(init_fd(), &our_term)) && init_our_term(&our_term))
		keep_term_struct(SAVE_OUR, &our_term);
	return (0);
}