//////////////////////////////////////////////////////////////
//   This is MMS64LP random number generator at 2026.01.20. //
//     ([Code-Name:'KUNIKOsan-20260120']).                  //
//   Use the compiler gcc.                                  //
//   MMS64LP is an academic product.                        //
//   Use MMS64LP within your responsibility.                //
//////////////////////////////////////////////////////////////
                      // LP means Long-Period (=approx. 10^75)

 /*=*=* ### Selection ### *=*=*/

/*** (1) Remove // below to test this code ***/

  //#define HowToUseMMS64LP   // main() in this module will be used
          // gcc MMS64LPtest.c -o MMS64LPtest

/*** (2) If you want to use original MMS, remove // below ***/

  //#define originalMMS

      //  The period of original MMS is  (p=2^63-25)x(q=2^63-165).
      //  The period of MMS64LP is
      //     (p=2^63-25)x(q=2^63-165)x(pp=2^63-259)x(qq=2^63-301).
      //   Concerning the role of pp & qq, see the functions
      //     MMS64plusRS_LP() and MMS64IniComLP() below.

 /*=*=* ### End of selection ### *=*=*/

#include <stdio.h>
#include <memory.h>

#ifdef originalMMS
  #define RAND_name "MMS64" 
 #else
  #define RAND_name "MMS64LP"
#endif

//*************************************************************//
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

typedef struct
    {
    unsigned long long int p; unsigned long long int q;
    unsigned long long int pp; unsigned long long int qq;
    unsigned long long int r; unsigned long long int s;
    unsigned long long int rr; unsigned long long int ss;
    unsigned long long int rk; unsigned long long int sk;
    unsigned long long int rrk; unsigned long long int ssk;
    unsigned long long int XpBase;
    } SIPara64LP;

SIPara64LP SIParaMMS64LPorg =
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
    0xa2cb4411ba257552,  // XpBase
    };

SIPara64LP SIParaMMS64LP =
    {
    0x7fffffffffffffe7,  // p=2^63-25
    0x7fffffffffffff5b,  // q=2^63-165
    0x7ffffffffffffefd,  // pp=2^63-259
    0x7ffffffffffffed3,  // qq=2^63-301
    0x39F750241C2D5D33,  // r=0x39f750241c2d5d7b-72
    0x32F50FEE9B2A32BB,  // s=0x32f50fee9b2a32d7-28
    0x39ce884256f4f9af,  // rr
    0x5664526cc2b19e75,  // ss
    0, 0,                // rk, sk      // P_i, Q_i
    0, 0,                // rrk, ssk    // (PP)_i, (QQ)_i
    0xa2cb4411ba257552,  // XpBase
    };

//********************************
void MMS64plusRS_LP(SIPara64LP *SIParaLLP)
    {
    SIParaLLP->rk += SIParaLLP->r;    // P_(i+1) = (P_i)+r mod p
    if (SIParaLLP->rk >= SIParaLLP->p) {SIParaLLP->rk -= SIParaLLP->p;}
    SIParaLLP->sk += SIParaLLP->s;    // Q_(i+1) = (Q_i)+s mod q
    if (SIParaLLP->sk >= SIParaLLP->q) {SIParaLLP->sk -= SIParaLLP->q;}

    SIParaLLP->rrk += SIParaLLP->rr;  // (PP)_(i+1) = (PP_i)+rr mod pp
    if (SIParaLLP->rrk >= SIParaLLP->pp) {SIParaLLP->rrk -= SIParaLLP->pp;}
    SIParaLLP->ssk += SIParaLLP->ss;  // (QQ)_(i+1) = (QQ_i)+ss mod qq
    if (SIParaLLP->ssk >= SIParaLLP->qq) {SIParaLLP->ssk -= SIParaLLP->qq;}
    }

void MMSshowRkSkLP(void)
    {
    uiLLHL LLHLn, LLHLwk;

    LLHLwk.I = SIParaMMS64LP.rk;   // set rk
    printf("rk  = %08x %08x  ", LLHLwk.HL.H, LLHLwk.HL.L);
    LLHLwk.I = SIParaMMS64LP.sk;   // set sk
    printf(" sk = %08x %08x\n", LLHLwk.HL.H, LLHLwk.HL.L);

    LLHLwk.I = SIParaMMS64LP.rrk;   // set rrk
    printf("rrk = %08x %08x  ", LLHLwk.HL.H, LLHLwk.HL.L);
    LLHLwk.I = SIParaMMS64LP.ssk;   // set ssk
    printf("ssk = %08x %08x\n", LLHLwk.HL.H, LLHLwk.HL.L);
    }

/********** for multiple-Integer computation (using mInt) ***********/
#define  mIntBase       0x100000000
#define  mIntBaseM1     0x0ffffffff
#define  mIntBaseBits   32
#define  mIntIntSize    10
#define  mIntIndexMin   1
#define  mIntIndexMax   9
typedef struct  {unsigned int mIdgt[mIntIntSize];} mInt;   // mInt is defined here
typedef struct  {unsigned int mIdgt[1+mIntIndexMax*2];} mIntD;

void DumpMint(mInt *M, char c);
void DumpMintD(mIntD *MD, char c);
int mIntADD_HL(mIntD *UD, mIntD *VD, mIntD *UVD);
int mIntSUB_HL(mIntD *UD, mIntD *VD, mIntD *WD);
int mIntMUL_HL(mInt *U, mInt *V, mIntD *UVD);
int mIntDIVs_HL(mInt *V, mIntD *QD, mIntD *RD);
int mIntDIV_HL(mIntD *UD, mInt *Vcl, mIntD *QD, mIntD *RD);
/*******************************************************/

/*******************************************************/

mInt MMS64LP_Ini_InitialNo;
            // the number given or determined by
            // MMSIni(), MMSIni_setNM(), MMSIni_setNMplusL(),
            // MMSIni_setNMLK(), MMSIni_plusNMLK(), MMSIni_setBin32x8()

void show_MMS64LP_Ini_InitialNo(void)
    {
    int  i;
    printf("\nMMS64LP_Ini_InitialNo is\n");
    for (i=mIntIndexMin-1; i<=mIntIndexMax; i++)
        {printf("%08x ", MMS64LP_Ini_InitialNo.mIdgt[i]);}
    printf("\n");
    }

