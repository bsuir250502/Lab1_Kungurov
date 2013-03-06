solution "lab1.c"
configurations { "Debug", "Release" }

project "lab1"
kind "ConsoleApp"
language "C"
files { "**.h", "**.c" }

configuration "Debug"
defines { "DEBUG" }
flags { "ExtraWarnings", "Symbols" }

configuration "Release"
defines { "NDEBUG" }
flags { "Optimize" }