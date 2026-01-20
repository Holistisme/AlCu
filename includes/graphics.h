/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 06:13:43 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 09:58:09 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AiCu.h"
#include "raylib.h"

/* ************************************************************************** */

#define NONE_SELECTED    -1
#define STICK_SCALE       6
#define UNREACHABLE_STICK 424242

/* ************************************************************************** */

typedef struct s_game {
  t_vector   *sticks;
  Model       stickModel;
  Model       selectedStickModel;
  BoundingBox stickBox;
  Camera3D    camera;
  Texture2D   stickTexture;
  Texture2D   backgroundTexture;
  int         clickedSticks[3];
  int         stickSelected;
} t_game;

/* ************************************************************************** */

int  setupWindow(t_game *game, t_vector *sticks);
int  renderGraphics(t_vector *sticks);

void drawBackground(const Texture2D texture);
void drawSticksHeap(t_game *game, int y);

void stopRender(t_game *game);

void selectStick(t_game *game);

/* ************************************************************************** */