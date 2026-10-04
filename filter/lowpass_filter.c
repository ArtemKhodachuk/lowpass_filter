#include "lowpass_filter.h"

bool init_filter(double k_value, lowpass_filter* filter) 
{
    if (k_value > 1.0 || k_value < 0) {
        return false;
    }
    
    filter->k = k_value;
    filter->accumilated_value = 0;
    return true;
}

double process_filter(double raw_value, lowpass_filter* filter) 
{
    filter->accumilated_value = filter->k * filter->accumilated_value + (1 - filter->k) * raw_value;
    return filter->accumilated_value;
}