/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:20:42 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/19 18:48:03 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AiCu.h"
#include "get_next_line.h"

/**
 * @brief	Prints the current state of the game board.
 * 
 * This function displays the game board, showing the number of matches
 * remaining in each line. It formats the output to align the matches
 * properly based on the maximum number of matches in any line.
 * 
 * @param	tab	The game board represented as a vector.
 * @param	max	The maximum number of matches in any line.
 */
void	ft_print_board(t_vector *tab, int max)
{
	int		tmp, space;

	max++;
	for (size_t i = 0; i < tab->index; i++)
	{
		tmp = ((int *)tab->buf)[i];
		space = max - tmp;
		for (int idx = 0; idx < space; idx++)
		{
			write(1, " ", 1);
		}
		for (int j = 0; j < tmp; j++)
		{
			write(1, "| ", 2);
		}
		write(1, "\n", 1);
	}
}
