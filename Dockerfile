FROM fedora:latest

RUN sudo dnf update -y && sudo dnf install -y cmake clang clang-devel clang-libs valgrind