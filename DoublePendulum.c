#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define HEIGHT 600
#define WIDTH 900

void draw_pendulum(float l, Vector2 start, float phi) {
  
  Vector2 end = (Vector2) {start.x + l * sinf(phi), start.y + l * cosf(phi)};
  DrawLineV(start, end, WHITE);

}

int main (int argc, int *argv[]) {
  
  InitWindow(WIDTH,HEIGHT, "DoublePendulum");

  SetTargetFPS(60);

  Vector2 start_pos = (Vector2) {WIDTH/2, 0};
  while (!WindowShouldClose()) {
    BeginDrawing();
  
    ClearBackground(BLACK);
    draw_pendulum(HEIGHT/3*2, start_pos, 0.5);
    EndDrawing();
  }


  return 0;
}
