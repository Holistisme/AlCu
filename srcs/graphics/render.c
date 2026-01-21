/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:49:24 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/21 10:58:45 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

static inline void updateWindow(t_game *game);
static inline void displayMessage(t_game *game);
static inline void drawCountdownMessage(double elapsedTime);

/* ************************************************************************** */

int renderGraphics(t_vector *sticks) {
  t_game game = {0};
  game.gameOn = true;

  if (setupWindow(&game, sticks) == EXIT_FAILURE)
    return EXIT_FAILURE;

  game.startTime = GetTime();
  for (size_t i = 0; i < 3; i++)
    game.clickedSticks[i] = NONE_SELECTED;

  while (!WindowShouldClose() && game.gameOn)
    updateWindow(&game);

  stopRender(&game);
  return EXIT_SUCCESS;
};

/* ************************************************************************** */

static void inline updateWindow(t_game *game) {
  game->stickSelected = -1;

  if (game->audioEnabled) {
    UpdateMusicStream(game->soundtrack);
    if (!IsMusicStreamPlaying(game->soundtrack)) {
      SeekMusicStream(game->soundtrack, 0.0f);
      PlayMusicStream(game->soundtrack);
    };
  };

  BeginDrawing();
  ClearBackground(RAYWHITE);

  if (game->ended) {
    char buffer[256];

    snprintf(buffer, sizeof(buffer), "Press Q or ESC to quit.");
    drawBackground(game->winner ? game->victoryBackground : game->defeatBackground);
    DrawText(buffer, GetScreenWidth() * 0.33,
      GetScreenHeight() * (game->winner ? 0.575 : 0.525), 90, YELLOW);
  } else {
    drawBackground(game->backgroundTexture);

    BeginMode3D(game->camera);
    for (size_t i = 0; i < 3 && i < game->sticks->index; i++)
      drawSticksHeap(game, i);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      selectStick(game);

    EndMode3D();
    displayMessage(game);
  };

  if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_Q)) {
    game->gameOn = false;
    return;
  };

  EndDrawing();
  ft_move_bonus(game);
};

/* ************************************************************************** */

static inline void	displayMessage(t_game *game)
{
	char	buffer[256];
	int		count = 0;
	double	elapsedTime = GetTime() - game->startTime;

	for (int i = 0; i < 3; i++)
		if (game->clickedSticks[i] != NONE_SELECTED)
			count++;

	if (!game->ended)
	{
    drawHiddenHeaps(game);
    drawHiddenSticks(game);
	};

	if (elapsedTime < 5.0)
    drawCountdownMessage(elapsedTime);
	else game->started = true;

	if (game->ended) {
		if (game->humanTurn) {
      if (!IsSoundPlaying(game->victorySound) && !game->ended) {
        game->ended  = true;
        game->winner = true;
        playAudio(game, game->victorySound);
      };
    } else {
      if (!IsSoundPlaying(game->defeatSound) && !game->ended) {
        game->ended = true;
        playAudio(game, game->defeatSound);
      };
    };
	} else if (game->humanTurn) {
		snprintf(buffer, sizeof(buffer),
      "Your turn - Select 1-3 sticks and press ENTER to confirm.\nSelected: %d",
      count);
		DrawText(buffer, GetScreenWidth() * 0.05,
      GetScreenHeight() * 0.9, 50, WHITE);
		if (game->aiMessage[0])
			DrawText(game->aiMessage, GetScreenWidth() * 0.05,
        GetScreenHeight() * 0.85, 50, ORANGE);
	}
}

static inline void drawCountdownMessage(double elapsedTime) {
  char buffer[256];
  const int countdown = 5 - (int)elapsedTime;

  snprintf(buffer, sizeof(buffer),
    "Game starting in %d second%s...",
    countdown, (countdown > 1) ? "s" : "");
  DrawText(buffer, GetScreenWidth() * 0.315,
    GetScreenHeight() * 0.60, 100, YELLOW);
};

/* ************************************************************************** */