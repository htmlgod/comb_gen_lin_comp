#!/bin/bash

placeholder="CPP-LIBRARY-TEMPLATE"
usage="Usage: $(basename $0) PROJECT_NAME"

[[ "$#" -eq 1 ]] || (echo "$usage"; exit 1)

project_name="$1"

echo "Preparing template"
gsed -i "s/"$placeholder"/"$project_name"/g" CMakeLists.txt || (echo "Failed"; exit 1)
gsed -i "s/"$placeholder"/"$project_name"/g" readme.md || (echo "failed"; exit 1)
gsed -i "s/"$placeholder"/"$project_name"/g" tests/tests.cpp || (echo "failed"; exit 1)

mv include/"$placeholder" include/"$project_name"
mv include/"$project_name"/"$placeholder".hpp include/"$project_name"/"$project_name".hpp
echo "Finish"
exit 0
