/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:01:34 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 20:55:38 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*b;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char) c;
	b = (unsigned char *) s;
	while (i < n)
	{
		if (b[i] == ch)
			return (b + i);
		i++;
	}
	return (NULL);
}
/*
int main() {
	char a = 'b';
	char str[] = "Artur barev dzez";
	int i = 0;
	char *s1 = memchr(str, a, sizeof(str));
	char *s2 = ft_memchr(str, a, sizeof(str));
	printf("Position = %ld, string is '%s'\n", s1 - str, s1);
	printf("Position = %ld, string is '%s'", s2 - str, s2);
}
*/
