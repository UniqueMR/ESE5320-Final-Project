#include <stdlib.h>
#include <thread>
#include <vector>
#include "Utilities.h"

#define INPUT_HEIGHT (270)
#define INPUT_WIDTH (480)

#define FILTER_LENGTH (7)

#define OUTPUT_HEIGHT (INPUT_HEIGHT - (FILTER_LENGTH - 1))
#define OUTPUT_WIDTH (INPUT_WIDTH - (FILTER_LENGTH - 1))

unsigned Coefficients[] = {2, 15, 62, 98, 62, 15, 2};

void Filter_horizontal(const unsigned char *Input, unsigned char *Output)
{
  for (int Y = 0; Y < INPUT_HEIGHT; Y++)
    for (int X = 0; X < OUTPUT_WIDTH; X++)
    {
      unsigned int Sum = 0;
      for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[Y * INPUT_WIDTH + X + i];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
}

void Filter_horizontal_coarse(const unsigned char *Input, unsigned char *Output, int Y_Start_Idx, int Y_End_Idx){
  for (int Y = Y_Start_Idx; Y < Y_End_Idx; Y++){
    for (int X = 0; X < OUTPUT_WIDTH; X++){
      unsigned int Sum = 0;
      for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[Y * INPUT_WIDTH + X + i];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
  }
}

void Filter_vertical(const unsigned char *Input, unsigned char *Output)
{
  for (int Y = 0; Y < OUTPUT_HEIGHT; Y++)
    for (int X = 0; X < OUTPUT_WIDTH; X++)
    {
      unsigned int Sum = 0;
      for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[(Y + i) * OUTPUT_WIDTH + X];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
}

void Filter_vertical_coarse(const unsigned char *Input, unsigned char *Output, int Y_Start_Idx, int Y_End_Idx){
  for (int Y = Y_Start_Idx; Y < Y_End_Idx; Y++)
    for (int X = 0; X < OUTPUT_WIDTH; X++)
    {
      unsigned int Sum = 0;
      for (int i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[(Y + i) * OUTPUT_WIDTH + X];
      Output[Y * OUTPUT_WIDTH + X] = Sum >> 8;
    }
}

void Filter(const unsigned char *Input, unsigned char *Output)
{
  unsigned char *Temp = (unsigned char *)malloc(INPUT_HEIGHT * OUTPUT_WIDTH);

  std::vector<std::thread> ths;
  ths.push_back(std::thread(&Filter_horizontal_coarse, Input, Temp, 0, INPUT_HEIGHT / 2));
  ths.push_back(std::thread(&Filter_horizontal_coarse, Input, Temp, INPUT_HEIGHT / 2, INPUT_HEIGHT));

  pin_thread_to_cpu(ths[0], 0);
  pin_thread_to_cpu(ths[1], 1);

  for (auto &th : ths)
  {
    th.join();
  }

  ths.clear();

  ths.push_back(std::thread(&Filter_vertical_coarse, Temp, Output, 0, OUTPUT_HEIGHT / 2));
  ths.push_back(std::thread(&Filter_vertical_coarse, Temp, Output, OUTPUT_HEIGHT / 2, OUTPUT_HEIGHT));

  pin_thread_to_cpu(ths[0], 0);
  pin_thread_to_cpu(ths[1], 1);

  for (auto &th : ths)
  {
    th.join();
  }
  // Filter_horizontal(Input, Temp);
  // Filter_vertical(Temp, Output);

  free(Temp);
}


