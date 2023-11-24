#!/bin/bash
make
../generated/unittest_HeartStone.exe
# Run the command to generate coverage
make gen_coverage

# Modify the CodeCoverageInfoFile.info file
sed -i 's/C++_Tranining.*.dir.*U://g' CodeCoverageInfoFile.info

# Generate HTML report
genhtml CodeCoverageInfoFile.info --num-spaces 4 --output-directory ./CodeCoverageOutput
