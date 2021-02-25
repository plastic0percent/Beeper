/*
 *  Beeper.cpp - Drive a QYF-068 beeper.
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

#include "Beeper.h"
#include "Arduino.h"

Beeper::Beeper(int pin)
{
    pinMode(pin, OUTPUT);
    _pin = pin;
}

/* Drive a QYF-068 beeper.
    @param pin Output pin of the beeper.
    @param freq The frequency to create.
    @param dur Duration in seconds.
*/
void Beeper::beep(unsigned long freq, float dur)
{
    // Beeper data (old):
    // delay/ms | frequency/Hz
    // 1        | 4432.0
    // 2        | 4221.2
    // 3        | 4155.3
    // 4        | 4115.8
    // 5        | 4089.9
    // 6        | 4074.6
    // 7        | 4058.1
    // (1+2)/2  | 4287.0
    // (1+3)/2  | 4208.0
    // (1+4)/2  | 4168.5
    // (1+5)/2  | 4142.2
    //
    // Beeper curve from regression: v=429.872/d+4001.3, d=429.872/(v-4001.3)
    //
    // Beeper data (new):
    // delay/us freq+-20/Hz residual1/Hz residual2/Hz residual3/Hz
    // 60       7920        5.8389248    -99.540106   -25.030691
    // 70       6813        -10.510046   -60.89152    -12.593434
    // 80       6000        2.9445392    -14.65508    13.984508
    // 90       5350        0.8291011    3.6399292    16.989575
    // 100      4842        14.375606    30.275936    31.393628
    // 110      4394        -4.7448454   19.705397    10.815126
    // 120      4017        -22.850089   7.2299469    -10.000292
    // 130      3747        11.897882    45.673797    21.386662
    // 140      3461        -12.106698   24.05424     -6.2816634
    // 150      3251        5.5429995    43.183958    7.605788
    // 160      3030        -15.814758   22.67246     -17.492692
    // 170      2878        8.6890942    47.57408     3.3615902
    // 180      2715        2.8568016    41.819965    -5.9901588
    // 190      2569        -2.2992067   36.513651    -14.515408
    // 200      2453        8.6386377    47.137968    -6.7881322
    // 210      2341        11.632968    49.702827    -6.8444065
    //
    // Beeper curve from regression *1 (y~k(x+a)^-1):
    //   v=495139/(d+2.56364), d=495139/v-2.56364
    // Beeper curve from regression 2 (y~kx^-1):
    //   v=481172/d, d=470164/v
    // Beeper curve from regression 3 (y~kx^-1+b):
    //   v=470164/d+108.97, d=470164/(v-108.97)

    unsigned long itersSoFar;
    unsigned long finalIter;
    double avgDelay = 495139 / freq - 2.56364;

    if (avgDelay >= 3000.0)
    {
        avgDelay /= 1000;
        finalIter = (dur * 1000) / (avgDelay * 2);
        for (itersSoFar = 0; itersSoFar < finalIter; ++itersSoFar)
        {
            digitalWrite(_pin, HIGH);
            delay((unsigned long)avgDelay);
            digitalWrite(_pin, LOW);
            delay((unsigned long)avgDelay + 1);
        }
    }
    else
    {
        finalIter = (dur * 1000000) / (avgDelay * 2);
        for (itersSoFar = 0; itersSoFar < finalIter; ++itersSoFar)
        {
            digitalWrite(_pin, HIGH);
            delayMicroseconds((unsigned int)avgDelay);
            digitalWrite(_pin, LOW);
            delayMicroseconds((unsigned int)avgDelay + 1);
        }
    }
}