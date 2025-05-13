/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:38:17 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:38:21 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*b;

	i = 0;
	b = (char *) s;
	if (c % 256 == 0)
		return (b + ft_strlen(b));
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == c % 256)
			return (b + i);
		i--;
	}
	return (NULL);
}
/*
int main() {
	int a = 65;
	char str[] = "BArtur barev dzez";
	printf("%s\n", strrchr(str, a));
	printf("%s", ft_strrchr(str, a));
}
*/
