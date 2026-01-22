////////////////////////////////////////////////////////////////
//   This is MMSnnnW random number generator at 2026.01.22.   //
//      ([Code-Name:'IKUKOsan-20260122']).                    //
//   Use the compiler gcc.                                    //
//   MMSnnnW is an academic product.                          //
//   Use MMSnnnW within your responsibility.                  //
////////////////////////////////////////////////////////////////

        //  Period of MMMnnnW is
        //  (p=2^63-25)x(q=2^63-165)x(pp=2^63-259)x(qq=2^63-301)
        //   = approx. 10^75.

        // 'W' of MMSnnnW means XOR is taken 'w'idely.
        // 'W' of MMSnnnW means 'double'-staged XOR (long-period).
        //  MMSnnnW uses Pi to define B(base).
        //  MMSnnn(originalMMS) uses Napier's const. to define B.

//------ Test of the code ------------------------------------//

// If you want to test this code,
// remove // below, and compile and run.

//#define HowToUseMMSnnnW   // main() in this module will be used 
              // gcc MMSnnnWtest.c -o MMSnnnWtest

#ifdef HowToUseMMSnnnW
  #define MMS64W    // nnn=64 for test
#endif

//------------------------------------------------------------//

/***** Selection (1) *****/

// remove one // below to indicate the bit-length nnn of RNs

//#define MMS64W
//#define MMS128W
//#define MMS192W
//#define MMS256W
//#define MMS384W
//#define MMS512W
//#define MMS1024W
//#define MMS2048W
//#define MMS4096W
//#define MMS8192W
//#define MMS16384W

/***** Selection (2) *****/

// If you use MMSIni*** functions in MMSIniFuncs.c, remove // below.

  #define UseMMSIni   // By this definition, 'MMSIniFuncs.c' is included

/***** Selection (3) *****/

// If you want to use original MMS, remove // below.

  //#define originalMMS  // Valid only for nnn = 64,...,4096

         // The period of original MMS is (p=2^63-25)x(q=2^63-165).

/*------- End of Selection ------*/

/******************/
#include <stdio.h>
#include <memory.h>
/******************/

#ifdef MMS64W
  #ifndef originalMMS	
	#define  RAND_name "MMS64W"
   #else
	#define  RAND_name "MMS64"
  #endif	   
    #define  HSHashBitSize 64         // L=8(byte)
    int  HSscrBitShiftSize = 32;      // 64/2(bit)    // can be modified
    int  HSscrBitShiftTimes = 2;      // can be modified
    int  HSHashBgnBit = 32;           // treat separately with HSscrBitShiftSize
  #ifdef originalMMS
    #define  HSxorEmbPosIntLL 1       // (intLL)(pos. starting from 1)
  #endif
    //----------------------------//
    #define  mIntIntSize_LL    2
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   1
#endif

/******************************/
#ifdef MMS128W
  #ifndef originalMMS	
	#define  RAND_name "MMS128W"
   #else
	#define  RAND_name "MMS128"
  #endif	   
    #define  HSHashBitSize 128        // L=16(byte)
    int  HSscrBitShiftSize = 64;      // 128/2(bit)   // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 64;           // treat separately with HSscrBitShiftSize
  #ifdef originalMMS
    #define  HSxorEmbPosIntLL 1       // (intLL)(pos. starting from 1)
  #endif
    //----------------------------//
    #define  mIntIntSize_LL    3
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   2
#endif

/******************************/
#ifdef MMS192W
  #ifndef originalMMS	
	#define  RAND_name "MMS192W"
   #else
	#define  RAND_name "MMS192"
  #endif	   
    #define  HSHashBitSize 192        // L=24(byte)
    int  HSscrBitShiftSize = 96;      // 192/2(bit)   // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 96;           // treat separately with HSscrBitShiftSize
  #ifdef originalMMS
    #define  HSxorEmbPosIntLL 2       // (intLL)(pos. starting from 1)
  #endif
    //----------------------------//
    #define  mIntIntSize_LL    4
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   3
#endif

/******************************/
#ifdef MMS256W
  #ifndef originalMMS	
	#define  RAND_name "MMS256W"
   #else
	#define  RAND_name "MMS256"
  #endif	   
    #define  HSHashBitSize 256        // L=32(byte)
    int  HSscrBitShiftSize = 128;     // 256/2(bit)  // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 128;          // treat separately with HSscrBitShiftSize
  #ifdef originalMMS
    #define  HSxorEmbPosIntLL 2       // (intLL)(pos. starting from 1)
  #endif
    //----------------------------//
    #define  mIntIntSize_LL    5
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   4
#endif

/******************************/
#ifdef MMS384W
  #ifndef originalMMS	
	#define  RAND_name "MMS384W"
   #else
	#define  RAND_name "MMS384"
  #endif	   
    #define  HSHashBitSize 384        // L=48(byte)
    int  HSscrBitShiftSize = 192;     // 384/2(bit)  // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 192;          // treat separately with HSscrBitShiftSize
  #ifdef originalMMS
    #define  HSxorEmbPosIntLL 3       // (intLL)(pos. starting from 1)
  #endif
    //----------------------------//
    #define  mIntIntSize_LL    7
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   6
#endif

/******************************/
#ifdef MMS512W
  #ifndef originalMMS	
	#define  RAND_name "MMS512W"
   #else
	#define  RAND_name "MMS512"
  #endif	   
    #define  HSHashBitSize 512        // L=64(byte)
    int  HSscrBitShiftSize = 256;     // 256(bit)  // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 256;          // treat separately with HSscrBitShiftSize
  #ifdef originalMMS
    #define  HSxorEmbPosIntLL 4       // (intLL)(pos. starting from 1)
  #endif
    //----------------------------//
    #define  mIntIntSize_LL    9
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   8
#endif

/******************************/
#ifdef MMS1024W
  #ifndef originalMMS	
	#define  RAND_name "MMS1024W"
   #else
	#define  RAND_name "MMS1024"
  #endif	   
    #define  HSHashBitSize 1024       // L=128(byte)
    int  HSscrBitShiftSize = 512;     // 1024/2(bit)  // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 512;          // treat separately with HSscrBitShiftSize
  #ifdef originalMMS
    #define  HSxorEmbPosIntLL 8       // (intLL)(pos. starting from 1)
  #endif
    //----------------------------//
    #define  mIntIntSize_LL    17
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   16
#endif

/******************************/
#ifdef MMS2048W
  #ifndef originalMMS	
	#define  RAND_name "MMS2048W"
   #else
	#define  RAND_name "MMS2048"
  #endif	   
    #define  HSHashBitSize 2048       // L=256(byte)
    int  HSscrBitShiftSize = 1024;    // 2048/2(bit)  // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 1024;         // treat separately with HSscrBitShiftSize
  #ifdef originalMMS
    #define  HSxorEmbPosIntLL 16      // (intLL)(pos. starting from 1)
  #endif
    //----------------------------//
    #define  mIntIntSize_LL    33
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   32
#endif

/******************************/
#ifdef MMS4096W
  #ifndef originalMMS	
	#define  RAND_name "MMS4096W"
   #else
	#define  RAND_name "MMS4096"
  #endif	   
    #define  HSHashBitSize 4096       // L=512(byte)
    int  HSscrBitShiftSize = 2048;    // 4096/2(bit)  // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 2048;         // treat separately with HSscrBitShiftSize
  #ifdef originalMMS
    #define  HSxorEmbPosIntLL 32      // (intLL)(pos. starting from 1)
  #endif
    //----------------------------//
    #define  mIntIntSize_LL    65
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   64
#endif

/******************************/
#ifdef MMS8192W
	#define  RAND_name "MMS8192W"
    #define  HSHashBitSize 8192       // L=1024(byte)
    int  HSscrBitShiftSize = 4096;    // 8192/2(bit)  // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 4096;         // treat separately with HSscrBitShiftSize
    //----------------------------//
    #define  mIntIntSize_LL    129
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   128
#endif

/******************************/
#ifdef MMS16384W
	#define  RAND_name "MMS16384W"
    #define  HSHashBitSize 16384       // L=2048(byte)
    int  HSscrBitShiftSize = 8192;    // 16384/2(bit)  // will be modified
    int  HSscrBitShiftTimes = 2;      // will be modified
    int  HSHashBgnBit = 8192;         // treat separately with HSscrBitShiftSize
    //----------------------------//
    #define  mIntIntSize_LL    257
    #define  mIntIndexMin_LL   1
    #define  mIntIndexMax_LL   256
#endif

/******************************/
#define  mIntMSB_LL    0x8000000000000000
#define  mIntBaseM1_LL     0xffffffffffffffff
#define  mIntBaseBits_LL   64

/********************** type def for mInt *********************/
typedef struct
    {
    unsigned long long int mIdgt_LL[mIntIntSize_LL];
    } mInt_LL;
