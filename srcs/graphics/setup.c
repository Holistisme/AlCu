/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 06:13:02 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/21 08:49:04 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "raylib.h"

/* ************************************************************************** */

static inline int setModel(Model *model, const char *path);
static inline int setTexture(Texture2D *texture, const char *path);

static inline void applyTexture(t_game *game);
static inline void setCamera   (t_game *game);

/* ************************************************************************** */

int setupWindow(t_game *game, t_vector *sticks) {
  InitWindow(GetScreenWidth(), GetScreenHeight(), "AlCu.exe");
  if (!IsWindowReady())
    return EXIT_FAILURE;

  SetTargetFPS(60);
  game->sticks = sticks;

  if (setModel(&game->stickModel, "assets/Stick.glb") == EXIT_FAILURE
    || setModel(&game->selectedStickModel, "assets/Stick.glb") == EXIT_FAILURE
    || setTexture(&game->stickTexture, "assets/textures/stick.jpg") == EXIT_FAILURE
    || setTexture(&game->heapTexture, "assets/textures/heap.png") == EXIT_FAILURE
    || setTexture(&game->branchTexture, "assets/textures/branch.png") == EXIT_FAILURE
    || setTexture(&game->backgroundTexture, "assets/textures/background.jpg") == EXIT_FAILURE)
  {
    stopRender(game);
    return EXIT_FAILURE;
  };

  game->stickBox = GetModelBoundingBox(game->stickModel);
  applyTexture(game);
  setCamera(game);

  // ! Setup audio can fail without threatening the graphics setup
  game->audioEnabled = setupAudio(game) == EXIT_SUCCESS;

  // ! Therefore, we do not treat it as a fatal error here
  // ! But if you want to treat it as such, uncomment the lines below
  // if (setupAudio(game) == EXIT_FAILURE) {
    // stopRender(game);
    // return EXIT_FAILURE;
  // };
  return EXIT_SUCCESS;
};

/* ************************************************************************** */

static inline int setModel(Model *model, const char *path) {
  *model = LoadModel(path);
  if (!IsModelValid(*model)) {
    *model = (Model){0};
    return EXIT_FAILURE;
  };
  return EXIT_SUCCESS;
};

static inline int setTexture(Texture2D *texture, const char *path) {
  *texture = LoadTexture(path);
  if (!IsTextureValid(*texture)) {
    *texture = (Texture2D){0};
    return EXIT_FAILURE;
  };
  return EXIT_SUCCESS;
};

/* ************************************************************************** */

static inline void applyTexture(t_game *game) {
  for (int i = 0; i < game->stickModel.materialCount; i++) {
    game->stickModel.materials[i].maps[MATERIAL_MAP_ALBEDO].texture = game->stickTexture;
    game->stickModel.materials[i].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
  };

  for (int i = 0; i < game->selectedStickModel.materialCount; i++)
    game->selectedStickModel.materials[i].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
};

static inline void setCamera(t_game *game) {
  game->camera.position   = (Vector3){0.0f, 0.0f, 10.0f};
  game->camera.target     = (Vector3){0.0f, 2.0f, 0.0f};
  game->camera.up         = (Vector3){0.0f, 1.0f, 0.0f};
  game->camera.fovy       = 45.0f;
  game->camera.projection = CAMERA_PERSPECTIVE;
};

/* ************************************************************************** */