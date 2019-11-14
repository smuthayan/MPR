// mouseposRecorder.cpp : Defines the entry point for the console application.
//
// #define NOMINMAX DEFINED IN THE PRECOMPILED HEADER
#include "stdafx.h"

#include <limits>

#include <iostream>

#include <fstream>

#include <Windows.h>

#include <ctime>

#include <cstddef>

#include <time.h>

#include <cmath>

::std::double_t calculateDist(::std::uint64_t pointX, ::std::uint64_t pointY, ::std::uint64_t pointX2, ::std::uint64_t pointY2) {
  ::std::int64_t changeInX = pointX2 - pointX;
  ::std::int64_t changeInY = pointY2 - pointY;

  return (::std::double_t) sqrt((pow(changeInX, 2) + pow(changeInY, 2)));
}

int main() {

  ::std::uint16_t counter = 0;
  ::std::uint32_t sleepTime;
  POINT tempPos;
  tempPos.x;
  tempPos.y;
  POINT lastPos;
  lastPos.x = -1;
  lastPos.y = -1;
  POINT firstPos;
  firstPos.x;
  firstPos.y;
  std::ofstream file;
  file.open("Output.txt", std::fstream::out);
  if (!file) {
    std::cout << "Error @ fstream Opening \"Output.txt\" ";
  }
  std::cout << "What is ms delay? Put 0 for no delay: ";
  std::cin >> sleepTime;
  std::cout << "\n";
  while (true) {
    if (std::cin.fail()) {
      std::cin.clear();
      #undef max // If you don't undef max you will get conflicts with <Windows.h> "max" and <iostream> "max"
      std::cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n'); // Clear buffer
      std::cout << "Please enter valid input!" << std::endl;
      std::cin >> sleepTime;
    }
    break;
  }

  while (true) {
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000) && (GetAsyncKeyState(VK_RBUTTON) & 0x8000)) // If all of these keys are pressed then execute. (Try and guess the game...)
    {
      while (true) {
        if (GetAsyncKeyState(VK_F12)) // You don't have to explicity call "file.close" as it automatically at the end of its scope
        {

          file.close();
          return 0;
        } else {

          GetCursorPos( & firstPos);
          Sleep(sleepTime);
          if (firstPos.x == lastPos.x && firstPos.y == lastPos.y) {
            // Do nothing if the last coordinates are the same as our current ones
          } else {

            tempPos.x = (firstPos.x - lastPos.x);
            tempPos.y = (firstPos.y - lastPos.y);
            // Print out coordinates to text file @ Dir of project

            file << "X pos: " << firstPos.x << " Y pos: " << firstPos.y << std::endl;

            if (counter >= 1) {
              file << "			Difference in X: " << tempPos.x << " Difference in Y: " << tempPos.y << std::endl;
              file << "			Distance between points: " << calculateDist(lastPos.x, lastPos.y, firstPos.x, firstPos.y) << std::endl; // ::std::uint64_t calculateDist(POINT pointX, POINT pointY, POINT pointX2, POINT pointY2)

            }
            lastPos.x = firstPos.x; // Use these for checking current against last coordinates
            lastPos.y = firstPos.y;
            counter++;
          }
        }

      }
    } else if (GetAsyncKeyState(VK_F12)) // Exit key
    {
      file.close(); // Writing to file before we close it otherwise it will be blank. Our object does not go out of scope so it won't write automatically resulting in us having to use a call to close it
      return 0;
    }

  }
  return 0;
}
