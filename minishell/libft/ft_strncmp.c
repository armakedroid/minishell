/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:26:15 by argharag          #+#    #+#             */
/*   Updated: 2025/03/20 19:11:33 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n)
	{
		if (s1[i] > '\0')
			i++;
		else
			return (0);
	}
	if (i == n)
		return (0);
	if (s1[i] < 0x00 || s2[i] < 0x00)
		return (s2[i] - s1[i]);
	return (s1[i] - s2[i]);
}
/*
int main() {
	char s1[] = "atoms\0bcd";
	char s2[] = "ato\356ms\0abc";
	int n = 8;
	printf("%d\n", strncmp(s1, s2, n));
	printf("%d", ft_strncmp(s1, s2, n));
}
*/
