#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define HEIGHT 600
#define WIDTH 900

#define MASS_RADIUS 20
#define LINE1 250
#define LINE2 250
#define LINE_THICKNESS 4

Vector2 start_pos = (Vector2) {WIDTH/2, 0};

Vector2 get_end(Vector2 start, float l, float phi){
  return (Vector2) {start.x + l * sinf(phi), start.y + l * cosf(phi)};
}

void draw_pendulum(float l, Vector2 start, float phi) {

  Vector2 end = get_end(start, l , phi); 
  DrawLineEx(start, end, LINE_THICKNESS, WHITE);
  DrawCircleV(end, MASS_RADIUS, RED);

}

void draw_double_pendulum(Vector2 start, float phi1, float phi2, float l1, float l2) {
  draw_pendulum(l2,get_end(start, l1, phi1), phi2);

  draw_pendulum(l1,start, phi1);
}

int main (int argc, int *argv[]) {
  
  InitWindow(WIDTH,HEIGHT, "DoublePendulum");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
  
    ClearBackground(BLACK);
    draw_double_pendulum(start_pos, 50*DEG2RAD, -30*DEG2RAD, LINE1, LINE2);
    EndDrawing();
  }


  return 0;
}
