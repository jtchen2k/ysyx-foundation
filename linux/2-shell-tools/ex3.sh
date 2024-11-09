#!/usr/bin/env bash

# keep running err.sh until return code is not 0

num_runs=0
echo -n > err.log

while true; do
    #redirect stdout and stderr to err.log
    ./err.sh >> err.log 2>&1
    if [[ $? -ne 0 ]]; then
        cat err.log
        echo "Error occurred after $num_runs runs." >&2
        break
    fi
    num_runs=$((num_runs + 1))
done