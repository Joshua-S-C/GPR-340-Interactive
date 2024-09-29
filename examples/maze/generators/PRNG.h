//
// Created by joshua.sinclairchong on 9/16/2024.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdint.h>
#include <ctime>
#include <chrono>
#include <iostream>

/// <summary>
/// Just a base class
/// </summary>
struct Generator {
  // Clamps numbers to this range. Use -1 as Max to ignore clamping
  int min = 0, max = -1;

  uint16_t a;  // Value

  /// <summary>
  /// Seeds value to time
  /// </summary>
  void init() {
    a = time(nullptr);
    clamp();
  }

  void setRange(int min, int max) {
    this->min = min;
    this->max = max;
  }

  /// <summary>
  /// Clamps value of a. Doesn't run if max is -1
  /// </summary>
  void clamp() {
    if (max == -1) return;

    a = min + (a % (max - min + 1));
  }

  void print() { std::cout << a << ", \t"; }

  virtual void shift() = 0;
};

/// <summary>
/// https://en.wikipedia.org/wiki/Xorshift
/// </summary>
struct Xorshift : Generator {
  Xorshift() { init(); }
  void shift() override {
    uint16_t x = a;

    // Maximum period combo
    x ^= x << 7;
    x ^= x >> 9;
    x ^= x << 8;

    a = x;

    clamp();
  }
};

/// <summary>
/// https://en.wikipedia.org/wiki/Lagged_Fibonacci_generator
/// I'm getting cycles of 168K with Int32, Addition, and no Range
/// Another implementation tracks more than just the previous 2 numbers, then takes does the operator on to different indices that can be further
/// apart.
/// </summary>
struct LFG : Generator {
  enum usedOperator {
    ADD = 0,  // Addition and Subtraction give the largest max period
    SUBTRACT = 1,
    MULTIPLY = 2,  // Not good cuz multiply by 0
    DIVIDE = 3,    // Not listed on the wikipedia, bad cuz divide by 0 lol
    MOD = 4,       // Not listed, same problem as divide
    XOR = 5
  };

  usedOperator op;
  std::string opName;

  uint16_t j;  // Previous number
  uint16_t k;  // Second previous number

  /// <summary>
  /// Initializes the previous two numbers (since they wouldn't exist)
  /// </summary>
  void init() {
    // Change These
    j = 7;
    k = 10;
    op = ADD;

    // Just setting the name for display
    switch (op) {
      case LFG::ADD:
        opName = "Add";
        break;
      case LFG::SUBTRACT:
        opName = "Subtract";
        break;
      case LFG::MULTIPLY:
        opName = "Multiply";
        break;
      case LFG::DIVIDE:
        opName = "Divide";
        break;
      case LFG::MOD:
        opName = "Mod";
        break;
      case LFG::XOR:
        opName = "Xor";
        break;
    }

    a = time(nullptr);
    clamp();
  }

  void shift() override {
    switch (op) {
      case ADD:
        a = j + k;
        break;
      case SUBTRACT:
        a = j - k;
        break;
      case MULTIPLY:
        a = j * k;
        break;
      case DIVIDE:
        a = j / k;
        break;
      case MOD:
        a = j % k;
        break;
      case XOR:
        a = j ^ k;
        break;
      default:
        std::cout << "Achievement Unlocked: How did we get here?";
    }

    clamp();

    k = j;
    j = a;
  }
};

#endif  // GENERATOR_H