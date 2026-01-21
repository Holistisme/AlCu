/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:22:27 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/21 03:41:16 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AiCu.h"
#include "get_next_line.h"

/**
 * @brief	Main game loop handling player and AI turns.
 * 
 * This function manages the game flow, alternating turns between the
 * player and the AI until all matches are removed from the board. It
 * also announces the winner at the end of the game.
 * 
 * @param	tab	The game board represented as a vector.
 * @param	max	The maximum number of matches in any line.
 */
inline void	ft_run(t_vector *tab, int max)
{
	bool	player_turn;

	player_turn = false;
	while (tab->index > 0)
	{
		ft_print_board(tab, max);
		if (player_turn)
		{
			ft_player_move(tab);
			player_turn = false;
		}
		else
		{
			ft_ai_move(tab);
			player_turn = true;
		}
	}
	if (!player_turn)
		write(1, "AI wins!\n", 10);
	else
		write(1, "Player wins!\n", 14);
}

/**
 * @brief	Handles the player's move.
 * 
 * This function prompts the player to choose a line and the number of
 * matches to remove. It validates the input and updates the game board
 * accordingly.
 * 
 * @param	tab	The game board represented as a vector.
 */
inline void	ft_player_move(t_vector *tab)
{
	int		line, matches = 0, current_value;
	char	*input;

	line = tab->index - 1;
	current_value = ((int *)tab->buf)[line];
	while (matches <= 0 || matches > current_value || matches > 3)
	{
		write(1, "Please choose between 1 and ", 28);
		ft_putnbr(current_value < 3 ? current_value : 3);
		write(1, " items\n", 7);
		input = get_next_line(0, 0);
		matches = ft_atoi(input);
		free(input);
		if (matches < 1 || matches > 3 || matches > current_value)
		{
			ft_putnbr(matches);
			write(1, " - Invalid choice\n", 18);
		}
	}
	((int *)tab->buf)[line] -= matches;
	if (((int *)tab->buf)[line] == 0)
		tab->index--;
	get_next_line(0, 1);
}

/**
 * @brief	AI move using a simple strategy based on modulo 4.
 * 
 * This function determines the AI's move by analyzing the current state
 * of the game board. It uses a strategy based on the modulo 4 of the
 * number of matches in the current line and the next line to decide how
 * many matches to remove.
 * 
 * @param	tab	The game board represented as a vector.
 * @return	int	Number of matches removed by the AI.
 */
inline int	ft_ai_move(t_vector *tab)
{
	int		line, matches = 0, current_value;
	bool	next_line_is_mod_4;

	line = tab->index - 1;
	current_value = ((int *)tab->buf)[line];
	
	if (tab->index == 2)
	{
		int next_line_value = ((int *)tab->buf)[line - 1];
		
		if (next_line_value > 5 && (next_line_value - 5) % 4 != 0)
		{
			if (current_value > 5)
			{
				matches = (current_value - 5) % 4;
				if (matches == 0)
					matches = 1;
			}
			else if (current_value == 5) // perdant
				matches = 1;
			else
				matches = current_value - 1;
		}
		else if (next_line_value == 5 || (next_line_value - 5) % 4 == 0)
		{
			matches = current_value % 4;
			if (matches == 0)
				matches = 1;
			if (matches > 3)
				matches = 3;
		}
		else
		{
			if (next_line_value == 1)
			{
				matches = current_value % 4;
				if (matches == 0)
					matches = 1;
				if (matches > 3)
					matches = 3;
			}
			else if (next_line_value >= 2 && next_line_value <= 4)
			{
				if (current_value > 5)
				{
					matches = (current_value - 5) % 4;
					if (matches == 0)
						matches = 1;
				}
				else if (current_value == 5) // perdant
					matches = 1;
				else
					matches = current_value - 1;
			}
		}
	}
	else if (tab->index == 1)
	{
		if (current_value > 5)
		{
			matches = (current_value - 5) % 4;
			if (matches == 0)
				matches = 1;
		}
		else
		{
			if (current_value == 5) // perdant
				matches = 1;
			else
				matches = current_value - 1;
		}
	}
	else
	{
		next_line_is_mod_4 = false;
		if (line > 0 && ((int *)tab->buf)[line - 1] % 4 == 0)
			next_line_is_mod_4 = true;
		
		if (next_line_is_mod_4 && tab->index > 1 && current_value <= 3)
			matches = current_value;
		else
		{
			matches = current_value % 4;
			if (matches == 0)
				matches = 1;
			if (matches >= current_value && current_value > 1)
				matches = current_value - 1;
		}
	}

	if (matches < 1)
		matches = 1;
	else if (matches > 3)
		matches = 3;

	((int *)tab->buf)[line] -= matches;
	if (((int *)tab->buf)[line] == 0)
		tab->index--;
	write(1, "AI took ", 8);
	ft_putnbr(matches);
	write(1, "\n", 1);
	return (matches);
}

// j'ai aussi vu une strat de XOR.