typedef struct
    {
    unsigned long long int mIdgt_LL[1+mIntIndexMax_LL*2];
    } mIntD_LL;

typedef struct                    /* Intel's MPU only */
    {
    unsigned int L;
    unsigned int H;
    } uiHL;
typedef union
    {
    unsigned long long int I;
    uiHL HL;
    } uiLLHL;
typedef union
    {
    unsigned long long int I;
    uiHL HL;
    double Dbl;
    } uiLLHL_Dbl;

typedef union
    {
    unsigned long long int  ui_LL[mIntIntSize_LL];
    unsigned char uc_LL[mIntIntSize_LL*sizeof(long long int)];
    } HS_LL;
typedef union
    {
    unsigned int  ui_LL[1+mIntIndexMax_LL*2];
    unsigned char uc_LL[(1+mIntIndexMax_LL*2)*sizeof(long long int)];
    } HSD_LL;

//*************************************************************//
typedef struct
    {
    unsigned long long int p; unsigned long long int q;
    unsigned long long int pp; unsigned long long int qq;
    unsigned long long int r; unsigned long long int s;
    unsigned long long int rr; unsigned long long int ss;
    unsigned long long int rk; unsigned long long int sk;
    unsigned long long int rrk; unsigned long long int ssk;
    unsigned long long int XpBase; unsigned long long int XqBase;
    unsigned long long int w0; unsigned long long int v0;
    uiLLHL wkLL; uiLLHL vkLL;
    } MMSParaLP;
MMSParaLP MMSWParaLPorg =
    {
    0x7fffffffffffffe7,  // p=2^63-25
    0x7fffffffffffff5b,  // q=2^63-165
    0x7ffffffffffffefd,  // pp=2^63-259
    0x7ffffffffffffed3,  // qq=2^63-301
    0x39F750241C2D5D33,  // r=0x39f750241c2d5d7b-72
    0x32F50FEE9B2A32BB,  // s=0x32f50fee9b2a32d7-28
    0x39ce884256f4f9af,  // rr
    0x5664526cc2b19e75,  // ss
    0, 0,                // rk, sk
    0, 0,                // rrk, ssk
    };
MMSParaLP MMSWParaLP =
    {
    0x7fffffffffffffe7,  // p=2^63-25
    0x7fffffffffffff5b,  // q=2^63-165
    0x7ffffffffffffefd,  // pp=2^63-259
    0x7ffffffffffffed3,  // qq=2^63-301
    0x39F750241C2D5D33,  // r=0x39f750241c2d5d7b-72
    0x32F50FEE9B2A32BB,  // s=0x32f50fee9b2a32d7-28
    0x39ce884256f4f9af,  // rr
    0x5664526cc2b19e75,  // ss
    0, 0,                // rk, sk
    0, 0,                // rrk, ssk
    };

/**************/
void MMSadvanceRSLP(MMSParaLP *SIParaLLP)
    {
    SIParaLLP->rk += SIParaLLP->r;
    if (SIParaLLP->rk >= SIParaLLP->p) {SIParaLLP->rk -= SIParaLLP->p;}
    SIParaLLP->sk += SIParaLLP->s;
    if (SIParaLLP->sk >= SIParaLLP->q) {SIParaLLP->sk -= SIParaLLP->q;}
    SIParaLLP->rrk += SIParaLLP->rr;
    if (SIParaLLP->rrk >= SIParaLLP->pp) {SIParaLLP->rrk -= SIParaLLP->pp;}
    SIParaLLP->ssk += SIParaLLP->ss;
    if (SIParaLLP->ssk >= SIParaLLP->qq) {SIParaLLP->ssk -= SIParaLLP->qq;}
    }

void MMSshowRkSkLP(void)  // for debug
    {
    uiLLHL LLHLn, LLHLwk;
	
    LLHLwk.I = MMSWParaLP.rk;   // set rk
	printf("rk  = %08x %08x  ", LLHLwk.HL.H, LLHLwk.HL.L);
    LLHLwk.I = MMSWParaLP.sk;   // set sk
	printf(" sk = %08x %08x\n", LLHLwk.HL.H, LLHLwk.HL.L);

    LLHLwk.I = MMSWParaLP.rrk;   // set rrk
	printf("rrk = %08x %08x  ", LLHLwk.HL.H, LLHLwk.HL.L);
    LLHLwk.I = MMSWParaLP.ssk;   // set ssk
	printf("ssk = %08x %08x\n", LLHLwk.HL.H, LLHLwk.HL.L);
	}

/*************** constant for hashing (1) *********************/

// 1.2718281828459...  MSB = 1   BaseForm[N[1+E/10,1500]*8,16]
// Used for nnn=64,128,...,4096 of originalMMS

#ifdef originalMMS	
  unsigned long long int HSconst1_4800bits_LL[1+5*5*3] =
    {
    0,
    0xa2cb4411ba257552,    0x232c1139a172a5c9,
    0xf8252780c2d5d7b7,    0x88603e0d04140a65,
    0x8f50b9293a8572fe,    0xb2a32d7a47027df8,
    0x314d239a22f4137e,    0xf72c9fc45dff7aad,
    0x073d976cac9ae2f6,    0x8113e1110c629efd,
    0x8aab03dfb3118ea4,    0x51a968e3602e1be4,
    0xc6ee1b9230c994e3,    0x9f96ab537155fb0a,
    0xa355c20fdb3ee518,    0x8c0223808a3a98ad,
    0x29ce884256f4fa65,    0x8b7bc557e02b30e1,
    0x9f7640872c71dc64,    0x22de2f94ad7d589e,
    0x9bce54c1c9354916,    0x860098f9f5fe6095,
    0xc00a675c3b3da313,    0x837d661f61e780cc,
    0xb60fd0709630804d,    0x8d993f0575afef7d,
    0x725798f26fc06ccd,    0xf44fc9e7190480bd,
    0x5afd753af38a2ffe,    0xe81573a4e0398ff8,
    0xf93ddf0be10500ab,    0xf270fdc631ec0071,
    0xad24165b91615b67,    0xe55e9f6e1d3197fc,
    0x784f56988d1af838,    0xefcc6a351a9d83b0,
    0x2403cf50bf40b1da,    0x9765da76fa2b0f90,
    0xadca2d3949fddbff,    0xdf561a225285fe1f,
    0xc815d58dd3a47202,    0xbbf439eb1f02c892,
    0x05f31eda2ac0db42,    0xcef2901598772c63,
    0x0c056cfc732ab918,    0xd460d2a247b93963,
    0x7c7caa270475fdcb,    0xe509c860fab4de57,
    0xbc19130d5e1fe29e,    0x7e47296c4433d99a,
    0x819778bab2d6c27e,    0xe371281afcbda382,
    0x2f7b9f99d5ec7b3d,    0x5501799bb6b37027,
    0x4927e4feb055ccd8,    0x01d51eba3d8f1be5,
    0x386c583f7d0cccd8,    0xd542f621feb5cef5,
    0x9bb3b6c2c2f51929,    0x82f524454cb4edaf,
    0x0f8abb4397404d60,    0x5ae8667fac692b66,
    0xcf32adbe0dcd7c18,    0x7614b2a271aa3ba5,
    0x3a58740d5bcaa621,    0x3f2410d6ebe46dc1,
    0xb6b25f7a89f365dc,    0x23e94f3d75b005a5,
    0x5c55ce1198f6627d,    0x1f0645a60fa79a6c,
    0xa4e6a7ff0f65f0e4,    0xbaa0e397eebb7b69,
    0xbe77706fc57a402b,    0x5336301d3dcdd060,
    0x9bbfc066652d86e2
    };
#endif

/*************** constant for hashing (2) *********************/

//https://xn--w6q13e505b.jp/value/hex.html

//π = 3.
// 243f6a8885 a308d31319 8a2e037073 44a4093822 299f31d008 2efa98ec4e ...
// -> a43f6a8885 a308d3...

