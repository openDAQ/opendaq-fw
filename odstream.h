/*
 *  Copyright (C) 2012 INGEN10 Ingenieria SL
 *  http://www.ingen10.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.

 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version:  120507
 *  Author:   JRB
 */

#ifndef ODSTREAM_H
#define ODSTREAM_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "datachannel.h"

#include "HardwareSerial.h"


//EDGE MODES
#define H_TO_L      0
#define L_TO_H      1


void stream_sm();
void burst_sm();
void ext_sm();


/******************************************************************************
 * Class
 ******************************************************************************/

//! DStream Class
/*!
    DStream Class defines all the variables and functions used for managing the automated data acquisition for openDAQ
 */

class DStream {
public:
    void (*tstreamCallback)();
    void ext_sm();

    int usingch;

    void Initialize();
    void Start();
    void Stop();
    void Pause();
    void Resume();

    //TODO: change second parameter to ms_period
    void CreateStreamChannel(uint8_t nb, unsigned long ms_period);
    void CreateExternalChannel(uint8_t nb, uint8_t edge);
    void CreateExternalChannel(uint8_t nb);
    void CreateBurstChannel(unsigned long us_period);

    void ConfigChan(uint8_t nb, int mode);
    void ConfigChan(uint8_t nb, int mode, int pchan, int nchan);
    void ConfigChan(uint8_t nb, int mode, int pchan, int nchan, int gain);
    void ConfigChan(uint8_t nb, int mode, int pchan, int nchan, int gain,
            int nsamples);
    void ConfigChan(uint8_t nb, int mode, int channel);

    void TriggerMode(uint8_t nb, int trigger_mode, int16_t trigger_value);
    void CheckTriggers();

    void SetupChan(uint8_t nb, unsigned long maxpoints, int repeat);

    void DeleteExperiments(uint8_t nb);
    void FlushChan(uint8_t nb);
};

#endif
