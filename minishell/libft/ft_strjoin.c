/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:05:45 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:33:46 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill(char *back, const char *s1, const char *s2)
{
	int	index;
	int	i;

	index = 0;
	i = 0;
	while (s1[index])
	{
		back[index] = s1[index];
		index++;
	}
	while (s2[i])
	{
		back[index++] = s2[i];
		i++;
	}
	back[index] = '\0';
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i1;
	int		i2;
	char	*back;

	if (!s1 || !s2)
		return (NULL);
	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	back = (char *)malloc((i1 + i2 + 1) * sizeof(char));
	if (!back)
		return (NULL);
	fill(back, s1, s2);
	return (back);
}
/*
int main()
{
    char *a1 = "Overlap";
    char *a2 = "lapOver";
    char *s = ft_strjoin(a1, a2);
    printf("%s\n", s);
    free(s); 
}
*/
