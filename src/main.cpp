#include <raylib-cpp.hpp>
#include "globals.h"
#include "GameManager.h"
#include "RendererRayLib.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

int main() {

    raylib::Window w(screenWidth, screenHeight, "Raycpp");
    SetTargetFPS(60);

    RendererRayLib renderer{};
    GameManager gm;

    Model model = LoadModel("res/biplane.glb");

    gm.populate();


    Camera camera = { 0 };
    camera.position = (Vector3){ 0.01f, 150.0f, 0.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 40.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 position = { 0.0f, 0.0f, 0.0f };

    Shader shader = LoadShader("res/lighting.vs", "res/fog.fs");
    shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

    // Ambient light level
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]){ 1.2f, 0.2f, 0.2f, 1.0f }, SHADER_UNIFORM_VEC4);

    float fogDensity = 0.15f;
    int fogDensityLoc = GetShaderLocation(shader, "fogDensity");
    SetShaderValue(shader, fogDensityLoc, &fogDensity, SHADER_UNIFORM_FLOAT);

    SetShaderValue(shader, shader.locs[SHADER_LOC_VECTOR_VIEW], &camera.position.x, SHADER_UNIFORM_VEC3);

    //CreateLight(LIGHT_POINT, (Vector3){ 0, 2, 6 }, Vector3Zero(), WHITE, shader);

    float yaw = 0.0f;
    float roll = 0.0f;

    while (!w.ShouldClose()) {
        auto dt = GetFrameTime();
        gm.update(dt);

        // Plane yaw (y-axis) controls
        if (IsKeyDown(KEY_LEFT)) yaw += 2.0f;
        else if (IsKeyDown(KEY_RIGHT)) yaw -= 2.0f;

        // Plane roll (z-axis) controls
        if (IsKeyDown(KEY_LEFT)) roll -= 0.6f;
        else if (IsKeyDown(KEY_RIGHT)) roll += 0.6f;
        else
        {
            if (roll > 0.0f) roll -= 0.5f;
            else if (roll < 0.0f) roll += 0.5f;
        }

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

        auto v = Vector3Transform((Vector3){0,0,30*dt}, model.transform);
        position = Vector3Add(position, v);

        BeginDrawing();

        renderer.render(gm);

        BeginMode3D(camera);
        DrawModel(model, position, 1.0f, WHITE);
        EndMode3D();

        EndDrawing();
    }

    return 0;
}