// Used for nnn=64,128,...,4096,8192,16384
unsigned long long int HSconst2_40000bits_LL[1+5*5*25] =
    {
    0,
    0xa43f6a8885a308d3,    0x13198a2e03707344,
    0xa4093822299f31d0,    0x082efa98ec4e6c89,
    0x452821e638d01377,    0xbe5466cf34e90c6c,
    0xc0ac29b7c97c50dd,    0x3f84d5b5b5470917,
    0x9216d5d98979fb1b,    0xd1310ba698dfb5ac,
    0x2ffd72dbd01adfb7,    0xb8e1afed6a267e96,
    0xba7c9045f12c7f99,    0x24a19947b3916cf7,
    0x0801f2e2858efc16,    0x636920d871574e69,
    0xa458fea3f4933d7e,    0x0d95748f728eb658,
    0x718bcd5882154aee,    0x7b54a41dc25a59b5,
    0x9c30d5392af26013,    0xc5d1b023286085f0,
    0xca417918b8db38ef,    0x8e79dcb0603a180e,
    0x6c9e0e8bb01e8a3e,    0xd71577c1bd314b27,
    0x78af2fda55605c60,    0xe65525f3aa55ab94,
    0x5748986263e81440,    0x55ca396a2aab10b6,
    0xb4cc5c341141e8ce,    0xa15486af7c72e993,
    0xb3ee1411636fbc2a,    0x2ba9c55d741831f6,
    0xce5c3e169b87931e,    0xafd6ba336c24cf5c,
    0x7a32538128958677,    0x3b8f48986b4bb9af,
    0xc4bfe81b66282193,    0x61d809ccfb21a991,
    0x487cac605dec8032,    0xef845d5de98575b1,
    0xdc262302eb651b88,    0x23893e81d396acc5,
    0x0f6d6ff383f44239,    0x2e0b4482a4842004,
    0x69c8f04a9e1f9b5e,    0x21c66842f6e96c9a,
    0x670c9c61abd388f0,    0x6a51a0d2d8542f68,
    0x960fa728ab5133a3,    0x6eef0b6c137a3be4,
    0xba3bf0507efb2a98,    0xa1f1651d39af0176,
    0x66ca593e82430e88,    0x8cee8619456f9fb4,
    0x7d84a5c33b8b5ebe,    0xe06f75d885c12073,
    0x401a449f56c16aa6,    0x4ed3aa62363f7706,
    0x1bfedf72429b023d,    0x37d0d724d00a1248,
    0xdb0fead349f1c09b,    0x075372c980991b7b,
    0x25d479d8f6e8def7,    0xe3fe501ab6794c3b,
    0x976ce0bd04c006ba,    0xc1a94fb6409f60c4,
    0x5e5c9ec2196a2463,    0x68fb6faf3e6c53b5,
    0x1339b2eb3b52ec6f,    0x6dfc511f9b30952c,
    0xcc814544af5ebd09,    0xbee3d004de334afd,
    0x660f2807192e4bb3,    0xc0cba85745c8740f,
    0xd20b5f39b9d3fbdb,    0x5579c0bd1a60320a,
    0xd6a100c6402c7279,    0x679f25fefb1fa3cc,
    0x8ea5e9f8db3222f8,    0x3c7516dffd616b15,
    0x2f501ec8ad0552ab,    0x323db5fafd238760,
    0x53317b483e00df82,    0x9e5c57bbca6f8ca0,
    0x1a87562edf1769db,    0xd542a8f6287effc3,
    0xac6732c68c4f5573,    0x695b27b0bbca58c8,
    0xe1ffa35db8f011a0,    0x10fa3d98fd2183b8,
    0x4afcb56c2dd1d35b,    0x9a53e479b6f84565,
    0xd28e49bc4bfb9790,    0xe1ddf2daa4cb7e33,
    0x62fb1341cee4c6e8,    0xef20cada36774c01,
    0xd07e9efe2bf11fb4,    0x95dbda4dae909198,
    0xeaad8e716b93d5a0,    0xd08ed1d0afc725e0,
    0x8e3c5b2f8e7594b7,    0x8ff6e2fbf2122b64,
    0x8888b812900df01c,    0x4fad5ea0688fc31c,
    0xd1cff191b3a8c1ad,    0x2f2f2218be0e1777,
    0xea752dfe8b021fa1,    0xe5a0cc0fb56f74e8,
    0x18acf3d6ce89e299,    0xb4a84fe0fd13e0b7,
    0x7cc43b81d2ada8d9,    0x165fa26680957705,
    0x93cc7314211a1477,    0xe6ad206577b5fa86,
    0xc75442f5fb9d35cf,    0xebcdaf0c7b3e89a0,
    0xd6411bd3ae1e7e49,    0x00250e2d2071b35e,
    0x226800bb57b8e0af,    0x2464369bf009b91e,
    0x5563911d59dfa6aa,    0x78c14389d95a537f,
    0x207d5ba202e5b9c5,    0x832603766295cfa9,
    0x11c819684e734a41,    0xb3472dca7b14a94a,
    0x1b5100529a532915,    0xd60f573fbc9bc6e4,
    0x2b60a47681e67400,    0x08ba6fb5571be91f,
    0xf296ec6b2a0dd915,    0xb6636521e7b9f9b6,
    0xff34052ec5855664,    0x53b02d5da99f8fa1,
    0x08ba47996e85076a,    0x4b7a70e9b5b32944,
    0xdb75092ec4192623,    0xad6ea6b049a7df7d,
    0x9cee60b88fedb266,    0xecaa8c71699a17ff,
    0x5664526cc2b19ee1,    0x193602a575094c29,
    0xa0591340e4183a3e,    0x3f54989a5b429d65,
    0x6b8fe4d699f73fd6,    0xa1d29c07efe830f5,
    0x4d2d38e6f0255dc1,    0x4cdd20868470eb26,
    0x6382e9c6021ecc5e,    0x09686b3f3ebaefc9,
    0x3c9718146b6a70a1,    0x687f358452a0e286,
    0xb79c5305aa500737,    0x3e07841c7fdeae5c,
    0x8e7d44ec5716f2b8,    0xb03ada37f0500c0d,
    0xf01c1f040200b3ff,    0xae0cf51a3cb574b2,
    0x25837a58dc0921bd,    0xd19113f97ca92ff6,
    0x9432477322f54701,    0x3ae5e58137c2dadc,
    0xc8b576349af3dda7,    0xa94461460fd0030e,
    0xecc8c73ea4751e41,    0xe238cd993bea0e2f,
    0x3280bba1183eb331,    0x4e548b384f6db908,
    0x6f420d03f60a04bf,    0x2cb8129024977c79,
    0x5679b072bcaf89af,    0xde9a771fd9930810,
    0xb38bae12dccf3f2e,    0x5512721f2e6b7124,
    0x501adde69f84cd87,    0x7a5847187408da17,
    0xbc9f9abce94b7d8c,    0xec7aec3adb851dfa,
    0x63094366c464c3d2,    0xef1c18473215d908,
    0xdd433b3724c2ba16,    0x12a14d432a65c451,
    0x50940002133ae4dd,    0x71dff89e10314e55,
    0x81ac77d65f11199b,    0x043556f1d7a3c76b,
    0x3c11183b5924a509,    0xf28fe6ed97f1fbfa,
    0x9ebabf2c1e153c6e,    0x86e34570eae96fb1,
    0x860e5e0a5a3e2ab3,    0x771fe71c4e3d06fa,
    0x2965dcb999e71d0f,    0x803e89d65266c825,
    0x2e4cc9789c10b36a,    0xc6150eba94e2ea78,
    0xa5fc3c531e0a2df4,    0xf2f74ea7361d2b3d,
    0x1939260f19c27960,    0x5223a708f71312b6,
    0xebadfe6eeac31f66,    0xe3bc4595a67bc883,
    0xb17f37d1018cff28,    0xc332ddefbe6c5aa5,
    0x6558218568ab9802,    0xeecea50fdb2f953b,
    0x2aef7dad5b6e2f84,    0x1521b62829076170,
    0xecdd4775619f1510,    0x13cca830eb61bd96,
    0x0334fe1eaa0363cf,    0xb5735c904c70a239,
    0xd59e9e0bcbaade14,    0xeecc86bc60622ca7,
    0x9cab5cabb2f3846e,    0x648b1eaf19bdf0ca,
    0xa02369b9655abb50,    0x40685a323c2ab4b3,
    0x319ee9d5c021b8f7,    0x9b540b19875fa099,
    0x95f7997e623d7da8,    0xf837889a97e32d77,
    0x11ed935f16681281,    0x0e358829c7e61fd6,
    0x96dedfa17858ba99,    0x57f584a51b227263,
    0x9b83c3ff1ac24696,    0xcdb30aeb532e3054,
    0x8fd948e46dbc3128,    0x58ebf2ef34c6ffea,
    0xfe28ed61ee7c3c73,    0x5d4a14d9e864b7e3,
    0x42105d14203e13e0,    0x45eee2b6a3aaabea,
    0xdb6c4f15facb4fd0,    0xc742f442ef6abbb5,
    0x654f3b1d41cd2105,    0xd81e799e86854dc7,
    0xe44b476a3d816250,    0xcf62a1f25b8d2646,
    0xfc8883a0c1c7b6a3,    0x7f1524c369cb7492,
    0x47848a0b5692b285,    0x095bbf00ad19489d,
    0x1462b17423820e00,    0x58428d2a0c55f5ea,
    0x1dadf43e233f7061,    0x3372f0928d937e41,
    0xd65fecf16c223bdb,    0x7cde3759cbee7460,
    0x4085f2a7ce77326e,    0xa607808419f8509e,
    0xe8efd85561d99735,    0xa969a7aac50c06c2,
    0x5a04abfc800bcadc,    0x9e447a2ec3453484,
    0xfdd567050e1e9ec9,    0xdb73dbd3105588cd,
    0x675fda79e3674340,    0xc5c43465713e38d8,
    0x3d28f89ef16dff20,    0x153e21e78fb03d4a,
    0xe6e39f2bdb83adf7,    0xe93d5a68948140f7,
    0xf64c261c94692934,    0x411520f77602d4f7,
    0xbcf46b2ed4a20068,    0xd40824713320f46a,
    0x43b7d4b7500061af,    0x1e39f62e97244546,
    0x14214f74bf8b8840,    0x4d95fc1d96b591af,
    0x70f4ddd366a02f45,    0xbfbc09ec03bd9785,
    0x7fac6dd031cb8504,    0x96eb27b355fd3941,
    0xda2547e6abca0a9a,    0x28507825530429f4,
    0x0a2c86dae9b66dfb,    0x68dc1462d7486900,
    0x680ec0a427a18dee,    0x4f3ffea2e887ad8c,
    0xb58ce0067af4d6b6,    0xaace1e7cd3375fec,
    0xce78a399406b2a42,    0x20fe9e35d9f385b9,
    0xee39d7ab3b124e8b,    0x1dc9faf74b6d1856,
    0x26a36631eae397b2,    0x3a6efa74dd5b4332,
    0x6841e7f7ca7820fb,    0xfb0af54ed8feb397,
    0x454056acba489527,    0x55533a3a20838d87,
    0xfe6ba9b7d096954b,    0x55a867bca1159a58,
    0xcca9296399e1db33,    0xa62a4a563f3125f9,
    0x5ef47e1c9029317c,    0xfdf8e80204272f70,
    0x80bb155c05282ce3,    0x95c11548e4c66d22,
    0x48c1133fc70f86dc,    0x07f9c9ee41041f0f,
    0x404779a45d886e17,    0x325f51ebd59bc0d1,
    0xf2bcc18f41113564,    0x257b7834602a9c60,
    0xdff8e8a31f636c1b,    0x0e12b4c202e1329e,
    0xaf664fd1cad18115,    0x6b2395e0333e92e1,
    0x3b240b62eebeb922,    0x85b2a20ee6ba0d99,
    0xde720c8c2da2f728,    0xd012784595b794fd,
    0x647d0862e7ccf5f0,    0x5449a36f877d48fa,
    0xc39dfd27f33e8d1e,    0x0a476341992eff74,
    0x3a6f6eabf4f8fd37,    0xa812dc60a1ebddf8,
    0x991be14cdb6e6b0d,    0xc67b55106d672c37,
    0x2765d43bdcd0e804,    0xf1290dc7cc00ffa3,
    0xb5390f92690fed0b,    0x667b9ffbcedb7d9c,
    0xa091cf0bd9155ea3,    0xbb132f88515bad24,
    0x7b9479bf763bd6eb,    0x37392eb3cc115979,
    0x8026e297f42e312d,    0x6842ada7c66a2b3b,
    0x12754ccc782ef11c,    0x6a124237b79251e7,
    0x06a1bbe64bfb6350,    0x1a6b101811caedfa,
    0x3d25bdd8e2e1c3c9,    0x444216590a121386,
    0xd90cec6ed5abea2a,    0x64af674eda86a85f,
    0xbebfe98864e4c3fe,    0x9dbc8057f0f7c086,
    0x60787bf86003604d,    0xd1fd8346f6381fb0,
    0x7745ae04d736fccc,    0x83426b33f01eab71,
    0xb08041873c005e5f,    0x77a057bebde8ae24,
    0x55464299bf582e61,    0x4e58f48ff2ddfda2,
    0xf474ef388789bdc2,    0x5366f9c3c8b38e74,
    0xb475f25546fcd9b9,    0x7aeb26618b1ddf84,
    0x846a0e79915f95e2,    0x466e598e20b45770,
    0x8cd55591c902de4c,    0xb90bace1bb8205d0,
    0x11a862487574a99e,    0xb77f19b6e0a9dc09,
    0x662d09a1c4324633,    0xe85a1f0209f0be8c,
    0x4a99a0251d6efe10,    0x1ab93d1d0ba5a4df,
    0xa186f20f2868f169,    0xdcb7da83573906fe,
    0xa1e2ce9b4fcd7f52,    0x50115e01a70683fa,
    0xa002b5c40de6d027,    0x9af88c27773f8641,
    0xc3604c0661a806b5,    0xf0177a28c0f586e0,
    0x006058aa30dc7d62,    0x11e69ed72338ea63,
    0x53c2dd94c2c21634,    0xbbcbee5690bcb6de,
    0xebfc7da1ce591d76,    0x6f05e4094b7c0188,
    0x39720a3d7c927c24,    0x86e3725f724d9db9,
    0x1ac15bb4d39eb8fc,    0xed54557808fca5b5,
    0xd83d7cd34dad0fc4,    0x1e50ef5eb161e6f8,
    0xa28514d96c51133c,    0x6fd5c7e756e14ec4,
    0x362abfceddc6c837,    0xd79a323492638212,
    0x670efa8e406000e0,    0x3a39ce37d3faf5cf,
    0xabc277375ac52d1b,    0x5cb0679e4fa33742,
    0xd382274099bc9bbe,    0xd5118e9dbf0f7315,
    0xd62d1c7ec700c47b,    0xb78c1b6b21a19045,
    0xb26eb1be6a366eb4,    0x5748ab2fbc946e79,
    0xc6a376d26549c2c8,    0x530ff8ee468dde7d,
    0xd5730a1d4cd04dc6,    0x2939bbdba9ba4650,
    0xac9526e8be5ee304,    0xa1fad5f06a2d519a,
    0x63ef8ce29a86ee22,    0xc089c2b843242ef6,
    0xa51e03aa9cf2d0a4,    0x83c061ba9be96a4d,
    0x8fe51550ba645bd6,    0x2826a2f9a73a3ae1,
    0x4ba99586ef5562e9,    0xc72fefd3f752f7da,
    0x3f046f6977fa0a59,    0x80e4a91587b08601,
    0x9b09e6ad3b3ee593,    0xe990fd5a9e34d797,
    0x2cf0b7d9022b8b51,    0x96d5ac3a017da67d,
    0xd1cf3ed67c7d2d28,    0x1f9f25cfadf2b89b,
    0x5ad6b4725a88f54c,    0xe029ac71e019a5e6,
    0x47b0acfded93fa9b,    0xe8d3c48d283b57cc,
    0xf8d5662979132e28,    0x785f0191ed756055,
    0xf7960e44e3d35e8c,    0x15056dd488f46dba,
    0x03a161250564f0bd,    0xc3eb9e153c9057a2,
    0x97271aeca93a072a,    0x1b3f6d9b1e6321f5,
    0xf59c66fb26dcf319,    0x7533d928b155fdf5,
    0x035634828aba3cbb,    0x28517711c20ad9f8,
    0xabcc5167ccad925f,    0x4de817513830dc8e,
    0x379d58629320f991,    0xea7a90c2fb3e7bce,
    0x5121ce64774fbe32,    0xa8b6e37ec3293d46,
    0x48de53696413e680,    0xa2ae0810dd6db224,
    0x69852dfd09072166,    0xb39a460a6445c0dd,
    0x586cdecf1c20c8ae,    0x5bbef7dd1b588d40,
    0xccd2017f6bb4e3bb,    0xdda26a7e3a59ff45,
    0x3e350a44bcb4cdd5,    0x72eacea8fa6484bb,
    0x8d6612aebf3c6f47,    0xd29be463542f5d9e,
    0xaec2771bf64e6370,    0x740e0d8de75b1357,
    0xf8721671af537d5d,    0x4040cb084eb4e2cc,
    0x34d2466a0115af84,    0xe1b0042895983a1d,
    0x06b89fb4ce6ea048,    0x6f3f3b823520ab82,
    0x011a1d4b277227f8,    0x611560b1e7933fdc,
    0xbb3a792b344525bd,    0xa08839e151ce794b,
    0x2f32c9b7a01fbac9,    0xe01cc87ebcc7d1f6,
    0xcf0111c3a1e8aac7,    0x1a908749d44fbd9a,
    0xd0dadecbd50ada38,    0x0339c32ac6913667,
    0x8df9317ce0b12b4f,    0xf79e59b743f5bb3a,
    0xf2d519ff27d9459c,    0xbf97222c15e6fc2a,
    0x0f91fc719b941525,    0xfae59361ceb69ceb,
    0xc2a8645912baa8d1,    0xb6c1075ee3056a0c,
    0x10d25065cb03a442,    0xe0ec6e0e1698db3b,
    0x4c98a0be3278e964,    0x9f1f9532e0d392df,
    0xd3a0342b8971f21e,    0x1b0a74414ba3348c,
    0xc5be7120c37632d8,    0xdf359f8d9b992f2e,
    0xe60b6f470fe3f11d,    0xe54cda541edad891,
    0xce6279cfcd3e7e6f,    0x1618b166fd2c1d05,
    0x848fd2c5f6fb2299,    0xf523f357a6327623,
    0x93a8353156cccd02,    0xacf081625a75ebb5,
    0x6e16369788d273cc,    0xde96629281b949d0,
    0x4c50901b71c65614,    0xe6c6c7bd327a140a,
    0x45e1d006c3f27b9a,    0xc9aa53fd62a80f00,
    0xbb25bfe235bdd2f6,    0x71126905b2040222,
    0xb6cbcf7ccd769c2b,    0x53113ec01640e3d3,
    0x38abbd602547adf0,    0xba38209cf746ce76,
    0x77afa1c520756060,    0x85cbfe4e8ae88dd8,
    0x7aaaf9b04cf9aa7e,    0x1948c25c02fb8a8c,
    0x01c36ae4d6ebe1f9,    0x90d4f869a65cdea0,
    0x3f09252dc208e69f,    0xb74e6132ce77e25b,
    0x578fdfe33ac372e6,    0xb83acb022002397a,
    0x6ec6fb5bffcfd4dd,    0x4cbf5ed1f43fe582,
    0x3ef4e8232d152af0,    0xe718c97059bd9820,
    0x1f4a9d62e7a529ba,    0x89e1248d3bf88656,
    0xc5114d0ebc4cee16,    0x034d8a3920e47882,
    0xe9ae8fbde3abdc1f,    0x6da51e525db2bae1,
    0x01f86e7a6d9c68a9,    0x2708fcd9293cbc0c,
    0xb03c86f8a8ad2c2f,    0x00424eebcacb452d,
    0x89cc71fcd59c7f91,    0x7f0622bc6d8a08b1,
    0x834d21326884ca82,    0xe3aacbf37786f2fa,
    0x2cab6e3dce535ad1,    0xf20ac607c6b8e14f,
    0x5eb4388e775014a6,    0x656665f7b64a43e4,
    0xba383d01b2e41079,    0x8eb2986f909e0ca4,
    0x1f7b37772c126030,    0x85088718c4e7d1bd,
    0x4065ffce8392fd8a,    0xaa36d12bb4c8c9d0,
    0x994fb0b714f96818,    0xf9a53998a0a178c6,
    0x2684a81e8ae972f6,    0xb8425eb67a29d486,
    0x551bd719af32c189,    0xd5145505dc81d53e,
    0x48424edab796ef46,    0xa0498f03667deede,
    0x03ac0ab3c497733d,    0x5316a89130a88fcc,
    0x9604440aceeb893a,    0x7725b82b0e1ef69d,
    0x302a5c8ee7b84def,    0x5a31b096c9ebf88d,
    0x512d788e7e4002ee,    0x87e02af6c358a1bb,
    0x02e8d7afdf9fb0e7,    0x790e942a3b3c1aba,
    0xc6ffa7af9df796f9,    0x321bb9940174a8a8,
    0xed22162ccff1bb99,    0xdaa8d551a4d5e44b,
    0xecdde3eca80dc509,    0x0393eef272523d31,
    0xd48e3a1c224eb65e,    0x6052c3a42109c32f,
    0x052ee388ed9f7ea9,    0x91c62f9777b55ba0,
    0x150cbca33aec6525,    0xdf31838343a9ce26,
    0x9362ad8b0134140b,    0x8df5cf811e9ff559,
    0x167f05643812f4e0,    0x588a52b0cbb8e944,
    0xef5b16a373c4eda1,    0x7dfcfeeaf54bcbbe,
    0x8773e3d2c531dcd0,    0x55c4672952774f3a,
    0x57ca6bc0467d3a3b,    0x24778425b7991e9a,
    0xdd825c26e452c8ee,    0xfcacde1e84833af3,
    0x61211d031732c131,    0xccadb247e606be8c,
    0x712b39f188b4ef39,    0x3a9fcdc5c5755169,
    0x1ff6994f39829cb0,    0x110165733343cbeb,
    0x61d3d0b444f30aef,    0xa8ae73752a3a1c9d,
    0xb4b70914d6ab250c,    0x853b7328495f948f,
    0xd2a4ed8e6cf751e4,    0xc320bb75d9caa0b3,
    0x8ba562624e84b03f,    0xeea8076e74a07fe5,
    0x8039e00c36ffdaf8,    0x03731358b9e671b9,
    0xdac4ce1cb25b10ed,    0x4dd3d5b1fcf2b480,
    0x4634f57925eac400,    0xa9ac55ea728932df,
    0x06041d055d31f502,    0xc539c2e32b89d9db,
    0x5bcc0a98c05bfd6f,    0x1b2506222e21be0e,
    0x60973b04ecd54a67,    0xb54fe638a6ed6615,
    0x981a910a5d92928d,    0xac6fc697e73c63ad,
    0x456edf5f457a8145,    0x51875a64cd3099f1,
    0x69b5f18a8c73ee0b,    0x5e57368f6c79f4bb,
    0x7a595926aab49ec6
    };
	
