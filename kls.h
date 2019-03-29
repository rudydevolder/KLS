// Uses pawelsky library found at
// https://github.com/pawelsky/FlexCAN_Library
#ifndef __KLS_H__
#define __KLS_H__

#include <FlexCAN.h>
#include <Metro.h>
#include <kinetis_flexcan.h>
#include <cstdlib>
#include <string>

void print_msg_binary(CAN_message_t &msg, bool print_header) {
    if (print_header) {
        Serial.println(F("id,\tlen,\text,\t[buf]"));
    }
    Serial.print(msg.id, HEX);
    Serial.write(',');
    Serial.write('\t');
    Serial.print(msg.len);
    Serial.write(',');
    Serial.write('\t');
    Serial.print(msg.ext);
    Serial.write(',');
    Serial.write('\t');
    Serial.write('"');
    char buf[4];
    int num_bits = 4 * msg.len;
    int msb = 1 << (num_bits - 1);
    for (int i = 0; i < num_bits; i++) {
        int temp = msg.buf[i];
        if (temp & msb) {
            buf[i % 4] = '1';
        } else {
            buf[i % 4] = '0';
        }
        if ((i + 1) % 4 == 0) {
            for (int j = 0; j < 3; j++) {
                Serial.write(buf[j]);
            }
        }
        temp <<= 1;
    }
}

void print_msg(CAN_message_t &msg, bool print_header) {
    if (print_header) {
        Serial.println(F("id,\tlen,\text,\t[buf]"));
    }
    Serial.print(msg.id, HEX);
    Serial.write(',');
    Serial.write('\t');
    Serial.print(msg.len);
    Serial.write(',');
    Serial.write('\t');
    Serial.print(msg.ext);
    Serial.write(',');
    Serial.write('\t');
    Serial.write('"');
    for (int j = 0; j < 8; j++) {
        Serial.print(msg.buf[j]);
    }
    Serial.println('"');
}

void print_msg_decode(CAN_message_t &msg) {
    // message 1
    if (msg.id == 0x0CF11E05) {
        unsigned int speed_lsb = msg.buf[0];
        unsigned int speed_msb = msg.buf[1] << 8;
        unsigned int speed = speed_msb + speed_lsb;
        Serial.println("Motor speed: %d RPM", speed);

        unsigned int curr_lsb = msg.buf[2];
        unsigned int curr_msb = msg.buf[3] << 8;
        unsigned int curr = (curr_msb + curr_lsb) / 10;
        Serial.println("Motor current: %d A", curr);

        unsigned int volt_lsb = msg.buf[4];
        unsigned int volt_msb = msg.buf[5] << 8;
        unsigned int volt = (volt_msb + volt_lsb) / 10;
        Serial.println("Motor voltage: %d V", volt);
    }

    if (msg.id == 0x0CF11F05) {
    }
}

#endif  // __KLS_H__