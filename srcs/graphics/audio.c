/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 00:58:09 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/21 04:34:28 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

static const char *audioFiles[] = {
  "assets/audio/confirm.wav",
  "assets/audio/defeat.wav",
  "assets/audio/deselect.wav",
  "assets/audio/leveling.wav",
  "assets/audio/select.wav",
  "assets/audio/victory.wav"
};

/* ************************************************************************** */

static inline int loadSoundtrack(t_game *game);
static inline int loadSounds    (t_game *game);

/* ************************************************************************** */

void playAudio(t_game *game, Sound sound) {
  if (game->audioEnabled)
    PlaySound(sound);
};

/* ************************************************************************** */

int setupAudio(t_game *game) {
  InitAudioDevice();
  if (!IsAudioDeviceReady()
    || loadSoundtrack(game) == EXIT_FAILURE
    || loadSounds(game) == EXIT_FAILURE)
  {
    deleteAudio(game);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
};

/* ************************************************************************** */

static inline int loadSoundtrack(t_game *game) {
  game->soundtrack = LoadMusicStream("assets/audio/soundtrack.mp3");
  if (!IsMusicValid(game->soundtrack)) {
    game->soundtrack = (Music){0};
    return EXIT_FAILURE;
  };

  PlayMusicStream(game->soundtrack);
  return EXIT_SUCCESS;
};

static inline int loadSounds(t_game *game) {
  Sound *sounds[] = {
    &game->confirmationSound,
    &game->defeatSound,
    &game->deselectSound,
    &game->levelingSound,
    &game->selectSound,
    &game->victorySound
  };

  for (size_t i = 0; i < sizeof(sounds) / sizeof(sounds[0]); i++) {
    Sound *sound = sounds[i];

    *sound = LoadSound(audioFiles[i]);
    if (!IsSoundValid(*sound)) {
      *sound = (Sound){0};
      return EXIT_FAILURE;
    };
  };
  return EXIT_SUCCESS;
};

/* ************************************************************************** */