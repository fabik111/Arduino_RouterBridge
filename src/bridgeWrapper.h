/*
    This file is part of the Arduino_RouterBridge library.

    Copyright (C) Arduino s.r.l. and/or its affiliated companies

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/
#pragma once
#include <functional>

constexpr int max_brick = 10;
class BrickBase {
  public:
    virtual void setup() = 0;
    virtual void loop() = 0;
};

class BridgeWrapper {
  public:
    static void registerCallbacks(std::function<void()> _setup, std::function<void()> _loop) {
      if (_setup != nullptr) {
          for (int i = 0; i < max_brick; i++) {
          if (setups[i] == nullptr) {
            setups[i] = _setup;
            break;
          }
        }
      }
      if (_loop != nullptr) {
        for (int i = 0; i < max_brick; i++) {
          if (loops[i] == nullptr) {
            loops[i] = _loop;
            break;
          }
        }
      }
    }

    static void setup() {
      for (int i = 0; i < max_brick; i++) {
        if (setups[i] != nullptr) {
          setups[i]();
        }
      }
    }

    static void loop() {
      for (int i = 0; i < max_brick; i++) {
        if (loops[i] != nullptr) {
          loops[i]();
        }
      }
    }
    BridgeWrapper() {
    }
  private:
    static inline std::function<void()> setups[max_brick];
    static inline std::function<void()> loops[max_brick];
};

