/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfahmi <mfahmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:09:45 by mfahmi            #+#    #+#             */
/*   Updated: 2025/10/20 16:39:17 by mfahmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del) (void*))
{
	if (!del || !lst)
		return ;
	del (lst->content);
	free (lst);
}
/*void del(void *content)
{
        free(content);
}*/
/*int main()
{
        t_list *head = NULL;
        t_list *lk_1, *lk_2, *lk_3;
        lk_1 = ft_malloc(sizeof(t_list));
        lk_2 = ft_malloc(sizeof(t_list));
        lk_3 = ft_malloc(sizeof(t_list));
        head = lk_1;
        lk_1->next = lk_2;
        lk_2->next = lk_3;
        lk_3->next = NULL;
        lk_1->content = ft_malloc (sizeof(char) * (4 + 1));
        strcpy(lk_1->content,"test");
        lk_2->content = (char *)"test";
        lk_3->content = (char *)"hihi";
        ft_lstdelone(lk_1 ,del);
}*/
