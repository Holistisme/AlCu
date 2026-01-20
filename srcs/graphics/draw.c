/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 03:52:33 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 10:26:36 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

static void drawStick(t_game *game, Vector3 position, int index);

/* ************************************************************************** */

void inline drawBackground(const Texture2D texture) {
  DrawTexturePro(
    texture,
    (Rectangle){0.0f, 0.0f, (float)texture.width,    (float)texture.height},
    (Rectangle)  {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
    (Vector2)  {0.0f, 0.0f},
    0.0f,
    WHITE
  );
};

/* ************************************************************************** */

void drawSticksHeap(t_game *game, int y) {
  const int size = ((int *)game->sticks->buf)[game->sticks->index - 1 - y];

  if (size % 2 == 0) {
    int j = 0;
    for (int i = 0; i < size / 2; i++)
      drawStick(game, (Vector3){-0.5 - (float)i, y * 2, 0}, i);
    for (int i = size / 2; i < size; i++)
      drawStick(game, (Vector3){0.5 + (float)j++, y * 2, 0}, i);
  } else {
    int j = 1;
    drawStick(game, (Vector3){0, y * 2, 0}, 0);
    for (int i = 1; i <= size / 2; i++)
      drawStick(game, (Vector3){-1 - (float)(i - 1), y * 2, 0}, i);
    for (int i = size / 2 + 1; i < size; i++)
      drawStick(game, (Vector3){1 + (float)(j++ - 1), y * 2, 0}, i);
  };
};

static void drawStick(t_game *game, Vector3 position, int index) {
  BoundingBox box;
  box.min = (Vector3){
    position.x + game->stickBox.min.x * STICK_SCALE,
    position.y + game->stickBox.min.y * STICK_SCALE,
    position.z + game->stickBox.min.z * STICK_SCALE,
  };
  box.max = (Vector3){
    position.x + game->stickBox.max.x * STICK_SCALE,
    position.y + game->stickBox.max.y * STICK_SCALE,
    position.z + game->stickBox.max.z * STICK_SCALE,
  };

  if ((int)position.y == 0)
    for (int i = 0; i < 3; i++)
      if (game->clickedSticks[i] == index)
        return;

  if (game->stickSelected == NONE_SELECTED &&
    GetRayCollisionBox(
      GetMouseRay(GetMousePosition(), game->camera), box).hit)
  {
    DrawModel(game->selectedStickModel, position, STICK_SCALE, BLACK);
    DrawModelWires(game->stickModel, position, STICK_SCALE, RED);
    game->stickSelected = UNREACHABLE_STICK;

    if ((int)position.y == 0)
      game->stickSelected = index;
  } else DrawModel(game->stickModel, position, STICK_SCALE, WHITE);
};

/* ************************************************************************** */