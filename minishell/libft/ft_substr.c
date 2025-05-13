/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:08:07 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:38:43 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t str1, size_t str2)
{
	if (str1 > str2)
		return (str2);
	return (str1);
}

static char	*poxos(char *s, size_t i)
{
	char		*back;
	size_t		m;

	m = 0;
	back = (char *)malloc(i * sizeof(char) + 1);
	if (!back)
		return (NULL);
	while (m < i)
	{
		back[m] = s[m];
		m++;
	}
	back[m] = '\0';
	return (back);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*back;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return ((char *)ft_calloc(1, sizeof(char)));
	back = (char *) s;
	return (poxos(back + start, min(len, ft_strlen(s) - start)));
}
/*
int	main()
{
	char *str = "Armakedroid";
	char *a = ft_substr(str, 7, 10);
	printf("%s",a);
}*/
