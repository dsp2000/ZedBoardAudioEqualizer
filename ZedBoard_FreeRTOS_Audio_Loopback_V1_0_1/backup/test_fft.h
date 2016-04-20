/*
 * test_fft.h
 *
 *  Created on: Apr 9, 2016
 *      Author: root
 */

#ifndef TEST_FFT_H_
#define TEST_FFT_H_

#include "audioPlayer.h"
#include "kiss_fftr.h"

#define THRESH      (8000000.0)
#define FFT_MEM     (2312)
#define CHUNK_SIZE 512 // defined in audioPlayer.h
#define CHUNK_BYTES (CHUNK_SIZE/4)

size_t fft_mem = FFT_MEM;

kiss_fft_scalar fft_buf[FFT_MEM];
kiss_fft_scalar fft_in[CHUNK_BYTES];
kiss_fft_cpx fft_out[CHUNK_BYTES / 2 + 1];


void test_fft_real(const char* title, const kiss_fft_scalar in[CHUNK_BYTES], kiss_fft_cpx out[CHUNK_BYTES / 2 + 1])
{
  kiss_fftr_cfg cfg;

  if ((cfg = kiss_fftr_alloc(CHUNK_BYTES, 0/*is_inverse_fft*/, fft_buf, &fft_mem)) != NULL)
  {
    kiss_fftr(cfg, in, out);
  }
  else
  {
    printf("not enough memory: (fft)\n");
    exit(-1);
  }

  // Frequency domain processing
  /*
  int i;
  for (i = 0; i < (CHUNK_BYTES / 2 + 1); i++)
  {

      if (out[i].r < -THRESH)
          out[i].r = -THRESH;
      if (out[i].r > THRESH)
          out[i].r = THRESH;

      if (out[i].i < -THRESH)
          out[i].i = -THRESH;
      if (out[i].i > THRESH)
          out[i].i = THRESH;

      //printf("r: %f, i: %f\n", out[i].r, out[i].i);
  }
  */

  if ((cfg = kiss_fftr_alloc(CHUNK_BYTES, 1/*is_inverse_fft*/, fft_buf, &fft_mem)) != NULL)
  {
    kiss_fftri(cfg, out, in);
  }
  else
  {
    printf("not enough memory: (ifft)\n");
    exit(-1);
  }

}

void process_audio(chunk_d_t *pChunk)
{
    int i;
    // Do audio processing
    for (i = 0; i < pChunk->bytesUsed/4; i++)
    {
        fft_in[i] = (kiss_fft_scalar)pChunk->u16_buff[i];
    }
    test_fft_real("Sample (real)", fft_in, fft_out);
    for (i = 0; i < pChunk->bytesUsed/4; i++)
    {
        //printf("old: %u, new: %+f, ratio: %u\n", pChunk->u16_buff[i], fft_in[i], (u32)fft_in[i]/pChunk->u16_buff[i]);
        pChunk->u16_buff[i] = ((u32)fft_in[i])/CHUNK_BYTES;
    }
}


#endif /* TEST_FFT_H_ */
