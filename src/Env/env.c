/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychirouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:50:28 by ychirouz          #+#    #+#             */
/*   Updated: 2024/02/14 15:50:34 by ychirouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ms_env_value(char *var, char **envv, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envv && envv[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envv[i], '='))
			n2 = ft_strchr_i(envv[i], '=');
		if (!ft_strncmp(envv[i], var, n2))
			return (ft_substr(envv[i], n2 + 1, ft_strlen(envv[i])));
		i++;
	}
	return (NULL);
}

char	**ms_set_newenv(char *var, char *value, char **envv, int n)
{
	int		i[2];
	char	*aux[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	while (!ft_strchr(var, '=') && envv && envv[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_i(envv[i[0]], '='))
			i[1] = ft_strchr_i(envv[i[0]], '=');
		if (!ft_strncmp(envv[i[0]], var, i[1]))
		{
			aux[0] = envv[i[0]];
			envv[i[0]] = aux[1];
			free(aux[0]);
			return (envv);
		}
	}
	envv = ft_extend_matrix(envv, aux[1]);
	free(aux[1]);
	return (envv);
}

static int	var_in_envp(char *argv, char **envv, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		return (-1);
	while (envv[ij[1]])
	{
		if (!ft_strncmp(envv[ij[1]], argv, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}

int	ms_export(t_prompt *prompt)
{
	int		ij[2];
	int		pos;
	char	**argv;

	argv = ((t_ms *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		ij[0] = 1;
		while (argv[ij[0]])
		{
			pos = var_in_envp(argv[ij[0]], prompt->envv, ij);
			if (pos == 1)
			{
				free(prompt->envv[ij[1]]);
				prompt->envv[ij[1]] = ft_strdup(argv[ij[0]]);
			}
			else if (!pos)
				prompt->envv = ft_extend_matrix(prompt->envv, argv[ij[0]]);
			ij[0]++;
		}
	}
	return (0);
}

int	ms_unset(t_prompt *prompt)
{
	char	**argv;
	char	*aux;
	int		ij[2];

	ij[0] = 0;
	argv = ((t_ms *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		while (argv[++ij[0]])
		{
			if (argv[ij[0]][ft_strlen(argv[ij[0]]) - 1] != '=')
			{
				aux = ft_strjoin(argv[ij[0]], "=");
				free(argv[ij[0]]);
				argv[ij[0]] = aux;
			}
			if (var_in_envp(argv[ij[0]], prompt->envv, ij))
				ft_matrix_replace_in(&prompt->envv, NULL, ij[1]);
		}
	}
	return (0);
}
