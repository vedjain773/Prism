#!/bin/sh
set -e

echo "Setting up Prism dependencies..."

mkdir -p libs include

#cfft
if [-d "libs/libcfft.a"]; then
    echo "CFFT already built, skipping..."
else
    echo "Building CFFT..."
    make lib
fi

# Raylib
if [ -d "libs/raylib" ]; then
    echo "Raylib already exists, skipping..."
else
    echo "Cloning Raylib..."
    git clone --depth 1 https://github.com/raysan5/raylib.git libs/raylib
fi

# miniaudio
if [ -f "include/miniaudio.h" ]; then
    echo "miniaudio already exists, skipping..."
else
    echo "Downloading miniaudio..."
    curl -o include/miniaudio.h https://raw.githubusercontent.com/mackron/miniaudio/master/miniaudio.h
fi

# Build Raylib
echo "Building Raylib..."
cd libs/raylib/src
make PLATFORM=PLATFORM_DESKTOP GLFW_LINUX_ENABLE_WAYLAND=TRUE
cd ../../..

echo "Done. Run 'make' to build Prism."
