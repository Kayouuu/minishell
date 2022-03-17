/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstiter_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:51:34 by lbattest          #+#    #+#             */
/*   Updated: 2022/03/17 09:43:38 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstiter_char(t_list_char *lst, void (*f)(void *))
{
	while (lst != 0)
	{
		f(lst->content);
		lst = lst->next;
	}
}
