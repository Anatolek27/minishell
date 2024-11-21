/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychirouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:51:11 by ychirouz          #+#    #+#             */
/*   Updated: 2024/02/14 15:51:14 by ychirouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

void	exec_child_cmd(t_prompt *prompt, t_ms *n, int l, t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!check_builtin(n) && n->full_cmd)
		execve(n->full_path, n->full_cmd, prompt->envv);
	else if (n->full_cmd && !ft_strncmp(*n->full_cmd, "pwd", l) \
		&& l == 3)
		g_status = ms_pwd();
	else if (check_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "echo", l) && l == 4)
		g_status = ms_echo(cmd);
	else if (check_builtin(n) && n->full_cmd && \
		!ft_strncmp(*n->full_cmd, "env", l) && l == 3)
	{
		ft_putmatrix_fd(prompt->envv, 1, 1);
		g_status = 0;
	}
}

static void	*child_redir(t_list *cmd, int fd[2])
{
	t_ms	*node;

	node = cmd->content;
	if (node->rd_file != STDIN_FILENO)
	{
		if (dup2(node->rd_file, STDIN_FILENO) == -1)
			return (ms_perror(DUPERR, NULL, 1));
		close(node->rd_file);
	}
	if (node->wr_file != STDOUT_FILENO)
	{
		if (dup2(node->wr_file, STDOUT_FILENO) == -1)
			return (ms_perror(DUPERR, NULL, 1));
		close(node->wr_file);
	}
	else if (cmd->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (ms_perror(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_ms	*n;
	int		l;

	n = cmd->content;
	l = 0;
	if (n->full_cmd)
		l = ft_strlen(*n->full_cmd);
	child_redir(cmd, fd);
	close(fd[READ_END]);
	exec_child_cmd(prompt, n, l, cmd);
	ft_lstclear(&prompt->cmds, free_content);
	exit(g_status);
}

void	exec_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		ms_perror(FORKERR, NULL, 1);
	}
	else if (!pid)
		child_process(prompt, cmd, fd);
}

void	*checking_fork(t_prompt *prompt, t_list *cmd, int fd[2])
{
	t_ms	*n;
	DIR		*dir;

	n = cmd->content;
	dir = NULL;
	if (n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n->rd_file == -1 || n->wr_file == -1)
		return (NULL);
	if ((n->full_path && access(n->full_path, X_OK) == 0) || check_builtin(n))
		exec_fork(prompt, cmd, fd);
	else if (!check_builtin(n) && ((n->full_path && \
		!access(n->full_path, F_OK)) || dir))
		g_status = 126;
	else if (!check_builtin(n) && n->full_cmd)
		g_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
