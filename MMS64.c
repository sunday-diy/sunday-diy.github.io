//////////////////////////////////////////////////////////////
//   This is MMS64 random number generator at 2025.09.26    //
//   Use the complier gcc.                                  //
//   MMS64 is an academic product.                          //
//   Use MMS64 within your responsibility.                  //
//////////////////////////////////////////////////////////////
// Period is  (p=2^63-25)x(q=2^63-165)

/*** Remove // in the next line to test this code ***/

//#define HowToUseMMS64


#include <stdio.h>
#include <memory.h>

#define RAND_name "MMS64"

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
    unsigned long long int r; unsigned long long int s;
    unsigned long long int rk; unsigned long long int sk;
    unsigned long long int XpBase; unsigned long long int XqBase;
    unsigned long long int w0; unsigned long long int v0;
    uiLLHL wkLL; uiLLHL vkLL;
    } SIPara64;
SIPara64 SIParaMMS64Korg =
    {
    0x7fffffffffffffe7,  // p=2^63-25
    0x7fffffffffffff5b,  // q=2^63-165
    0x39F750241C2D5D33,  // r=0x39f750241c2d5d7b-72
    0x32F50FEE9B2A32BB,  // s=0x32f50fee9b2a32d7-28
    0, 0,                // rk, sk
    0xa2cb4411ba257552,  // XpBase  (from 1.e)
    0xa8365eed39e1c070,  // XqBase  (from 1.Pi)(not used)
    0xa2cb4411ba257552,  // w0
    0xa8365eed39e1c070,  // v0
    0, 0               // wkLL, vkLL
    };
SIPara64 SIParaMMS64K =
    {
    0x7fffffffffffffe7,  // p=2^63-25
    0x7fffffffffffff5b,  // q=2^63-165
    0x39F750241C2D5D33,  // r=0x39f750241c2d5d7b-72
    0x32F50FEE9B2A32BB,  // s=0x32f50fee9b2a32d7-28
    0, 0,                // rk, sk
    0xa2cb4411ba257552,  // XpBase
    0xa8365eed39e1c070,  // XqBase
    0xa2cb4411ba257552,  // w0
    0xa8365eed39e1c070,  // v0
    0, 0               // wkLL, vkLL
    };
/********** for multiple-Integer computation ***********/
#define  mIntBase       0x100000000
#define  mIntBaseM1     0x0ffffffff
#define  mIntBaseBits   32
#define  mIntIntSize    6
#define  mIntIndexMin   1
#define  mIntIndexMax   5
typedef struct  {unsigned int mIdgt[mIntIntSize];} mInt;
typedef struct  {unsigned int mIdgt[1+mIntIndexMax*2];} mIntD;

void DumpMint(mInt *M, char c);
void DumpMintD(mIntD *MD, char c);
int mIntADD_HL(mIntD *UD, mIntD *VD, mIntD *UVD);
int mIntSUB_HL(mIntD *UD, mIntD *VD, mIntD *WD);
int mIntMUL_HL(mInt *U, mInt *V, mIntD *UVD);
int mIntDIVs_HL(mInt *V, mIntD *QD, mIntD *RD);
int mIntDIV_HL(mIntD *UD, mInt *Vcl, mIntD *QD, mIntD *RD);
/*******************************************************/

/*=======================================*/
typedef struct 
    {
    unsigned long long lo64;
    unsigned long long hi64;
    } my_i128;
/*=======================================*/

/**************/
void MMS64plusRS(SIPara64 *SIParaL)
    {
    SIParaL->rk += SIParaL->r;
    if (SIParaL->rk >= SIParaL->p) {SIParaL->rk -= SIParaL->p;}
    SIParaL->sk += SIParaL->s;
    if (SIParaL->sk >= SIParaL->q) {SIParaL->sk -= SIParaL->q;}
    }

//********************************
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
//*********************************//
unsigned long long int SSI64Ksc_A_MMS(SIPara64 *SIParaL) 
    {
    int    i;
    uiLLHL  WLL1, XLL1, WLL1_Wk;
    uiLLHL  WLL2, XLL2, WLL2_Wk;
    my_i128 u, v, umv;

    XLL1.I = SIParaL->XpBase;
    XLL1.I ^= (SIParaL->rk);
	//printf("XLL1.I = %9.2f\n", XLL1.I);  // debug

    XLL2.I = SIParaL->XpBase;
    XLL2.I ^= (SIParaL->sk);
	//printf("XLL2.I = %9.2f\n", XLL2.I);  // debug

    MMS_X64_X64(u, XLL1.I, XLL2.I);

    return(u.hi64);
    }