/************/

unsigned long long int MMS_RN_counter[4];  // count generated RN after MMSIni_**

void clear_RN_counter(void)
    {
    MMS_RN_counter[0] = 0;  MMS_RN_counter[1] = 0;
    MMS_RN_counter[2] = 0;  MMS_RN_counter[3] = 0;
    }
void up_RN_counter(void)
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

void show_MMS_RN_counter(void)
    {
    printf("MMS_RN_counter is\n");
    printf("  %08x %08x %08x %08x\n", MMS_RN_counter[0],
           MMS_RN_counter[1], MMS_RN_counter[2], MMS_RN_counter[3]);
    }

//********************************
// called by MMS64_compute_Rand()
// (original MMS64)
#define MMS_X64_X64(out, in1, in2) \
     __asm__("mov %3, %%rcx; \
              mov %2, %%rax; \
              mov  $0x8000000000000000, %%r10; \
              or  %%r10, %%rax; \
              or  %%r10, %%rcx; \
              mul %%rcx;     \
              shl $32, %%rdx; \
              shr $32, %%rax; \
              or  %%rdx, %%rax; \
              or  %%r10, %%rax; \
              mov %%rax, %%rcx; \
              mul %%rcx;     \
              mov %%rdx, %1; \
              shl $32, %%rdx; \
              shr $32, %%rax; \
              or  %%rdx, %%rax; \
              mov %%rax, %0; \
              "              \
             : "=r"(out.hi64), "=r"(out.lo64) \
             : "r"(in1), "r"(in2)     \
             : "%rax", "%rcx", "%rdx", "%r10" \
             );

//********************************
// called by MMS64LP_compute_Rand()
#define MMS_X64_X64_LP(out, in1, in2, in3, in4) \
     __asm__("mov %3, %%rcx; \
              mov %2, %%rax; \
              mov  $0x8000000000000000, %%r10; \
              or  %%r10, %%rax; \
              or  %%r10, %%rcx; \
              mul %%rcx;     \
              shl $32, %%rdx; \
              shr $32, %%rax; \
              or  %%rdx, %%rax; \
              or  %%r10, %%rax; \
              mov %%rax, %%rcx; \
              mov %4, %%rdx; \
              xor %%rdx, %%rax; \
              mov %5, %%rdx; \
              xor %%rdx, %%rcx; \
              mul %%rcx;     \
              mov %%rdx, %1; \
              shl $32, %%rdx; \
              shr $32, %%rax; \
              or  %%rdx, %%rax; \
              mov %%rax, %0; \
              "              \
             : "=r"(out.hi64), "=r"(out.lo64) \
             : "r"(in1), "r"(in2), "r"(in3), "r"(in4) \
             : "%rax", "%rcx", "%rdx", "%r10" \
             );
//*********************************//

/*=======================================*/
typedef struct 
    {
    unsigned long long lo64;
    unsigned long long hi64;
    } my_i128;
/*=======================================*/

unsigned long long int MMS64_compute_Rand(SIPara64LP *SIParaLLP) //original MMS64
    {
    int    i;
    uiLLHL  XLL1, XLL2;
    my_i128 u;
                       // xxxx :  xxxx is the corresponding step in the algorithm of MMS
    XLL1.I = SIParaLLP->XpBase;       // B(base)
    XLL1.I ^= (SIParaLLP->rk);        // X_i = (B XOR P_i)  in (S0)

    XLL2.I = SIParaLLP->XpBase;       // B(base)
    XLL2.I ^= (SIParaLLP->sk);        // Y_i = (B XOR Q_i)  in (S0)

    MMS_X64_X64(u, XLL1.I, XLL2.I);   // step (S1)-(S4) of MMS64

    return(u.hi64);                   // (S4):return 64-bit RN
    }

//*********************************//
unsigned long long int MMS64LP_compute_Rand(SIPara64LP *SIParaLLP) //Long-Period MMS64
    {
    int    i;
    uiLLHL  XLL1, XLL2;
    uiLLHL  XLL3, XLL4;
    my_i128 u;
    XLL1.I = SIParaLLP->XpBase;      // B(base)
    XLL1.I ^= (SIParaLLP->rk);       // X_i = (B XOR P_i) in (S0)

    XLL2.I = SIParaLLP->XpBase;      // B(base)
    XLL2.I ^= (SIParaLLP->sk);       // Y_i = (B XOR Q_i) in (S0)

   // (M_i)*(M_i) in Step (S3) is modified as
   //
   //   (M_i XOR (PP_i))*(M_i XOR (QQ)_i)

    XLL3.I = (SIParaLLP->rrk);       // (PP)_i : XOR is taken with M_i in (S3)

    XLL4.I = (SIParaLLP->ssk);       // (QQ)_i : XOR is taken with M_i in (S3)

    MMS_X64_X64_LP(u, XLL1.I, XLL2.I, XLL3.I, XLL4.I);   // step (S1)-(S4) of MMS64
                                                         // ( (S3) is modified )

    return(u.hi64);                  // (S4):return 64-bit RN
    }
//*********************************//

/**************/
#ifndef originalMMS
unsigned long long int MMS64LP_getBin64(void)  //return 64-bit RN
    {
    unsigned long long int RanBits;

    RanBits=MMS64LP_compute_Rand(&SIParaMMS64LP);    // MMS64LP

    MMS64plusRS_LP(&SIParaMMS64LP);      // prepare next P_i, ..., (QQ)_i
    up_RN_counter();
    return(RanBits);
    }
#endif

/**************/
#ifdef originalMMS
unsigned long long int MMS64_getBin64(void)  //return 64-bit RN
    {
    unsigned long long int RanBits;

    RanBits=MMS64_compute_Rand(&SIParaMMS64LP);      // MMS64

    MMS64plusRS_LP(&SIParaMMS64LP);      // prepare next P_i, ..., (QQ)_i
    up_RN_counter();
    return(RanBits);
    }
#endif

