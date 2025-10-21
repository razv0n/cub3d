/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:39:45 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/20 16:39:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*newnode;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	newnode = NULL;
	while (lst != NULL)
	{
		content = f(lst->content);
		newnode = ft_lstnew(content);
		if (!newnode)
		{
			ft_lstclear (&newnode, del);
		}
		ft_lstadd_back(&head, newnode);
		lst = lst->next;
	}
	return (head);
}
/*void *f(void *p)
{
        char *k = (char *)p;
        for (int i = 0 ; i < k[i] ; i++)
                k[i] >= 'a' && k[i] <= 'z' ? k[i] -= 32: k[i];
        return (p);
}
void del (void *content)
{
        free(content);
}
int main ()
{
    t_list    *head = NULL;
    t_list    *lk, *lk_2, *lk_3;
    lk = ft_malloc (sizeof(t_list));
    lk_2 = ft_malloc (sizeof(t_list));
    head = lk;
    lk->next = lk_2;
    lk_2->next = NULL;
    //lk_3 = ft_malloc (sizeof(t_list));
    lk->content = ft_strdup("hello");
    lk_2->content = ft_strdup("lol");
    t_list *head_1 = ft_lstmap(head, f, del);
}*/
