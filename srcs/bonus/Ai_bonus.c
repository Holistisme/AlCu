/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ai_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:27:08 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/21 12:53:16 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

static inline	void	validateSelection(t_game *game);

inline	void	ft_move_bonus(t_game *game)
{
	int		ai_matches = 0;
	double	elapsedTime = GetTime() - game->startTime;

	if (elapsedTime < 5.0)
		return;

	if (!game->humanTurn && game->sticks->index > 0 && !game->ended)
	{
		const size_t index = game->sticks->index;

		ai_matches = ft_ai_move(game->sticks);
		if (index > 1 && index != game->sticks->index)
			playAudio(game, game->levelingSound);

		snprintf(game->aiMessage, sizeof(game->aiMessage), "AI took %d stick%s", ai_matches, (ai_matches > 1) ? "s" : "");
		game->humanTurn = true;

		game->clickedSticks[0] = NONE_SELECTED;
		game->clickedSticks[1] = NONE_SELECTED;
		game->clickedSticks[2] = NONE_SELECTED;
	}

	if (game->humanTurn && IsKeyPressed(KEY_ENTER))
		validateSelection(game);

	if (game->sticks->index == 0) {
		if (game->humanTurn) {
			if (!IsSoundPlaying(game->victorySound) && !game->ended) {
				game->ended = true;
				playAudio(game, game->victorySound);
			};
		} else {
			if (!IsSoundPlaying(game->defeatSound) && !game->ended) {
				game->ended = true;
				playAudio(game, game->defeatSound);
			};
		};
		game->ended = true;
	}
}

static inline void	validateSelection(t_game *game)
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
			game->humanTurn = false;
			game->aiMessage[0] = 0;

			game->clickedSticks[0] = NONE_SELECTED;
			game->clickedSticks[1] = NONE_SELECTED;
			game->clickedSticks[2] = NONE_SELECTED;
		}
	}
}

/* ************************************************************************** */