/**************/
#ifndef originalMMS
double MMS64LP_getU01(void)  //return RN in [0,1)
    {
    uiLLHL_Dbl MMS64Dbl;

    MMS64Dbl.I=MMS64LP_compute_Rand(&SIParaMMS64LP);   // MMS64Lp
    MMS64Dbl.I >>= 12;
    MMS64Dbl.I |= 0x3ff0000000000000;     /*set exponent 2^0*/

    MMS64plusRS_LP(&SIParaMMS64LP);      // prepare next P_i, ..., (QQ)_i
    up_RN_counter();
    return(MMS64Dbl.Dbl-1);
    }
#endif

/**************/
#ifdef originalMMS
double MMS64_getU01(void)  //return RN in [0,1)
    {
    uiLLHL_Dbl MMS64Dbl;

    MMS64Dbl.I=MMS64_compute_Rand(&SIParaMMS64LP);     // MMS64
    MMS64Dbl.I >>= 12;
    MMS64Dbl.I |= 0x3ff0000000000000;     /*set exponent 2^0*/

    MMS64plusRS_LP(&SIParaMMS64LP);      // prepare next P_i, ..., (QQ)_i
    up_RN_counter();
    return(MMS64Dbl.Dbl-1);
    }
#endif

/*===============================================================*/
//   The code below is for MMSIni_functions and for debugging.
//   You can omit the code below if you use only functions
//
//       MMS64LP_getBin64(void)  and  MMS64LP_getU01(void).
//
/*===============================================================*/

/******** to debug mInt ********/
void DumpMint(mInt *M, char c)
    {
    int  i;
    printf("%c ", c);
    for (i=mIntIndexMin-1; i<=mIntIndexMax; i++)
        {printf("%08x ", M->mIdgt[i]);}
    printf("\n");
    }
void DumpMintD(mIntD *MD, char c)
    {
    int  i;
    printf("%c ", c);
    for (i=mIntIndexMin-1; i<=mIntIndexMax*2; i++)
        {printf("%08x ", MD->mIdgt[i]);}
    printf("\n");
    }

/*===============================================================*/
int mIntMUL_HL(mInt *U, mInt *V, mIntD *UVD)
    {
    uiLLHL LLHLu, LLHLv, LLHLw;
    int i, j, iPj;
    unsigned long long int c, uv;
    uiLLHL LLMulAddWk;

    if (U->mIdgt[mIntIndexMin-1] != 0) {return(1);}
    if (V->mIdgt[mIntIndexMin-1] != 0) {return(2);}

    memset(UVD, 0, sizeof(mIntD));

    LLHLu.I = 0;
    LLHLv.I = 0;
    LLHLw.I = 0;

    for (j=mIntIndexMax; j>=mIntIndexMin; j--)       /* V */
        {
        if (V->mIdgt[j] == 0)
            {
            UVD->mIdgt[j] = 0;
            continue;
            }

        c=0;
        LLHLv.HL.L = V->mIdgt[j];
        for (i=mIntIndexMax; i>=mIntIndexMin; i--)   /* U */
            {
            iPj = i+j;
            LLHLu.HL.L = U->mIdgt[i];
            uv = LLHLv.I * LLHLu.I;   /* u*v */
            LLMulAddWk.I = (uv & mIntBaseM1);
            LLHLw.HL.L = UVD->mIdgt[iPj];
            LLMulAddWk.I += LLHLw.I;
            LLMulAddWk.I += c;
            UVD->mIdgt[iPj] = LLMulAddWk.HL.L;
            c = (uv >> mIntBaseBits);
            c += (LLMulAddWk.I >> mIntBaseBits);
            }
        UVD->mIdgt[j] = (unsigned int)c;
        }
    return(0);
    }
/*===============================================================*/
int mIntSUB_HL(mIntD *UD, mIntD *VD, mIntD *WD)
    {
    uiLLHL LLsubWk, LLHLu, LLHLv;
    int j;

    if (UD->mIdgt[mIntIndexMin-1] != 0) {return(1);}
    if (VD->mIdgt[mIntIndexMin-1] != 0) {return(2);}

    LLsubWk.I = 0;
    LLHLu.I = 0;
    LLHLv.I = 0;
    for (j=mIntIndexMax*2; j>=mIntIndexMin; j--)
        {
        LLHLu.HL.L = UD->mIdgt[j];
        LLsubWk.I += LLHLu.I;
        LLHLv.HL.L = VD->mIdgt[j];
        LLsubWk.I -= LLHLv.I;
        WD->mIdgt[j] = LLsubWk.HL.L;

        if (LLsubWk.HL.H != 0)
            { LLsubWk.I = -1; }
          else
            { LLsubWk.I = 0; }
        }

    WD->mIdgt[mIntIndexMin-1] = LLsubWk.HL.L;
    return(0);
    }
/*===============================================================*/
int mIntADD_HL(mIntD *UD, mIntD *VD, mIntD *WD)
    {
    uiLLHL LLaddWk, LLHLu, LLHLv;
    int j;

    if (UD->mIdgt[mIntIndexMin-1] != 0) {return(1);}
    if (VD->mIdgt[mIntIndexMin-1] != 0) {return(2);}

    LLaddWk.I = 0;
    LLHLu.I = 0;
    LLHLv.I = 0;
    for (j=mIntIndexMax*2; j>=mIntIndexMin; j--)
        {
        LLHLu.HL.L = UD->mIdgt[j];
        LLaddWk.I += LLHLu.I;
        LLHLv.HL.L = VD->mIdgt[j];
        LLaddWk.I += LLHLv.I;
        WD->mIdgt[j] = LLaddWk.HL.L;
        LLaddWk.I>>=mIntBaseBits;
        }

    WD->mIdgt[mIntIndexMin-1] = LLaddWk.HL.H;
    return(0);
    }
/*===============================================================*/
int mIntDIVs_HL(mInt *V, mIntD *QD, mIntD *RD)
    {
    unsigned long long int Dv, rbPr;
    int  j;

    // Situation  is   VleftPos=mIntIndexMax;

    Dv = V->mIdgt[mIntIndexMax];
    /* U is copied in R by mIntDIV() */

    QD->mIdgt[mIntIndexMin-1] = 0;
    for(j=mIntIndexMin-1; j<mIntIndexMax*2; j++)   /* R */
        {
        rbPr = (unsigned long long int)(RD->mIdgt[j]*mIntBase + RD->mIdgt[j+1]);
        RD->mIdgt[j] = 0;
        QD->mIdgt[j+1] = (unsigned int)(rbPr / Dv);
        RD->mIdgt[j+1] = (unsigned int)(rbPr % Dv);
        }

    return(0);
    }

