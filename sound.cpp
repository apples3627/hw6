#include <iostream>
#include <fstream>
using namespace std;

float len(int eumpyo) {
    float T;
    if (eumpyo == 4) T = 1.0; //4분음표
    else if (eumpyo == 8) T = 0.5; // 8분음표
    else if (eumpyo == 16) T = 0.25; // 16분음표
    return T;
}

float Freq(char hh) {
    if (hh == 'C') return 261.63; // C도
    else if (hh == 'D') return 293.66; // D레
    else if (hh == 'E') return 329.63; // E미
    else if (hh == 'F') return 349.23; // F파
    else if (hh == 'G') return 392.00; // G솔
    else if (hh == 'A') return 440.00; // A라
    else if (hh == 'B') return 493.88; // B시
    else return 0;
}

float volume(char ss) {
    //H=10 M=5 L=8
    if (ss == 'H') return 10000.0; 
    else if (ss == 'M') return 5000.0; 
    else if (ss == 'L') return 8000.0; 
    else return 0;
}

int main() {
    ifstream xx("10s.wav", ios::binary | ios::in);
    if (!xx) return 22;
    char header[44];
    xx.read(header, 44);

    short* n = (short*)(header + 22); 
    int* fs = (int*)(header + 24);    
    int* b = (int*)(header + 28);      
    *n = 1; 

    ofstream yy("sound.wav", ios::binary | ios::out);
    if (!yy) return 33;  
    yy.write(header, 44 * sizeof(char)); 

    ifstream zz("piece.txt");
    int readpiece;
    zz >> readpiece; 

    for(int i = 0; i < readpiece; ++i) {
        int eu;
        char hh, ss;
        zz >> eu >> hh >> ss; 

        float f = Freq(hh); 
        float a = volume(ss); 
        float T = len(eu);     

        int N = *fs * T; 
        short* data = new short[N];

        const float pi = 3.141592;
        float dt = 1.0 / *fs;

        for (int j = 0; j < N; ++j) {
            data[j] = static_cast<short>(a * sin(2.0 * pi * f * j * dt));
        }
        yy.write((char*)data, N * sizeof(short));
        delete[] data;
    }
    zz.close();
    yy.close();
    return 1;
}
