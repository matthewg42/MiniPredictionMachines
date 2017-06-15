#pragma once

class EspID_ {
public:
    EspID_() {;}
    void begin();
    const char* get() { return _id; }

private:
    char _id[20];

};

extern EspID_ EspID;

