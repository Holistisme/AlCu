/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:49:24 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 06:57:54 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

static void inline updateWindow(t_game *game);

/* ************************************************************************** */

int renderGraphics(t_vector *sticks) {
  t_game game;

  if (setupWindow(&game, sticks) == EXIT_FAILURE)
    return EXIT_FAILURE;

  while (!WindowShouldClose())
    updateWindow(&game);

  stopRender(&game);
  return EXIT_SUCCESS;
};

/* ************************************************************************** */

static void inline updateWindow(t_game *game) {
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "+ %d", 42);

  BeginDrawing();
  ClearBackground(RAYWHITE);
  drawBackground(game->backgroundTexture);
  BeginMode3D(game->camera);
  for (size_t i = 0; i < 3; i++)
    drawSticksHeap(game, i);
  EndMode3D();
  DrawText(buffer, GetScreenWidth() * 0.925, GetScreenHeight() * 0.725, 50, WHITE);
  EndDrawing();
};

/* ************************************************************************** */