/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:08:26 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/20 16:39:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}
/*int main()
{
    t_list *head = NULL;
    t_list *nww = ft_malloc (sizeof(t_list));
    t_list *nw = ft_malloc (sizeof(t_list));
    nw->content = (char *)"hello";
    ft_lstadd_front(&head, nw);
    nww->content = (char *)"hello";
    ft_lstadd_front(&head, nww);
}*/
