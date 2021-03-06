/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 00:26:38 by aroulin           #+#    #+#             */
/*   Updated: 2017/11/20 15:30:10 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int					*shell_interectative(void)
{
	static int status;

	return (&status);
}

static int			init_our_term(struct termios *term)
{
	(*term).c_lflag &= ~(ICANON);
	(*term).c_lflag &= ~(ECHO);
	(*term).c_cc[VMIN] = 1;
	(*term).c_cc[VTIME] = 0;
	return (1);
}

static void			mine_terminal(int ret)
{
	if (tcgetpgrp(STDIN_FILENO) != getpgid(0))
	{
		kill(getpgid(0), SIGTTIN);
		mine_terminal(ret);
	}
}

int					init_term(void)
{
	static struct termios	old_term;
	static struct termios	our_term;
	static int				ret;

	if (isatty(STDIN_FILENO) == 1)
	{
		if (!my_getenv("TERM"))
			add_environment("TERM=vt100");
		if ((tgetent(NULL, my_getenv("TERM"))) == ERR)
			ret = 1;
		if (!(tcgetattr(init_fd(), &old_term)))
			keep_term_struct(SAVE_OLD, &old_term);
		else
			ret = 1;
		if (!(tcgetattr(init_fd(), &our_term)) && init_our_term(&our_term))
			keep_term_struct(SAVE_OUR, &our_term);
		else
			ret = 1;
		mine_terminal(ret);
		*shell_interectative() = 1;
	}
	else
		*shell_interectative() = 0;
	return (0);
}