/******** to debug mInt_LL ********/
void DumpMint_LL(unsigned long long int *M, char c)
    {
    int  i;

    printf("[%c] ", c);
    for (i=mIntIndexMin_LL-1; i<=mIntIndexMax_LL; i++)
        {
        if (M[i] == 0)
			{printf("Z ");}
		  else
		    {printf("%016llx ", M[i]);}
		}
    printf("\n");
    }
void DumpMintD_LL(unsigned long long int *MD, char c)
    {
    int  i;

    printf("[%c] ", c);
    for (i=mIntIndexMin_LL-1; i<=mIntIndexMax_LL*2; i++)
        {
        if (MD[i] == 0)
			{printf("Z ");}
		  else
		    {printf("%016llx ", MD[i]);}
		}
    printf("\n");
    }

/*===============================================================*/

/************/

unsigned long long int MMS_RN_counter[4];  // count generated RN after MMSIni_**

void clear_MMS_RN_counter(void)
    {
    MMS_RN_counter[0] = 0;  MMS_RN_counter[1] = 0;
    MMS_RN_counter[2] = 0;  MMS_RN_counter[3] = 0;
    }
void up_MMS_RN_counter(void)
    {
    MMS_RN_counter[3]++;   //increase RN counter
    if (MMS_RN_counter[3] == 0)
        {
        MMS_RN_counter[2]++;
        if (MMS_RN_counter[2] == 0)
            {
            MMS_RN_counter[1]++;
            if (MMS_RN_counter[1] == 0)
                {
                MMS_RN_counter[0]++;
                }
            }
        }
    }

