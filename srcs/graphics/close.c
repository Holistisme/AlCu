/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 06:21:54 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/21 04:34:02 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

static inline void deleteGraphics(t_game *game);

/* ************************************************************************** */

void stopRender(t_game *game) {
  if (!game)
    return;

  deleteAudio(game);
  deleteGraphics(game);
  if (IsWindowReady())
    CloseWindow();
};

/* ************************************************************************** */

void deleteAudio(t_game *game) {
  Sound *sounds[] = {
    &game->confirmationSound,
    &game->defeatSound,
    &game->deselectSound,
    &game->levelingSound,
    &game->selectSound,
    &game->victorySound
  };

  if (IsAudioDeviceReady()) {
    if (IsMusicValid(game->soundtrack)) {
      StopMusicStream(game->soundtrack);
      UnloadMusicStream(game->soundtrack);
    };

    for (size_t i = 0; i < sizeof(sounds) / sizeof(sounds[0]); i++) {
      Sound *sound = sounds[i];

      if (IsSoundValid(*sound)) {
        StopSound(*sound);
        UnloadSound(*sound);
      };
    };

    CloseAudioDevice();
  };

  game->soundtrack = (Music){0};
  for (size_t i = 0; i < sizeof(sounds) / sizeof(sounds[0]); i++) {
    Sound *sound = sounds[i];
    *sound = (Sound){0};
  };
};

/* ************************************************************************** */

static inline void deleteGraphics(t_game *game) {
  Texture2D *textures[] = {
    &game->stickTexture,
    &game->backgroundTexture
  };
  Model *models[] = {
    &game->stickModel,
    &game->selectedStickModel
  };

  if (IsWindowReady()) {
    for (size_t i = 0; i < sizeof(textures) / sizeof(textures[0]); i++) {
      Texture2D *texture = textures[i];

      if (IsTextureValid(*texture))
        UnloadTexture(*texture);
    };

    for (size_t i = 0; i < sizeof(models) / sizeof(models[0]); i++) {
      Model *model = models[i];

      if (IsModelValid(*model))
        UnloadModel(*model);
    };
  };

  for (size_t i = 0; i < sizeof(textures) / sizeof(textures[0]); i++)
    *textures[i] = (Texture2D){0};
  for (size_t i = 0; i < sizeof(models) / sizeof(models[0]); i++)
    *models[i] = (Model){0};
};

/* ************************************************************************** */