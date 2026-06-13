#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include <math.h>

#define HEIGHT 600
#define WIDTH 900

#define MASS_RADIUS 20
#define LINE1 250
#define LINE2 125
#define LINE_THICKNESS 4
#define G 981
#define TRACE_LEN 200
#define TRACE_THICKNESS 2

int current_trace_length = 0;

Vector2 trace[TRACE_LEN];

float l1,l2,phi1,phi2,phi1_d, phi2_d, phi1_dd, phi2_dd, m1, m2;

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
  // draw second pendulum
  Vector2 end_l1 = get_end(start, l1, phi1);
  draw_pendulum(l2, end_l1, phi2);
  
  // draw first pendulum
  draw_pendulum(l1,start, phi1);

  //draw the trace
  Vector2 end_l2 = get_end(end_l1, l2, phi2);
  if (current_trace_length < TRACE_LEN) current_trace_length++;
  
  Vector2 trace_copy[TRACE_LEN];
  memcpy(trace_copy, trace, TRACE_LEN*sizeof(Vector2));
  for (int i = 1; i< TRACE_LEN; ++i) {
    trace[i] = trace_copy[i-1];
  }
  trace[0] = end_l2;
  Color color = RED;
  for (int i = 1; i< current_trace_length; ++i) {
    color.a = (unsigned char)((float)0xFF * ( 1 - (float) i / (float) current_trace_length));
    DrawRectangleV(trace[i], (Vector2){TRACE_THICKNESS, TRACE_THICKNESS}, color);
  }
}

void step(float dt) {
  // angular acceleration (according to differential equations)
  phi1_dd = (-G*(2*m1+m2)*sinf(phi1)-m2*G*sinf(phi1-2*phi2)-2*sinf(phi1-phi2)*m2*(phi2_d*phi2_d*l2 + phi1_d*phi1_d*l1*cosf(phi1-phi2))) / (l1*(2*m1+m2-m2*cosf(2*phi1-2*phi2)));

  phi2_dd = 2*sinf(phi1-phi2)*(phi1_d*phi1_d*l1*(m1+m2) + G * (m1+m2)*cosf(phi1) + phi2_d*phi2_d*l1*m2*cosf(phi1-phi2)) / (l2 * (2*m1+m2-m2*cosf(2*phi1-2*phi2)));

  // anular velocity
  phi1_d += phi1_dd * dt;
  phi2_d += phi2_dd * dt;

  //angle itself
  phi1 += phi1_d * dt;
  phi2 += phi2_d * dt;


}

void initSolver(){
  l1 = LINE1;
  l2 = LINE2;
  phi1 = GetRandomValue(-90, 90)*DEG2RAD;
  phi2 = GetRandomValue(-90, 90)*DEG2RAD;
  phi1_d = 0;
  phi2_d = 0;
  m1 = 1;
  m2 = 2;
}

int main (int argc, int *argv[]) {
  
  InitWindow(WIDTH,HEIGHT, "DoublePendulum");

  SetTargetFPS(60);
  
  initSolver();
  while (!WindowShouldClose()) {
    step(GetFrameTime());
    BeginDrawing();
    
    ClearBackground(BLACK);
    draw_double_pendulum(start_pos, phi1, phi2, l1, l2);
    EndDrawing();
  }


  return 0;
}
