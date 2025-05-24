/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 21:28:30 by argharag          #+#    #+#             */
/*   Updated: 2025/05/24 19:15:00 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// static void	ft_free(char ***back, int words)
// {
// 	int	i;

// 	i = 0;
// 	while (i < words)
// 	{
// 		if ((*back)[i] != NULL)
// 			free((*back)[i]);
// 		(*back)[i] = NULL;
// 		i++;
// 	}
// 	free(*back);
// 	*back = NULL;
// }

// static void	word_dup_help(const char **s, int in_quotes, int *len, char c)
// {
// 	if (**s == '\'')
// 	{
// 		in_quotes = 1;
// 		(*s)++;
// 	}
// 	while ((*s)[*len] && ((*s)[*len] != c || in_quotes))
// 	{
// 		if ((*s)[*len] == '\'' && in_quotes)
// 		{
// 			in_quotes = 0;
// 			break ;
// 		}
// 		(*len)++;
// 	}
// }

// static char	*word_dup(const char **s, char c)
// {
// 	char	*back;
// 	int		len;
// 	int		i;
// 	int		in_quotes;

// 	len = 0;
// 	in_quotes = 0;
// 	word_dup_help(s, in_quotes, &len, c);
// 	back = malloc(len);
// 	if (!back)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 		back[i++] = *(*s)++;
// 	back[i] = '\0';
// 	if (**s == '\'')
// 		(*s)++;
// 	return (back);
// }

// static char	**allocate_words(char const *s, char c, int word_count)
// {
// 	char		**back;
// 	int			i;
// 	const char	*word_start;

// 	back = (char **)malloc((word_count + 1) * sizeof(char *));
// 	if (back == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < word_count)
// 	{
// 		while (*s == c)
// 			s++;
// 		word_start = s;
// 		while (*s != '\0' && *s != c)
// 			s++;
// 		back[i] = word_dup(&word_start, c);
// 		if (back[i] == NULL)
// 		{
// 			ft_free(&back, i);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	back[i] = NULL;
// 	return (back);
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		word_count;
// 	int		in_quotes;
// 	int		i;

// 	word_count = 0;
// 	in_quotes = 0;
// 	i = 0;
// 	if (s == NULL)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		while (s[i] == c && !in_quotes)
// 			i++;
// 		if (s[i])
// 			word_count++;
// 		while (s[i] && (s[i] != c || in_quotes))
// 		{
// 			if (s[i] == '\'')
// 				in_quotes = !in_quotes;
// 			i++;
// 		}
// 	}
// 	return (allocate_words(s, c, word_count));
// }
/*
int main()
{
	char c[] = "         split        this for   me  !          ";
	char **back = ft_split(c,' ');
	if (!back)
		printf("OK\n");
	int i = 0;
	
	while (i < ft_word(c, ' '))
	{
		printf("%s |", back[i]);
		i++;
	}
	printf("\n%s", back[i]);
	i = 0;
	while (back[i])
	{
		free(back[i]);
		i++;
	}
	free(back);
}*/

#include "libft.h"

static void	ft_free(char ***back, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		if ((*back)[i] != NULL)
			free((*back)[i]);
		(*back)[i] = NULL;
		i++;
	}
	free(*back);
	*back = NULL;
}

static void	word_dup_help(const char **s, int *len, char c)
{
	while ((*s)[*len] && ((*s)[*len] != c))
		(*len)++;
}

static char	*word_dup(const char **s, char c)
{
	char	*back;
	int		len;
	int		i;

	len = 0;
	word_dup_help(s, &len, c);
	back = malloc(len);
	if (!back)
		return (NULL);
	i = 0;
	while (i < len)
		back[i++] = *(*s)++;
	back[i] = '\0';
	return (back);
}

static char	**allocate_words(char const *s, char c, int word_count)
{
	char		**back;
	int			i;
	const char	*word_start;

	back = (char **)malloc((word_count + 1) * sizeof(char *));
	if (back == NULL)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (*s == c)
			s++;
		word_start = s;
		while (*s != '\0' && *s != c)
			s++;
		back[i] = word_dup(&word_start, c);
		if (back[i] == NULL)
		{
			ft_free(&back, i);
			return (NULL);
		}
		i++;
	}
	back[i] = NULL;
	return (back);
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	int		i;

	word_count = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			word_count++;
		 while (s[i] && (s[i] != c))
		 {
		 //	if (s[i] == '\'')
		 //		in_quotes = !in_quotes;
		 	i++;
		 }
	}
	return (allocate_words(s, c, word_count));
}
