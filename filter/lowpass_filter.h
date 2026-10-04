#pragma once 
#include "stdbool.h"

typedef struct
{
    double k;
    double accumilated_value;    
} lowpass_filter;

bool init_filter(double k, lowpass_filter* filter);

double process_filter(double raw_value, lowpass_filter* filter);