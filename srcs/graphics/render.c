/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:49:24 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/21 04:02:11 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

static void inline updateWindow(t_game *game, bool *player_turn, bool *game_over, bool *game_on);
static inline void	displayMessage(t_game *game, bool player_turn, bool game_over);

/* ************************************************************************** */

int renderGraphics(t_vector *sticks) {
  t_game game = {0};
  bool   player_turn = false, game_over = false, game_on = true;

  if (setupWindow(&game, sticks) == EXIT_FAILURE)
    return EXIT_FAILURE;

  game.clickedSticks[0] = NONE_SELECTED;
  game.clickedSticks[1] = NONE_SELECTED; // ? Reset after confirmation
  game.clickedSticks[2] = NONE_SELECTED;
  game.startTime = GetTime();
  game.aiMessage[0] = '\0';

  printf("Lines remaining: %d\n", game.sticks->buf[game.sticks->index - 1]);
  while (!WindowShouldClose() && game_on)
    updateWindow(&game, &player_turn, &game_over, &game_on);

  stopRender(&game);
  return EXIT_SUCCESS;
};

/* ************************************************************************** */

static void inline updateWindow(t_game *game, bool *player_turn, bool *game_over, bool *game_on) {
  game->stickSelected = -1;
  if (game->audioEnabled)
    UpdateMusicStream(game->soundtrack);
  BeginDrawing();
  ClearBackground(RAYWHITE);
  drawBackground(game->backgroundTexture);
  BeginMode3D(game->camera);

  for (size_t i = 0; i < 3 && i < game->sticks->index; i++)
    drawSticksHeap(game, i);

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    selectStick(game);

  if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_Q))
  {
    *game_on = false;
	return ;
  }
  
  EndMode3D();
  displayMessage(game, *player_turn, *game_over);
  EndDrawing();
  ft_move_bonus(game, player_turn, game_over);
};

/* ************************************************************************** */

static inline void	displayMessage(t_game *game, bool player_turn, bool game_over)
{
	char	buffer[256];
	int		count = 0;
	double	elapsedTime = GetTime() - game->startTime;

	for (int i = 0; i < 3; i++)
		if (game->clickedSticks[i] != NONE_SELECTED)
			count++;
	
	// Afficher le nombre de lignes restantes en haut
	if (!game_over)
	{
		if (game->sticks->index > 1)
			snprintf(buffer, sizeof(buffer), "Lines remaining: %zu\nRemaining on line: %d\nOn next line: %d", game->sticks->index, \
			((int *)game->sticks->buf)[game->sticks->index - 1], ((int *)game->sticks->buf)[game->sticks->index - 2]);
		else
			snprintf(buffer, sizeof(buffer), "Lines remaining: %zu\nRemaining on line: %d", game->sticks->index, \
			((int *)game->sticks->buf)[game->sticks->index - 1]);
		// snprintf(buffer, sizeof(buffer), "Lines remaining: %zu", game->sticks->index);
		DrawText(buffer, GetScreenWidth() * 0.4, GetScreenHeight() * 0.05, 40, SKYBLUE);
	}
	
	// Pause initiale de 5 secondes
	if (elapsedTime < 5.0)
	{
		snprintf(buffer, sizeof(buffer), "Game starting in %.0f seconds...", 5.0 - elapsedTime);
		DrawText(buffer, GetScreenWidth() * 0.35, GetScreenHeight() * 0.5, 50, YELLOW);
		return;
	}
	
	if (game_over)
	{
		if (player_turn) {
      if (!IsSoundPlaying(game->victorySound) && !game->ended) {
        game->ended = true;
        playAudio(game, game->victorySound);
      };
			snprintf(buffer, sizeof(buffer), "Player wins !\nPress ESC or Q to quit.");
    } else {
      if (!IsSoundPlaying(game->defeatSound) && !game->ended) {
        game->ended = true;
        playAudio(game, game->defeatSound);
      };
			snprintf(buffer, sizeof(buffer), "AI wins !\nPress ESC or Q to quit.");
    };
		DrawText(buffer, GetScreenWidth() * 0.35, GetScreenHeight() * 0.5, 80, RED);
	}
	else if (player_turn)
	{
		snprintf(buffer, sizeof(buffer), "Your turn - Select 1-3 sticks and press ENTER to confirm.\nSelected: %d", count);
		DrawText(buffer, GetScreenWidth() * 0.1, GetScreenHeight() * 0.9, 30, WHITE);
		// Afficher le message de l'IA si disponible
		if (game->aiMessage[0] != '\0')
			DrawText(game->aiMessage, GetScreenWidth() * 0.1, GetScreenHeight() * 0.85, 30, ORANGE);
	}
	else
	{
		snprintf(buffer, sizeof(buffer), "AI is thinking...");
		DrawText(buffer, GetScreenWidth() * 0.4, GetScreenHeight() * 0.9, 30, WHITE);
	}
}
