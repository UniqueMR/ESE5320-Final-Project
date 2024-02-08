#include "App.h"

#define STAGES (4)

int main()
{
  unsigned char *Input_data = (unsigned char *)malloc(FRAMES * FRAME_SIZE);
  unsigned char *Temp_data[STAGES - 1];
  unsigned char *Output_data = (unsigned char *)malloc(MAX_OUTPUT_SIZE);
  // unsigned char *Output_data1 = (unsigned char *)malloc(MAX_OUTPUT_SIZE);
  // unsigned char *Output_data2 = (unsigned char *)malloc(MAX_OUTPUT_SIZE);

  if (Input_data == NULL)
    Exit_with_error("malloc failed at main for Input_data");

  if (Output_data == NULL)
    Exit_with_error("malloc failed at main for Output_data");

  for (int Stage = 0; Stage < STAGES - 1; Stage++)
  {
    Temp_data[Stage] = (unsigned char *)malloc(FRAME_SIZE);
    if (Temp_data[Stage] == NULL)
      Exit_with_error("malloc failed at main for Temp_data");
  }

  Load_data(Input_data);

  stopwatch total_time;
  int Size = 0;
  // int Length1 = 0; 
  // int Length2 = 0;
  total_time.start();
  for (int Frame = 0; Frame < FRAMES; Frame++)
  {
    std::vector<std::thread> ths;
    ths.push_back(std::thread(&Scale_coarse, Input_data + Frame * FRAME_SIZE, Temp_data[0], 0, INPUT_HEIGHT_SCALE / 2));
    ths.push_back(std::thread(&Scale_coarse, Input_data + Frame * FRAME_SIZE, Temp_data[0], INPUT_HEIGHT_SCALE / 2, INPUT_HEIGHT_SCALE));

    pin_thread_to_cpu(ths[0], 0);
    pin_thread_to_cpu(ths[1], 1);

    for (auto &th : ths)
    {
      th.join();
    }

    Filter(Temp_data[0], Temp_data[1]);

    //Differentiate
    ths.clear();

    ths.push_back(std::thread(&Differentiate_coarse, Temp_data[1], Temp_data[2], 0, INPUT_HEIGHT_DIFF / 2));
    ths.push_back(std::thread(&Differentiate_coarse, Temp_data[1], Temp_data[2], INPUT_HEIGHT_DIFF / 2, INPUT_HEIGHT_DIFF));

    pin_thread_to_cpu(ths[0], 0);
    pin_thread_to_cpu(ths[1], 1);

    for (auto &th : ths)
    {
      th.join();
    }

    // //Compress
    // ths.clear();

    // ths.push_back(std::thread(&Compress_coarse, Temp_data[2], Output_data1, 0, SIZE_COMPRESS / 2, std::ref(Length1)));
    // ths.push_back(std::thread(&Compress_coarse, Temp_data[2], Output_data2, SIZE_COMPRESS / 2, SIZE_COMPRESS, std::ref(Length2)));

    // pin_thread_to_cpu(ths[0], 0);
    // pin_thread_to_cpu(ths[1], 1);

    // for (auto &th : ths)
    // {
    //   th.join();
    // }

    // Size = (Length1 + Length2) / 8 + 1;

    // Differentiate(Temp_data[1], Temp_data[2]);
    Size = Compress(Temp_data[2], Output_data);
  }
  total_time.stop();
  std::cout << "Total time taken by the loop is: " << total_time.latency() << " ns." << std::endl;

  Store_data("Output.bin", Output_data, Size);
  // Store_data("Output.bin", Output_data1, Length1 / 8 + 1);
  Check_data(Output_data, Size);
  // Check_data(Output_data1, Size);

  for (int i = 0; i < STAGES - 1; i++)
    free(Temp_data[i]);
  free(Input_data);
  free(Output_data);

  return EXIT_SUCCESS;
}
