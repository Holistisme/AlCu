/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:22:39 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/21 12:50:53 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

int	main(int ac, char **av)
{
	t_vector	*tab = ft_new_vector(sizeof(int));
	int			max = 0;

	if (!tab)
	{
		ft_error("ERROR: Memory allocation failed.\n");
		return (1);
	}
	if (ac <= 2)
	{
		if (!this_is_sparsing(ac, av, tab, &max))
			return (ft_free_vector(&tab), 1);
	}
	else
		return (ft_error("ERROR: Usage './alum1_bonus' or './alum1_bonus [file]'\n"), 1);
	const int status = renderGraphics(tab);
	if (status == EXIT_FAILURE)
		ft_error("ERROR: Graphics initialization failed.\n");
	ft_free_vector(&tab);
	return (status);
}

/* ************************************************************************** */