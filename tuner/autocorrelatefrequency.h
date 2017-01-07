#include "Arduino.h"

//    FILE: frequencyDSP.ino
//  AUTHOR: rob tillaart (org version akellyirl)
// VERSION: 0.1.03
// PURPOSE: frequency analysis using DSP
//    DATE: 2013-10-27
//     URL: 
//http://www.instructables.com/id/Reliable-Frequency-Detection-Using-DSP-Techniques
float autoCorrelateFrequency(char * sample, int len, float sampleFreq)
{
  long sum = 0;
  long sum_old = 0;
  int thresh = 0;
  byte pd_state = 0;
  int period = 0;  // 0 results in inf

  // Autocorrelation
  for (int i=0; i < len && (pd_state != 3); i++)
  {
    sum_old = sum;
    sum = 0;

    for (int k=0; k <len-i; k++)
    {
      sum += ((sample[k]) & (sample[k+i]))&1;
    }
    sum >>=8;///= 256;

    // Peak Detect State Machine
    // 0: initial, set threshold
    // 1: detect positive slope
    // 2: detect negative slope
    // 3: peak found
    if (pd_state == 0)
    {
      thresh = sum / 2;
      pd_state = 1;
    } 
    else if (pd_state == 1 && (sum > thresh) && (sum - sum_old) > 0) 
    {
      pd_state = 2;
    }
    else if (pd_state == 2 && (sum - sum_old) <= 0) 
    {
      period = i;
      pd_state = 3;
    } 
  }

  return sampleFreq/period;
}
