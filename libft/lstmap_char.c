/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:09:39 by lbattest          #+#    #+#             */
/*   Updated: 2022/03/17 09:44:03 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_char	*lstmap_char(t_list_char *lst, void *(*f)(void *),
	void (*del)(void *))
{
	t_list_char	*new;
	t_list_char	*tmp;

	new = 0;
	while (lst)
	{
		tmp = lstnew_char(f(lst->content));
		if (!lst->content)
			del(lst->content);
		lst = lst->next;
		lstadd_back_char(&new, tmp);
	}
	return (new);
}
