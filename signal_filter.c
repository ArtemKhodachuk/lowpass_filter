#include "stdio.h"
#include "filter/lowpass_filter.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
    FILE *input_file;
    FILE *output_file;

    char line[256];

    lowpass_filter filter;
    double time;
    double raw_value;
    double filtered_value;

    if (argc != 4)
    {
        printf("Usage: ./signal_filter.exe <k> <input.csv> <output.csv>\n");
        printf("Example: ./signal_filter.exe 0.90 data/signal.csv data/output.csv\n");

        return 1;
    }

    input_file = fopen(argv[2], "r");

    if (input_file == NULL)
    {
        printf("Error: could not open input file: %s\n", argv[2]);

        return 1;
    }

    output_file = fopen(argv[3], "w");

    if (output_file == NULL)
    {
        printf("Error: could not open output file: %s\n", argv[3]);

        return 1;
    }


    if (!init_filter(strtod(argv[1], NULL), &filter)) 
    {
        printf("Error: invalid k value (should be between 0 and 1)");

        return 1; 
    }

    fprintf(output_file, "t,raw,filtered\n");

    fgets(line, sizeof(line), input_file);
    
    while (fgets(line, sizeof(line), input_file) != NULL)
    {
        if (sscanf(line,"%lf,%lf",&time,&raw_value) != 2)
        {
            printf("Warning: invalid line skipped: %s", line);

            continue;
        }

        filtered_value = process_filter(raw_value, &filter);

        fprintf(output_file, "%.6f,%.6f,%.6f\n", time, raw_value, filtered_value);
    }

    fclose(input_file);
    fclose(output_file);

    printf("Filtering complete. Input file: %s Output file: %s", argv[2], argv[3]);

    return 0;
}