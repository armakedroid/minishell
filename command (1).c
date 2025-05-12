/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:36:24 by argharag          #+#    #+#             */
/*   Updated: 2025/03/27 19:24:00 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"



int sorted(t_my_nodes *stack)
{
    while(stack->next)
    {
        if(stack->num < stack->next->num)
            stack = stack ->next;
        else
            return (0);
    }
    return (1);
        
}

int	command(t_my_nodes **a, int i)
{
    (void)a;
    return (i);
}
