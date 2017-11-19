/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <aroulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 18:56:57 by aroulin           #+#    #+#             */
/*   Updated: 2017/11/19 01:28:59 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int					finish_process(t_process *process)
{
	int			terminated;
	int			nb_process;

	nb_process = 0;
	terminated = 0;
	while (process)
	{
		if (process->status == -1)
			;
		else if (WIFSIGNALED(process->status) ||
					WIFEXITED(process->status) || WIFSTOPPED(process->status))
			terminated++;
		nb_process++;
		process = process->next;
	}
	log_trace("Return finishstatus %d", (terminated - nb_process) == 0 ? 1 : 0);
	return ((terminated - nb_process) == 0 ? 1 : 0);
}

int					terminate_process(t_process *process)
{
	if (WIFSIGNALED(process->status))
		return (1);
	else if (WIFEXITED(process->status))
		return (-1);
	else
		return (0);
}

void				memdel_jobs(t_jobs **jobs)
{
	t_process	*process;

	while ((*jobs)->process)
	{
		process = (*jobs)->process;
		(*jobs)->process = (*jobs)->process->next;
		ft_memdel((void **)&process->command);
		ft_memdel((void **)&process);
	}
	ft_memdel((void **)jobs);
}

void				reset_process(t_jobs *jobs)
{
	t_jobs		**addr_jobs;
	t_jobs		*temp;

	addr_jobs = jobs_table();
	temp = *addr_jobs;
	if (*addr_jobs == jobs)
	{
		memdel_jobs(addr_jobs);
		log_debug("On est premier ! %d", *jobs_table() ? 1 : 0);
	}
	else
		while (temp)
		{
			if (temp == jobs)
			{
				if (temp->prev)
						temp->prev->next = temp->next;
				if (temp->next)
					temp->next->prev = temp->prev;
				memdel_jobs(&temp);
			}
			temp = temp->next;
		}
}

void				first_process(t_jobs *jobs)
{
	if (jobs->process)
		while (jobs->process->prev)
			jobs->process = jobs->process->prev;
}

void				close_fildes(t_process *process)
{
	while (process->next)
	{
		close_pipe(process->fildes);
		process = process->next;
	}
}
