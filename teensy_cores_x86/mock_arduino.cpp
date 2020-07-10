/*
  DSM2_tx implements the serial communication protocol used for operating
  the RF modules that can be found in many DSM2-compatible transmitters.

  Copyrigt (C) 2012  Erik Elmore <erik@ironsavior.net>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.  
*/

#include <sys/timeb.h>
#include <iostream>
#include "mock_arduino.h"
#include <unistd.h>
#include <sys/time.h>
timeb t_start;
unsigned tv_start_unsigned;

unsigned long millis() {
  timeb t_now;
  ftime(&t_now);
  return (t_now.time  - t_start.time) * 1000 + (t_now.millitm - t_start.millitm);
}

unsigned long micros() {
  struct timeval tv_now;
  gettimeofday(&tv_now,NULL);
  unsigned long time_in_micros = 1000000 * tv_now.tv_sec + tv_now.tv_usec;
  return (time_in_micros - tv_start_unsigned);
}

void delay(unsigned long ms) {
  unsigned long start = millis();
  while(millis() - start < ms){
    usleep(1000);
  }
}

void initialize_mock_arduino() {
  ftime(&t_start);
  struct timeval tv_start;
  gettimeofday(&tv_start,NULL);

  tv_start_unsigned = 1000000 * tv_start.tv_sec + tv_start.tv_usec;
}

//void _putchar(char character)
//{
//  cout << character;
//}
