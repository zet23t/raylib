#include <memory.h>
#include <raylib.h>

int main()
{
    // test if encode/decode works as expected
    char testData[1024] = { 0 };
    for (int i = 0; i < 1024; i++) 
    {
        for (int j = 0; j < i; j++) testData[j] = (char)((j * 17 + 281) % 1023 );
        int encodedSize = 0;
        char *encodedData = EncodeDataBase64((unsigned char *)testData, i, &encodedSize);
        int decodedSize = 0;
        unsigned char *decodedData = DecodeDataBase64(encodedData, &decodedSize);
        if (decodedSize != i)
        {
            TraceLog(LOG_ERROR, "Base64 encode/decode size mismatch: original %d, decoded %d", i, decodedSize);
            return -1;
        }
        if (memcmp(testData, decodedData, i) != 0)
        {
            TraceLog(LOG_ERROR, "Base64 encode/decode data mismatch at size %d", i);
            return -1;
        }
        MemFree(encodedData);
        MemFree(decodedData);
    }

    TraceLog(LOG_INFO, "Base64 encode/decode test passed.");

    {
        const char maliciousBase64Input[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        int decodedSize = 0;
        unsigned char *decodedData = DecodeDataBase64(maliciousBase64Input, &decodedSize);
        if (decodedData) {
            MemFree(decodedData);
        }
    }


    char maliciousBase64[128] = {0};

    for (int i = 50; i < 127; i++)
    {
        TraceLog(LOG_INFO, "Testing Base64 decoding with input length: %d", i);
        for (int j = 0; j < i; j++)
        {
            maliciousBase64[j] = 'A'; 
        }
        maliciousBase64[i] = '\0';
        int decodedSize = 0;
        unsigned char *decodedData = DecodeDataBase64(maliciousBase64, &decodedSize);
        if (decodedData) {
            MemFree(decodedData);
        }
    }

    TraceLog(LOG_INFO, "Base64 decoding handled malicious input without crashing.");

    return 0;
}