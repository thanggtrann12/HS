#!/bin/bash

# Set the CMake parameters based on script arguments
ENABLE_UT=false
BUILD=false
RUN=false

while [[ "$#" -gt 0 ]]; do
    case $1 in
        -u|--enable-ut)
            ENABLE_UT=true
            ;;
        -b|--build)
            BUILD=true
            ;;
        -r|--run)
            RUN=true
            ;;
        *)
            echo "Unknown parameter: $1"
            exit 1
            ;;
    esac
    shift
done

# Run CMake with specified parameters
if [ "$ENABLE_UT" = true ]; then
     cd build
     cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"  -DENABLE_UT=ON .
     cd ..

else
     cd build
     cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
     cd ..
fi

# Build the project if specified
if [ "$BUILD" = true ]; then
    cd build
    make
    cd ..
fi

# Run unit tests if specified
if [ "$ENABLE_UT" = true ] && [ "$RUN" = true ]; then
    cd build
    make test
    cd ..
fi

# Run the executable if specified
if [ "$RUN" = true ]; then
    ./generated/HeartStone.exe
fi
