#include "App.h"

void Scale_coarse(const unsigned char *Input, unsigned char *Output, int Y_Start_Idx, int Y_End_Idx)
{
  for (int Y = Y_Start_Idx; Y < Y_End_Idx; Y += 2)
  {
    for (int X = 0; X < INPUT_WIDTH_SCALE; X += 2)
    {
      Output[(Y / 2) * INPUT_WIDTH_SCALE / 2 + (X / 2)] = Input[Y * INPUT_WIDTH_SCALE + X];
    }
  }
}

#define HEIGHT (540)
#define WIDTH (960)

void Scale(const unsigned char *Input, unsigned char *Output)
{
  for (int Y = 0; Y < HEIGHT; Y += 2)
    for (int X = 0; X < WIDTH; X += 2)
      Output[(Y / 2) * WIDTH / 2 + (X / 2)] = Input[Y * WIDTH + X];
}
