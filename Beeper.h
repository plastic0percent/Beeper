/*
 *  Beeper.h - Drive a QYF-068 beeper.
 *
 *  Copyright (C) 2021 Zhang Maiyun
 *
 *  This file is part of Skymirror_ino.
 *  Skymirror_ino is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Skymirror_ino is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *  along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef Beeper_h
#define Beeper_h

#include <Arduino.h>
#include <Servo.h>

class Beeper
{
  public:
    Beeper(int pin);
    // Beep for DUR seconds long
    void beep(unsigned long freq, float dur);
    // Beep indefinitely
    void beep_forever(unsigned long freq);
    double get_delay(unsigned long freq);
  private:
    Servo pwm;
    int _pin;
};

#endif

