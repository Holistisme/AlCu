/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 08:56:44 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/21 09:26:06 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

void drawHiddenHeaps(t_game *game)
{
  char buffer[64];
  if (game->sticks->index <= 3)
    return;

  snprintf(buffer, sizeof(buffer), "+%zu", game->sticks->index - 3);
  DrawTextureEx(game->heapTexture,
    (Vector2){GetScreenWidth() * 0.475,
      GetScreenHeight() * 0.05},
      0.0f,
      0.33f,
      WHITE);
  DrawText(buffer, GetScreenWidth() * 0.485,
    GetScreenHeight() * 0.0475, 33, YELLOW);
};

/* ************************************************************************** */

static inline void drawBranchCount(const int count, const float y);
static inline void drawBranchTexture(t_game *game, const float y);

/* ************************************************************************** */

void drawHiddenSticks(t_game *game)
{
  const double yPositions[3]  = {0.225, 0.45, 0.70};
  const int    stickCounts[3] = {
    ((int *)game->sticks->buf)[game->sticks->index - 3],
    ((int *)game->sticks->buf)[game->sticks->index - 2],
    ((int *)game->sticks->buf)[game->sticks->index - 1],
  };

  for (int i = 0; i < 3; i++) {
    if (stickCounts[i] > 9) {
      drawBranchCount(stickCounts[i], yPositions[i]);
      drawBranchTexture(game, yPositions[i]);
    };
  };
};

static inline void drawBranchCount(const int count, const float y) {
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "+%d", count - 9);
  DrawText(buffer, GetScreenWidth() * 0.925,
    GetScreenHeight() * y, 50, YELLOW);
};

static inline void drawBranchTexture(t_game *game, const float y) {
  DrawTextureEx(game->branchTexture,
    (Vector2){GetScreenWidth() * 0.9,
      GetScreenHeight() * y},
      0.0f,
      0.25f,
      WHITE);
};

/* ************************************************************************** */