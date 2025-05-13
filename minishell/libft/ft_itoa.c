/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:08:26 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 23:43:20 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_range(int nb)
{
	if (nb == 0)
		return (1);
	if (nb > 0)
		return (1 + ft_range(nb / 10));
	return (0);
}

static char	*ft_reverse(char *str)
{
	int		i;
	int		a;
	char	tmp;

	a = 0;
	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	while (a < i)
	{
		tmp = str[i];
		str[i] = str[a];
		str[a] = tmp;
		i--;
		a++;
	}
	return (str);
}

static char	*ft_min_version(int i)
{
	char	*back;

	if (!i)
	{
		back = (char *)malloc(2);
		if (!back)
			return (NULL);
		back[0] = '0';
		back[1] = '\0';
		return (back);
	}
	back = (char *)malloc(12);
	if (!back)
		return (NULL);
	ft_strlcpy(back, "-2147483648", 12);
	return (back);
}

char	*ft_itoa(int i)
{
	char	*back;
	int		index;
	char	a;

	a = 0;
	if (i <= 0)
	{
		if (i == 0 || i == -2147483648)
			return (ft_min_version(i));
		a = '-';
		i = -i;
	}
	index = 0;
	back = (char *)malloc(ft_range(i) + (a != 0));
	if (!back)
		return (NULL);
	while (i)
	{
		back[index++] = (i % 10) + '0';
		i /= 10;
	}
	if (a == '-')
		back[index++] = '-';
	back[index++] = '\0';
	return (ft_reverse(back));
}
/*
int main()
{
	int i = -2147483648LL;
	int j = 6;
	int k = 23647;
	char *a = ft_itoa(i);
	char *b = ft_itoa(j);
	char *c = ft_itoa(k);
	printf("INT_MIN = %s\n0       =  %s\nINT_MAX =  %s", a, b, c);
}
*/
