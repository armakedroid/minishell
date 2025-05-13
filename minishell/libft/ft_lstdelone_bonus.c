/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:02:14 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 20:48:01 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*void	del(void *content)
{
	if (content)
		free(content);
	//(void)content;
}*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
int main(void)
{
	t_list *node1 = ft_lstnew(ft_strdup("Artur"));
	t_list *node2 = ft_lstnew(ft_strdup("jan"));

	node1->next = node2;
	ft_lstdelone(node2, &del);
	//node1->next = NULL;

	t_list *i = node1;
	while (i)
	{
		printf("%s\n", (char *)i->content);
		i = i->next;
	}
}*/
