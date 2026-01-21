/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 06:13:43 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/21 04:34:49 by aheitz           ###   ########.fr       */
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
  double      startTime;
  char        aiMessage[256];

  // ? Audio */
  Music soundtrack;
  Sound selectSound;
  Sound levelingSound;
  Sound deselectSound;
  Sound confirmationSound;
  Sound victorySound;
  Sound defeatSound;
  bool  audioEnabled;

  // ? Game state */
  bool ended;
} t_game;

/* ************************************************************************** */

int  renderGraphics(t_vector *sticks);

int  setupWindow(t_game *game, t_vector *sticks);
int  setupAudio(t_game *game);

void playAudio(t_game *game, Sound sound);

void drawBackground(const Texture2D texture);
void drawSticksHeap(t_game *game, int y);

void stopRender(t_game *game);
void deleteAudio(t_game *game);

void selectStick(t_game *game);

void ft_move_bonus(t_game *game, bool *player_turn, bool *game_over);

/* ************************************************************************** */