/****************/
int mIntDIV_HL(mIntD *UD, mInt *Vcl, mIntD *QD, mIntD *RD)
    {
    uiLLHL IHLu, IHLv;
    mInt V;
    int i, j, iPj, D, M;
    int VleftPos;
    unsigned long long int vq, vqL, c;
    unsigned long long int rbPr, QHAT, RHAT, LHS, RHS;
    uiLLHL MulSubWk;

    if (UD->mIdgt[mIntIndexMin-1] != 0) {return(1);}
    if (Vcl->mIdgt[mIntIndexMin-1] != 0) {return(2);}

    VleftPos=1;
    for (j=mIntIndexMin; j<=mIntIndexMax; j++)    /* Vcl */
        {
        if(Vcl->mIdgt[j] == 0)
           { VleftPos ++; }
         else
           { break; }
        }

    if (VleftPos > mIntIndexMax) {return(3);}

    memcpy(&V, Vcl, sizeof(mInt));
    memcpy(RD, UD, sizeof(mIntD));
    memset(QD, 0, sizeof(mIntD));

    if (VleftPos == mIntIndexMax) {return(mIntDIVs_HL(Vcl, QD, RD));}
                                     /* U is copied in R */

    /* normalization */
    RD->mIdgt[mIntIndexMin-1] = 0;
    V.mIdgt[VleftPos-1] = 0;
    if((V.mIdgt[VleftPos] >> (mIntBaseBits/2)) == 0)
        {
        D = mIntBaseBits/2 ;
        for(i=VleftPos; i<mIntIndexMax; i++)
            {
            V.mIdgt[i] = (unsigned int)((V.mIdgt[i]<<D) | (V.mIdgt[i+1]>>D));
            }
        V.mIdgt[mIntIndexMax]<<=D;
        for(i=mIntIndexMin-1; i<mIntIndexMax*2; i++)
            {
            RD->mIdgt[i] = (unsigned int)((RD->mIdgt[i]<<D) | (RD->mIdgt[i+1]>>D));
            }
        RD->mIdgt[mIntIndexMax*2]<<=D;
        }
      else
        {
        D = 0;
        }
    
    M = VleftPos - mIntIndexMin;  /* M >= 0 */

    for(j=0; j<=M+mIntIndexMax; j++)   /* R */
        {
        /* determine QHAT */
        rbPr = (unsigned long long int)
               (RD->mIdgt[mIntIndexMin-1+j]*mIntBase + RD->mIdgt[mIntIndexMin+j]);
        if (RD->mIdgt[mIntIndexMin-1+j] >= V.mIdgt[VleftPos])
            {QHAT = mIntBaseM1;}
          else
            {QHAT = (unsigned long long int)(rbPr / V.mIdgt[VleftPos]);}
        while (1)
            {
            RHAT = (unsigned long long int)(rbPr - QHAT * V.mIdgt[VleftPos]);
            LHS = (unsigned long long int)(V.mIdgt[VleftPos+1] * QHAT);
            if (RHAT>=mIntBase) {break;}   // if carry happens in the next
            RHS = (unsigned long long int)
                  ((RHAT<<mIntBaseBits) + RD->mIdgt[mIntIndexMin-1+j+2]);

            if (LHS > RHS)
                {QHAT--;}
              else
                {break;}
            }
        //printf("QHAT=%x\n", QHAT);

        /* MUL & SUB */
        IHLu.I = 0;
        IHLv.I = 0;
        c=0;
        for(i=mIntIndexMax; i>=VleftPos-1; i--)  /* V */
           {
           iPj = i+j-M;   //iPj = i-(VleftPos-1)+j+(mIntIndexMin-1);
           //printf("iPj=%d  ",iPj);
           IHLu.HL.L = RD->mIdgt[iPj];
           MulSubWk.I  = IHLu.I;                                 /* u */
           //printf("%4x  ", MulSubWk.I);
           MulSubWk.I  -= c;
           //printf("%4x  ", MulSubWk.I);
           IHLv.HL.L = V.mIdgt[i];                               /* v */
           //printf("(v)%4x  ", IHLv.I);
           vq = (unsigned long long int)(IHLv.I*QHAT);           /* v*q */
           //printf("(vq)%4x  ", vq);
           c = (unsigned long long int)(vq >> mIntBaseBits);     /* vqH */
           //printf("(nc)%2x  ", c);
           vqL = (unsigned long long int)(vq & mIntBaseM1);
           //printf("(vqL)%4x  ", vqL);
           MulSubWk.I -= vqL;
           //printf("%4x  ", MulSubWk.I);
           RD->mIdgt[iPj] = MulSubWk.HL.L;
           if ((int)MulSubWk.HL.H < 0)
               {
               MulSubWk.HL.L = MulSubWk.HL.H;
               MulSubWk.HL.H = mIntBaseM1;
               c -= MulSubWk.I;
               }
           //printf("c=%4x  \n", c);
           }
       QD->mIdgt[mIntIndexMax-M+j] = (unsigned int)QHAT;

       if(c != 0)  // Ex. in radix 10  u=8640  v=433,  q=20  --> q=19
           {                           /*  kuwae-gaeshi */
           //printf("kuwae-gaesi c=%16Lx\n", c);
           QD->mIdgt[mIntIndexMax-M+j]--;
           MulSubWk.I = 0;
           for(i=mIntIndexMax; i>=VleftPos-1; i--)    /* V */
               {
               iPj = i+j-M;
               IHLu.HL.L = RD->mIdgt[iPj];
               MulSubWk.I  += IHLu.I;
               IHLv.HL.L = V.mIdgt[i];
               MulSubWk.I += IHLv.I;
               RD->mIdgt[iPj] = MulSubWk.HL.L;
               MulSubWk.I >>= mIntBaseBits;
               }
           }
       }                            /* end of loop j */

    /* adjust remainder */
    if (D != 0)
        {
        for (i=mIntIndexMax*2; i>=mIntIndexMin; i--)
            {
            RD->mIdgt[i] =
                 (unsigned int)((RD->mIdgt[i]>>D) | (RD->mIdgt[i-1]<<D));
            }
        RD->mIdgt[mIntIndexMin-1] >>= D;
        }
    return(0);
    }

