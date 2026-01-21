/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:27:19 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/21 12:47:07 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AiCu.h"
#include <stdlib.h>

/* ************************************************************************** */

int	main(int ac, char **av)
{
	t_vector	*tab = ft_new_vector(sizeof(int));
	int			max = 0;

	if (!tab)
	{
		ft_error("ERROR: Memory allocation failed.\n");
		return (EXIT_FAILURE);
	}
	if (ac <= 2)
	{
		if (!this_is_sparsing(ac, av, tab, &max))
			return (ft_free_vector(&tab), 1);
	}
	else
		return (ft_error("ERROR: Usage './alum1' or './alum1 [file]'\n"), EXIT_FAILURE);
	ft_run(tab, max);
	ft_free_vector(&tab);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */