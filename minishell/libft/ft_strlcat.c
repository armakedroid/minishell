/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:06:03 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:25:13 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	m;
	size_t	k;

	i = 0;
	m = ft_strlen(dst);
	k = ft_strlen(dst);
	if (dstsize != 0)
	{
		while (src[i] != '\0' && m + 1 < dstsize)
		{
			dst[m] = src[i];
			m++;
			i++;
		}
		dst[m] = '\0';
	}
	m = ft_strlen(src);
	if (dstsize <= k)
		return (m + dstsize);
	return (m + k);
}
/*
int main() {
	char str1[] = "Artur";
	char str2[] = "Artur";
	char dst1[20] = "45";
	char dst2[20] = "45";

	int i = strlcat(dst1, str1, 1);
	int k = ft_strlcat(dst2, str2, 1);

	printf("Original = %s = %d\n", dst1, i);
	printf("My       = %s = %d", dst2, k);
}
*/
