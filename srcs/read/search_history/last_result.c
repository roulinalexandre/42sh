/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 21:17:57 by aroulin           #+#    #+#             */
/*   Updated: 2017/09/05 21:17:58 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int			last_resultat(int res)
{
	static int save;

	if (res != -42)
		save = res;
	return (save);
}