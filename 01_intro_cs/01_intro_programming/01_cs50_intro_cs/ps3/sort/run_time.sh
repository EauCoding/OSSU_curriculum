#!/bin/bash

# List of already compiled files
compiled_files=("sort1" "sort2" "sort3")

# Input files for each compiled file
input_files=("reversed50000.txt" "sorted50000.txt")

# Run and time each compiled file with each input
for compiled_file in "${compiled_files[@]}"; do
    for input_file in "${input_files[@]}"; do
        echo "Running $compiled_file with input $input_file"

        # Measure the time using 'time' command and redirect the output to a file
        { time "./$compiled_file" "$input_file"; } 2> "output_${compiled_file}_${input_file}.txt"

        # Extract the real time from the output file and print it
        real_time=$(grep real "output_${compiled_file}_${input_file}.txt" | awk '{print $2}')
        echo "Run time for $compiled_file with $input_file: $real_time"

        # Clean up the output file
        rm "output_${compiled_file}_${input_file}.txt"
    done
done
