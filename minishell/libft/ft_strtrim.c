/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:07:53 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:26:54 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		a;
	int		index;
	char	*back;

	a = 0;
	i = 0;
	index = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[a])
		a++;
	while (s1[index] && ft_set(s1[index], set))
		index++;
	while (a > index && ft_set(s1[a - 1], set))
		a--;
	back = (char *)malloc((a - index + 1) * sizeof(char));
	if (!back)
		return (0);
	while (index < a)
		back[i++] = s1[index++];
	back[i++] = '\0';
	return (back);
}
/*
int	main()
{
	char const *a = NULL;
	char const *b = NULL;
	char *back = ft_strtrim(a,b);
	printf("%s",back);
}
*/
