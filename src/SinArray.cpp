// Brushless motor library
// copyright Alexandre Iooss, 2017-2018
// Please see README.txt for license information

#include "SinArray.h"
#include "Arduino.h"

int SinArray::sin_array[N_VALUES];
bool SinArray::sin_array_empty = true;

void SinArray::generate()
{
  // Skip if already done
  if (!sin_array_empty)
  {
    return;
  }

  // Generate sin array
  for (int i = 0; i < N_VALUES; i++)
  {
    sin_array[i] = sin(2. * M_PI * i / (double)N_VALUES) * STORE_TYPE_RANGE;
  }

  // Mark done
  sin_array_empty = false;
}

double SinArray::getSinByOffset(int offset)
{
  // Offset must be positive and between  and N_VALUES-1
  offset = offset % N_VALUES;
  if (offset < 0)
  {
    offset = N_VALUES + offset;
  }

  return sin_array[offset] / (double)STORE_TYPE_RANGE;
}

double SinArray::getSinDegree(double a)
{
  int offset = (a * N_VALUES) / 360;
  return getSinByOffset(offset);
}

double SinArray::getSin(double r)
{
  int offset = (r * N_VALUES) / (2. * M_PI);
  return getSinByOffset(offset);
}
