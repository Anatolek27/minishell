/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychirouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:50:45 by ychirouz          #+#    #+#             */
/*   Updated: 2024/02/14 15:50:49 by ychirouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*find_command(char **env_path, char *cmd, char *full_path)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static DIR	*cmd_checks(t_prompt *prompt, t_list *cmd, char ***s, char *path)
{
	t_ms	*n;
	DIR		*dir;

	dir = NULL;
	n = cmd->content;
	if (n && n->full_cmd)
		dir = opendir(*n->full_cmd);
	if (n && n->full_cmd && ft_strchr(*n->full_cmd, '/') && !dir)
	{
		*s = ft_split(*n->full_cmd, '/');
		n->full_path = ft_strdup(*n->full_cmd);
		free(n->full_cmd[0]);
		n->full_cmd[0] = ft_strdup(s[0][ft_matrixlen(*s) - 1]);
	}
	else if (!check_builtin(n) && n && n->full_cmd && !dir)
	{
		path = ms_env_value("PATH", prompt->envv, 4);
		*s = ft_split(path, ':');
		free(path);
		n->full_path = find_command(*s, *n->full_cmd, n->full_path);
		if (!n->full_path || !n->full_cmd[0] || !n->full_cmd[0][0])
			ms_perror(NCMD, *n->full_cmd, 127);
	}
	return (dir);
}

void	check_cmd(t_prompt *prompt, t_list *cmd, char **s, char *path)
{
	t_ms	*n;
	DIR		*dir;

	n = cmd->content;
	dir = cmd_checks(prompt, cmd, &s, path);
	if (!check_builtin(n) && n && n->full_cmd && dir)
		ms_perror(IS_DIR, *n->full_cmd, 126);
	else if (!check_builtin(n) && n && n->full_path && \
		access(n->full_path, F_OK) == -1)
		ms_perror(NDIR, n->full_path, 127);
	else if (!check_builtin(n) && n && n->full_path && \
		access(n->full_path, X_OK) == -1)
		ms_perror(NPERM, n->full_path, 126);
	if (dir)
		closedir(dir);
	ft_free_matrix(&s);
}

void	*exec_cmd(t_prompt *prompt, t_list *cmd)
{
	int		fd[2];

	check_cmd(prompt, cmd, NULL, NULL);
	if (pipe(fd) == -1)
		return (ms_perror(PIPERR, NULL, 1));
	if (!checking_fork(prompt, cmd, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (cmd->next && !((t_ms *)cmd->next->content)->rd_file)
		((t_ms *)cmd->next->content)->rd_file = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_ms *)cmd->content)->rd_file > 2)
		close(((t_ms *)cmd->content)->rd_file);
	if (((t_ms *)cmd->content)->wr_file > 2)
		close(((t_ms *)cmd->content)->wr_file);
	return (NULL);
}
