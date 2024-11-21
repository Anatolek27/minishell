/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoi_itoa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychirouz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:02:26 by ychirouz          #+#    #+#             */
/*   Updated: 2024/02/14 16:02:28 by ychirouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_fillz(char *str, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		str[i] = '0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*suite(int i, unsigned int nnn, int sign)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str = ft_fillz(str, i);
	--i;
	while (i >= 0)
	{
		str[i] = (nnn % 10) + '0';
		nnn /= 10;
		i--;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned int	nn;
	unsigned int	nnn;
	int				sign;
	char			*str;

	i = 1;
	sign = 0;
	if (n < 0)
	{
		i++;
		sign = 1;
		nn = n * (-1);
	}
	else
		nn = n;
	nnn = nn;
	while (nn / 10 > 0)
	{
		nn /= 10;
		i++;
	}
	str = suite(i, nnn, sign);
	return (str);
}

int	ft_atoi(const char *s)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			sign *= -1;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + sign * (s[i] - '0');
		if (res > 2147483647)
			return (-1);
		else if (res < -2147483648)
			return (0);
		i++;
	}
	return ((int)res);
}
