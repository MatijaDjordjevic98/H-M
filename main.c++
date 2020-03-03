#include <iostream>

using namespace std;

const unsigned short mixCol[4][4] = { 
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}
};

unsigned char xtime(unsigned char b)    // multiply on x
{
  unsigned char mask = 0x80, m = 0x1b;
  unsigned char high_bit = b & mask;
  b = b << 1;
  if (high_bit) {    // mod m(x)
    b = b ^ m;
  }
  return b;
}

unsigned char mul_bytes(unsigned char a, unsigned char b)
{
  unsigned char c = 0, mask = 1, bit, d;
  int i, j;
  for (i = 0; i < 8; i++)
  {
    bit = b & mask;
    if (bit)
    {
      d = a;
      for (j = 0; j < i; j++)
      {    // multiply on x^i
        d = xtime(d);
      }
      c = c ^ d;    // xor to result
    }
    b = b >> 1;
  }
  return c;
}

void columnMix(unsigned short state[4][4]){
    unsigned short sub[4];
    
    
    for(unsigned char i = 0; i < 4; i++){
        for(unsigned char j = 0; j < 4; j++) sub[j] = state[j][i];
        for(unsigned char j = 0; j < 4; j++) state[j][i] = mul_bytes(mixCol[j][0], sub[0])^
                                                           mul_bytes(mixCol[j][1], sub[1])^
                                                           mul_bytes(mixCol[j][2], sub[2])^
                                                           mul_bytes(mixCol[j][3], sub[3]);
    }
    
}

int main() {

    unsigned short state[4][4] = { 
        {0xd4, 0xc9, 0x72, 0x4d},
        {0xf2, 0x67, 0x21, 0x63},
        {0x7d, 0x10, 0xc9, 0x67},
        {0xda, 0x72, 0xf0, 0x72}
    };
    
    columnMix(state);
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cout << std::hex << state[i][j] << ' ';
        }
        cout << endl;
    }

    unsigned short a = 0x53, b = 0xca;
    
    cout << std::hex << mul_bytes(a, b) << ' ';
    return 0;
}

