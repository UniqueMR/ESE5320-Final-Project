#include "Pipeline.h"
#include <stdlib.h>

static unsigned Coefficients[] = {2, 15, 62, 98, 62, 15, 2};

static void Filter_horizontal_SW(const unsigned char * Input,
		                      unsigned char * Output)
{
  int X, Y, i;
  for (Y = 0; Y < SCALED_FRAME_HEIGHT; Y++)
    for (X = 0; X < OUTPUT_FRAME_WIDTH; X++)
    {
      unsigned int Sum = 0;
      for (i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[Y * SCALED_FRAME_WIDTH + X + i];
      Output[Y * OUTPUT_FRAME_WIDTH + X] = Sum >> 8;
    }
}

static void Filter_horizontal_HW(const unsigned char * Input, unsigned char * Output)
{
    int X, Y, i;
    unsigned int Sum;
    unsigned char window[FILTER_LENGTH]; // Sliding window buffer

    for (Y = 0; Y < SCALED_FRAME_HEIGHT; Y++)
    {
        // Initialize the sliding window for the start of each row
        for (i = 0; i < FILTER_LENGTH; i++)
        {
            window[i] = Input[Y * SCALED_FRAME_WIDTH + i];
        }

        for (X = 0; X < OUTPUT_FRAME_WIDTH; X++)
        {
            // Compute convolution using the sliding window
            Sum = 0;
            for (i = 0; i < FILTER_LENGTH; i++)
            {
                Sum += Coefficients[i] * window[i];
            }

            Output[Y * OUTPUT_FRAME_WIDTH + X] = Sum >> 8;

            // Slide the window: remove the oldest value and fetch the next value from input
            for (i = 0; i < FILTER_LENGTH - 1; i++)
            {
                window[i] = window[i + 1];
            }
            window[FILTER_LENGTH - 1] = Input[Y * SCALED_FRAME_WIDTH + X + FILTER_LENGTH];
        }
    }
}

static void Filter_vertical_SW(const unsigned char * Input,
		                    unsigned char * Output)
{
  int X, Y, i;
  for (Y = 0; Y < OUTPUT_FRAME_HEIGHT; Y++)
    for (X = 0; X < OUTPUT_FRAME_WIDTH; X++)
    {
      unsigned int Sum = 0;
      for (i = 0; i < FILTER_LENGTH; i++)
        Sum += Coefficients[i] * Input[(Y + i) * OUTPUT_FRAME_WIDTH + X];
      Output[Y * OUTPUT_FRAME_WIDTH + X] = Sum >> 8;
    }
}

void Filter_SW(const unsigned char * Input,
	           unsigned char * Output)
{
  unsigned char * Temp = (unsigned char *) malloc(SCALED_FRAME_HEIGHT * OUTPUT_FRAME_WIDTH);
  Filter_horizontal_SW(Input, Temp);
  Filter_vertical_SW(Temp, Output);
  free(Temp);
}

void Filter_HW(const unsigned char * Input,
	           unsigned char * Output)
{
  unsigned char * Temp = (unsigned char *) malloc(SCALED_FRAME_HEIGHT * OUTPUT_FRAME_WIDTH);
  Filter_horizontal_HW(Input, Temp);
  // Filter_horizontal_SW(Input, Temp);
  Filter_vertical_SW(Temp, Output);
  free(Temp);
}
