/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:22:39 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/21 04:06:12 by aheitz           ###   ########.fr       */
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
		ft_error("ERROR\nCould't allocate memory\n");
		return (1);
	}
	if (ac <= 2)
	{
		if (!this_is_sparsing(ac, av, tab, &max))
			return (ft_free_vector(&tab), 1);
	}
	else
		return (ft_error("ERROR\nUsage: './alum1' or './alum1 [file]'\n"), 1);
	printf("main %d   %d   %d   %d\n", tab->buf[0], tab->buf[1], tab->buf[2], tab->buf[3]);

	const int status = renderGraphics(tab);
	ft_free_vector(&tab);
	return (status);
}

