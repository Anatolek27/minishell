/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychirouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:48:23 by ychirouz          #+#    #+#             */
/*   Updated: 2024/02/14 15:49:02 by ychirouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

extern int	g_status;

int	main(int argc, char **argv, char **envv)
{
	char				*str;
	char				*out;
	t_prompt			prompt;

	prompt = init_prompt(argv, envv);
	while (argv && argc)
	{
		signal(SIGINT, ms_sig_hdl);
		signal(SIGQUIT, SIG_IGN);
		str = ms_dsplprompt(prompt);
		if (str)
			out = readline(str);
		else
			out = readline("42Evaluation@minishell $ ");
		free(str);
		if (!check_args(out, &prompt))
			break ;
	}
	exit(g_status);
}
