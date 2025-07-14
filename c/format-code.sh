#!/bin/zsh

clang-format -style=file:${HOME}/github/dotfiles/clang-format.yml -i src/**/*.h src/**/*.c examples/**/*.c scruffy/**/*.c