void show_MMS_RN_counter(void)  // for debug
    {
    printf("MMS_RN_counter is\n");
    printf("  %08x %08x %08x %08x\n", MMS_RN_counter[0],
           MMS_RN_counter[1], MMS_RN_counter[2], MMS_RN_counter[3]);
    }

/*=========== Inline Assembling ============*/
#define __int64 long long
typedef struct 
    {
    unsigned __int64 lo64;
    unsigned __int64 hi64;
    } my_i128;
//********************************
#define ADD_64_64(out, in1, in2) \
     __asm__("mov %2, %%rax; \
              mov %3, %%rcx; \
              xorq %%rdx, %%rdx; \
              addq %%rcx, %%rax; \
              adcq %%rdx, %%rdx; \
              mov %%rdx, %0; \
              mov %%rax, %1; \
              "              \
             : "=r"(out.hi64), "=r"(out.lo64) \
             : "r"(in1), "r"(in2)     \
             : "%rax", "%rcx", "%rdx" \
             );
//********************************
#define MUL_64_64(out, in1, in2) \
     __asm__("mov %2, %%rax; \
              mov %3, %%rcx; \
              mul %%rcx;     \
              mov %%rdx, %0; \
              mov %%rax, %1; \
              "              \
             : "=r"(out.hi64), "=r"(out.lo64) \
             : "r"(in1), "r"(in2)     \
             : "%rax", "%rcx", "%rdx" \
             );
/*======== End of Inline Assembling ========*/

