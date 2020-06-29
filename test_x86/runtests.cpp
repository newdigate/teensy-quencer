#include <stdint.h>
#include <iostream>
#include "SD/SD.h"
#include <unistd.h>
#include <dirent.h>
using namespace std;

void millis_test();
void delay_test();

int main(int argc, char **argv){
	  std::cout << "starting app...\n";
    initialize_mock_arduino();

    millis_test();
    delay_test();
    std::cout << "complete...\n";
}

void millis_test() {
  unsigned long start = millis();
  cout << "millis() test start: " << start << endl;
  while( millis() - start < 10000 ) {
	cout << millis() << endl;
	delay(1);
  }
  unsigned long end = millis();
  cout << "End of test - duration: " << end - start << "ms" << endl;
}

void delay_test() {
  unsigned long start = millis();
  cout << "delay() test start: " << start << endl;
  while( millis() - start < 10000 ) {
	cout << millis() << endl;
	delay(250);
  }
  unsigned long end = millis();
  cout << "End of test - duration: " << end - start << "ms" << endl;
}