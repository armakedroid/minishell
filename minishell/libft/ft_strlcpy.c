/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:25:26 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:25:27 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
/*
int main() {
	char str1[] = "gakdhasdhajshdkjahdkjashdkjahkjd";
	char str2[] = "gakdhasdhajshdkjahdkjashdkjahkjd";
	char dst1[20];
	char dst2[20];

	int i = strlcpy(dst1, str1, 15);
	int k = ft_strlcpy(dst2, str2, 15);

	printf("Original = %s = %d\n", dst1, i);
	printf("My       = %s = %d", dst2, k);
}
*/
