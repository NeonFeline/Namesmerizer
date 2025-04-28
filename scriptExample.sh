#!/bin/bash

mkdir -p output  # make sure output directory exists

for file in ./input/*; do
    filename=$(basename "$file")                      # just the filename, no path
    newname=$(./namesmerizer "$filename")       # pass only the filename
    newname=$(echo "$newname" | tr -d '\r\n')         # clean any newlines or carriage returns

    cp "$file" "./output/$newname"
    echo "Copied '$file' to './output/$newname'"
done