/*================================================================*/
/**************/
void MMS64IniValidityCheck(mIntD *UD, mInt *Vcl, mIntD *QD, mIntD *RD, char ChkId)
    {
    mInt   U;
    mIntD  UVD, wkD;
    int    i, err=0;
    uiLLHL LLHLV, LLHLR;

    memcpy(&U, &QD->mIdgt[mIntIndexMax], sizeof(mInt));
    U.mIdgt[mIntIndexMin-1] = 0;
    mIntMUL_HL(&U, Vcl, &UVD);
    mIntADD_HL(&UVD, RD, &wkD);
    if (memcmp((char *)&wkD, (char *)UD, sizeof(mIntD)) != 0) {err=1;}

    LLHLV.HL.H = Vcl->mIdgt[mIntIndexMax-1];
    LLHLV.HL.L = Vcl->mIdgt[mIntIndexMax];
    LLHLR.HL.H = RD->mIdgt[mIntIndexMax*2-1];
    LLHLR.HL.L = RD->mIdgt[mIntIndexMax*2];
    if (LLHLV.I<=LLHLR.I) {err=2;}

    if (err != 0)
        {
        printf("Validity-Error detected by MMS64IniValidityCheck() [%ck, err#=%d]\n", ChkId, err);
        printf("\n[UD] ");
        for (i=0; i<=mIntIndexMax*2; i++) {printf("%08x ", UD->mIdgt[i]);}
        printf("\n[Vcl]");
        for (i=0; i<=mIntIndexMax; i++) {printf("%08x ", Vcl->mIdgt[i]);}
        printf("\n[QD] ");
        for (i=0; i<=mIntIndexMax*2; i++) {printf("%08x ", QD->mIdgt[i]);}
        printf("\n[RD] ");
        for (i=0; i<=mIntIndexMax*2; i++) {printf("%08x ", RD->mIdgt[i]);}
        printf("\n[UVD]");
        for (i=0; i<=mIntIndexMax*2; i++) {printf("%08x ", UVD.mIdgt[i]);}
        printf("\n[wkD]");
        for (i=0; i<=mIntIndexMax*2; i++) {printf("%08x ", wkD.mIdgt[i]);}
        printf("\n\nIf your compiler is icc, use the compiler option -O0 and try again.\n\n");
        }
    }

/**************/
unsigned long long int MMS64IniComLP_sub(unsigned long long int P,  // (P,R)= (p,r), (q,s)
                                         unsigned long long int R)  //     (pp,rr), (qq,ss)
// compute R*(i=MMS64LP_Ini_InitialNo) mod P
     {
     mInt  V, Vcl;
     mIntD UVD, QD, RD;
     int   c, mIntResult;
     uiLLHL LLHLwk;

     memset(&V, 0, sizeof(mInt));
     memset(&Vcl, 0, sizeof(mInt));
     memset(&UVD, 0, sizeof(mIntD));
     memset(&QD, 0, sizeof(mIntD));
     memset(&RD, 0, sizeof(mIntD));

     LLHLwk.I = R;  
     V.mIdgt[mIntIndexMax-1] = LLHLwk.HL.H;
     V.mIdgt[mIntIndexMax] = LLHLwk.HL.L;
     mIntResult = mIntMUL_HL(&MMS64LP_Ini_InitialNo, &V, &UVD);  // r*i
     //DumpMintD(&UVD, 'm');  //debug
     if (mIntResult != 0)
         {
         printf("mIntMUL_HL(n*r) != 0 : %d\n", mIntResult); //error
         return(-1);
         }

     LLHLwk.I = P;  
     Vcl.mIdgt[mIntIndexMax-1] = LLHLwk.HL.H;
     Vcl.mIdgt[mIntIndexMax] = LLHLwk.HL.L;
     mIntResult = mIntDIV_HL(&UVD, &Vcl, &QD, &RD);  // r*i mod p
     //DumpMintD(&QD, 'Q');  //debug
     //DumpMintD(&RD, 'R');  //debug
     if (mIntResult != 0)
         {
         printf("mIntDIVL_HL(UVD/p) != 0 : %d\n", mIntResult); //error
         return(-2);
         }
     MMS64IniValidityCheck(&UVD, &Vcl, &QD, &RD, 'r');

     LLHLwk.HL.H = RD.mIdgt[mIntIndexMax*2-1];
     LLHLwk.HL.L = RD.mIdgt[mIntIndexMax*2];
     return(LLHLwk.I);   // return r*i mod p
     }
/**************/
void MMS64IniComLP(SIPara64LP *SIParaLLP, mInt *N)
// compute rk(=P_i), sk(=Q_i), rrk(=(PP)_i) and ssk(=(QQ)_i) 
//      which correspond to the initialize-number N(=i)
     {
     memcpy(&MMS64LP_Ini_InitialNo, N, sizeof(mInt));  //copy N as i

     SIParaLLP->rk = MMS64IniComLP_sub(SIParaLLP->p, SIParaLLP->r);
     // P_i = r*i mod p
     //MMSshowRkSkLP();    //debug 

     SIParaLLP->sk = MMS64IniComLP_sub(SIParaLLP->q, SIParaLLP->s);
     // Q_i = s*i mod q
     //MMSshowRkSkLP();    //debug 

     SIParaLLP->rrk = MMS64IniComLP_sub(SIParaLLP->pp, SIParaLLP->rr);
     // (PP)_i =rr*i mod pp
     //MMSshowRkSkLP();    //debug
 
     SIParaLLP->ssk = MMS64IniComLP_sub(SIParaLLP->qq, SIParaLLP->ss);
     // (QQ)_i =ss*i mod qq
     //MMSshowRkSkLP();    //debug 

     clear_RN_counter();
     }

