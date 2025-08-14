#!/bin/bash

# List of algorithm filenames (excluding bms.c++)
files=(
    bms.c++
    dfs.c++
    bfs.c++
    dfs_bfs.c++
    dfs_history.c++
    bfs_history.c++
    hc.c++
    bs.c++
    hc_history.c++
    bs_history.c++
    oracle.c++
    bnb.c++
    bnb_cost_eh.c++
    bnb_cost_history.c++
    astar.c++
)

# Create empty files
for file in "${files[@]}"; do
    if [[ ! -f "$file" ]]; then
        touch "$file"
        echo "Created $file"
    else
        echo "$file already exists, skipping."
    fi
done