//********************************
int mIntMUL_HL_ASM_LL(unsigned long long int *U, unsigned long long int *V,
                  unsigned long long int *UVD)
    {
    my_i128  LLHLuv, LLMulAddWk1, LLMulAddWk2;
    int i, j, iPj;
    unsigned long long int c;
	
    if (U[mIntIndexMin_LL-1] != 0) {return(1);}
    if (V[mIntIndexMin_LL-1] != 0) {return(2);}

    memset(UVD, 0, sizeof(mIntD_LL));
	
    for (j=mIntIndexMax_LL; j>=mIntIndexMin_LL; j--)       /* V */
        {
        if (V[j] == 0)
            {
            UVD[j] = 0;
            continue;
            }

        c=0;
        for (i=mIntIndexMax_LL; i>=mIntIndexMin_LL; i--)   /* U */
            {
            iPj = i+j;
			if (U[i] != 0)
			    {	
				MUL_64_64(LLHLuv, U[i], V[j]);
				ADD_64_64(LLMulAddWk1, LLHLuv.lo64, UVD[iPj]);
				ADD_64_64(LLMulAddWk2, LLMulAddWk1.lo64, c);
				UVD[iPj] = LLMulAddWk2.lo64;
				c = LLHLuv.hi64 + LLMulAddWk1.hi64 + LLMulAddWk2.hi64;
				}
			  else
			    {
				//MUL_64_64(LLHLuv, U[i], V[j]);
				//ADD_64_64(LLMulAddWk1, LLHLuv.lo64, UVD[iPj]);
				//ADD_64_64(LLMulAddWk2, LLMulAddWk1.lo64, c);
				ADD_64_64(LLMulAddWk2, UVD[iPj], c);
				UVD[iPj] = LLMulAddWk2.lo64;
				//c = LLHLuv.hi64 + LLMulAddWk1.hi64 + LLMulAddWk2.hi64;
				c = LLMulAddWk2.hi64;
				}
            }
        UVD[j] = c;
        //DumpmIntD_LL(UVD, 'm'); //debug
        }
    
    //DumpMint_LL(U, 'u');    //debug
    //DumpMint_LL(V, 'v');    //debug
    //DumpMintD_LL(UVD, 'M'); //debug
    
    return(0);
    }
/*==================================================*/

/****************/
#ifdef originalMMS
// valid for nnn = 64, 128, ..., 4096 of originalMMS
int MMSloop_originalMMS(HS_LL *HashValueM_LL, int BitShiftSize, int BitShiftTimes)
    {
    int  i, j, k, mIntResult;
    int  HSBitShift_IntLLSize, HSBitShift_BitSizeRmdr, HSBitShift_BitSizeRmdrC;
    int  HSHashBgnInt_LL, HSHashBgnBitRmdr;
    int  n;
	
	unsigned long long int scrFMLL[1+mIntIndexMax_LL];
	unsigned long long int scrYMLL[1+mIntIndexMax_LL];
	unsigned long long int scrWk1MDLL[1+mIntIndexMax_LL*2]; 

    int  wk1, wk2;
    unsigned int uiWk1;
    uiLLHL uiLLHL1, uiLLHL2, uiLLHL3;
    int InitValBytes;

    InitValBytes = sizeof(mInt_LL);
    //memset(&scrFMLL, 0, sizeof(mInt_LL));  //debug
    memcpy(&scrFMLL, HSconst1_4800bits_LL, InitValBytes);
   // DumpMint_LL(scrFMLL, 'f');   //debug
    //memset(&scrYMLL, 0, sizeof(mInt_LL));  //debug
    memcpy(&scrYMLL, HSconst1_4800bits_LL, InitValBytes);
    //DumpMint_LL(scrYMLL, 'y');    //debug

    //printf("rk=%016llx  sk=%016llx\n", MMSWParaLP.rk, MMSWParaLP.sk) ;  //debug
   if ((HSHashBitSize % 128) != 0)
        {
        scrYMLL[HSxorEmbPosIntLL]  ^= MMSWParaLP.rk;
        scrFMLL[HSxorEmbPosIntLL]  ^= MMSWParaLP.sk;
        }
      else
        {
 	    uiLLHL1.I = MMSWParaLP.rk;
	    uiLLHL2.I = MMSWParaLP.sk;
        scrYMLL[HSxorEmbPosIntLL]  ^= (unsigned long long int)uiLLHL1.HL.H;
        scrFMLL[HSxorEmbPosIntLL]  ^= (unsigned long long int)uiLLHL2.HL.H;
        uiLLHL1.HL.H = uiLLHL1.HL.L;  uiLLHL1.HL.L = 0;
        uiLLHL2.HL.H = uiLLHL2.HL.L;  uiLLHL2.HL.L = 0;
        scrYMLL[HSxorEmbPosIntLL+1]  ^= uiLLHL1.I;
        scrFMLL[HSxorEmbPosIntLL+1]  ^= uiLLHL2.I;
        }

    //DumpMint_LL(scrYMLL, 'Y');   //debug
    //DumpMint_LL(scrFMLL, 'F');   //debug
 
  // scramble main ASM
    HSBitShift_IntLLSize = HSscrBitShiftSize / mIntBaseBits_LL;
    HSBitShift_BitSizeRmdr = HSscrBitShiftSize % mIntBaseBits_LL;
    HSBitShift_BitSizeRmdrC = mIntBaseBits_LL-HSBitShift_BitSizeRmdr;
	
    //printf("HSBitShift_IntLLSize : %d  HSBitShift_BitSizeRmdr : %d\n",
    //        HSBitShift_IntLLSize, HSBitShift_BitSizeRmdr);  //debug
    //printf("HSBitShift_BitSizeRmdrC : %d\n", HSBitShift_BitSizeRmdrC); //debug

    for (i=1; i<=HSscrBitShiftTimes; i++)
        {
        scrFMLL[mIntIndexMin_LL] |= mIntMSB_LL;
        scrYMLL[mIntIndexMin_LL] |= mIntMSB_LL;
        //DumpMint_LL(scrYMLL, 'y');   //debug
        //DumpMint_LL(scrFMLL, 'f');   //debug
        mIntResult = mIntMUL_HL_ASM_LL(scrFMLL, scrYMLL, scrWk1MDLL);
        if (mIntResult != 0)
		    {printf("mIntResult != 0"); return(3000+mIntResult);}
		//printf("** i of D ** %d\n", i);		  //debug	 
        //DumpMintD_LL(scrWk1MDLL, 'D');   //debug
        
        for (j=1; j<=mIntIndexMax_LL; j++)
            {
            if (HSBitShift_BitSizeRmdr==0)
                {
                scrFMLL[j]  = scrWk1MDLL[j+HSBitShift_IntLLSize];
                scrYMLL[j]  = scrFMLL[j];
                }
              else
                {
                scrFMLL[j]  = (scrWk1MDLL[j+HSBitShift_IntLLSize]<<HSBitShift_BitSizeRmdr);
                scrFMLL[j]  |= (scrWk1MDLL[j+HSBitShift_IntLLSize+1]>>HSBitShift_BitSizeRmdrC);
                scrYMLL[j]  = scrFMLL[j];
                }  
            }
        //DumpMint_LL(scrFMLL, 'F');   //debug
        }

    //DumpMintD_LL(scrWk1MDLL, 'W');   //debug

    // take out random number
    HSHashBgnInt_LL = HSHashBgnBit/mIntBaseBits_LL;
    HSHashBgnBitRmdr = HSHashBgnBit % mIntBaseBits_LL;
    //printf("HSHashBgnBit : %d  HSHashBgnInt : %d  HSHashBgnBitRmdr : %d\n",
    //        HSHashBgnBit, HSHashBgnInt_LL, HSHashBgnBitRmdr); //debug
    //DumpMintD_LL(scrWk1MDLL, 'W');   //debug
    for (j=1; j<=mIntIndexMax_LL; j++)
        {
        if (HSHashBgnBitRmdr==0)
            {
            HashValueM_LL->ui_LL[j] = scrWk1MDLL[j+HSHashBgnInt_LL];
            }
          else
            {
            HashValueM_LL->ui_LL[j] = (scrWk1MDLL[HSHashBgnInt_LL+j] << HSHashBgnBitRmdr);
            HashValueM_LL->ui_LL[j] |=
                (scrWk1MDLL[HSHashBgnInt_LL+j+1] >> (mIntBaseBits_LL-HSHashBgnBitRmdr));
            }
        }
    
    HashValueM_LL->ui_LL[mIntIndexMin_LL-1]=0;
    //DumpMint_LL((unsigned long long int *)HashValueM_LL, 'H');   //debug

    return(0);
    }
#endif

