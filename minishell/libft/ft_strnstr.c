/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:26:30 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:26:32 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	m;
	size_t	k;
	char	*str1;
	char	*str2;

	str1 = (char *) haystack;
	str2 = (char *) needle;
	m = 0;
	if (*str2 == '\0')
		return (str1);
	while (str1[m] != '\0' && m < len)
	{
		k = 0;
		while (str2[k] != '\0' && str1[m + k] == str2[k] && (m + k) < len)
		{
			k++;
			if (str2[k] == '\0')
				return (str1 + m);
		}
		m++;
	}
	return (NULL);
}
/*
int main() {
	char str1[30] = "aaabcabcd";
	char str2[10] = "aabc";

	printf("Original = %s\n", strnstr(str1, str2, -1));
	printf("My       = %s\n", ft_strnstr(str1, str2, -1));
}
*/
