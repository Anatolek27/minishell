/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychirouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:53:00 by ychirouz          #+#    #+#             */
/*   Updated: 2024/02/14 15:53:03 by ychirouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_status;

static void	mini_getpid(t_prompt *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ms_perror(FORKERR, NULL, 1);
		ft_free_matrix(&p->envv);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&p->envv);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

static t_prompt	init_vars(t_prompt prompt, char *str, char **argv)
{
	char	*num;

	str = getcwd(NULL, 0);
	prompt.envv = ms_set_newenv("PWD", str, prompt.envv, 3);
	free(str);
	str = ms_env_value("SHLVL", prompt.envv, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	prompt.envv = ms_set_newenv("SHLVL", num, prompt.envv, 5);
	free(num);
	str = ms_env_value("PATH", prompt.envv, 4);
	if (!str)
		prompt.envv = ms_set_newenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", prompt.envv, 4);
	free(str);
	str = ms_env_value("_", prompt.envv, 1);
	if (!str)
		prompt.envv = ms_set_newenv("_", argv[0], prompt.envv, 1);
	free(str);
	return (prompt);
}

t_prompt	init_prompt(char **argv, char **envv)
{
	t_prompt	prompt;
	char		*str;

	str = NULL;
	prompt.cmds = NULL;
	prompt.envv = ft_dup_matrix(envv);
	g_status = 0;
	mini_getpid(&prompt);
	prompt = init_vars(prompt, str, argv);
	return (prompt);
}
