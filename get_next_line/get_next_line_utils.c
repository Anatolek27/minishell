/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akunegel <akunegel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:16:19 by akunegel          #+#    #+#             */
/*   Updated: 2024/02/12 19:19:36 by akunegel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strrrrchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return (s + ft_strlen(s));
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strrjoin(char *str, char *buff)
{
	int		i;
	int		j;
	char	*join;

	i = -1;
	j = 0;
	if (!str)
	{
		str = (char *)malloc(sizeof(char));
		str[0] = '\0';
	}
	if (!str || !buff)
		return (NULL);
	join = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(buff)) + 1));
	if (join == NULL)
		return (NULL);
	while (str[++i] != '\0')
		join[i] = str[i];
	while (buff[j] != '\0')
		join[i++] = buff[j++];
	join[ft_strlen(str) + ft_strlen(buff)] = '\0';
	free(str);
	return (join);
}

char	*new_str(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new)
		return (NULL);
	while (str[++i] != '\0')
		new[j++] = str[i];
	new[j] = '\0';
	free(str);
	return (new);
}

char	*clean_line(char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = -1;
	while (str[++i] != '\0' && str[i] != '\n')
		s[i] = str[i];
	if (str[i] == '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