/**************/
void MMSIni(unsigned long long int n)
     {
     uiLLHL LLHLn;
     mInt  U;

     memset(&U, 0, sizeof(mInt));
     LLHLn.I =n;  
     U.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntIndexMax] = LLHLn.HL.L;

     MMS64IniComLP(&SIParaMMS64LP, &U);
     }

/**************/
void MMSIni_setNM(unsigned long long int n, 
                                   unsigned long long int m)
     {
     uiLLHL LLHLn;
     mInt  U, V;
     mIntD UVD;
     int   mIntResult;

     memset(&U, 0, sizeof(mInt));
     memset(&V, 0, sizeof(mInt));
     memset(&UVD, 0, sizeof(mIntD));

     LLHLn.I = n;  
     U.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntIndexMax] = LLHLn.HL.L;
     LLHLn.I = m;  
     V.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     V.mIdgt[mIntIndexMax] = LLHLn.HL.L;
     mIntResult = mIntMUL_HL(&U, &V, &UVD);
     if (mIntResult != 0)
         {
         printf("mIntMUL_HL(setNM) != 0 : %d\n", mIntResult); //error
         return;
         }
     memcpy(&U, &UVD.mIdgt[mIntIndexMax], sizeof(mInt));

     MMS64IniComLP(&SIParaMMS64LP, &U);
     }

/**************/
void MMSIni_setNMplusL(unsigned long long int n, 
                  unsigned long long int m, unsigned long long int l)
     {
     uiLLHL LLHLn;
     mInt  U, V;
     mIntD UVD;
     int   mIntResult;
     mIntD UD, UVD2;

     memset(&U, 0, sizeof(mInt));
     memset(&V, 0, sizeof(mInt));
     memset(&UVD, 0, sizeof(mIntD));
     memset(&UD, 0, sizeof(mIntD));
     memset(&UVD2, 0, sizeof(mIntD));

     LLHLn.I = n;  
     U.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntIndexMax] = LLHLn.HL.L;
     LLHLn.I = m;  
     V.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     V.mIdgt[mIntIndexMax] = LLHLn.HL.L;
     mIntResult = mIntMUL_HL(&U, &V, &UVD);
     if (mIntResult != 0)
         {
         printf("mIntMUL_HL(setNMplusL) != 0 : %d\n", mIntResult); //error
         return;
         }
     LLHLn.I = l;  
     UD.mIdgt[mIntIndexMax*2-1] = LLHLn.HL.H;
     UD.mIdgt[mIntIndexMax*2] = LLHLn.HL.L;
     mIntResult = mIntADD_HL(&UD, &UVD, &UVD2);
     if (mIntResult != 0)
         {
         printf("mIntADD_HL(setNMplusL) != 0 : %d\n", mIntResult); //error
         return;
         }
     memcpy(&U, &UVD2.mIdgt[mIntIndexMax], sizeof(mInt));

     MMS64IniComLP(&SIParaMMS64LP, &U);
     }

/**************/
void MMS64Ini_compNMLK(unsigned long long int n, unsigned long long int m,
               unsigned long long int l,  unsigned long long int k, mIntD *NMLK)
     {
     uiLLHL LLHLn;
     mInt  U, V, W;
     mIntD UVD;
     int   mIntResult;

     memset(&U, 0, sizeof(mInt));
     memset(&V, 0, sizeof(mInt));
     memset(&UVD, 0, sizeof(mIntD));

     LLHLn.I = n;  
     U.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntIndexMax] = LLHLn.HL.L;
     //DumpMint(&U, 'n');  //debug
     LLHLn.I = m;  
     V.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     V.mIdgt[mIntIndexMax] = LLHLn.HL.L;
     //DumpMint(&V, 'm');  //debug
     mIntResult = mIntMUL_HL(&U, &V, &UVD);
     //DumpMintD(&UVD, 'M');  //debug
     if (mIntResult != 0)
         {
         printf("mIntMUL_HL(compNMLK_1) != 0 : %d\n", mIntResult); //error
         return;
         }
     memcpy(&W, &UVD.mIdgt[mIntIndexMax], sizeof(mInt));
     //DumpMint(&W, 'W');  //debug

     LLHLn.I = l;  
     U.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntIndexMax] = LLHLn.HL.L;
     //DumpMint(&U, 'l');  //debug
     mIntResult = mIntMUL_HL(&U, &W, &UVD);
     //DumpMintD(&UVD, 'M');  //debug
     if (mIntResult != 0)
         {
         printf("mIntMUL_HL(compNMLK_2) != 0 : %d\n", mIntResult); //error
         return;
         }
     memcpy(&W, &UVD.mIdgt[mIntIndexMax], sizeof(mInt));
     //DumpMint(&W, 'W');  //debug

     LLHLn.I = k;  
     U.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntIndexMax] = LLHLn.HL.L;
     //DumpMint(&U, 'k');  //debug
     mIntResult = mIntMUL_HL(&U, &W, &UVD);
     //DumpMintD(&UVD, 'M');  //debug
     if (mIntResult != 0)
         {
         printf("mIntMUL_HL(compNMLK_3) != 0 : %d\n", mIntResult); //error
         return;
         }

     memcpy(NMLK, &UVD, sizeof(mIntD));
     //DumpMint(&W, 'W');  //debug

     }

/**************/
void MMSIni_setNMLK(unsigned long long int n, unsigned long long int m,
                      unsigned long long int l,  unsigned long long int k)
     {
     mInt  W;
     mIntD NMLKvalD;
     
     MMS64Ini_compNMLK(n,m,l,k,&NMLKvalD);
     memcpy(&W, &NMLKvalD.mIdgt[mIntIndexMax], sizeof(mInt));
     //DumpMint(&W, 'W');  //debug

     MMS64IniComLP(&SIParaMMS64LP, &W);
     }

