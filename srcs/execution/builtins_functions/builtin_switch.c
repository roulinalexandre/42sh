/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_switch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:22:55 by aroulin           #+#    #+#             */
/*   Updated: 2017/10/30 15:22:57 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

uint8_t		error_builtin(char *from, char *error, char *args)
{
	ft_putstr_fd(from, STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putchar_fd(10, STDERR_FILENO);
	return (1);
}

uint8_t		fg_switch_process(t_jobs *jobs, int index, char *error,char *args)
{
	if (index != -1 && jobs[index].process)
	{
		reset_signal();
		modify_foreground(jobs[index].process, true);
		set_fildes(jobs[index].process->pgid);
		if (!jobs[index].process->running)
		{
			kill(-(jobs[index].process->pgid), SIGCONT);
			modify_runing(jobs[index].process, true);
			update_status(jobs[index].process);
			print_status(jobs[index].process, index);
		}
		wait_process(jobs);
		set_fildes(getpgid(0));
		init_signal();
		return (0);
	}
	else
		return (error_builtin(FG, error, args));
}

uint8_t		bg_switch_process(t_jobs *jobs, int index, char *error, char *args)
{
	if (index != -1 && jobs[index].process)
	{
		modify_runing(jobs[index].process, true);
		modify_foreground(jobs[index].process, false);
		kill(-jobs[index].process->pgid, SIGCONT);
		update_status(jobs[index].process);
		print_status(jobs[index].process, index);
		pjt(jobs + index);
		return (0);
	}
	else
		return (error_builtin(BG, error, args));
}

uint8_t		builtin_foreground(t_node *node, int info)
{
	int			id;
	t_jobs		*jobs;

	(void)info;
	jobs = jobs_table();
	if (node->content->command[1] && node->content->command[1][0] == '%')
	{
		id = (ft_atoi(node->content->command[1] + 1) - 1);
		return (var_return(fg_switch_process(jobs, id, NO_JOB, node->content->command[1] + 1)));
	}
	else
	{
		id = MAX_CHILD - 1;
		while (id >= 0)
		{
			if (jobs[id].process && jobs[id].process->foreground == false)
				break ;
			id--;
		}
		return (fg_switch_process(jobs, id, NO_CUR_JOB, NULL));
	}
}

uint8_t		builtin_background(t_node *node, int info)
{
	int			id;
	t_jobs		*jobs;

	(void)info;
	jobs = jobs_table();
	if (node->content->command[1] && node->content->command[1][0] == '%')
	{
		id = (ft_atoi(node->content->command[1] + 1) - 1);
		return (var_return(bg_switch_process(jobs, id, NO_JOB, node->content->command[1] + 1)));
	}
	else
	{
		id = MAX_CHILD - 1;
		while (id >= 0 && !jobs[id].process->pid && !jobs[id].process->running)
			id--;
		return (var_return(bg_switch_process(jobs, id, NO_CUR_JOB, NULL)));
	}
}