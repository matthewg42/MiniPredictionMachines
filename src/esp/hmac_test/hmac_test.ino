#include <MutilaDebug.h>
#include <Crypto.h>

// Note: expected values come from this nifty site:
// https://www.freeformatter.com/hmac-generator.html#ad-output

// A minimal key for easy testing
const byte key1[] = "1";
const byte key1len = 1;
const char* key1expected = "90D74404F77BDDEC38E7E5FDB8A1D81C66942F1BFF4CC05DB34D12F0145B10A5";

// Corner case 1: key length = blocksize-1
const byte key2[] = "123456789012345678901234567890123456789012345678901234567890123";
const byte key2len = 63;
const char* key2expected = "551E0041BA4EB6344D86126BDD2692D702013794290CAE522E06F3C2ACBCE126";

// Corner case 2: key length = blocksize
const byte key3[] = "1234567890123456789012345678901234567890123456789012345678901234";
const byte key3len = 64;
const char* key3expected = "5C1EFD03F17B3C5F2AA79D640DD75A9EF695B8CAF2B0700118E9E8CF726742DD";

// Corner case 3: key length = blocksize+1 (key will be hashed)
const byte key4[] = "12345678901234567890123456789012345678901234567890123456789012345";
const byte key4len = 65;
const char* key4expected = "B40A3A8ADE2E85B08F2865CCB36DCD38512750FD76835C280DACA8C9580A2E83";

const char* data = "All your hmac are belong to us";
const byte datalen = 30;

void testHmac(const byte* key, const byte len, const char* expected)
{
    DB("key length = ");
    DBLN(len);
    DB("expected   = ");
    DBLN(expected);
    DB("calculated = ");
    SHA256HMAC hmac(key, len);
    hmac.doUpdate(data, datalen);
    byte digest[SHA256_SIZE];
    hmac.doFinal(digest);
    for (byte i=0; i<SHA256_SIZE; i++) {
        if (digest[i] < 0x10) { DB('0'); }
        DB(digest[i], HEX);
    }
    DBLN();
    DBLN();
}

void setup() {
    DBBEGIN;

    testHmac(key1, key1len, key1expected);
    testHmac(key2, key2len, key2expected);
    testHmac(key3, key3len, key3expected);
    testHmac(key4, key4len, key4expected);
}

void loop() {
}
