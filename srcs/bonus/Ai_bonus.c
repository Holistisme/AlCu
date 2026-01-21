/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ai_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:27:08 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/21 09:21:47 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AiCu.h"
#include "get_next_line.h"
#include "graphics.h"
#include "raylib.h"

static inline	void	validateSelection(t_game *game, bool *player_turn);

inline	void	ft_move_bonus(t_game *game, bool *player_turn, bool *game_over)
{
	int		ai_matches = 0;
	double	elapsedTime = GetTime() - game->startTime;

	// Bloquer les interactions pendant la pause initiale
	if (elapsedTime < 5.0)
		return;

	if (!*player_turn && game->sticks->index > 0 && !*game_over)
	{
		const size_t index = game->sticks->index;

		ai_matches = ft_ai_move(game->sticks);
		if (index > 1 && index != game->sticks->index)
			playAudio(game, game->levelingSound);

		snprintf(game->aiMessage, sizeof(game->aiMessage), "AI took %d stick%s", ai_matches, (ai_matches > 1) ? "s" : "");
		*player_turn = true;
		
		game->clickedSticks[0] = NONE_SELECTED;
		game->clickedSticks[1] = NONE_SELECTED;
		game->clickedSticks[2] = NONE_SELECTED;
	}

	if (*player_turn && IsKeyPressed(KEY_ENTER))
		validateSelection(game, player_turn);
	
	if (game->sticks->index == 0)
		*game_over = true;
}

static inline void	validateSelection(t_game *game, bool *player_turn)
{
	int		count = 0, line, current_value;
	
	for (int i = 0; i < 3; i++)
		if (game->clickedSticks[i] != NONE_SELECTED)
			count++;
	
	if (count > 0 && count <= 3)
	{
		line = game->sticks->index - 1;
		current_value = ((int *)game->sticks->buf)[line];
		
		if (count <= current_value)
		{
			((int *)game->sticks->buf)[line] -= count;
			if (((int *)game->sticks->buf)[line] == 0) {
				if (game->sticks->index > 1)
					playAudio(game, game->levelingSound);
				game->sticks->index--;
			};

			playAudio(game, game->confirmationSound);
			*player_turn = false;
			// Effacer le message de l'IA
			game->aiMessage[0] = '\0';
			
			game->clickedSticks[0] = NONE_SELECTED;
			game->clickedSticks[1] = NONE_SELECTED;
			game->clickedSticks[2] = NONE_SELECTED;
		}
	}
}