//*********************************//
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

       if(c != 0)  // Ex. in radix 10  u=8640  v=433,  q^=20  --> q=19
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
void SSI64IniValidityCheck(mIntD *UD, mInt *Vcl, mIntD *QD, mIntD *RD, char ChkId)
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
        printf("Validity-Error detected by SSI64IniValidityCheck() [%ck, err#=%d]\n", ChkId, err);
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
void MMS64IniCom(SIPara64 *SIParaL, mInt *N)
     {
     mInt  U, V, Vcl;
     mIntD UVD, QD, RD;
     int   c, mIntResult;
     uiLLHL LLHLn, LLHLwk;

     memcpy(&U, N, sizeof(mInt));

     memset(&V, 0, sizeof(mInt));
     memset(&Vcl, 0, sizeof(mInt));
     memset(&UVD, 0, sizeof(mIntD));
     memset(&QD, 0, sizeof(mIntD));
     memset(&RD, 0, sizeof(mIntD));

     LLHLwk.I = SIParaL->r;  
     V.mIdgt[mIntIndexMax-1] = LLHLwk.HL.H;
     V.mIdgt[mIntIndexMax] = LLHLwk.HL.L;
     mIntResult = mIntMUL_HL(&U, &V, &UVD);
     if (mIntResult != 0)
         {
         printf("mIntMUL_HL(n*r) != 0 : %d\n", mIntResult); //error
         DumpMint(&U, 'U');
         DumpMint(&V, 'V');
         DumpMintD(&UVD, 'm');
         return;
         }
     LLHLwk.I = SIParaL->p;  
     Vcl.mIdgt[mIntIndexMax-1] = LLHLwk.HL.H;
     Vcl.mIdgt[mIntIndexMax] = LLHLwk.HL.L;
     mIntResult = mIntDIV_HL(&UVD, &Vcl, &QD, &RD);
     if (mIntResult != 0)
         {
         printf("mIntDIVL_HL(n*r) != 0 : %d\n", mIntResult); //error
         DumpMintD(&UVD, 'U');
         DumpMint(&Vcl, 'V');
         DumpMintD(&QD, 'Q');
         DumpMintD(&RD, 'R');
         return;
         }
     SSI64IniValidityCheck(&UVD, &Vcl, &QD, &RD, 'r');
     LLHLwk.HL.H = RD.mIdgt[mIntIndexMax*2-1];
     LLHLwk.HL.L = RD.mIdgt[mIntIndexMax*2];
     SIParaL->rk = LLHLwk.I;   // set rk

     LLHLwk.I = SIParaL->s;  
     V.mIdgt[mIntIndexMax-1] = LLHLwk.HL.H;
     V.mIdgt[mIntIndexMax] = LLHLwk.HL.L;
     mIntResult = mIntMUL_HL(&U, &V, &UVD);
     if (mIntResult != 0)
         {
         printf("mIntMUL_HL(n*s) != 0 : %d\n", mIntResult); //error
         DumpMint(&U, 'U');      
         DumpMint(&V, 'V');      
         DumpMintD(&UVD, 'm');   
         return;
         }
     LLHLwk.I = SIParaL->q;  
     Vcl.mIdgt[mIntIndexMax-1] = LLHLwk.HL.H;
     Vcl.mIdgt[mIntIndexMax] = LLHLwk.HL.L;
     mIntResult = mIntDIV_HL(&UVD, &Vcl, &QD, &RD);
     if (mIntResult != 0)
         {
         printf("mIntDIVL_HL(n*s) != 0 : %d\n", mIntResult); //error
         DumpMintD(&UVD, 'U');
         DumpMint(&Vcl, 'V');
         DumpMintD(&QD, 'Q');
         DumpMintD(&RD, 'R');
         return;
         }
     SSI64IniValidityCheck(&UVD, &Vcl, &QD, &RD, 's');
     LLHLwk.HL.H = RD.mIdgt[mIntIndexMax*2-1];
     LLHLwk.HL.L = RD.mIdgt[mIntIndexMax*2];
     SIParaL->sk = LLHLwk.I;
     }

/**************/
void MMS64Ini(unsigned long long int n)
     {
     uiLLHL LLHLn;
     mInt  U;

     memset(&U, 0, sizeof(mInt));
     LLHLn.I =n;  
     U.mIdgt[mIntIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntIndexMax] = LLHLn.HL.L;

     MMS64IniCom(&SIParaMMS64K, &U);
     }

/**************/
void MMS64IniNM(unsigned long long int n, 
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
         printf("mIntMUL_HL(nmr1) != 0 : %d\n", mIntResult); //error
         DumpMint(&U, 'U');
         DumpMint(&V, 'V');
         DumpMintD(&UVD, 'm');
         return;
         }
     memcpy(&U, &UVD.mIdgt[mIntIndexMax], sizeof(mInt));

     MMS64IniCom(&SIParaMMS64K, &U);
     }

