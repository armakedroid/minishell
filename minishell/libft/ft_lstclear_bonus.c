/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:02:36 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 20:47:27 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	del(void *c)
{
	free(c);
}
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*new;

	while (*lst)
	{
		new = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = new;
	}
}
/*
int main() {
    t_list *node1 = ft_lstnew(ft_strdup("Artur"));
    t_list *node2 = ft_lstnew(ft_strdup("jan"));
    t_list *node3 = ft_lstnew(ft_strdup("!"));

    node1->next = node2;
	node2->next = node3;

    t_list *current = node1;
	while(current)
	{
		printf("%s\n",(char *)current->content);
		current = current->next;
	}
    ft_lstclear(&node1,&del);
	if(!node1)
		printf("ha jan");
}
*/
