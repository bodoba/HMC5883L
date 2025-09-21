cmake_minimum_required(VERSION 3.10.0)
project(TankBot VERSION 0.1.0 LANGUAGES C)

include_directories(/opt/local/include)
link_directories(/opt/local/lib)

add_executable(hmc5883l hmc5883l.c  hmc5883l.h
                        i2chelper.c i2chelper.h
                        example.c)

target_link_libraries(hmc5883l wiringPi m)
