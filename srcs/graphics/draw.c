/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 03:52:33 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 06:53:27 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

static void drawStick(t_game *game, Vector3 position);

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

  game->stickSelected = false;
  if (size % 2 == 0) {
    for (int i = 0; i < size / 2; i++) {
      drawStick(game, (Vector3){-0.5 - (float)i, y * 2, 0});
      drawStick(game, (Vector3){ 0.5 + (float)i, y * 2, 0});
    };
  } else {
    drawStick(game, (Vector3){0, y * 2, 0});
    for (int i = 1; i <= size / 2; i++) {
      drawStick(game, (Vector3){-1 - (float)(i - 1), y * 2, 0});
      drawStick(game, (Vector3){ 1 + (float)(i - 1), y * 2, 0});
    };
  };
};

static void drawStick(t_game *game, Vector3 position) {
  BoundingBox box;
  box.min = (Vector3){
    position.x + game->stickBox.min.x * 6,
    position.y + game->stickBox.min.y * 6,
    position.z + game->stickBox.min.z * 6,
  };
  box.max = (Vector3){
    position.x + game->stickBox.max.x * 6,
    position.y + game->stickBox.max.y * 6,
    position.z + game->stickBox.max.z * 6,
  };

  if (!game->stickSelected &&
    GetRayCollisionBox(
      GetMouseRay(GetMousePosition(), game->camera), box).hit)
  {
    DrawModel(game->selectedStickModel, position, 6, BLACK);
    DrawModelWires(game->stickModel, position, 6, RED);
    game->stickSelected = true;
  } else DrawModel(game->stickModel, position, 6, WHITE);
};

/* ************************************************************************** */