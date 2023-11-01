git clone https://github.com/Microsoft/vcpkg.git
cmake . -B_build -DCMAKE_TOOLCHAIN_FILE="./vcpkg/scripts/buildsystems/vcpkg.cmake"