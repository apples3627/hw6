#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inputFile("Beatles-LetItBe-wav_30s.wav", ios::binary | ios::in);
    char header[44];
    inputFile.read(header, 44);
    short channel;
    int sampleRate;
    int byteRate;
    channel = *(short*)(header + 22);
    sampleRate = *(int*)(header + 24);
    byteRate = *(int*)(header + 28);
    sampleRate = 44100;
    ofstream outputFile("10s.wav", ios::binary | ios::out);
    outputFile.write(header, 44);

    int sampleplay = 10 * sampleRate * channel; 
    short data[sampleplay];

    inputFile.read((char*)data, sampleplay * sizeof(short));
    outputFile.write((char*)data, sampleplay * sizeof(short));

    inputFile.close();
    outputFile.close();
    return 0;
}
