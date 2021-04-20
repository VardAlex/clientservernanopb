cmake_minimum_required(VERSION 3.19)
project(client)

set(CMAKE_CXX_STANDARD 14)

add_executable(client client.cpp pb_decode.c pb_encode.c pb_common.c msg.pb.c)