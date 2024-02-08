#define HEIGHT (540)
#define WIDTH (960)
#define MAX_SHIFT (15)
#include <stdio.h>


#ifdef VECTORIZED
#include <arm_neon.h>
void Scale(const unsigned char *Input, unsigned char *Output)
{
  // Write your NEON accelerated version of Scale here.
  // uint64x2_t Mask = vdupq_n_u64(0xFF00FF00FF00FF00);
  uint64x2_t Mask = vdupq_n_u64(0x00FF00FF00FF00FF);
  uint8x16_t vMask = vreinterpretq_u8_u64(Mask);
  for(int Y = 0; Y< HEIGHT; Y += 2){
    for(int X_base = 0; X_base + MAX_SHIFT <= WIDTH; X_base += 16){
      uint8x16_t vInput = vld1q_u8(Input + Y * WIDTH + X_base);
      uint8x16_t vRes = vandq_u8(vInput, vMask);
      uint16x8_t vRes_u16 = vreinterpretq_u16_u8(vRes);
      uint8x8_t vRes_u8 = vqmovn_u16(vRes_u16);
      vst1_u8(Output + (Y / 2) * (WIDTH / 2) + (X_base / 2), vRes_u8);
    }
  }
}

#else
void Scale(const unsigned char *Input, unsigned char *Output)
{
  for(int Y = 0; Y < HEIGHT; Y += 2)
  {
    for(int X = 0; X < WIDTH; X += 2)
    {
      Output[(Y / 2) * (WIDTH / 2) + (X / 2)] = Input[(Y * WIDTH) + X];
    }
  }
}
#endif