/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:57:08 by argharag          #+#    #+#             */
/*   Updated: 2025/01/27 20:03:47 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*b;

	b = (char *) s;
	if (c % 256 == 0)
		return (b + ft_strlen(b));
	i = 0;
	while (b[i] != '\0')
	{
		if (b[i] == c % 256)
			return (b + i);
		i++;
	}
	return (NULL);
}
/*
int main() {
	int a = 'e' + 256;
	char str[] = "teste";
	printf("%d\n%c\n", a % 256, a);
	printf("%s\n", strchr(str, a));
	printf("%s", ft_strchr(str, a));
}
*/
