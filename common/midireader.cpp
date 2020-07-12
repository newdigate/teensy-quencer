//
// Created by Nicholas Newdigate on 12/07/2020.
//
#include "midireader.h"

struct smf_header {
    uint16_t format;
    // 0 = single track file format
    // 1 = multiple track file format
    // 2 = multiple song file format (i.e., a series of type 0 files
    uint16_t num_tracks;
    uint16_t division;
};

uint32_t varfieldGet(File &file, uint16_t &progress);

bool midireader::open(const char *filename) {
    if (!SD.exists(filename))
        return false;

    _midifile = SD.open(filename);

    if (!_midifile)
        return false;

    unsigned char buffer[6];
    if (_midifile.read(buffer, 4) != 4) {
        return false;
    }

    if (buffer[0] != 'M' || buffer[1] != 'T' || buffer[2] != 'h' || buffer[3] != 'd')
        return false;

    if (_midifile.read(buffer, 4) != 4) {
        return false;
    }

    auto header_length = static_cast<unsigned long>(buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3]);
    if (header_length != 6) {
        return false;
    }

    smf_header header = smf_header();
    // big-endian SMF doesn't allow reading directly to a struct
    //_midifile.read((char*)&buffer, header);

    _midifile.read(buffer, 2);
    header.format = static_cast<uint16_t>(buffer[0] << 8 | buffer[1]);

    _midifile.read(buffer, 2);
    header.num_tracks = static_cast<uint16_t>(buffer[0] << 8 | buffer[1]);

    _midifile.read(buffer, 2);
    header.division = static_cast<uint16_t>(buffer[0] << 8 | buffer[1]);

    if (header.format != 1)
        return false;

    for (uint16_t i = 0; i < header.num_tracks; i++) {
        _midifile.read(buffer, 4);

        if (buffer[0] != 'M' || buffer[1] != 'T' || buffer[2] != 'r' || buffer[3] != 'k')
            return false;

        _midifile.read(buffer, 4);
        auto track_length = static_cast<unsigned long>(buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3]);;

        _track_offset.push_back(_midifile.position());
        _track_size.push_back(track_length-4);
        _midifile.seek(_track_offset[i] + track_length);
        _numTracks++;
    }

    _pulses_per_quater_note = header.division;
    if (_track_offset.size() > 0) {
        _current_track = 0;
        _midifile.seek(_track_offset[0]);
    } else
    {
        _current_track = -1;
        return false;
    }

    return true;
}

void midireader::readMetaText() {
    uint16_t progress = 0;
    uint32_t length = varfieldGet(_midifile, progress);
    _currentTrackOffset += progress;
    char *text = new char[length+1];
    text[length] = 0;
    _midifile.read(text, length);
    Serial.printf("text: ");
    Serial.print(text);
    Serial.println();
    delete[] text;
    _currentTrackOffset += length;
}

