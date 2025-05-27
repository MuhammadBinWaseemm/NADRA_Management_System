#include <iostream>
#include <windows.h>  // For playing sound on Windows
#include <random>
#include <ctime>
#include <tuple>
#include <bitset>
#include <iomanip>
#include <algorithm>
using namespace std;
class Account
{
private:

    const int BLOCK_SIZE = 16; // AES block size (16 bytes)
	                       //complex hash constants (k values)
const unsigned int k[64] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};
// Permutation and substitution tables (truncated for brevity)
const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6,
    64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7
};

const int IP_INV[64] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};

const int E[48] = {
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};

const int P[32] = {
    16,  7, 20, 21,
    29, 12, 28, 17,
     1, 15, 23, 26,
     5, 18, 31, 10,
     2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25
};

const int S_BOX[8][4][16] = {
    // S-Box 1
    {
        {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
        { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
        { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
        {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
    },
    // S-Box 2
    {
        {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
        { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
        { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
        {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
    },
    // S-Box 3
    {
        {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
        {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
        {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
        { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
    },
    // S-Box 4
    {
        { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
        {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
        {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
        { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
    },
    // S-Box 5
    {
        { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
        {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
        { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
        {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
    },
    // S-Box 6
    {
        {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
        {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
        { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
        { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
    },
    // S-Box 7
    {
        { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
        {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
        { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
        { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
    },
    // S-Box 8
    {
        {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
        { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
        { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
        { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
    }
};

const int PC1[56] = {
    57, 49, 41, 33, 25, 17,  9, 
     1, 58, 50, 42, 34, 26, 18, 
    10,  2, 59, 51, 43, 35, 27, 
    19, 11,  3, 60, 52, 44, 36, 
    63, 55, 47, 39, 31, 23, 15, 
     7, 62, 54, 46, 38, 30, 22, 
    14,  6, 61, 53, 45, 37, 29, 
    21, 13,  5, 28, 20, 12,  4
};

const int PC2[48] = {
    14, 17, 11, 24,  1,  5, 
     3, 28, 15,  6, 21, 10, 
    23, 19, 12,  4, 26,  8, 
    16,  7, 27, 20, 13,  2, 
    41, 52, 31, 37, 47, 55, 
    30, 40, 51, 45, 33, 48, 
    44, 49, 39, 56, 34, 53, 
    46, 42, 50, 36, 29, 32
};

const int SHIFT_SCHEDULE[16] = {
    1, 1, 2, 2, 
    2, 2, 2, 2, 
    1, 2, 2, 2, 
    2, 2, 2, 1
};

// Rijndael S-Box for SubBytes transformation
const unsigned char SBOX[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

// Rijndael Inverse S-Box for inverse SubBytes transformation
const unsigned char ISBOX[256] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

string MAC[10]={
		"7&F;VU#5En%hbZ9Ao,gu(sp1lh].|3(i",
        "uI)<@*+W6teQ:2?<?sc02?nsr Vy70=S",
        "L.vY!;u6h)?E)9f)wC_PI@/lr&M6B/RP",
        "Xez|*hWQX/JOQZ/6X(K1zLW3)bp#tBvl",
        "T(J2Lvuis4F_CKLFt,&eo%Fd=J|Q3U73",
        "Dk8/s;&.}*.)[JJ]%yBA4<Jkovvx&\"@7",
        "7cf|R)&-HovJaC{'Qc[<G#(k<;*r%e0F",
        "JsxV^kvz}[w+?E>KqE?g*i3|ejlGpwV0",
        "Yc/M|t}WrFM>.DfJ}?97=SE%mF{Xos}n",
        "xt-(^?Xx1eaiR^*ZiNhU2HM4(je&MaT]"
	};

    // Actual Complex Hash Variabes
    string username;
    string salt="";
    string pepper="";
    string hashedpassword;        // Variables for storing Hashed Values
    string hashedcnic;
    string hashedmac;
    string hashedphone;
    string hasheddate;
    int Enabled;
     //      RSA variables
    vector<int>hashedpasswordd;
    vector<int>hasheddatee;
    vector<int>hashedcnicc;
    vector<int>hashedphonee;
    //       DES variables
    bitset<64>hashedpassworddd;
    bitset<64>hasheddateee;
    bitset<64>hashedcniccc;
    bitset<64>hashedphoneee;
    // AES DES RSA key variables
    string AESK , DESK;
    int p,q,n,e,d;
    vector<bitset<48>> keys;
    bitset<64> key;
    // Testing
    string input;
    char Ch;
    //LinkedList Variables
    struct Node
    {
    	Node *next;
    	string Username;
    	string Salt="";
    	string Pepper="";
    	int key;
    	string mac;
    	string password;                    //Variables for List
    	string date;
    	string cnic;
    	string phone;
    	int Enabled;
    	vector<int>passwordd;
	    vector<int>datee;
	    vector<int>cnicc;
	    vector<int>phonee;
	    bitset<64>hashedpassworddd;
	    bitset<64>hasheddateee;
	    bitset<64>hashedcniccc;
	    bitset<64>hashedphoneee;
	    string AESK , DESK;
    	int n=0,e=0,d=0,p=0,q=0;
   		vector<bitset<48>> keys;
	};
	struct node
{
	string data;
	int h;
	int m;
	int s;
	node *next;
};
node *stack=nullptr;
    Node *head=nullptr;
    int currentkey=1;
    int K;
    

public:

    void SignUp()
    {
    	SecureZeroMemory(&pepper[0],pepper.size());
    	SecureZeroMemory(&salt[0],salt.size());
    	taken:system("cls");
    	taken2:;
    	cout<<"\n\t\tCryptography Algorithms";
    	cout<<"\n\t\t1. Complex Hashing";
    	cout<<"\n\t\t2. AES (Symmetric)";
    	cout<<"\n\t\t3. DES (Symmetric)";
    	cout<<"\n\t\t4. RSA (Asymmetric)";
    	cout<<"\n\t\tChoose a security mechanism for your Account (1-4): ";
    	cin>>Enabled;
    	cin.ignore();
    	if(Enabled!=1 && Enabled!=2 && Enabled!=3 && Enabled!=4)
    	{
    		HANDLE console_color; 
		    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,4);
    		cout<<"\n\t\tInvalid Input";
    		SetConsoleTextAttribute(console_color,10);
    		goto taken2;
		}
		if(Enabled==1)
		{
			for (int i = 0; i < 32; ++i)                               //generating salt
        		salt += generateSecureRandomCharacter();
        	for (int i = 0; i < 32; ++i)                                    //generating pepper
        		pepper += generateSecureRandomCharacter();
		}
		else if(Enabled==2)
		{
			cout<<"\n\t\tSet an AES key : ";
    		getline(cin,AESK);

			// Ensure the key is exactly 16 characters
		    if (AESK.length() < BLOCK_SIZE) {
		        AESK.append(BLOCK_SIZE - AESK.length(), '\0'); // Pad with '0'
		    } else if (AESK.length() > BLOCK_SIZE) {
		        AESK = AESK.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		}
		else if(Enabled==3)
		{
			cout<<"\n\t\tSet a DES key : ";
			getline(cin,DESK);
			DESK=toHex(DESK);
			// Ensure the key is exactly 16 characters
		    if (DESK.length() < BLOCK_SIZE) {
		        DESK.append(BLOCK_SIZE - DESK.length(), '0'); // Pad with '0'
		    } else if (DESK.length() > BLOCK_SIZE) {
		        DESK = DESK.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
			bitset<64> key(stoull(DESK, nullptr, 16));
			keys = generateKeys(key);
		}
		else
		{	
			prime:;
			cout<<"\n\t\tEnter large prime number 1 : ";
			cin>>p;
			cin.ignore();
		    if (p < 2)
			{
		        cout << "\n\t\tNot a prime"; // Numbers less than 2 are not prime
		        goto prime;
  			}
  			
    	for (int i = 2; i * i <= p; i++) 
		{ 									
        	if (p % i == 0) 
			{
            	cout << "\n\t\tNot a prime";
            	goto prime;
       	 	}
    	}
		    primee:;
			cout<<"\n\t\tEnter large prime number 2 : ";
			cin>>q;
			cin.ignore();
			if (q < 2)
			{
		        cout << "\n\t\tNot a prime"; // Numbers less than 2 are not prime
		        goto primee;
  			}
    	for (int i = 2; i * i <= q; i++) 
		{ 									
        	if (q % i == 0) 
			{
            	cout << "\n\t\tNot a prime";
            	goto primee;
       	 	}
    	}
			if(p==q || q<=15 && p<=15 || q-p<=10)
			{
				cout<<"\n\t\tInput Large and different Prime numbers : ";
				goto prime;
			}
			tie(n, e, d) = generateKeys(p, q);

			system("cls");
		    
		}

    	mac:;
    	bool x=0;
    	cout<<"\nEnter MAC address : ";
            getline(cin,input);
            for(int i=0 ; i<10 ; i++)
            {
            	if(complexhash(input)==MAC[i])
            	{
            		PlaySound(TEXT("C:/Users/PC/Downloads/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);
            		cout<<"\n\t\tDevice recognized ! \n\n";
            		system("pause");
            		system("cls");
            		hashedmac=MAC[i];
            		x=1;
            		break;
            		
				}
			}
				if(x==0)
				{
					HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
					PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
                    cout<<"\n\t\tDevice not recognized ! \n";
					SetConsoleTextAttribute(console_color,10);
                    goto mac;
				}
        cout << "\n\t\t\tAccount SignUp\n";                                       //Account SignUp
        while (1)
        {
            cout << "\nUsername : ";
            getline(cin, username); 
            if(userexists())
            {
            	HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
            	PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
            	cout<<"\n\t\tUsername already Taken\n";
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,10);
            	system("pause");
            	continue;
			}
            PasswordCheck(input);
        if(Enabled==1)
        	hashedpassword=complex_hash(input,salt,pepper,currentkey);
		else if(Enabled==2)
		{
			
			input=toHex(input);

			// Pad or truncate the input to 16 characters
		if (input.length() < BLOCK_SIZE) 
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		     else if (input.length() > BLOCK_SIZE) 
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		hashedpassword = aesLikeEncrypt(input, AESK);
		
		}
		else if(Enabled==3)
		{
			input = toHex(input);
		     // Ensure the plaintext is exactly 16 characters
		    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) {
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		    bitset<64> plaintext(stoull(input, nullptr, BLOCK_SIZE));
			hashedpassworddd=des(plaintext, keys, false);	
		}
		else
			 hashedpasswordd=encrypt(input,e,n);
        SecureZeroMemory(&input[0], input.size());                 // Securely wipe memory after hashing
        break;
        }
        while (1)
        {
            system("cls");
            cout << "\n\t\t\tAccount SignUp\n";
            cout << "\nEnter your date of birth(D/M/Y) : ";
            getline(cin, input);  
            if(Enabled==1)
        		hasheddate=complex_hash(input,salt,pepper,currentkey);
			else if(Enabled==2)
			{
				input=toHex(input);
				// Pad or truncate the input to 16 characters
			    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) 
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
			    hasheddate = aesLikeEncrypt(input, AESK);
			}
			else if(Enabled==3)
			{
				input = toHex(input);
		     // Ensure the plaintext is exactly 16 characters
		    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) {
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		    bitset<64> plaintext(stoull(input, nullptr, BLOCK_SIZE));
			hasheddateee=des(plaintext, keys, false);	
			}
			else
				hasheddatee = encrypt(input, e, n);
            SecureZeroMemory(&input[0], input.size());         // Securely wipe memory after hashing
			wr:;
            cout << "\nEnter your CNIC no. (without dashes): ";
            getline(cin, input);  
            if(input.length()!=13)
            {
            	HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
				PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
            	cout<<"\n\n\tInvalid CNIC number. Please try again.\n";
				SetConsoleTextAttribute(console_color,10);
				goto wr;
			}
             if(Enabled==1)
        		hashedcnic=complex_hash(input,salt,pepper,currentkey);
			else if(Enabled==2)
			{
				input=toHex(input);
				
				// Pad or truncate the input to 16 characters
			    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) 
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
			    hashedcnic = aesLikeEncrypt(input, AESK);
			}
			else if(Enabled==3)
			{
				input = toHex(input);
		     // Ensure the plaintext is exactly 16 characters
		    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) {
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		    bitset<64> plaintext(stoull(input, nullptr, BLOCK_SIZE));
			hashedcniccc=des(plaintext, keys, false);
			}
				
			else
				hashedcnicc=encrypt(input,e,n);
            SecureZeroMemory(&input[0], input.size());             // Securely wipe memory after hashing
			wrr:;
            cout << "\nEnter your phone no.(03*********) : ";
            getline(cin, input);  
            if(input.length()!=11)
            {
            	HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
				PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
            	cout<<"\n\n\tInvalid Phone no. Please try again.\n";
				SetConsoleTextAttribute(console_color,10);
				goto wrr;
			}
            if(Enabled==1)
        		hashedphone=complex_hash(input,salt,pepper,currentkey);
			else if(Enabled==2)
			{
				input=toHex(input);
				// Pad or truncate the input to 16 characters
			    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) 
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
			    hashedphone = aesLikeEncrypt(input, AESK);
			}
			else if(Enabled==3)
			{
				input = toHex(input);
		     // Ensure the plaintext is exactly 16 characters
		    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) {
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		    bitset<64> plaintext(stoull(input, nullptr, BLOCK_SIZE));
			hashedphoneee=des(plaintext, keys, false);
			}
			else
				hashedphonee=encrypt(input,e,n);
            SecureZeroMemory(&input[0], input.size());  // Securely wipe memory after hashing
            break;
        }
        cout<<"\n\t\tSignUp Complete !\n\n";
        input="Account Created of User : "+username+ " on device : "+hashedmac;
        push(stack,input);
        PlaySound(TEXT("C:/Users/PC/Downloads/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);
        system("pause");
        insertNode();
        p=q=n=e=d=0;
    }

    int Signin()
    {
    	char ch;
    	int i = 0;
        system("cls");
        cout << "\n\t\t\tSignin";                                  //SignIn
        int count = 0;
        char check;
        while (1)
        {
            cout << "\nUsername : ";
            getline(cin, username);  
            if(username=="Admin")                               //For Admin Purposes
            {  
            	cout<<"\nPassword : ";
            	cin>>input;
            	if(input=="@@@")
            	{
            		printlist();
	            	system("pause");
					return 0;	
				}
			}
			if(username=="ABZ")                               //For Admin Purposes
            {  
            	cout<<"\nPassword : ";
            	cin>>input;
            	if(input=="###")
            	{
            		printlistt();
	            	system("pause");
					return 0;	
				}
			}
            if (!searchuser())                               //Check if user exists
            {
            	HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
                PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
                cout << "\nUser not found.";
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,10);
                continue;
            }
            	
            while (1)
		    {
		    	mac:;
		    	cout<<"\nEnter MAC address : ";
		    	getline(cin,input);
		    	if(complexhash(input)!=hashedmac)
		    	{
		    		HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
                    PlaySound(TEXT("C:/Users/PC/Downloads/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
                    cout << "\nInvalid MAC Address.";
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,10);
					goto mac;
		    		
				}
				pass:;
                cout << "\nPassword : ";               
                getline(cin,input);
                if (Enabled==1 && complex_hash(input,salt,pepper,K)!= hashedpassword)
                {
                	HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
                    PlaySound(TEXT("C:/Users/PC/Downloads/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
                    cout << "\nWrong Password.";
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,10);
                    count++;
                    if (count >= 3)
                    {
                    	
                        cout << "\n\t\t\tForgot Password?(y/n)";
                        cin >> check;
                        cin.ignore();  // To clear the buffer after reading a char input
                    }
                    if (check == 'y' || check == 'Y')
                    {
                        Forgot();
                        return 0;
                    }
                    goto pass;
                }
                else if(Enabled==2)
                {
                	input=toHex(input);
                		// Pad or truncate the input to 16 characters
			    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) 
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
			   
				if(aesLikeEncrypt(input, AESK)!=hashedpassword)
				{
                	HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
                    PlaySound(TEXT("C:/Users/PC/Downloads/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
                    cout << "\nWrong Password.";
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,10);
                    count++;
                    if (count >= 3)
                    {
                    	
                        cout << "\n\t\t\tForgot Password?(y/n)";
                        cin >> check;
                        cin.ignore();  // To clear the buffer after reading a char input
                    }
                    if (check == 'y' || check == 'Y')
                    {
                        Forgot();
                        return 0;
                    }
                    goto pass;
            	}
                	
				}
				else if(Enabled==3)
				{
					input = toHex(input);
				     // Ensure the plaintext is exactly 16 characters
				    if (input.length() < BLOCK_SIZE) {
				        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
				    } else if (input.length() > BLOCK_SIZE) {
				        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
				    }
					bitset<64> plaintextInput(stoull(input, nullptr, BLOCK_SIZE));
					if(des(plaintextInput, keys, false)!=hashedpassworddd)
					{
						HANDLE console_color; 
					    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(console_color,4);
	                    PlaySound(TEXT("C:/Users/PC/Downloads/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
	                    cout << "\nWrong Password.";
					    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(console_color,10);
	                    count++;
                    if (count >= 3)
                    {
                    	
                        cout << "\n\t\t\tForgot Password?(y/n)";
                        cin >> check;
                        cin.ignore();  // To clear the buffer after reading a char input
                    }
                    if (check == 'y' || check == 'Y')
                    {
                        Forgot();
                        return 0;
                    }
                    goto pass;
				}
				}
				else if(Enabled==4 && encrypt(input,e,n)!=hashedpasswordd)
				{
					
					HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
                    PlaySound(TEXT("C:/Users/PC/Downloads/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
                    cout << "\nWrong Password.";
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,10);
                    count++;
                    if (count >= 3)
                    {
                    	
                        cout << "\n\t\t\tForgot Password?(y/n)";
                        cin >> check;
                        cin.ignore();  // To clear the buffer after reading a char input
                    }
                    if (check == 'y' || check == 'Y')
                    {
                        Forgot();
                        return 0;
                    }
                    goto pass;
					
				}
                break;
            }
            wrr:;
            string input;
            cout<<"\nEnter your CNIC no. : ";
            getline(cin,input);
            if(Enabled==1 && complex_hash(input,salt,pepper,K)!=hashedcnic)
            	{
            		PlaySound(TEXT("C:/Users/PC/Downloads/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
            		HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
            		cout<<"\n\t\tInvalid CNIC no. ";
            		SetConsoleTextAttribute(console_color,10);
            		goto wrr;		
				}
			else if(Enabled==2)
			{
				input=toHex(input);
					// Pad or truncate the input to 16 characters
			    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) 
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters

				if(aesLikeEncrypt(input, AESK)!=hashedcnic)
				{
					PlaySound(TEXT("C:/Users/PC/Downloads/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
            		HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
            		cout<<"\n\t\tInvalid CNIC no. ";
            		SetConsoleTextAttribute(console_color,10);
            		goto wrr;	
				}
				
			}
			else if(Enabled==3)
			{
					input = toHex(input);
		     // Ensure the plaintext is exactly 16 characters
		    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) {
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		    bitset<64> plaintext(stoull(input, nullptr, BLOCK_SIZE));
				if(des(plaintext, keys, false)!=hashedcniccc)
				{
					PlaySound(TEXT("C:/Users/PC/Downloads/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
            		HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
            		cout<<"\n\t\tInvalid CNIC no. ";
            		SetConsoleTextAttribute(console_color,10);
            		goto wrr;	
            	}
			}
			else if(Enabled==4 && encrypt(input,e,n)!=hashedcnicc)
			{
				PlaySound(TEXT("C:/Users/PC/Downloads/Denied.wav"), NULL, SND_FILENAME | SND_SYNC);
            		HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
            		cout<<"\n\t\tInvalid CNIC no. ";
            		SetConsoleTextAttribute(console_color,10);
            		goto wrr;		
			}
			 SecureZeroMemory(&input[0], input.size());
            PlaySound(TEXT("C:/Users/PC/Downloads/Access.wav"), NULL, SND_FILENAME | SND_SYNC);
 
			input="User with username : "+username+" Signed In on device : "+hashedmac;
	        push(stack,input);
            cout<<"\n\n\t\tAccess Granted ! \n\n"; 
            system("pause");
            return 1;
            system("cls");
            return 1;
        }
    }

    void Forgot()                                    //Function for authorization when user forgets password
    {
    	string date , cn , ph ;
        system("cls");
        	while (1)
            {
                cout << "\nEnter your date of birth(D/M/Y) : ";
                getline(cin, date);  
                cout << "\nEnter your CNIC.no : ";
                getline(cin, cn);  
                cout << "\nEnter your phone no. : ";
                getline(cin, ph);                          
                if (Enabled==1 && complex_hash(cn,salt,pepper,K) == hashedcnic && complex_hash(date,salt,pepper,K) == hasheddate && complex_hash(ph,salt,pepper,K) == hashedphone)
                {
                	SecureZeroMemory(&date[0], date.size());      // Securely wipe memory after hashing
          		    SecureZeroMemory(&cn[0], cn.size());   // Securely wipe memory after hashing
            	    SecureZeroMemory(&ph[0], ph.size()); 
                    Change();
                    break;
                }
                else if(Enabled==2)
                {
                	cn=toHex(cn);
                	if (cn.length() < BLOCK_SIZE) {
		        cn.append(BLOCK_SIZE - cn.length(), '0'); // Pad with '0'
		    } else if (cn.length() > BLOCK_SIZE) 
		        cn = cn.substr(0, BLOCK_SIZE); // Truncate to 16 characters
				    date=toHex(date);
					if (date.length() < BLOCK_SIZE) {
		        date.append(BLOCK_SIZE - date.length(), '0'); // Pad with '0'
		    } else if (date.length() > BLOCK_SIZE) 
		        date = date.substr(0, BLOCK_SIZE); // Truncate to 16 characters
				    ph=toHex(ph);
					if (ph.length() < BLOCK_SIZE) {
		        ph.append(BLOCK_SIZE - ph.length(), '0'); // Pad with '0'
		    } else if (ph.length() > BLOCK_SIZE) 
		        ph = ph.substr(0, BLOCK_SIZE); // Truncate to 16 characters
                	if (aesLikeEncrypt(cn, AESK) == hashedcnic && aesLikeEncrypt(date, AESK) == hasheddate && aesLikeEncrypt(ph, AESK) == hashedphone)
                	{
	                	SecureZeroMemory(&date[0], date.size());      // Securely wipe memory after hashing
	          		    SecureZeroMemory(&cn[0], cn.size());   // Securely wipe memory after hashing
	            	    SecureZeroMemory(&ph[0], ph.size()); 
	                    Change();
	                    break;
	                    
                	}
                	else
                	{
                		HANDLE console_color; 
					    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(console_color,4);
	                    PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
	                    cout << "\n\t\tPrivate information doesn't match. Try Again.";
					    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(console_color,10);
                		continue;
					}
                	
				}
				else if(Enabled==3)
				{
					cn = toHex(cn);
		     // Ensure the plaintext is exactly 16 characters
		    if (cn.length() < BLOCK_SIZE) {
		        cn.append(BLOCK_SIZE - cn.length(), '0'); // Pad with '0'
		    } else if (cn.length() > BLOCK_SIZE) {
		        cn = cn.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		    bitset<64> plaintext(stoull(cn, nullptr, BLOCK_SIZE));
		    date = toHex(date);
		     // Ensure the plaintext is exactly 16 characters
		    if (date.length() < BLOCK_SIZE) {
		        date.append(BLOCK_SIZE - date.length(), '0'); // Pad with '0'
		    } else if (date.length() > BLOCK_SIZE) {
		        date = date.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		    bitset<64> plaintextt(stoull(date, nullptr, BLOCK_SIZE));
		    ph = toHex(ph);
		     // Ensure the plaintext is exactly 16 characters
		    if (ph.length() < BLOCK_SIZE) {
		        ph.append(BLOCK_SIZE - ph.length(), '0'); // Pad with '0'
		    } else if (ph.length() > BLOCK_SIZE) {
		        ph = ph.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		    bitset<64> plaintexttt(stoull(ph, nullptr, BLOCK_SIZE));
					if(des(plaintext, keys, false) == hashedcniccc && des(plaintextt, keys, false) == hasheddateee && des(plaintexttt, keys, false) == hashedphoneee)
				{
					SecureZeroMemory(&date[0], date.size());      // Securely wipe memory after hashing
          		    SecureZeroMemory(&cn[0], cn.size());   // Securely wipe memory after hashing
            	    SecureZeroMemory(&ph[0], ph.size()); 
                    Change();
                    break;
                }
					
				}
				else if(Enabled==4 && encrypt(cn,e,n) == hashedcnicc && encrypt(date,e,n) == hasheddatee && encrypt(ph,e,n) == hashedphonee)
				{
					SecureZeroMemory(&date[0], date.size());      // Securely wipe memory after hashing
          		    SecureZeroMemory(&cn[0], cn.size());   // Securely wipe memory after hashing
            	    SecureZeroMemory(&ph[0], ph.size()); 
                    Change();
                    break;
					
				}
                else
                {
                	HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
                    PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
                    cout << "\n\t\tPrivate information doesn't match. Try Again.";
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,10);
                    continue;
                }
            
        }
    }

    void Change()                                           //function for additional account services
    {
        int x;
        PlaySound(TEXT("C:/Users/PC/Downloads/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);
        cout<<"\n\t\tAuthenticated ! \n\t\t";
        while (1)
        {
            system("cls");
            cout << "\n\t\t\tAccount Recovery";
            cout << "\n\t\t\t1.Change Username";
            cout << "\n\t\t\t2.Change Password";
            cout << "\n\t\t\t3.Delete Account";
            cout << "\n\t\t\tChoose from (1-3)  ";
            cout << "\nReturn(R)";
            cout << "\n\t\tYou choose:";
            cin >> Ch;
            cin.ignore();  // To clear the buffer after reading a char input
            switch (Ch)
            {
            case '1':
            	system("cls");
            	again:;
            	cout<<"\n\t\tEnter new username : ";
            	input=username;
            	getline(cin,username);
            	if(userexists())
            	{
            		HANDLE console_color; 
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,4);
            		PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
            		cout<<"\n\t\tSorry , username already taken\n";
				    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(console_color,10);
            		system("pause");
            		goto again;
				}
            	updateuser();
				
            	cout << "\n\t\tYour username has been changed !";
            	input="User with username : "+input+" changed their username to "+username+" on device : "+hashedmac;
            	PlaySound(TEXT("C:/Users/PC/Downloads/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);

                system("pause");
                break;
            case '2':
                system("cls");
                PasswordCheck(input);
                if(Enabled==1)
        		hashedpassword=complex_hash(input,salt,pepper,K);
				else if(Enabled==2)
				{
					input=toHex(input);
					// Pad or truncate the input to 16 characters
				if (input.size() > BLOCK_SIZE) 
				    input = input.substr(0, BLOCK_SIZE);
				else if (input.size() < BLOCK_SIZE) 
				    input.append(BLOCK_SIZE - input.size(), '0');
				hashedpassword = aesLikeEncrypt(input, AESK);
				}
				else if(Enabled==3)
				{	
					input = toHex(input);
		     // Ensure the plaintext is exactly 16 characters
		    if (input.length() < BLOCK_SIZE) {
		        input.append(BLOCK_SIZE - input.length(), '0'); // Pad with '0'
		    } else if (input.length() > BLOCK_SIZE) {
		        input = input.substr(0, BLOCK_SIZE); // Truncate to 16 characters
		    }
		    bitset<64> plaintext(stoull(input, nullptr, BLOCK_SIZE));

					hashedpassworddd=des(plaintext, keys, false);	
				}
				else
					hashedpasswordd=encrypt(input,e,n);
                updatepass();
                SecureZeroMemory(&input[0], input.size());              // Securely wipe memory after hashing

                cout << "\n\t\tYour password has been changed !";
                input="User with username : "+input+" changed their password on device : "+hashedmac;
                push(stack,input);
                PlaySound(TEXT("C:/Users/PC/Downloads/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);

                system("pause");
                break;
            case '3':
                system("cls");
                cout << "\n\t\tAre you sure you want to delete your account(y/n)?";
                cin >> Ch;
                cin.ignore();                             // To clear the buffer after reading a char input
                if (Ch == 'y' || Ch == 'Y')
                {
				    
                	input="Account with username : "+username+" was deleted from device : "+hashedmac;
                	push(stack,input);
	                delnode();
	                SecureZeroMemory(&hashedpassword[0],hashedpassword.size());              // Securely wipe memory after hashing
	                SecureZeroMemory(&hasheddate[0], hasheddate.size());                    // Securely wipe memory after hashing
	                SecureZeroMemory(&hashedcnic[0], hashedcnic.size());                 // Securely wipe memory after hashing
	                SecureZeroMemory(&hashedphone[0], hashedphone.size()); 
	                SecureZeroMemory(&salt[0], salt.size()); 
	                SecureZeroMemory(&pepper[0],pepper.size());
	                SecureZeroMemory(&hashedmac[0],hashedmac.size());
	                SecureZeroMemory(&hashedmac[0],hashedmac.size());
	                K=0;
                    x = 1;
                    cout << "\n\t\tYour Account has been deleted !";
                    PlaySound(TEXT("C:/Users/PC/Downloads/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);
                    system("pause");
                }
                break;
            case 'R':
            case 'r':
                x = 1;
                break;
            default:
            	HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
                PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
                cout << "\n\t\t\tInvalid command";
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,10);
                break;
            }
            if (x == 1)
                break;
        }
    }
    void insertNode()                                      //inserting Node to head function
{
	Node *newNode=new Node;
	newNode->Username=username;
	SecureZeroMemory(&username[0],username.size());
	newNode->key = currentkey++;
	newNode->mac = hashedmac;
	newNode->next=nullptr;
	newNode->password=hashedpassword;
	newNode->Enabled=Enabled;
	newNode->date=hasheddate;                                                //assigning values 
	newNode->cnic=hashedcnic;
	newNode->phone=hashedphone;
	SecureZeroMemory(&hashedmac[0],hashedmac.size());
	SecureZeroMemory(&hasheddate[0], hasheddate.size());
	SecureZeroMemory(&hashedpassword[0], hashedpassword.size());
	SecureZeroMemory(&hashedcnic[0], hashedcnic.size());                         //securley wiping
	SecureZeroMemory(&hashedphone[0], hashedphone.size());
	if(Enabled==1)
	{
		newNode->Salt = salt;
		newNode->Pepper = pepper;
		SecureZeroMemory(&pepper[0],pepper.size());
    	SecureZeroMemory(&salt[0],salt.size());
	}
	else if(Enabled==2)
	{
		newNode->AESK=AESK;
	}
	else if(Enabled==3)
	{
		newNode->DESK=DESK;
		newNode->keys=keys;
		newNode->hashedpassworddd=hashedpassworddd;
	    newNode->hasheddateee=hasheddateee;
	    newNode->hashedcniccc=hashedcniccc;
	    newNode->hashedphoneee=hashedphoneee;
	    
	}
	else
	{
		newNode->n=n;
		newNode->e=e;
		newNode->d=d;
		newNode->p=p;
		newNode->q=q;
		newNode->passwordd=hashedpasswordd;
		newNode->datee=hasheddatee;
		newNode->phonee=hashedphonee;
		newNode->cnicc=hashedcnicc;
		
	}
	if(head==nullptr)
	{
		head=newNode;
		
	}
	else
	{
		Node *temp=head;
		while(temp->next!=nullptr)
		{
			temp=temp->next;
		}
		temp->next=newNode;
	}
	
	
}
void printlist()                                      //function to print List for understanding
{
	system("cls");
	cout<<"\n\t\tList Of Accounts : \n\n";
	if(head==nullptr)
	{
		cout<<"\n\t\tNo Accounts\n";
		
	}
	else
	{
		Node *temp=head;
			while(temp!=nullptr)
		{
			cout<<temp->key<<".\tUsername :  "<<temp->Username;
			if(temp->Enabled==1)
			{
			cout<<"\n\n\tSalt : "<<temp->Salt<<"\n\n\tPepper : "<<temp->Pepper;
			cout<<"\n\n\tPassword : "<<temp->password<<endl<<endl;
		}
		else if(temp->Enabled==2)
		{
			cout<<"\n\n\tAES Key : "<<temp->AESK;
			cout<<"\n\n\tPassword : "<<temp->password<<endl<<endl;
		}
		else if(temp->Enabled==3)
		{
			cout<<"\n\n\tDES key : "<<DESK;
			cout<<"\n\n\tGenerated Keys : ";
			for (size_t i = 0; i < temp->keys.size(); ++i) 
			{
      		  cout << temp->keys[i];
    		}
			cout<<"\n\n\tPassword : "<<temp->hashedpassworddd<<endl<<endl;
		}
		else
		{
			cout<<"\n\n\tPrime Numbers : "<<temp->p<<" "<<temp->q;
			cout << "\n\n\tPublic Key (n, e): (" << n << ", " << e << ")" << endl;
		    cout << "\n\tPrivate Key (n, d): (" << n << ", " << d << ")" << endl;
		    cout<<"\n\tPassword : ";
			for (size_t i = 0; i < temp->passwordd.size(); ++i) {
        cout<<temp->passwordd[i] ;
}
			cout<<endl<<endl;
		    
		}
			temp=temp->next;
		}
	}
}
void printlistt()                                      //function to print List for understanding
{
	int x;
	system("cls");
	cout<<"\n\t\t1.List Of Accounts";
	cout<<"\n\t\t2.ReviewHistory";
	cout<<"\n\n\tSir please choose from (1-2) : ";
	cin>>x;
	cin.ignore();
	if(x==1)
	{
	cout<<"\n\t\tList Of Accounts : \n\n";
	if(head==nullptr)
	{
		cout<<"\n\t\tNo Accounts\n";
		
	}
	else
	{
		Node *temp=head;
			while(temp!=nullptr)
		{
			cout<<temp->key<<".\tUsername :  "<<temp->Username;
			if(temp->Enabled==1)
			{
			cout<<"\n\n\tSalt : "<<temp->Salt<<"\n\n\tPepper : "<<temp->Pepper;
			cout<<"\n\n\tPassword : "<<temp->password<<endl<<endl;
		}
		else if(temp->Enabled==2)
		{
			cout<<"\n\n\tAES Key : "<<temp->AESK;
			cout<<"\n\n\tPassword : ";
			string dec=aesLikeDecrypt(temp->password,temp->AESK);
			    // Remove padding
		    dec.erase(find(dec.begin(), dec.end(), '\0'), dec.end());
    		cout<<hexToString(dec)<<endl<<endl;
		}
		else if(temp->Enabled==3)
		{
			cout<<"\n\n\tDES key : "<<DESK;
			cout<<"\n\n\tGenerated Keys : ";
			for (size_t i = 0; i < temp->keys.size(); ++i) 
			{
      		  cout << temp->keys[i];
    		}
			cout<<"\n\n\tPassword : ";
			bitset<64> decrypted = des(temp->hashedpassworddd, keys, true);
    		string D=bitsetToString(decrypted);
    		reverse(D.begin(), D.end());
    		cout<<D<<endl<<endl;
		}
		else
		{
			cout<<"\n\n\tPrime Numbers : "<<temp->p<<" "<<temp->q;
			cout << "\n\n\tPublic Key (n, e): (" << temp->n << ", " << temp->e << ")" << endl;
		    cout << "\n\tPrivate Key (n, d): (" << temp->n << ", " << temp->d << ")" << endl;
		    cout<<"\n\tPassword : ";
			cout<<decrypt(temp->passwordd, temp->d,temp-> n)<<endl<<endl;
		    
		}
			temp=temp->next;
		}
	}
	}
	else
	{
		display(stack);
	}
}
void delnode()
{
	Node *temp=head;
	Node *prev=nullptr;
	if(username==head->Username)
	{
		head=temp->next;
		delete temp;
		return;
	}
	while(temp != nullptr)
	{
		if(temp->Username==username)
		{
			prev->next=temp->next;
			delete temp;
			return;
		}
		prev=temp;
		temp=temp->next;
	}
	
	cout<<"\n\t\tTarget not found";
}
int searchuser()                                  //searching for user
{
    Node *temp = head;
    while (temp != nullptr) 
	{
      
        if (username == temp->Username) 
		{
            hashedpassword = temp->password;
            Enabled=temp->Enabled;
            hasheddate=temp->date;
            hashedcnic=temp->cnic;
            hashedmac=temp->mac;
            hashedphone=temp->phone;
	    if(Enabled==1)
		{
				K=temp->key;
	            pepper = temp->Pepper;
	            salt = temp->Salt;
		}
		else if(Enabled==2)
		{
			AESK=temp->AESK;
			
		}
		else if(Enabled==3)
		{
			DESK=temp->DESK;
			keys=temp->keys;
		}
		else
		{
			n=temp->n;
			e=temp->e;
			d=temp->d;
		hashedpasswordd=temp->passwordd;
		hasheddatee=temp->datee;
		hashedphonee=temp->phonee;
		hashedcnicc=temp->cnicc;
	}
            return 1;  
        }
        temp = temp->next;  
    }
    return 0;  
}

int userexists()                                  //checking if userexits
{
	Node *temp=head;
	while(temp!=nullptr)
	{
		if(username!=temp->Username)
		{	
			temp=temp->next;
			continue;
		}
		else
			return 1;
	}
	return 0;
}
void updatepass()                   //function to change password
{
	Node *temp=head;
	while(temp!=nullptr)
	{
		if(username==temp->Username)
		{	
			temp->password=hashedpassword;
			temp->passwordd=hashedpasswordd;
			temp->hashedpassworddd=hashedpassworddd;
			return;
		}
		temp=temp->next;
	}
}
void updateuser()             //function to change username
{
	Node *temp=head;
	while(temp!=nullptr)
	{
		if(input==temp->Username)
		{	
			temp->Username=username;
			return;
		}
		temp=temp->next;
	}
}
// Right rotate function
unsigned int rightRotate(unsigned int x, unsigned int n) 
{
    return (x >> n) | (x << (32 - n));
}

// Custom character set for final hash output
const string CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_+=<>?;:,.[]{}|`/\"' ";
                                                                                                
// Function to convert integer to a custom base (using CHARSET)
char intToCustomChar(unsigned int value) 
{
    return CHARSET[value % CHARSET.length()];
}

// Pad message with optional salt
vector<unsigned char> padMessage(const string &input) {
    // Start with the original input
    vector<unsigned char> padded(input.begin(), input.end());
    
    // Append a 0x80 byte (the "1" bit in padding)
    padded.push_back(0x80);

    // Pad with zeros until the message length is 448 mod 512
    while ((padded.size() * 8) % 512 != 448) 
        padded.push_back(0x00);

    // Append the original message length as a 64-bit big-endian integer
    unsigned long long bitLength = input.size() * 8;
    for (int i = 7; i >= 0; --i)
        padded.push_back((bitLength >> (i * 8)) & 0xFF);

    return padded;
}

// The main SHA-256 computation
// Main custom hash function
string complex_hash(const string &input, const string &salt, const string &pepper , int num) 
{
    string modifiedInput="";
	for(int i=0 ;i<=input.length() ; i++)
	{
		modifiedInput+=input[i];                          //Adding pepper to input
		modifiedInput+=pepper;
	}
    vector<unsigned char> padded = padMessage(modifiedInput);

    // Initializing the hash values
    unsigned int h[8] = 
	{
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // Process the padded message in 512-bit blocks
    for (size_t i = 0; i < padded.size(); i += 64)
	 {
        vector<unsigned int> w(64);
        for (int t = 0; t < 16; ++t) 
		{
            w[t] = (padded[i + t * 4] << 24) | (padded[i + t * 4 + 1] << 16) |
                   (padded[i + t * 4 + 2] << 8) | padded[i + t * 4 + 3];
        }

        for (int t = 16; t < 64; ++t) 
		{
            unsigned int s0 = rightRotate(w[t - 15], 7) ^ rightRotate(w[t - 15], 18) ^ (w[t - 15] >> 3);
            unsigned int s1 = rightRotate(w[t - 2], 17) ^ rightRotate(w[t - 2], 19) ^ (w[t - 2] >> 10);
            w[t] = w[t - 16] + s0 + w[t - 7] + s1;
        }

        unsigned int a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], h_val = h[7];

        for (int t = 0; t < 64; ++t) 
		{
            unsigned int s1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
            unsigned int ch = (e & f) ^ ((~e) & g);
            unsigned int temp1 = h_val + s1 + ch + k[t] + w[t];
            unsigned int s0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
            unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
            unsigned int temp2 = s0 + maj;

            h_val = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += h_val;
    }

    // Combine the final hash value and convert to a string
    string hash_result;
    for (int i = 0; i < 8; ++i) 
	{
        hash_result += intToCustomChar(h[i] >> 24);
        hash_result += intToCustomChar(h[i] >> 16);
        hash_result += intToCustomChar(h[i] >> 8);
        hash_result += intToCustomChar(h[i]);
    }

	num=num%hash_result.length();                          //num % 32

	modifiedInput="";
	for(int i=0 ;i<=hash_result.length() ; i++)               
	{
		if(i==num)
			modifiedInput+=salt;                       //Adding Salt at specific position
		modifiedInput+=hash_result[i];
	}

    return 	modifiedInput;                               //returning result
}
string complexhash(const string &input) 
{
   
    vector<unsigned char> padded = padMessage(input);

    // Initializing the hash values
    unsigned int h[8] = 
	{
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // Process the padded message in 512-bit blocks
    for (size_t i = 0; i < padded.size(); i += 64)
	 {
        vector<unsigned int> w(64);
        for (int t = 0; t < 16; ++t) 
		{
            w[t] = (padded[i + t * 4] << 24) | (padded[i + t * 4 + 1] << 16) |
                   (padded[i + t * 4 + 2] << 8) | padded[i + t * 4 + 3];
        }

        for (int t = 16; t < 64; ++t) 
		{
            unsigned int s0 = rightRotate(w[t - 15], 7) ^ rightRotate(w[t - 15], 18) ^ (w[t - 15] >> 3);
            unsigned int s1 = rightRotate(w[t - 2], 17) ^ rightRotate(w[t - 2], 19) ^ (w[t - 2] >> 10);
            w[t] = w[t - 16] + s0 + w[t - 7] + s1;
        }

        unsigned int a = h[0], b = h[1], c = h[2], d = h[3], e = h[4], f = h[5], g = h[6], h_val = h[7];

        for (int t = 0; t < 64; ++t) 
		{
            unsigned int s1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
            unsigned int ch = (e & f) ^ ((~e) & g);
            unsigned int temp1 = h_val + s1 + ch + k[t] + w[t];
            unsigned int s0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
            unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
            unsigned int temp2 = s0 + maj;

            h_val = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
        h[5] += f;
        h[6] += g;
        h[7] += h_val;
    }

    // Combine the final hash value and convert to a string
    string hash_result;
    for (int i = 0; i < 8; ++i) 
	{
        hash_result += intToCustomChar(h[i] >> 24);
        hash_result += intToCustomChar(h[i] >> 16);
        hash_result += intToCustomChar(h[i] >> 8);
        hash_result += intToCustomChar(h[i]);
    }

	return hash_result;
}
void PasswordCheck(string &password) 
{
    bool upper = false;
    bool lower = false;
    bool symbols = false;
    bool goodLength = false;
    bool hasNumber = false;
    bool s_password = false;

    while (!s_password) 
	{
		cout << "\nPassword requirements:\n";
        cout << "- At least one uppercase letter\n";
        cout << "- At least one lowercase letter\n";
        cout << "- At least one special symbol (e.g., @, #, $, etc.)\n";
        cout << "- At least one numeric digit (0-9)\n";
        cout << "- At least 6 characters long\n\n";
        missed:;
        cout << "Enter a password : ";
       	getline(cin,password);
            
        // Reset the validation flags for each attempt
        upper = lower = symbols = goodLength = hasNumber = false;

        // Check each character of the password
        for (size_t i = 0; i < password.length(); i++) 
		{
            char c = password[i];
            if (isupper(c)) upper = true;
            if (islower(c)) lower = true;
            if (ispunct(c)) symbols = true;          // Checks for punctuation/symbols
            if (isdigit(c)) hasNumber = true;        // Checks for numeric digits
        }

        // Check the length requirement
        goodLength = (password.length() >= 6);

        // If all conditions are met, mark the password as strong
        
        if (upper && lower && symbols && goodLength && hasNumber) 
		{
            s_password = true;
            PlaySound(TEXT("C:/Users/PC/Downloads/Bubble.wav"), NULL, SND_FILENAME | SND_SYNC);
            cout << "Strong password accepted.\n"; 
            system("pause");
        } 
		else 
		{
			system("cls");
			PlaySound(TEXT("C:/Users/PC/Downloads/User.wav"), NULL, SND_FILENAME | SND_SYNC);
			HANDLE console_color; 
		    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,4);
            cout << "Weak password. Please try again.\n"; 
		    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,10);
            if (!upper) cout << "- Add at least one uppercase letter.\n";                                  //Conditions to be fulfilled
            if (!lower) cout << "- Add at least one lowercase letter.\n";
            if (!symbols) cout << "- Add at least one special symbol.\n";
            if (!hasNumber) cout << "- Add at least one numeric digit.\n";
            if (!goodLength) cout << "- Make the password at least 6 characters long.\n";
            goto missed;
        }
    }
}

// Function to generate a cryptographically secure random character
char generateSecureRandomCharacter() 
{

    const string allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?`/\"' ";
         

    // Use random_device to get a cryptographically secure random number
    
    random_device rd;
    mt19937 gen(rd());              // Mersenne Twister generator
    uniform_int_distribution<> dis(0, allowedChars.size() - 1);

    // Randomly pick a character from the allowed list
    return allowedChars[dis(gen)];
}
void display(node *&top)
{
	node *temp=top;

	for(int i=1 ; temp!=nullptr ; temp=temp->next,i++)
	{
		cout<<"\n\t\tTime : "<<temp->h<<":"<<temp->m<<":"<<temp->s;
		cout<<"\n\n\n\t"<<temp->data;
	}
	cout<<endl<<endl;
}
void push(node *&top ,string D)
{
	     	// Get the current time
    time_t now = time(0);

    // Convert to local time format
    tm* localTime = localtime(&now);
	node *temp=new node;
	temp->data=D;
	temp->h=localTime->tm_hour;
	temp->m=localTime->tm_min;
	temp->s=localTime->tm_sec;
	if(top==nullptr)
	{
		temp->next=nullptr;
		top=temp;
	}
	else
	{
		temp->next=top;
		top=temp;		
	}
}
// Utility function to perform bitwise permutation
template <size_t InputSize, size_t OutputSize>
bitset<OutputSize> permute(const bitset<InputSize>& input, const int* table) {
    bitset<OutputSize> output;
    for (size_t i = 0; i < OutputSize; ++i) {
        output[OutputSize - 1 - i] = input[InputSize - table[i]];
    }
    return output;
}

// Function to split a 64-bit block into two 32-bit halves
void splitBlock(const bitset<64>& block, bitset<32>& left, bitset<32>& right) {
    for (size_t i = 0; i < 32; ++i) {
        left[31 - i] = block[63 - i];
        right[31 - i] = block[31 - i];
    }
}

// Function to merge two 32-bit halves into a 64-bit block
bitset<64> mergeBlock(const bitset<32>& left, const bitset<32>& right) {
    bitset<64> block;
    for (size_t i = 0; i < 32; ++i) {
        block[63 - i] = left[31 - i];
        block[31 - i] = right[31 - i];
    }
    return block;
}

// Function to generate 16 subkeys
vector<bitset<48>> generateKeys(const bitset<64>& key) {
    vector<bitset<48>> keys;
    bitset<56> permutedKey = permute<64, 56>(key, PC1);

    bitset<28> C, D;
    for (size_t i = 0; i < 28; ++i) {
        C[27 - i] = permutedKey[55 - i];
        D[27 - i] = permutedKey[27 - i];
    }

    for (int round = 0; round < 16; ++round) {
        C = (C << SHIFT_SCHEDULE[round]) | (C >> (28 - SHIFT_SCHEDULE[round]));
        D = (D << SHIFT_SCHEDULE[round]) | (D >> (28 - SHIFT_SCHEDULE[round]));

        bitset<56> combinedKey;
        for (size_t i = 0; i < 28; ++i) {
            combinedKey[55 - i] = C[27 - i];
            combinedKey[27 - i] = D[27 - i];
        }

        keys.push_back(permute<56, 48>(combinedKey, PC2));
    }

    return keys;
}

// Function to perform DES round function
bitset<32> roundFunction(const bitset<32>& right, const bitset<48>& subkey) {
    bitset<48> expandedRight = permute<32, 48>(right, E);
    bitset<48> xorResult = expandedRight ^ subkey;

    bitset<32> substituted;
    for (int i = 0; i < 8; ++i) {
        int row = (xorResult[47 - 6 * i] << 1) | xorResult[47 - 6 * i - 5];
        int col = (xorResult[47 - 6 * i - 1] << 3) | (xorResult[47 - 6 * i - 2] << 2) |
                  (xorResult[47 - 6 * i - 3] << 1) | xorResult[47 - 6 * i - 4];
        substituted |= bitset<32>(S_BOX[i][row][col]) << (28 - 4 * i);
    }

    return permute<32, 32>(substituted, P);
}

// DES encryption and decryption
bitset<64> des(const bitset<64>& block, const vector<bitset<48>>& keys, bool isDecrypt) {
    bitset<64> permutedBlock = permute<64, 64>(block, IP);
    bitset<32> left, right;
    splitBlock(permutedBlock, left, right);

    for (int round = 0; round < 16; ++round) {
        bitset<32> temp = right;
        right = left ^ roundFunction(right, keys[isDecrypt ? 15 - round : round]);
        left = temp;
    }

    bitset<64> preOutput = mergeBlock(right, left);
    return permute<64, 64>(preOutput, IP_INV);
}
// Custom function to mimic AES SubBytes transformation
void subBytes(vector<unsigned char>& state) {
    for (auto& byte : state) {
        byte = SBOX[byte];
    }
}

// Custom function to mimic AES Inverse SubBytes transformation
void invSubBytes(vector<unsigned char>& state) {
    for (auto& byte : state) {
        byte = ISBOX[byte];
    }
}

// Custom function to mimic AES ShiftRows transformation
void shiftRows(vector<unsigned char>& state) {
    vector<unsigned char> temp = state;
    int rows = 4;
    for (int row = 1; row < rows; ++row) {
        for (int col = 0; col < 4; ++col) {
            state[row * 4 + col] = temp[row * 4 + (col + row) % 4];
        }
    }
}

// Custom function to mimic AES Inverse ShiftRows transformation
void invShiftRows(vector<unsigned char>& state) {
    vector<unsigned char> temp = state;
    int rows = 4;
    for (int row = 1; row < rows; ++row) {
        for (int col = 0; col < 4; ++col) {
            state[row * 4 + col] = temp[row * 4 + (col - row + 4) % 4];
        }
    }
}

// Custom function to mimic AES AddRoundKey transformation
void addRoundKey(vector<unsigned char>& state, const vector<unsigned char>& key) {
    for (size_t i = 0; i < state.size(); ++i) {
        state[i] ^= key[i];
    }
}

// Custom AES-like encryption function
string aesLikeEncrypt(const string& input, const string& key) {
    vector<unsigned char> state(BLOCK_SIZE, 0);
    vector<unsigned char> roundKey(key.begin(), key.end());

    // Copy input to state, padding if necessary
    for (size_t i = 0; i < input.size() && i < BLOCK_SIZE; ++i) {
        state[i] = input[i];
    }

    // Mimic a single AES round
    addRoundKey(state, roundKey);
    subBytes(state);
    shiftRows(state);
    addRoundKey(state, roundKey);

    // Convert state to hexadecimal string for output
    stringstream encryptedHex;
    for (auto byte : state) {
        encryptedHex << hex << setw(2) << setfill('0') << (int)byte;
    }

    return encryptedHex.str();
}
// Custom AES-like decryption function
string aesLikeDecrypt(const string& encryptedHex, const string& key) 
{
    vector<unsigned char> state(BLOCK_SIZE, 0);
    vector<unsigned char> roundKey(key.begin(), key.end());

    // Convert hexadecimal input to state
    for (size_t i = 0; i < encryptedHex.size() && i / 2 < BLOCK_SIZE; i += 2) {
        state[i / 2] = stoi(encryptedHex.substr(i, 2), nullptr, 16);
    }

    // Mimic a single AES round (reversed operations)
    addRoundKey(state, roundKey);
    invShiftRows(state); // Inverse of ShiftRows
    invSubBytes(state);  // Inverse of SubBytes
    addRoundKey(state, roundKey);

    // Convert state back to string
    string decrypted;
    for (auto byte : state) {
        decrypted.push_back(static_cast<char>(byte));
    }

    return decrypted;
}
// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute modular exponentiation
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd
            result = (result * base) % mod;
        }
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

// Function to compute modular multiplicative inverse
int modInverse(int e, int phi) {
    for (int d = 1; d < phi; ++d) {
        if ((e * d) % phi == 1) {
            return d;
        }
    }
    return -1; // No inverse found
}

// Function to generate RSA keys
tuple<int, int, int> generateKeys(int p, int q) {
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Choose a small public exponent e such that 1 < e < phi and gcd(e, phi) == 1
    int e = 3;
    while (gcd(e, phi) != 1) {
        e++;
    }

    // Calculate the private key d
    int d = modInverse(e, phi);

    return make_tuple(n, e, d);
}

// RSA encryption
vector<int> encrypt(const string &message, int e, int n) 
{
    vector<int> ciphertext;
    for (char ch : message) {
        int encryptedChar = modExp(static_cast<int>(ch), e, n);
        ciphertext.push_back(encryptedChar);
    }
    return ciphertext;
}

// RSA decryption
string decrypt(const vector<int> &ciphertext, int d, int n) 
{
    string decryptedMessage;
    for (int encryptedChar : ciphertext) {
        char decryptedChar = static_cast<char>(modExp(encryptedChar, d, n));
        decryptedMessage += decryptedChar;
    }
    return decryptedMessage;
}
string bitsetToString(const bitset<64>& input) {
    string result;
    
    // Process each 8 bits (1 byte) from the bitset
    for (size_t i = 0; i < 64; i += 8) {
        // Extract the byte (8 bits)
        unsigned long byteValue = (input.to_ullong() >> i) & 0xFF; // Right shift and mask with 0xFF
        
        // Convert the byte to a char and append to the result string
        result += static_cast<char>(byteValue);
    }
    
    return result;
}
string toHex(const string &input) {
    stringstream ss;
    for (unsigned char c : input) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(c);
    }
    return ss.str();
}


string hexToString(const string& hex) {
    stringstream result;
    
    // Iterate over the hex string two characters at a time
    for (size_t i = 0; i < hex.length(); i += 2) {
        // Extract two hex characters and convert to a single byte
        string byteString = hex.substr(i, 2);
        char byte = static_cast<char>(stoi(byteString, nullptr, 16));
        result << byte;
    }
    
    return result.str();
}


};