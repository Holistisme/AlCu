/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:22:39 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/21 11:43:53 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AiCu.h"
#include "get_next_line.h"
#include "graphics.h"

int	main(int ac, char **av)
{
	t_vector	*tab = ft_new_vector(sizeof(int));
	int			max = 0;

	if (!tab)
	{
		ft_error();
		return (1);
	}
	if (ac <= 2)
	{
		if (!this_is_sparsing(ac, av, tab, &max))
			return (ft_free_vector(&tab), 1);
	}
	else
		return (ft_error(), 1);
	const int status = renderGraphics(tab);
	ft_free_vector(&tab);
	return (status);
}

