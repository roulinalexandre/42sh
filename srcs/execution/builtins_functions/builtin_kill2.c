/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_kill2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:21:05 by jle-quel          #+#    #+#             */
/*   Updated: 2017/11/17 16:21:20 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static const t_signal	g_info[] = {
		(t_signal){SIGHUP, "HUP"},
		(t_signal){SIGINT, "INT"},
		(t_signal){SIGQUIT, "QUIT"},
		(t_signal){SIGILL, "ILL"},
		(t_signal){SIGTRAP, "TRAP"},
		(t_signal){SIGABRT, "ABRT"},
		(t_signal){SIGEMT, "EMT"},
		(t_signal){SIGFPE, "FPE"},
		(t_signal){SIGKILL, "KILL"},
		(t_signal){SIGBUS, "BUS"},
		(t_signal){SIGSEGV, "SEGV"},
		(t_signal){SIGSYS, "SYS"},
		(t_signal){SIGPIPE, "PIPE"},
		(t_signal){SIGALRM, "ALRM"},
		(t_signal){SIGTERM, "TERM"},
		(t_signal){SIGURG, "URG"},
		(t_signal){SIGSTOP, "STOP"},
		(t_signal){SIGTSTP, "TSTP"},
		(t_signal){SIGCONT, "CONT"},
		(t_signal){SIGCHLD, "CHLD"},
		(t_signal){SIGTTIN, "TTIN"},
		(t_signal){SIGTTOU, "TTOU"},
		(t_signal){SIGIO, "IO"},
		(t_signal){SIGXCPU, "XCPU"},
		(t_signal){SIGXFSZ, "XFSZ"},
		(t_signal){SIGVTALRM, "VTALRM"},
		(t_signal){SIGPROF, "PROF"},
		(t_signal){SIGWINCH, "WINCH"},
		(t_signal){SIGINFO, "INFO"},
		(t_signal){SIGUSR1, "USR1"},
		(t_signal){SIGUSR2, "USR2"},
		(t_signal){0, NULL}
};

uint8_t			signal_from_str(char *status)
{
	size_t			index;

	index = 0;
	while (g_info[index].signal)
	{
		if (ft_strcmp(status, g_info[index].status) == 0)
		{
			ft_putnbr(g_info[index].signal);
			ft_putchar(10);
			return (0);
		}
		index++;
	}
	return (var_return(error_msg(KILL, UNKNOWN, status)));
}

uint8_t			signal_from_int(uint8_t signal)
{
	size_t			index;

	index = 0;
	while (g_info[index].signal)
	{
		if (g_info[index].signal == signal)
		{
			ft_putstr(g_info[index].status);
			ft_putchar(10);
			return (0);
		}
		index++;
	}
	return (var_return(error_msg(KILL, UNKNOWN, NULL)));
}

uint8_t			all_signal(void)
{
	size_t			index;

	index = 0;
	while (g_info[index].signal)
	{
		ft_putstr(g_info[index].status);
		ft_putchar(32);
		index++;
	}
	ft_putchar(10);
	return (var_return(0));
}

uint8_t			kill_process(char *string1, char *string2)
{
	int					signal;
	int					index;

	index = -1;
	signal = SIGTERM;
	if (string1 && ft_strisdigit(string1 + 1))
		signal = ft_atoi(string1 + 1);
	else if (string1 && ft_strisalpha(string1 + 1))
	{
		while (g_info[++index].signal)
			if (ft_strcmp(g_info[index].status, string1 + 1) == 0)
				signal = g_info[index].signal;
	}
	if (ft_strisdigit(string2))
	{
		if (kill(ft_atoi(string2), 0) != 0)
			return (var_return(error_msg(KILL, NO_PROCESS, string2)));
		else
			return (var_return(kill(ft_atoi(string2), signal)));
	}
	else
		return (var_return(error_msg(KILL, ILLEGAL, string2)));
}
