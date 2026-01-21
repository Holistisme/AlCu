/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:27:19 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/21 05:29:43 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AiCu.h"
#include "graphics.h"
#include "get_next_line.h"

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
	// renderGraphics(tab);
	ft_run(tab, max);
	ft_free_vector(&tab);
	return (0);
}