bool midireader::read(midimessage &midiMessage) {
    if (_numTracks > 0
        && _current_track < _numTracks
        && _currentTrackOffset < _track_size[_current_track]) {

        uint8_t channel = 0;
        unsigned char status_byte = 0;

        while (_currentTrackOffset < _track_size[_current_track]) {

            uint16_t progress = 0;
            uint32_t delta_ticks = varfieldGet(_midifile, progress);
            _currentTrackOffset += progress;

            unsigned char new_status_byte[1];
            _midifile.read(new_status_byte, 1);

            bool running_status = false;
            if (new_status_byte[0] >= 0x80) {
                status_byte = new_status_byte[0];
                channel = new_status_byte[0] & 0x0f;
            } else
                running_status = true;

            unsigned char key, velocity, nextByte;
            uint32_t length = 0;
            if (status_byte < 0xF0) {
                bool read_second_byte = true;
                switch (status_byte >> 4) {
                    // Channel Voice Messages ( 3 bytes / or 2 bytes )
                    //case 0x80:
                    //case 0x90:
                    //case 0xA0:  // Polyphonic Key Pressure (Aftertouch).
                    //case 0xD0:  // Channel Pressure (After-touch).
                    //case 0xE0:  // Pitch Wheel Change.
                    case 0xC:   // Control Change (and/or Channel Mode Message
                    case 0xD: {  // Program Change
                        read_second_byte = false;
                        break;
                    }

                    default:
                        break;

                }
                //bool noteOn = (status_byte & 0xF0 == 0x80);
                channel = status_byte & 0x0F;

                if (running_status)
                    key = new_status_byte[0];
                else {
                    _midifile.read(new_status_byte, 1);
                    _currentTrackOffset++;
                    key = new_status_byte[0];
                }

                if (read_second_byte) {
                    _midifile.read(new_status_byte, 1);
                    _currentTrackOffset++;
                    velocity = new_status_byte[0];
                } else
                    velocity = 0;

                midiMessage.status = status_byte;
                midiMessage.delta_ticks = delta_ticks;
                midiMessage.key = key;
                midiMessage.velocity = velocity;
                midiMessage.channel = channel;

                Serial.printf("delta: 0x%04x (%04d) \t\t\tst:(%02x): %s \t\t\t ch:%02d \tkey:%03d \tvel:%03d\n",
                              midiMessage.delta_ticks, midiMessage.delta_ticks,
                              midiMessage.status, voice_message_status_name(midiMessage.status),
                              midiMessage.channel + 1,
                              midiMessage.key, midiMessage.velocity);
                return true;
            } else {

                switch (status_byte) {
                    case 0xF0 : {
                        progress = 0;
                        length = varfieldGet(_midifile, progress);
                        Serial.printf("sysex length:%d\n", length);
                        _currentTrackOffset += progress;
                        _midifile.seek(length);
                        _currentTrackOffset += length;
                        break;
                    }

                    case 0xFF : {
                        nextByte = _midifile.read();
                        _currentTrackOffset++;

                        switch (nextByte) {
                            case 0x00: {// Sequence Number                                
                                uint8_t sequence_number = _midifile.read();
                                _currentTrackOffset++;
                                Serial.printf("sequence number: %d\n", sequence_number);
                                break;
                            }
                            case 0x01: {// Text event                                
                                uint8_t text_length = _midifile.read();

                                _currentTrackOffset++;
                                char b[255];
                                _midifile.read(b, text_length);
                                _currentTrackOffset+= text_length;
                                Serial.printf("text event: %s\n", b);
                                break;
                            }
                            case 0x02: {// Copyright Notice                                
                                uint8_t text_length = _midifile.read();

                                _currentTrackOffset++;
                                char b[255];
                                _midifile.read(b, text_length);
                                _currentTrackOffset+= text_length;
                                Serial.printf("copywrite event: %s\n", b);
                                break;
                            }                       
                            case 0x2F: {
                                // End of Track -> FF 2F 00
                                uint8_t nn = _midifile.read();
                                Serial.printf("end of track\n");
                                _currentTrackOffset++;
                                break;
                            }
                            case 0x51: {
                                // FF 51 03 tttttt Set Tempo
                                char c = _midifile.read();
                                _currentTrackOffset++;
                                if (c == 3) {
                                    // nn dd cc bb
                                    uint8_t nn = _midifile.read();
                                    uint8_t dd = _midifile.read(); // denomiator = 2^dd
                                    uint8_t cc = _midifile.read(); //
                                    uint64_t microseconds_per_quarter_note = nn << 16 | dd << 8 | cc;
                                    float millieconds_per_quarter_note = microseconds_per_quarter_note / 1000;
                                    float bpm = 60000 / millieconds_per_quarter_note;
                                    Serial.printf("tempo : %f\n", bpm);
                                    _currentTrackOffset += 3;
                                }
                                break;
                            }
                            case 0x54: {
                                // FF 54 05 hr mn se fr ff SMPTE Offset
                                char c = _midifile.read();
                                _currentTrackOffset++;
                                if (c == 5) {
                                    uint8_t hr = _midifile.read();
                                    uint8_t mn = _midifile.read();
                                    uint8_t se = _midifile.read();
                                    uint8_t fr = _midifile.read();
                                    uint8_t ff = _midifile.read();
                                    Serial.printf("SMPTE Offset : %02d:%02d:%02d:%02d:%02d\n", hr, mn, se, fr, ff);
                                    _currentTrackOffset += 5;
                                }

                                break;
                            }
                            case 0x58: {
                                // 04 - Time Signature
                                char c = _midifile.read();
                                _currentTrackOffset++;
                                if (c == 4) {
                                    // nn dd cc bb
                                    uint8_t nn = _midifile.read();
                                    uint8_t dd = _midifile.read(); // denomiator = 2^dd
                                    uint8_t cc = _midifile.read(); //
                                    uint8_t bb = _midifile.read();
                                    uint8_t denominator = 2 ^dd;
                                    _currentTrackOffset += 4;
                                    Serial.printf("Time Signature: %d / %d, %d %d\n", nn, denominator, cc, bb);
                                }
                                break;
                            }

                            case 0x59: {
                                // FF 59 02 sf mi Key Signature
                                char c = _midifile.read();
                                _currentTrackOffset++;
                                if (c == 2) {
                                    // nn dd cc bb
                                    uint8_t sf = _midifile.read();
                                    uint8_t mi = _midifile.read();

                                    _currentTrackOffset += 2;
                                    Serial.printf("Key Signature: %d %d\n", sf, mi);
                                }
                                break;
                            }

                            default: {
                                if ((nextByte > 1) && (nextByte < 8))
                                    readMetaText();
                                else {
                                    uint8_t nn = _midifile.read();
                                    _currentTrackOffset++;
                                    Serial.printf("Meta - 0x%x 0x%x 0x%02x\n", status_byte, nextByte, nn);
                                    for (uint8_t jjj = 0; jjj < nn; jjj++) {
                                        uint8_t xx = _midifile.read();
                                        _currentTrackOffset++;
                                         Serial.print((char)xx);
                                    }
                                    Serial.println();
                                }
                                break;
                            }

                        }
                        break;
                    }

                    default: {
                        Serial.printf("unread - status_byte %x %d\n", status_byte, status_byte);
                        break;
                    }

                }
            }
        }
    }
}

uint32_t varfieldGet(File &file, uint16_t &progress)
{
    uint32_t ret = 0;
    uint8_t byte_in;

    for (;;)
    {
        if (file.available()) {
            // return error
            byte_in = file.read();
            progress++;
        }
        ret = (ret << 7) | (byte_in & 0x7f);
        if (!(byte_in & 0x80))
            return ret;
    }
}

const char* midireader::voice_message_status_name(unsigned char status) {
    switch (status & 0xF0) {
        case 0x80 : return "note off";
        case 0x90 : return "note on";
        case 0xA0 : return "after touch";
        case 0xB0 : return "control change";
        case 0xC0 : return "program change";
        case 0xD0 : return "channel pressure";
        case 0xE0 : return "pitch wheel";
    }
    return "[?]";
}

bool midireader::setTrackNumber(unsigned char trackNumber) {
    if (trackNumber < _numTracks){
        _midifile.seek(_track_offset[trackNumber]);
        _currentTrackOffset = 0;
    } else return false;
}