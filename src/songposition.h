//
// Created by Nicholas Newdigate on 30/06/2020.
//

#ifndef TEENSYSEQUENCER_SONGPOSITION_H
#define TEENSYSEQUENCER_SONGPOSITION_H


#include <cstdint>
namespace newdigate { 
    struct songposition {
        long bar = 1;
        unsigned long beat = 1;
        unsigned long sixtyFourth = 0;
        unsigned long ticks = 0;
        unsigned long totalTicks = 0;
    };
}

#endif //TEENSYSEQUENCER_SONGPOSITION_H