/****************/
int MMSloop_W(HS_LL *HashValueM_LL, int BitShiftSize, int BitShiftTimes)
    {
    int  i, j, k, mIntResult;
    int  HSBitShift_IntLLSize, HSBitShift_BitSizeRmdr, HSBitShift_BitSizeRmdrC;
    int  HSHashBgnInt_LL, HSHashBgnBitRmdr;
    int  n;
	
    //HS_LL   scrFM, scrYM;
	unsigned long long int scrFMLL[1+mIntIndexMax_LL];
	unsigned long long int scrYMLL[1+mIntIndexMax_LL];
    //HSD_LL  scrWk1MD;
	unsigned long long int scrWk1MDLL[1+mIntIndexMax_LL*2]; 

    int  wk1, wk2;
    unsigned int uiWk1;
    uiLLHL uiLLHL1, uiLLHL2, uiLLHL3;
    int InitValBytes;

    InitValBytes = sizeof(mInt_LL);

    //memset(&scrFMLL, 0, sizeof(mInt_LL));  //debug
    //memcpy(&scrFMLL, HSconst1_4800bits_LL, InitValBytes);
    memcpy(&scrFMLL, HSconst2_40000bits_LL, InitValBytes);
    //DumpMint_LL(scrFMLL, 'f');   //debug

    //memset(&scrYMLL, 0, sizeof(mInt_LL));  //debug
    //memcpy(&scrYMLL, HSconst1_4800bits_LL, InitValBytes);
    memcpy(&scrYMLL, HSconst2_40000bits_LL, InitValBytes);
    //DumpMint_LL(scrYMLL, 'y');    //debug

    for (n=1; n<=HSHashBitSize/mIntBaseBits_LL; n++)  // '26.01.09
        {
        scrYMLL[n]  ^= MMSWParaLP.rk;  // '26.01.09
        scrFMLL[n]  ^= MMSWParaLP.sk;  // '26.01.09
        }
    //DumpMint_LL(scrYMLL, 'Y');   //debug
    //DumpMint_LL(scrFMLL, 'F');   //debug
 
  // scramble main ASM
    HSBitShift_IntLLSize = HSscrBitShiftSize / mIntBaseBits_LL;
    HSBitShift_BitSizeRmdr = HSscrBitShiftSize % mIntBaseBits_LL;
    HSBitShift_BitSizeRmdrC = mIntBaseBits_LL-HSBitShift_BitSizeRmdr;
	
    //printf("HSBitShift_IntLLSize : %d  HSBitShift_BitSizeRmdr : %d\n",
    //        HSBitShift_IntLLSize, HSBitShift_BitSizeRmdr);  //debug
    //printf("HSBitShift_BitSizeRmdrC : %d\n", HSBitShift_BitSizeRmdrC); //debug

    for (i=1; i<=HSscrBitShiftTimes; i++)
        {
        scrFMLL[mIntIndexMin_LL] |= mIntMSB_LL;
        scrYMLL[mIntIndexMin_LL] |= mIntMSB_LL;
        //DumpMint_LL(scrYMLL, 'y');   //debug
        //DumpMint_LL(scrFMLL, 'f');   //debug
        mIntResult = mIntMUL_HL_ASM_LL(scrFMLL, scrYMLL, scrWk1MDLL);
        if (mIntResult != 0)
		    {printf("mIntResult != 0"); return(3000+mIntResult);}
		//printf("** i of D ** %d\n", i);		  //debug	 
        //DumpMintD_LL(scrWk1MDLL, 'D');   //debug
        
        for (j=1; j<=mIntIndexMax_LL; j++)
            {
            if (HSBitShift_BitSizeRmdr==0)
                {
                scrFMLL[j]  = scrWk1MDLL[j+HSBitShift_IntLLSize];
                scrYMLL[j]  = scrFMLL[j];
                }
              else
                {
                scrFMLL[j]  = (scrWk1MDLL[j+HSBitShift_IntLLSize]<<HSBitShift_BitSizeRmdr);
                scrFMLL[j]  |= (scrWk1MDLL[j+HSBitShift_IntLLSize+1]>>HSBitShift_BitSizeRmdrC);
                scrYMLL[j]  = scrFMLL[j];
                }  
            }
        //DumpMint_LL(scrFMLL, 'F');   //debug

        if (i==1)  //2025.12.13
            {
            //memset(&scrYMLL, 0, sizeof(mInt_LL));  //debug
            //memset(&scrFMLL, 0, sizeof(mInt_LL));  //debug
            //DumpMint_LL(scrYMLL, 'Y');   //debug
            //DumpMint_LL(scrFMLL, 'F');   //debug
            for (n=1; n<=HSHashBitSize/mIntBaseBits_LL; n++)  // '26.01.09
                {
                scrYMLL[n]  ^= MMSWParaLP.rrk;  // '26.01.09
                scrFMLL[n]  ^= MMSWParaLP.ssk;  // '26.01.09
                }
            //DumpMint_LL(scrYMLL, 'y');   //debug
            //DumpMint_LL(scrFMLL, 'f');   //debug
            }
        }

    //DumpMintD_LL(scrWk1MDLL, 'W');   //debug

    // take out random number
    HSHashBgnInt_LL = HSHashBgnBit/mIntBaseBits_LL;
    HSHashBgnBitRmdr = HSHashBgnBit % mIntBaseBits_LL;
    //printf("HSHashBgnBit : %d  HSHashBgnInt : %d  HSHashBgnBitRmdr : %d\n",
    //        HSHashBgnBit, HSHashBgnInt_LL, HSHashBgnBitRmdr); //debug
    //DumpMintD_LL(scrWk1MDLL, 'W');   //debug
    for (j=1; j<=mIntIndexMax_LL; j++)
        {
        if (HSHashBgnBitRmdr==0)
            {
            HashValueM_LL->ui_LL[j] = scrWk1MDLL[j+HSHashBgnInt_LL];
            }
          else
            {
            HashValueM_LL->ui_LL[j] = (scrWk1MDLL[HSHashBgnInt_LL+j] << HSHashBgnBitRmdr);
            HashValueM_LL->ui_LL[j] |=
                (scrWk1MDLL[HSHashBgnInt_LL+j+1] >> (mIntBaseBits_LL-HSHashBgnBitRmdr));
            }
        }
    
    HashValueM_LL->ui_LL[mIntIndexMin_LL-1]=0;
    //DumpMint_LL((unsigned long long int *)HashValueM_LL, 'H');   //debug

    return(0);
    }

/*****************************************************/
int getMMSRand_W(HS_LL *HashValueM_LL)
    {
    MMSloop_W(HashValueM_LL, HSscrBitShiftSize, HSscrBitShiftTimes);

	MMSadvanceRSLP(&MMSWParaLP);
    up_MMS_RN_counter();

	return(0);
    }
	
/*****************************************************/
#ifdef originalMMS
  int getMMSRand_org(HS_LL *HashValueM_LL)
    {
    // valid for nnn = 64, ..., 4096 of originalMMS
    MMSloop_originalMMS(HashValueM_LL, HSscrBitShiftSize, HSscrBitShiftTimes);

	MMSadvanceRSLP(&MMSWParaLP);
    up_MMS_RN_counter();

	return(0);
    }
#endif

	
/*** ====== Functions for Initialization ====== ***/

#ifdef UseMMSIni
  #include "MMSIniFuncs.c"
#endif

/*** ========================================== ***/


/********************* testMMSnnnW ***********************/

/**************/
void TypeRandHex_LL(HS_LL *HashValueM_LL)
    {
    int  i;
    unsigned long long int v;

    for (i=mIntIndexMin_LL; i<=mIntIndexMax_LL; i++)
    	{
        v = HashValueM_LL->ui_LL[i];
        printf("%016llx ", v);
        }
	//printf("\n");
    }

