/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:06:31 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:25:58 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
static char	uplow(unsigned int i, char c)
{
i	char	a;

	if (i % 2 == 0)
		a = c - 32;
	else
		a = c;
	return (a);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*back;

	i = 0;
	while (s[i] != '\0')
		i++;
	back = (char *)malloc(i * sizeof(char) + 1);
	if (!back)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		back[i] = f(i, s[i]);
		i++;
	}
	back[i++] = '\0';
	return (back);
}
/*
int main()
{
	char a[] = "artur jan barev";
	char *str = ft_strmapi(a,&uplow);
	printf("%s", str);
	free(str);
}*/
