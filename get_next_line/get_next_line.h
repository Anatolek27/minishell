/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akunegel <akunegel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:16:55 by akunegel          #+#    #+#             */
/*   Updated: 2024/02/12 19:16:55 by akunegel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

//#include <stdio.h>

char	*get_next_line(int fd);

char	*ft_strrrrchr(char *str, int c);

char	*ft_strrjoin(char *str, char *buff);

char	*new_str(char *str);

char	*clean_line(char *str);
#endif
