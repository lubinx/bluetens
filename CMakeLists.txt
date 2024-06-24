cmake_minimum_required(VERSION 3.20)

include(".vscode/intro.cmake")
project(bluetens)

build_target(QN908X_bluetens
    DEVICE
        "QN908XC"
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
    DEFINITIONS
        # NVM_TAG="bluetens"
        "QN908X"
        "BLUETENS2"
    OUTPUT_DIR
        "../_bin"
)

print_targets()
