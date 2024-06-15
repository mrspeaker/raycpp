#include <raylib-cpp.hpp>
#include "globals.h"
#include "GameManager.h"
#include "RendererRayLib.h"
#include <iostream>

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

# define RLIGHTS_IMPLEMENTATION
# include "./rlights.h"

int main() {

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    raylib::Window w(screenWidth, screenHeight, "Raycpp");
    w.SetTargetFPS(60);

    RendererRayLib renderer{};
    GameManager gm;

    raylib::Model model("res/biplane.glb");
    raylib::Model control("res/control.glb");

    gm.populate();

    raylib::Camera3D camera(
                     (Vector3){ 0.001f, 200.0f, 0.0f },
                     (Vector3){ 0.0f, 0.0f, 0.0f },
                     (Vector3){ 0.0f, 1.0f, 0.0f },
                     40.0f,
                     CAMERA_PERSPECTIVE);

    Vector3 position = { 0.0f, 10.0f, 0.0f };

    raylib::Shader shader("res/lighting.vs", "res/lighting.fs");

    for (int i = 0; i < model.materialCount; i++) {
        model.materials[i].shader = shader;
    }
    for (int i = 0; i < control.materialCount; i++) {
        control.materials[i].shader = shader;
    }

    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], &camera.position.x, SHADER_UNIFORM_VEC3);

    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 0.5f, 0.5f, 0.5f, 1.0f }, SHADER_UNIFORM_VEC4);

    Light lights[MAX_LIGHTS] = { 0 };
    lights[0] = CreateLight(LIGHT_POINT, (Vector3){ -0, 50, -0 }, Vector3Zero(), WHITE, shader);

    float yaw = 0.0f;
    float roll = 0.0f;

    while (!w.ShouldClose()) {
        auto dt = GetFrameTime();
        gm.update(dt);


        auto xo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        auto yo = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

        auto yawo = 0.0;
        if (IsKeyDown(KEY_LEFT)||xo < -0.5) yawo += 1.0f;
        else if (IsKeyDown(KEY_RIGHT)||xo > 0.5) yawo -= 1.0f;

        yaw += yawo;

        auto yawsp = 0.5f;
        if (yawo > 0) {
            if (roll > -50.0) {
                roll -= yawsp * roll > 0 ? 2 : 1;
            }
        }
        else if (yawo < 0) {
            if (roll < 50.0) {
                roll += yawsp * roll < 0 ? 2 : 1;
            }
        }
        else
        {
            if (roll > 0.0f) roll -= 0.5f;
            else if (roll < 0.0f) roll += 0.5f;
        }

        if (IsKeyDown(KEY_UP)) position.y -= 10.0f * dt;
        else if (IsKeyDown(KEY_DOWN)) position.y += 10.0f * dt;
        camera.position.x = position.x;
        camera.position.z = position.z - 50;

        camera.target.x = position.x;
        camera.target.z = position.z;

        SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], &camera.position.x, SHADER_UNIFORM_VEC3);

        model.transform = MatrixRotateXYZ((Vector3){ DEG2RAD*0.0, DEG2RAD*yaw, DEG2RAD*roll });

        auto w2 = 100.0;
        auto h2 = 60.0;
        if (position.x > h2) {
            position.x = -h2;
        }
        if (position.x < -h2) {
            position.x = h2;
        }
        if (position.z > w2) {
            position.z = -w2;
        }
        if (position.z < -w2) {
            position.z = w2;
        }

        auto v = Vector3Transform((Vector3){0,0,20*dt}, model.transform);
        position = Vector3Add(position, v);

        w.BeginDrawing();

        renderer.render(gm);

        camera.BeginMode();
        shader.BeginMode();

        DrawGrid(10, 20);
        DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, WHITE);

        model.Draw(position, 1.0f, WHITE);
        for (int j = 0; j < 3; j++) {
            for (int i = 0; i < 4; i++) {
                control.Draw(
                             (Vector3){(j - 1) * 30.0f, 0.0, (i - 2) * 45.0f + 25.0f},
                             1.0f, WHITE);
            }
        }

        shader.EndMode();
        camera.EndMode();

        // DrawFPS(10, 10);

        w.EndDrawing();
    }

    return 0;
}
