/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:52:49 by lbattest          #+#    #+#             */
/*   Updated: 2022/03/17 09:43:14 by psaulnie         ###   ########.fr       */
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
