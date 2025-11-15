/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:09:13 by mfahmi            #+#    #+#             */
/*   Updated: 2025/11/15 23:40:37 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_list	*ft_lstnew_ptr(void *content)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}

void	ft_lstadd_back_ptr(t_list **start, t_list *new)
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

void	*add_ptr(void *ptr, t_list **head)
{
	t_list	*new_node;

	new_node = ft_lstnew_ptr(ptr);
	if (!new_node)
		return (free(ptr), NULL);
	ft_lstadd_back_ptr(head, new_node);
	return (new_node);
}

t_list	**return_ptr(void)
{
	static t_list	*head;

	return (&head);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	t_list	**head;

	head = return_ptr();
	ptr = malloc(size);
	if (!ptr)
		ft_free_all(nothing);
	if (!add_ptr(ptr, head))
		ft_free_all(nothing);
	return (ptr);
}
