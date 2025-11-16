/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:24:57 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/20 16:39:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **start, t_list *new)
{
	t_list	*help;

	if (!new || !start)
		return ;
	if (*start == NULL)
	{
		*start = new;
		return ;
	}
	help = *start;
	while (help->next != NULL)
		help = help->next;
	help->next = new;
}
/*int main ()
{
	t_list    *head = NULL;
	t_list    *lk, *lk_2, *lk_3;
	lk = ft_malloc (sizeof(t_list));
		lk_2 = ft_malloc (sizeof(t_list));
	head = lk;
	lk->next = lk_2;
	lk_2->next = NULL;
	lk_3 = ft_malloc (sizeof(t_list));
	t_list *test = ft_lstlast(&head, lk_3);
		//if (test == lk)
			//    printf ("done");
	//else
			//printf ("faild");
}*/
