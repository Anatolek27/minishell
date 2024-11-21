/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akunegel <akunegel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:16:30 by akunegel          #+#    #+#             */
/*   Updated: 2024/02/12 19:16:32 by akunegel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*rd_file(char *str, int fd)
{
	char	*buff;
	int		nb_bytes;

	nb_bytes = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (!ft_strrrrchr(str, '\n') && nb_bytes != 0)
	{
		nb_bytes = read(fd, buff, BUFFER_SIZE);
		if (nb_bytes == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[nb_bytes] = '\0';
		str = ft_strrjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = rd_file(str, fd);
	if (!str)
		return (NULL);
	line = clean_line(str);
	str = new_str(str);
	return (line);
}