/**************/
int mainSample_MMSW(void)
    {
    HS_LL  HashValue_LL;
    unsigned long long int N, M, L, K;
	uiLLHL uiLLHLwk;
    unsigned int Bin32x8[8];

    printf("[%s] SBit=%d Lp=%d DBit=%d HSBitSz=%d ",
        RAND_name, HSscrBitShiftSize, HSscrBitShiftTimes, HSHashBgnBit,
        HSHashBitSize);
    printf("mIntSize_LL=%d\n", mIntIntSize_LL);

 	printf("== Using getMMSRand_W() without initialization ==\n");
	
    //MMSshowRkSkLP(); //debug
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= c6a0e9a5 ce728727)  0th RN");
	#endif
 	printf("\n");
    //MMSshowRkSkLP(); //debug

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= dd57efd7 482c204a)  1st RN");
	#endif
 	printf("\n");
    //MMSshowRkSkLP(); //debug

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= aa779e77 7c3ca63f)  2nd RN");
	#endif
 	printf("\n");
    //MMSshowRkSkLP(); //debug

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 71ae8298 73419b24)  3rd RN");
	#endif
 	printf("\n");
    //MMSshowRkSkLP(); //debug

    /***********/
  #ifdef UseMMSIni
 	printf("\n== Using MMSIni() & getMMSRand_W() ==\n");
	printf("MMSIni(0)\n");
    N = 0;
    MMSIni(N);

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= c6a0e9a5 ce728727)  0th RN");
	#endif
 	printf("\n");

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= dd57efd7 482c204a)  1st RN");
	#endif
 	printf("\n");

    //
	printf("MMSIni(3)\n");
    N = 3;
    MMSIni(N);

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 71ae8298 73419b24)  3rd RN");
	#endif
 	printf("\n");

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 27ccd0b4 82b9a15f)  4th RN");
	#endif
 	printf("\n");

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= c845fa04 d7fbfc16)  5th RN");
	#endif
 	printf("\n");

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 363c7bed fc61b454)  6th RN");
	#endif
 	printf("\n");

    show_MMS_RN_counter();  //debug
 	printf("\n");

    /*************/
	printf("MMSIni(202)\n");
    N = 202;
    MMSIni(N);

	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 1083857d 351138ff)  202th RN");
	#endif
 	printf("\n");

    /***********************************/

    ///////////
 	printf("\n== Using MMSIni_setNM() ==\n");
    N = 101; M = 2;
    printf("  N = 101; M = 2\n");
    printf("MMSIni_setNM(N,M)  // set to generate N*M_th RN\n");
    MMSIni_setNM(N,M);
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 1083857d 351138ff)  202th RN");
	#endif
 	printf("\n");

    ///////////
 	printf("\n== Using MMSIni_setNMplusL() ==\n");
    N = 50;  M = 4;  L = 2;
    printf("  N = 50; M = 4; L = 2\n");
    printf("MMSIni_setNMplusL(N,M,L)  // set to generate N*M+L_th RN\n");
    MMSIni_setNMplusL(N,M,L);
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 1083857d 351138ff)  202th RN");
	#endif
 	printf("\n");

  ////////////////////////

    printf("\n======== using MMSIni_setNMLK() ========\n");
    N=0x8000000000000001; M=N; L=N; K=N;
	printf("  N = M = L = K = 0x8000000000000001\n");
 	printf("MMSIni_setNMLK(N,M,L,K)  // set to generate NxMxLxK-th RN\n");
    MMSIni_setNMLK(N,M,L,K);
    //show_MMS64LP_Ini_InitialNo();  //debug
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);     // NxMxLxK-th RN
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= b0ab734c 6da7b4c5)  NxMxLxK-th RN");
	#endif
 	printf("\n");

    printf("\n======== using MMSIni_setNMLK() and MMSIni_plusNMLK() ========\n");
    N=0x8000000000000001; M=N; L=N; K=5;
	printf("  N = M = L = 0x8000000000000001,  k = 5\n");
 	printf("MMSIni_setNMLK(N,M,L,5)  // set to generate NxMxLx(K=5)-th RN\n");
    MMSIni_setNMLK(N,M,L,K);
    //show_MMS64LP_Ini_InitialNo();  //debug
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);     // NxMxLxK-th RN
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 8a54c078 6a0fd725)  NxMxLx(K=5)-th RN");
	#endif
 	printf("\n");

    N=0x8000000000000001; M=N; L=N; K=3;
	printf("\n  N = M = L = 0x8000000000000001,  k = 3\n");
 	printf("MMSIni_setNMLK(N,M,L,3)  // set to generate NxMxLx(K=3)-th RN\n");
    MMSIni_setNMLK(N,M,L,K);
    //show_MMS64LP_Ini_InitialNo();  //debug
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);     // NxMxLxK-th RN
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= f081f438 07b17853)  NxMxLx(K=3)-th RN");
	#endif
 	printf("\n");

    N=0x8000000000000001; M=N; L=N; K=2;
	printf("\n  N = M = L = 0x8000000000000001,  k = 2\n");
    printf(" // set to generate (previous MMSIni_** No)+NxMxLx(K=2)-th RN\n");
 	printf("MMSIni_plusNMLK(N,M,L,2)\n");
    MMSIni_plusNMLK(N,M,L,K);
    //show_MMS64LP_Ini_InitialNo();  //debug
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);     // NxMxLxK-th RN
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 8a54c078 6a0fd725)  NxMxLx(K=(3+2)=5)-th RN");
	#endif
 	printf("\n");

    printf("\n======== using MMSIni_setBin32x8() ========\n");
    memset(&Bin32x8, 0, sizeof(Bin32x8));
    Bin32x8[0] = 0xffffffff;
    Bin32x8[7] = 0x11111111;
    printf("  Bin32x8[0]=0xffffffff; Bin32x8[1]...[6]=0; Bin32x8[7] = 0x11111111;\n");
    printf("MMSIni_setBin32x8(Bin32x8)  // set to generate ffffffff0000...000011111111-th RN\n");
    MMSIni_setBin32x8(Bin32x8);
	//printf("  ffffffff 0000...0000 11111111 -th RN is\n");
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= c74024a2 18c15bdc)");
	#endif
 	printf("\n");

    Bin32x8[7] = 0x11111110;
	printf("\n  Bin32x8[0]=0xffffffff; Bin32x8[1]...[6]=0; Bin32x8[7] = 0x11111110;\n");
    printf("MMSIni_setBin32x8(Bin32x8)  // set to generate ffffffff0000...000011111110-th RN\n");
    MMSIni_setBin32x8(Bin32x8);
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 1ca87f69 63790836)");
	#endif
 	printf("\n");

    printf("\n  [Next RN is ffffffff0000...000011111111-th RN]\n");
	printf("getMMSRand_W()  ");
    getMMSRand_W(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= c74024a2 18c15bdc)");
	#endif
 	printf("\n");
 	printf("\n");

  #endif

    return(0);
    }
/**************/
#ifdef originalMMS
  int mainSample_OriginalMMS(void)
    {
    HS_LL  HashValue_LL;
    unsigned long long int N, M, L, K;
	uiLLHL uiLLHLwk;
    unsigned int Bin32x8[8];

    printf("[%s] SBit=%d Lp=%d DBit=%d HSBitSz=%d ",
        RAND_name, HSscrBitShiftSize, HSscrBitShiftTimes, HSHashBgnBit,
        HSHashBitSize);
    printf("mIntSize_LL=%d\n", mIntIntSize_LL);

 	printf("== Using getMMSRand_org() without initialization ==\n");
	
	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 2549db80 13fc8303)  0th RN");
	#endif
 	printf("\n");


	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 8b4b011c 79312836)  1st RN");
	#endif
 	printf("\n");

	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= e1a2d4f0 c2625b32)  2nd RN");
	#endif
 	printf("\n");

	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 8d9e8f81 819305cb)  3rd RN");
	#endif
 	printf("\n");

    /***********/
  #ifdef UseMMSIni
 	printf("\n== Using MMSIni() & getMMSRand_org() ==\n");
	printf("MMSIni(0)\n");
    N = 0;
    MMSIni(N);

	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 2549db80 13fc8303)  0th RN");
	#endif
 	printf("\n");

	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 8b4b011c 79312836)  1st RN");
	#endif
 	printf("\n");

    //
	printf("MMSIni(3)\n");
    N = 3;
    MMSIni(N);

	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 8d9e8f81 819305cb)  3rd RN");
	#endif
 	printf("\n");

	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 8717d60d 6c5c95e5)  4th RN");
	#endif
 	printf("\n");

	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= c4ee2aaa 625bba24)  5th RN");
	#endif
 	printf("\n");

	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= 6b73173a 3c33acee)  6th RN");
	#endif
 	printf("\n");

    show_MMS_RN_counter();  //debug
 	printf("\n");

    /*************/
	printf("MMSIni(202)\n");
    N = 202;
    MMSIni(N);

	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= e619c76f af442894)  202th RN");
	#endif
 	printf("\n");

    /***********************************/

    ///////////
 	printf("\n== Using MMSIni_setNM() ==\n");
    N = 101; M = 2;
    printf("  N = 101; M = 2\n");
    printf("MMSIni_setNM(N,M)  // set to generate N*M_th RN\n");
    MMSIni_setNM(N,M);
	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= e619c76f af442894)  202th RN");
	#endif
 	printf("\n");

    ///////////
 	printf("\n== Using MMSIni_setNMplusL() ==\n");
    N = 50;  M = 4;  L = 2;
    printf("  N = 50; M = 4; L = 2\n");
    printf("MMSIni_setNMplusL(N,M,L)  // set to generate N*M+L_th RN\n");
    MMSIni_setNMplusL(N,M,L);
	printf("getMMSRand_org()  ");
    getMMSRand_org(&HashValue_LL);
    TypeRandHex_LL(&HashValue_LL);
	#ifdef MMS64W
 	printf("(= e619c76f af442894)  202th RN");
	#endif
 	printf("\n");

  #endif

    return(0);
    }
#endif

/**************/
#ifdef HowToUseMMSnnnW
int main()
    {
  #ifndef originalMMS
	mainSample_MMSW();
   #else
    mainSample_OriginalMMS();
  #endif

    return(0);
    }

#endif

///////// NOTE //////////////////////////////////////////
// The code above is not refined; and
//    should be tested by many users.
// If you find bugs, please mail to
//    hiroshimayaguchi at-mark yahoo.co.jp .
// (At that time, include the code-name (such as
//   IKUKOsan-20260122) in the subject of the mail.)
//
// MMSnnnW RNG : Last updated at 2026.01.22
//      (Code Name : IKUKOsan-20260122)
// This NOTE : Last updated at 2026.01.22
/////////////////////////////////////////////////////////