/**************/
void MMSIni_plusNMLK(unsigned long long int n, unsigned long long int m,
                      unsigned long long int l,  unsigned long long int k)
     {
     mInt  W;
     mIntD NMLKvalD, currIniValD, nextIniValD;
     int   mIntResult;

     
     MMS64Ini_compNMLK(n,m,l,k,&NMLKvalD);
     //DumpMintD(&NMLKvalD, 'p');  //debug

     memset(&currIniValD, 0, sizeof(mIntD));
     memcpy(&currIniValD.mIdgt[mIntIndexMax], &MMS64LP_Ini_InitialNo, sizeof(mInt));
     //DumpMintD(&currIniValD, 'c');  //debug
     mIntResult = mIntADD_HL(&NMLKvalD, &currIniValD, &nextIniValD);
     //DumpMintD(&nextIniValD, 'a');  //debug
     if (mIntResult != 0)
         {
         printf("mIntADD_HL(plusNMLK) != 0 : %d\n", mIntResult); //error
         return;
         }
     memcpy(&W, &nextIniValD.mIdgt[mIntIndexMax], sizeof(mInt));

     MMS64IniComLP(&SIParaMMS64LP, &W);
     }

/**************/
void MMSIni_setBin32x8(unsigned int *Bin32x8)
     {
     uiLLHL LLHLn;
     mInt  U;

     memset(&U, 0, sizeof(mInt));
     memcpy(&U.mIdgt[mIntIndexMax-7], Bin32x8, sizeof(int)*8);
     //DumpMint(&U, 'u');  //debug
     MMS64IniComLP(&SIParaMMS64LP, &U);
     }

/*******************************************************/

/*********** How to use original MMS64 ************/
#ifdef originalMMS
int mainSample_originalMMS64(void)
    {
    unsigned long long int ranBin64;
    unsigned long long int N, M, L, K;
    unsigned int Bin32x8[8];

    double   ranU01;

    printf("[RAND_name] : %s (= MMS64)\n", RAND_name);
    /****************** MMS64LP *******************/
    printf("======== using MMSIni() and MMS64_getBin64() ========\n");
    printf("MMSIni(0)  // set to generate 0th RN\n");
    N = 0;  MMSIni(N);
    ranBin64=MMS64_getBin64();
    printf("MMS64_getBin64()  %016llx  (= 2549db80 13fc8303)  // 0th RN\n", ranBin64);
    ranBin64=MMS64_getBin64();
    printf("MMS64_getBin64()  %016llx  (= 8b4b011c 79312836)  // 1st RN\n", ranBin64);
    ranBin64=MMS64_getBin64();
    printf("MMS64_getBin64()  %016llx  (= e1a2d4f0 c2625b32)  // 2nd RN\n", ranBin64);
    ranBin64=MMS64_getBin64();
    printf("MMS64_getBin64()  %016llx  (= 8d9e8f81 819305cb)  // 3rd RN\n\n", ranBin64);

    printf("MMSIni(202)  // set to generate 202-th RN\n");
    N = 202;  MMSIni(N);
    ranBin64=MMS64_getBin64(); 
    printf("MMS64_getBin64()  %016llx  (= e619c76f af442894)  // 202_th RN\n\n", ranBin64);

  ////////////////////////

    printf("\n======== using MMS64_getU01() ========\n");
    printf("MMSIni(0)  // set to generate 0th RN\n");
    MMSIni(0);
    ranU01=MMS64_getU01();
    printf("MMS64_getU01()  %12.10f  (= 0.1456582248)  // 0th RN\n", ranU01);
    ranU01=MMS64_getU01();
    printf("MMS64_getU01()  %12.10f  (= 0.5441132254)  // 1st RN\n", ranU01);
    ranU01=MMS64_getU01();
    printf("MMS64_getU01()  %12.10f  (= 0.8813908661)  // 2nd RN\n", ranU01);
    ranU01=MMS64_getU01();
    printf("MMS64_getU01()  %12.10f  (= 0.5532006923)  // 3rd RN\n\n", ranU01);

  ////////////////////////

    printf("======== using MMSIni_setNM() ========\n");
    N = 101;  M = 2;
    printf("  N = 101; M = 2\n");
    printf("MMSIni_setNM(N,M)  // set to generate N*M_th RN\n");
    MMSIni_setNM(N,M);
    ranBin64=MMS64_getBin64(); 
    printf("MMS64_getBin64()  %016llx  (= e619c76f af442894)  // 101*2_th RN\n\n", ranBin64);

  ////////////////////////

    printf("======== using MMSIni_setNMplusL() ========\n");
    N = 50;  M = 4;  L = 2;
    printf("  N = 50; M = 4; L = 2\n");
    printf("MMSIni_setNMplusL(N,M,L)  // set to generate N*M+L_th RN\n");
    MMSIni_setNMplusL(N,M,L);
    ranBin64=MMS64_getBin64(); 
    printf("MMS64_getBin64()  %016llx  (= e619c76f af442894)  // 50*4+2_th RN\n", ranBin64);

    return(0);
    }
#endif

/*******************************************************/

