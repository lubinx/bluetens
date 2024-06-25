cmake_minimum_required(VERSION 3.20)

include(".vscode/intro.cmake")
project(bluetens)

build_target(QN908X_bluetens
    DEVICE
        "QN908X"
    DRIVER
        "../qn908x"
    CONFIG_DIR
        "bluetens2/qn908x"
    INCLUDE_DIRS
        "."
        "sh"
        "bluetens2"
    SRCS
        "*.c"
        "*.cpp"
        "sh/*.cpp"
        "bluetens2/*.cpp"
        "${ULTRACORE_ROOT}/src/hw/common_gpio.c"
    DEFINITIONS
        NVM_TAG="bluetens"
        "BLUETENS2"
    OUTPUT_DIR
        "../_bin"
)

print_targets()