/**************/
void MMS64IniNML(unsigned long long int n, 
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
         printf("mIntMUL_HL(nmr1) != 0 : %d\n", mIntResult); //error
         DumpMint(&U, 'U');
         DumpMint(&V, 'V');
         DumpMintD(&UVD, 'm');
         return;
         }
     LLHLn.I = l;  
     UD.mIdgt[mIntIndexMax*2-1] = LLHLn.HL.H;
     UD.mIdgt[mIntIndexMax*2] = LLHLn.HL.L;
     mIntResult = mIntADD_HL(&UD, &UVD, &UVD2);
     if (mIntResult != 0)
         {
         printf("mIntADD_HL != 0 : %d\n", mIntResult); //error
         DumpMintD(&UD, 'U');
         DumpMintD(&UVD, 'V');
         DumpMintD(&UVD2, 'A');
         return;
         }
     memcpy(&U, &UVD2.mIdgt[mIntIndexMax], sizeof(mInt));

     MMS64IniCom(&SIParaMMS64K, &U);
     }

/*******************************************************/
/**************/
unsigned long long int MMS64_Bin64(void)
    {
    unsigned long long int RanBits;
    RanBits=SSI64Ksc_A_MMS(&SIParaMMS64K);
    MMS64plusRS(&SIParaMMS64K);
    return(RanBits);
    }
/**************/
double MMS64_U01(void)
    {
    uiLLHL_Dbl MMS64Dbl;
    MMS64Dbl.I=SSI64Ksc_A_MMS(&SIParaMMS64K);
    MMS64plusRS(&SIParaMMS64K);
    MMS64Dbl.I >>= 12;
    MMS64Dbl.I |= 0x3ff0000000000000;     /*set exponent 2^0*/
    return(MMS64Dbl.Dbl-1);
    }

/*********** How to use MMS64 **************************/
int mainSample_MMS(void)
    {
    unsigned long long int ranBin64;
    unsigned long long int n, m, l;
    double   ranU01;

    /****************** MMS64 *******************/
    printf("======== using MMS64_Bin64() ========\n");
    printf("MMS64Ini(0)  // set to generate 1st RN\n");
    MMS64Ini(0);
    ranBin64=MMS64_Bin64();                 //the 1st random number
    printf("MMS64_Bin64()  %016llx  (= 2549db8013fc8303)  // 1st RN\n", ranBin64);
    ranBin64=MMS64_Bin64();                 //the 2nd random number
    printf("MMS64_Bin64()  %016llx  (= 8b4b011c79312836)  // 2nd RN\n", ranBin64);
    ranBin64=MMS64_Bin64();                 //the 3rd random number
    printf("MMS64_Bin64()  %016llx  (= e1a2d4f0c2625b32)  // 3rd RN\n", ranBin64);
    ranBin64=MMS64_Bin64();                 //the 4th random number
    printf("MMS64_Bin64()  %016llx  (= 8d9e8f81819305cb)  // 4th RN\n\n", ranBin64);

	printf("MMS64Ini(202)  // set to generate 202-th RN\n");
	MMS64Ini(202);
    ranBin64=MMS64_Bin64(); 
    printf("MMS64_Bin64()  %016llx  (= e619c76faf442894)  // 202_th RN\n", ranBin64);

	printf("\nMMS64IniNM(101,2)  // set to generate N*M_th RN\n");
	MMS64IniNM(101,2);
    ranBin64=MMS64_Bin64(); 
    printf("MMS64_Bin64()  %016llx  (= e619c76faf442894)  // 101*2_th RN\n", ranBin64);

	printf("\nMMS64IniNML(50,4,2)  // set to generate N*M+L_th RN\n");
	MMS64IniNML(50,4,2);
    ranBin64=MMS64_Bin64(); 
    printf("MMS64_Bin64()  %016llx  (= e619c76faf442894)  // 50*4+2_th RN\n", ranBin64);

  ////////////////////////

    printf("\n======== using MMS64_U01() ========\n");
    printf("MMS64Ini(0)  // set to generate 1st RN\n");
    MMS64Ini(0);
    ranU01=MMS64_U01();                 //the 1st random number
    printf("MMS64_U01()  %12.10f  (= 0.1456582248)  // 1st RN\n", ranU01);
    ranU01=MMS64_U01();                 //the 2nd random number
    printf("MMS64_U01()  %12.10f  (= 0.5441132254)  // 2nd RN\n", ranU01);
    ranU01=MMS64_U01();                 //the 3rd random number
    printf("MMS64_U01()  %12.10f  (= 0.8813908661)  // 3rd RN\n", ranU01);
    ranU01=MMS64_U01();                 //the 4th random number
    printf("MMS64_U01()  %12.10f  (= 0.5532006923)  // 4th RN\n\n", ranU01);

    return(0);
    }

//*********************************//

#ifdef HowToUseMMS64
int main()
    {
    mainSample_MMS();
    return(0);
    }
#endif
