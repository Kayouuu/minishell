/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:52:49 by lbattest          #+#    #+#             */
/*   Updated: 2022/05/05 14:53:36 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstclear_char(t_list_char **lst, void (*del)(void *))
{
	t_list_char	*tmp;

	while (*lst != 0)
	{
		tmp = (*lst)->next;
		lstdelone_char(*lst, del);
		(*lst) = tmp;
	}
}
