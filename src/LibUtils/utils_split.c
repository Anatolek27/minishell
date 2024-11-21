/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychirouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:04:30 by ychirouz          #+#    #+#             */
/*   Updated: 2024/02/14 16:04:33 by ychirouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	nbmots(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			nb++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (nb);
}

static int	len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static void	frees(char **str, int mot)
{
	while (mot > 0)
	{
		free(str[mot]);
		mot--;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		mot;
	int		i;
	char	**str;

	mot = 0;
	i = 0;
	str = (char **)malloc(sizeof(char *) * (nbmots(s, c) + 1));
	if (!str)
		return (NULL);
	while (mot < nbmots(s, c))
	{
		while (s[i] == c)
			i++;
		str[mot] = ft_substr(s, i, len(s, c, i));
		if (!str)
		{
			frees(str, nbmots(s, c));
			return (NULL);
		}
		i += len(s, c, i);
		mot++;
	}
	str[mot] = 0;
	return (str);
}