/*********** How to use MMS64LP **************************/
#ifndef originalMMS
int mainSample_MMS64LP(void)
    {
    unsigned long long int ranBin64;
    unsigned long long int N, M, L, K;
    unsigned int Bin32x8[8];

    double   ranU01;

    printf("[RAND_name] : %s (=MMS64LP)\n", RAND_name);

    /****************** MMS64LP *******************/
    printf("======== using MMSIni() and MMS64LP_getBin64() ========\n");
    printf("MMSIni(0)  // set to generate 0th RN\n");
    N = 0;  MMSIni(N);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64();
    printf("MMS64LP_getBin64()  %016llx  (= 2549db80 13fc8303)  // 0th RN\n", ranBin64);
    ranBin64=MMS64LP_getBin64();
    printf("MMS64LP_getBin64()  %016llx  (= 0e5b563b c3f478ef)  // 1st RN\n", ranBin64);
    ranBin64=MMS64LP_getBin64();
    printf("MMS64LP_getBin64()  %016llx  (= 94b7e929 a96480a3)  // 2nd RN\n", ranBin64);
    //MMSshowRkSkLP(); //debug
    ranBin64=MMS64LP_getBin64();
    printf("MMS64LP_getBin64()  %016llx  (= c8b2fa4e 9adefdb5)  // 3rd RN\n\n", ranBin64);
    //show_MMS_RN_counter();  //debug
    printf("MMSIni(202)  // set to generate 202-th RN\n");
    N = 202;  MMSIni(N);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= 675475cc f3be8e0c)  // 202_th RN\n\n", ranBin64);
    //show_MMS_RN_counter();  //debug

  ////////////////////////

    printf("\n======== using MMS64LP_getU01() ========\n");
    printf("MMSIni(0)  // set to generate 0th RN\n");
    MMSIni(0);
    ranU01=MMS64LP_getU01();
    printf("MMS64LP_getU01()  %12.10f  (= 0.1456582248)  // 0th RN\n", ranU01);
    ranU01=MMS64LP_getU01();
    printf("MMS64LP_getU01()  %12.10f  (= 0.0560811897)  // 1st RN\n", ranU01);
    ranU01=MMS64LP_getU01();
    printf("MMS64LP_getU01()  %12.10f  (= 0.5809312560)  // 2nd RN\n", ranU01);
    ranU01=MMS64LP_getU01();
    printf("MMS64LP_getU01()  %12.10f  (= 0.7839809839)  // 3rd RN\n\n", ranU01);
    //show_MMS_RN_counter();  //debug

  ////////////////////////

    printf("\n======== using MMSIni_setNM() ========\n");
    N = 101;  M = 2;
    printf("  N = 101; M = 2\n");
    printf("MMSIni_setNM(N,M)  // set to generate N*M_th RN\n");
    MMSIni_setNM(N,M);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= 675475cc f3be8e0c)  // 101*2_th RN\n\n", ranBin64);

  ////////////////////////

    printf("======== using MMSIni_setNMplusL() ========\n");
    N = 50;  M = 4;  L = 2;
    printf("  N = 50; M = 4; L = 2\n");
    printf("MMSIni_setNMplusL(N,M,L)  // set to generate N*M+L_th RN\n");
    MMSIni_setNMplusL(N,M,L);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= 675475cc f3be8e0c)  // 50*4+2_th RN\n\n", ranBin64);

  ////////////////////////

    printf("\n======== using MMSIni_setNMLK() ========\n");
    N=0x8000000000000001; M=N; L=N; K=N;
    printf("  N = M = L = K = 0x8000000000000001\n");
    printf("MMSIni_setNMLK(N,M,L,K)  // set to generate NxMxLxK-th RN\n");
    MMSIni_setNMLK(N,M,L,K);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= 8ef8a094 afc1f818)  // NxMxLxK-th RN\n", ranBin64);
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= 8546d6bb 6528fd23)  // next RN\n", ranBin64);
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= c6facea1 8145868b)  // next RN\n", ranBin64);
    //show_MMS_RN_counter();  //debug

  ////////////////////////

    printf("\n======== using MMSIni_setNMLK() and MMSIni_plusNMLK() ========\n");
    N=0x8000000000000001; M=N; L=N; K=5;
    printf("  N = M = L = 0x8000000000000001,  k = 5\n");
    printf("MMSIni_setNMLK(N,M,L,5)  // set to generate NxMxLx5-th RN\n");
    MMSIni_setNMLK(N,M,L,K);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= ed68fc67 1dd34d27)  // \n", ranBin64);

    N=0x8000000000000001; M=N; L=N; K=3;
    printf("\n  N = M = L = 0x8000000000000001,  k = 3\n");
    printf("MMSIni_setNMLK(N,M,L,3)  // set to generate NxMxLx3-th RN\n");
    MMSIni_setNMLK(N,M,L,K);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= 3aca75d8 68b7bce8)  // \n", ranBin64);

    N=0x8000000000000001; M=N; L=N; K=2;
    printf("\n  N = M = L = 0x8000000000000001,  k = 2\n");
    printf("MMSIni_plusNMLK(N,M,L,2)  // set to generate (previous MMSIni_** No)+NxMxLx2-th RN\n");
    MMSIni_plusNMLK(N,M,L,K);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= ed68fc67 1dd34d27)  // = NxMxLx5-th RN\n", ranBin64);

  ////////////////////////

    printf("\n======== using MMSIni_setBin32x8() ========\n");
    memset(&Bin32x8, 0, sizeof(Bin32x8));
    Bin32x8[0] = 0xffffffff;
    Bin32x8[7] = 0x11111111;
    printf("  Bin32x8[0]=0xffffffff; Bin32x8[1]...[6]=0; Bin32x8[7] = 0x11111111;\n");
    printf("MMSIni_setBin32x8(Bin32x8)  // set to generate ffffffff0000...000011111111-th RN\n");
    MMSIni_setBin32x8(Bin32x8);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= a44d9790 2d4cb5da)  // \n", ranBin64);

    Bin32x8[7] = 0x11111110;
    printf("\n  Bin32x8[0]=0xffffffff; Bin32x8[1]...[6]=0; Bin32x8[7] = 0x11111110;\n");
    printf("MMSIni_setBin32x8(Bin32x8)  // set to generate ffffffff0000...000011111110-th RN\n");
    MMSIni_setBin32x8(Bin32x8);
    //show_MMS64LP_Ini_InitialNo();  //debug
    ranBin64=MMS64LP_getBin64(); 
    printf("MMS64LP_getBin64()  %016llx  (= 4b8dd729 9e5a30de)  // \n", ranBin64);

    printf("\n  [Next RN is ffffffff0000...000011111111-th RN]\n");
    ranBin64=MMS64LP_getBin64();
    printf("MMS64LP_getBin64()  %016llx  (= a44d9790 2d4cb5da)  // \n", ranBin64);

    return(0);
    }
#endif

//*********************************//

#ifdef HowToUseMMS64LP
int main()
    {

  #ifndef originalMMS
    mainSample_MMS64LP();
   #else
    mainSample_originalMMS64();
  #endif

    return(0);
    }
#endif

///////// NOTE //////////////////////////////////////////
// The code above is not so refined; and
//    should be tested by many users.
// If you find bugs, please mail to
//    hiroshimayaguchi at-mark yahoo.co.jp .
// (At that time, include the code-name (such as
//   KUNIKOsan-20260120) in the subject of the mail.)
//
// MMS64LP RNG : Last updated at 2026.01.20
//      (Code Name : KUNIKOsan-20260120)
// This NOTE : Last updated at 2026.01.20
/////////////////////////////////////////////////////////
