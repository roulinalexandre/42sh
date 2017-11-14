//
// Created by Alexandre ROULIN on 11/4/17.
//

#include <sh.h>

static int 				compare_heredoc(t_cmd *cmd, char *string)
{
	int			index;

	index = 0;
	if (cmd)
	{
		while (cmd->c && string[index])
		{
			if (cmd->c != string[index])
				return (cmd->c - string[index]);
			cmd = cmd->next;
			index++;
		}
		return (cmd->c - string[index]);
	}
	return (-1);
}

char		*convert_to_str(t_cmd *cmd)
{
	t_cmd		*temp;
	size_t		len;
	char		*string;

	temp = cmd;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	string = (char *)ft_memalloc(sizeof(char) * (len));
	len = 0;
	while (cmd->c)
	{
		string[len++] = cmd->c;
		cmd = cmd->next;
	}
	string[len] = '\0';
	return (string);
}

char 		**build_table(char **heredoc, char *str)
{
	char		**temp;
	size_t		len;

	len = 0;
	temp = (char **)ft_memalloc(sizeof(char *) * (ft_tablen(heredoc) + 2));
	if (heredoc)
	{
		while (heredoc[len])
		{
			temp[len] = heredoc[len];
			len++;
		}
		free((void *)heredoc);
	}
	temp[len++] = str;
	temp[len] = NULL;
	return (temp);
}

void		do_heredoc(t_node *node)
{
	t_cmd				*cmd;
	char				**heredoc;
	int					fildes;
	char				*temp;

	node->content->heredoc = ft_strjoin("/tmp/", (temp = ft_itoa(time(NULL))));
	fildes = open(node->content->heredoc, O_WRONLY | O_CREAT, 0644);
	heredoc = NULL;
	while (0x2A)
	{
		cmd = first_cmd(read_stdin(HEREDOC), 1);
		log_error("%d %d", signal_reception(-1), SIGINT);
		if (signal_reception(-1) == SIGINT)
		{
			ft_memdel_tab(&heredoc);
			free((void *)temp);
			return ;
		}
		else if (compare_heredoc(cmd, node->right->content->command[0]) == 0 || signal_reception(-1) == 1)
		{
			ft_putstrtab_fd(heredoc, 10, fildes);
			ft_memdel_tab(&heredoc);
			memdel_cmd(&cmd);
			free((void *)temp);
			return ;
		}
		else
		{
			heredoc = build_table(heredoc, convert_to_str(cmd));
			memdel_cmd(&cmd);
		}
	}
	free((void *)temp);
}