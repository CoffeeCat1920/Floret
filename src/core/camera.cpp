#include "../../include/core/camera.h"

Camera2D camera = {0};

void InitCamera() {
    camera.target = (Vector2){ 0.0f, 0.0f };
    camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 2.5f;
}
