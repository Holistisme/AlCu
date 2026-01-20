/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:49:24 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 03:40:00 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../raylib/src/raylib.h"

/* ************************************************************************** */

static inline Camera3D setCamera();
static void inline updateWindow(Camera3D *camera, Model model, Texture2D bgTexture);
static void inline drawBackground(const Texture2D texture);

/* ************************************************************************** */

#define STICK_COLOR (Color){154, 96, 48, 255}

int openGraphicsWindow() {
  InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "AlCu.exe");
  SetTargetFPS(60);

  Model stick = LoadModel("models/Stick.glb");
  if (!stick.meshCount) {
    CloseWindow();
    return -1;
  };

  Texture2D background = LoadTexture("textures/background.jpg");
  if (!background.id) {
    UnloadModel(stick);
    CloseWindow();
    return -1;
  };

  for (int i = 0; i < stick.materialCount; i++)
    stick.materials[i].maps[MATERIAL_MAP_ALBEDO].color = STICK_COLOR;

  Camera3D camera = setCamera();
  while (!WindowShouldClose())
    updateWindow(&camera, stick, background);

  UnloadTexture(background);
  UnloadModel(stick);
  CloseWindow();
  return 0;
};

/* ************************************************************************** */

static inline Camera3D setCamera() {
  Camera3D camera = {0};

  camera.position   = (Vector3){0.0f, 0.0f, 10.0f};
  camera.target     = (Vector3){0.0f, 2.0f, 0.0f};
  camera.up         = (Vector3){0.0f, 1.0f, 0.0f};
  camera.fovy       = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  return camera;
};

static void inline drawBackground(const Texture2D texture) {
  DrawTexturePro(
    texture,
    (Rectangle){0.0f, 0.0f, (float)texture.width, (float)texture.height},
    (Rectangle)  {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()},
    (Vector2)  {0.0f, 0.0f},
    0.0f,
    WHITE
  );
};

static void inline updateWindow(Camera3D *camera, Model model, Texture2D bgTexture) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawBackground(bgTexture);
    BeginMode3D(*camera);
    DrawModel(model, (Vector3){-1,   0, 0}, 3, WHITE);
    DrawModel(model, (Vector3){0,    0, 0}, 3, WHITE);
    DrawModel(model, (Vector3){1,    0, 0}, 3, WHITE);
    DrawModel(model, (Vector3){-0.5, 2, 0}, 3, WHITE);
    DrawModel(model, (Vector3){0.5,  2, 0}, 3, WHITE);
    DrawModel(model, (Vector3){0,    4, 0}, 3, WHITE);
    EndMode3D();
    EndDrawing();
};