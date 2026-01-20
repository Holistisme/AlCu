/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 06:13:02 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 06:59:48 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "raylib.h"

/* ************************************************************************** */

static int  inline setModels   (t_game *game);
static int  inline setTextures (t_game *game);
static void inline applyTexture(t_game *game);
static void inline setCamera   (t_game *game);

/* ************************************************************************** */

int setupWindow(t_game *game, t_vector *sticks) {
  InitWindow(GetScreenWidth(), GetScreenHeight(), "AlCu.exe");
  SetTargetFPS(60);
  game->sticks = sticks;

  if (setModels(game) == EXIT_FAILURE || setTextures(game) == EXIT_FAILURE)
    return EXIT_FAILURE;

  game->stickBox = GetModelBoundingBox(game->stickModel);
  applyTexture(game);
  setCamera(game);

  return EXIT_SUCCESS;
};

/* ************************************************************************** */

static int inline setModels(t_game *game) {
  game->stickModel = LoadModel("models/Stick.glb");
  if (!game->stickModel.meshCount) {
    CloseWindow();
    return EXIT_FAILURE;
  };

  game->selectedStickModel = LoadModel("models/Stick.glb");
  if (!game->selectedStickModel.meshCount) {
    UnloadModel(game->stickModel);
    CloseWindow();
    return EXIT_FAILURE;
  };

  return EXIT_SUCCESS;
};

static int inline setTextures(t_game *game) {
  game->stickTexture = LoadTexture("textures/stick.jpg");
  if (!game->stickTexture.id) {
    UnloadModel(game->stickModel);
    UnloadModel(game->selectedStickModel);
    CloseWindow();
    return EXIT_FAILURE;
  };

  game->backgroundTexture = LoadTexture("textures/background.jpg");
  if (!game->backgroundTexture.id) {
    UnloadModel(game->stickModel);
    UnloadModel(game->selectedStickModel);
    UnloadTexture(game->stickTexture);
    CloseWindow();
    return EXIT_FAILURE;
  };

  return EXIT_SUCCESS;
};

static void inline applyTexture(t_game *game) {
  for (int i = 0; i < game->stickModel.materialCount; i++) {
    game->stickModel.materials[i].maps[MATERIAL_MAP_ALBEDO].texture = game->stickTexture;
    game->stickModel.materials[i].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
  };
  for (int i = 0; i < game->selectedStickModel.materialCount; i++)
    game->selectedStickModel.materials[i].maps[MATERIAL_MAP_ALBEDO].color = WHITE;
};

static void inline setCamera(t_game *game) {
  game->camera.position   = (Vector3){0.0f, 0.0f, 10.0f};
  game->camera.target     = (Vector3){0.0f, 2.0f, 0.0f};
  game->camera.up         = (Vector3){0.0f, 1.0f, 0.0f};
  game->camera.fovy       = 45.0f;
  game->camera.projection = CAMERA_PERSPECTIVE;
};

/* ************************************************************************** */