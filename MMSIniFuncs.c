//////////////////////////////////////////////////////////
//   This is MMSIniFuncs.c at 2026.01.19.               //
//      ([Code-Name:'TORANOSUKE-20260119']).            //
//   Use the compiler gcc.                              //
//   This module is an academic product.                //
//   Use this module within your responsibility.        //
//////////////////////////////////////////////////////////
//   This MMSIniFuncs.c is included by MMMnnnW.c.

#include <stdio.h>
#include <memory.h>

//------------------------------------------------------------//

// Remove // below if you want to test this module.

//#define testMMSIni   // main() in this module will be used 

//------------------------------------------------------------//

typedef struct
    {
    unsigned int L;
    unsigned int H;
    } uiHLHB;
typedef union
    {
    unsigned long long int I;
    uiHLHB HL;
    } uiLLHLHB;

/**************/
#ifdef testMMSIni

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

#endif

/********** for multiple-Integer computation ***********/
#define  mIntHBBase       0x100000000
#define  mIntHBBaseM1     0x0ffffffff
#define  mIntHBBaseBits   32
#define  mIntHBIntSize    10
#define  mIntHBIndexMin   1
#define  mIntHBIndexMax   9
typedef struct  {unsigned int mIdgt[mIntHBIntSize];} mIntHB;
typedef struct  {unsigned int mIdgt[1+mIntHBIndexMax*2];} mIntHBD;

void DumpMintHB(mIntHB *M, char c);
void DumpMintHBD(mIntHBD *MD, char c);
int mIntHBADD_HL(mIntHBD *UD, mIntHBD *VD, mIntHBD *UVD);
int mIntHBSUB_HL(mIntHBD *UD, mIntHBD *VD, mIntHBD *WD);
int mIntHBMUL_HL(mIntHB *U, mIntHB *V, mIntHBD *UVD);
int mIntHBDIVs_HL(mIntHB *V, mIntHBD *QD, mIntHBD *RD);
int mIntHBDIV_HL(mIntHBD *UD, mIntHB *Vcl, mIntHBD *QD, mIntHBD *RD);
/*******************************************************/

mIntHB MMS64LP_Ini_InitialNo;   // the number given or determined by
    //  MMSIni(), MMSIni_setNM(), MMSIni_setNMplusL(),
    //  MMSIni_setNMLK(), MMSIni_plusNMLK(), MMSIni_setBin32x8()

void show_MMS64LP_Ini_InitialNo(void)
    {
    int  i;
    printf("\nMMS64LP_Ini_InitialNo is\n");
    for (i=mIntHBIndexMin-1; i<=mIntHBIndexMax; i++)
        {printf("%08x ", MMS64LP_Ini_InitialNo.mIdgt[i]);}
    printf("\n");
    }

/*===============================================================*/
/******** to debug mIntHB ********/
void DumpMintHB(mIntHB *M, char c)
    {
    int  i;
    printf("%c ", c);
    for (i=mIntHBIndexMin-1; i<=mIntHBIndexMax; i++)
        {printf("%08x ", M->mIdgt[i]);}
    printf("\n");
    }
	
void DumpMintHBD(mIntHBD *MD, char c)
    {
    int  i;
    printf("%c ", c);
    for (i=mIntHBIndexMin-1; i<=mIntHBIndexMax*2; i++)
        {printf("%08x ", MD->mIdgt[i]);}
    printf("\n");
    }

/*===============================================================*/
int mIntHBMUL_HL(mIntHB *U, mIntHB *V, mIntHBD *UVD)
    {
    uiLLHLHB LLHLu, LLHLv, LLHLw;
    int i, j, iPj;
    unsigned long long int c, uv;
    uiLLHLHB LLMulAddWk;

    if (U->mIdgt[mIntHBIndexMin-1] != 0) {return(1);}
    if (V->mIdgt[mIntHBIndexMin-1] != 0) {return(2);}

    memset(UVD, 0, sizeof(mIntHBD));

    LLHLu.I = 0;
    LLHLv.I = 0;
    LLHLw.I = 0;

    for (j=mIntHBIndexMax; j>=mIntHBIndexMin; j--)       /* V */
        {
        if (V->mIdgt[j] == 0)
            {
            UVD->mIdgt[j] = 0;
            continue;
            }

        c=0;
        LLHLv.HL.L = V->mIdgt[j];
        for (i=mIntHBIndexMax; i>=mIntHBIndexMin; i--)   /* U */
            {
            iPj = i+j;
            LLHLu.HL.L = U->mIdgt[i];
            uv = LLHLv.I * LLHLu.I;   /* u*v */
            LLMulAddWk.I = (uv & mIntHBBaseM1);
            LLHLw.HL.L = UVD->mIdgt[iPj];
            LLMulAddWk.I += LLHLw.I;
            LLMulAddWk.I += c;
            UVD->mIdgt[iPj] = LLMulAddWk.HL.L;
            c = (uv >> mIntHBBaseBits);
            c += (LLMulAddWk.I >> mIntHBBaseBits);
            }
        UVD->mIdgt[j] = (unsigned int)c;
        }
    return(0);
    }
/*===============================================================*/
int mIntHBSUB_HL(mIntHBD *UD, mIntHBD *VD, mIntHBD *WD)
    {
    uiLLHLHB LLsubWk, LLHLu, LLHLv;
    int j;

    if (UD->mIdgt[mIntHBIndexMin-1] != 0) {return(1);}
    if (VD->mIdgt[mIntHBIndexMin-1] != 0) {return(2);}

    LLsubWk.I = 0;
    LLHLu.I = 0;
    LLHLv.I = 0;
    for (j=mIntHBIndexMax*2; j>=mIntHBIndexMin; j--)
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

    WD->mIdgt[mIntHBIndexMin-1] = LLsubWk.HL.L;
    return(0);
    }
/*===============================================================*/
int mIntHBADD_HL(mIntHBD *UD, mIntHBD *VD, mIntHBD *WD)
    {
    uiLLHLHB LLaddWk, LLHLu, LLHLv;
    int j;

    if (UD->mIdgt[mIntHBIndexMin-1] != 0) {return(1);}
    if (VD->mIdgt[mIntHBIndexMin-1] != 0) {return(2);}

    LLaddWk.I = 0;
    LLHLu.I = 0;
    LLHLv.I = 0;
    for (j=mIntHBIndexMax*2; j>=mIntHBIndexMin; j--)
        {
        LLHLu.HL.L = UD->mIdgt[j];
        LLaddWk.I += LLHLu.I;
        LLHLv.HL.L = VD->mIdgt[j];
        LLaddWk.I += LLHLv.I;
        WD->mIdgt[j] = LLaddWk.HL.L;
        LLaddWk.I>>=mIntHBBaseBits;
        }

    WD->mIdgt[mIntHBIndexMin-1] = LLaddWk.HL.H;
    return(0);
    }
/*===============================================================*/
int mIntHBDIVs_HL(mIntHB *V, mIntHBD *QD, mIntHBD *RD)
    {
    unsigned long long int Dv, rbPr;
    int  j;

    // Situation  is   VleftPos=mIntHBIndexMax;

    Dv = V->mIdgt[mIntHBIndexMax];
    /* U is copied in R by mIntHBDIV() */

    QD->mIdgt[mIntHBIndexMin-1] = 0;
    for(j=mIntHBIndexMin-1; j<mIntHBIndexMax*2; j++)   /* R */
        {
        rbPr = (unsigned long long int)(RD->mIdgt[j]*mIntHBBase + RD->mIdgt[j+1]);
        RD->mIdgt[j] = 0;
        QD->mIdgt[j+1] = (unsigned int)(rbPr / Dv);
        RD->mIdgt[j+1] = (unsigned int)(rbPr % Dv);
        }

    return(0);
    }

/****************/
int mIntHBDIV_HL(mIntHBD *UD, mIntHB *Vcl, mIntHBD *QD, mIntHBD *RD)
    {
    uiLLHLHB IHLu, IHLv;
    mIntHB V;
    int i, j, iPj, D, M;
    int VleftPos;
    unsigned long long int vq, vqL, c;
    unsigned long long int rbPr, QHAT, RHAT, LHS, RHS;
    uiLLHLHB MulSubWk;

    if (UD->mIdgt[mIntHBIndexMin-1] != 0) {return(1);}
    if (Vcl->mIdgt[mIntHBIndexMin-1] != 0) {return(2);}

    VleftPos=1;
    for (j=mIntHBIndexMin; j<=mIntHBIndexMax; j++)    /* Vcl */
        {
        if(Vcl->mIdgt[j] == 0)
           { VleftPos ++; }
         else
           { break; }
        }

    if (VleftPos > mIntHBIndexMax) {return(3);}

    memcpy(&V, Vcl, sizeof(mIntHB));
    memcpy(RD, UD, sizeof(mIntHBD));
    memset(QD, 0, sizeof(mIntHBD));

    if (VleftPos == mIntHBIndexMax) {return(mIntHBDIVs_HL(Vcl, QD, RD));}
                                     /* U is copied in R */

    /* normalization */
    RD->mIdgt[mIntHBIndexMin-1] = 0;
    V.mIdgt[VleftPos-1] = 0;
    if((V.mIdgt[VleftPos] >> (mIntHBBaseBits/2)) == 0)
        {
        D = mIntHBBaseBits/2 ;
        for(i=VleftPos; i<mIntHBIndexMax; i++)
            {
            V.mIdgt[i] = (unsigned int)((V.mIdgt[i]<<D) | (V.mIdgt[i+1]>>D));
            }
        V.mIdgt[mIntHBIndexMax]<<=D;
        for(i=mIntHBIndexMin-1; i<mIntHBIndexMax*2; i++)
            {
            RD->mIdgt[i] = (unsigned int)((RD->mIdgt[i]<<D) | (RD->mIdgt[i+1]>>D));
            }
        RD->mIdgt[mIntHBIndexMax*2]<<=D;
        }
      else
        {
        D = 0;
        }
    
    M = VleftPos - mIntHBIndexMin;  /* M >= 0 */

    for(j=0; j<=M+mIntHBIndexMax; j++)   /* R */
        {
        /* determine QHAT */
        rbPr = (unsigned long long int)
               (RD->mIdgt[mIntHBIndexMin-1+j]*mIntHBBase + RD->mIdgt[mIntHBIndexMin+j]);
        if (RD->mIdgt[mIntHBIndexMin-1+j] >= V.mIdgt[VleftPos])
            {QHAT = mIntHBBaseM1;}
          else
            {QHAT = (unsigned long long int)(rbPr / V.mIdgt[VleftPos]);}
        while (1)
            {
            RHAT = (unsigned long long int)(rbPr - QHAT * V.mIdgt[VleftPos]);
            LHS = (unsigned long long int)(V.mIdgt[VleftPos+1] * QHAT);
            if (RHAT>=mIntHBBase) {break;}   // if carry happens in the next
            RHS = (unsigned long long int)
                  ((RHAT<<mIntHBBaseBits) + RD->mIdgt[mIntHBIndexMin-1+j+2]);

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
        for(i=mIntHBIndexMax; i>=VleftPos-1; i--)  /* V */
           {
           iPj = i+j-M;   //iPj = i-(VleftPos-1)+j+(mIntHBIndexMin-1);
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
           c = (unsigned long long int)(vq >> mIntHBBaseBits);     /* vqH */
           //printf("(nc)%2x  ", c);
           vqL = (unsigned long long int)(vq & mIntHBBaseM1);
           //printf("(vqL)%4x  ", vqL);
           MulSubWk.I -= vqL;
           //printf("%4x  ", MulSubWk.I);
           RD->mIdgt[iPj] = MulSubWk.HL.L;
           if ((int)MulSubWk.HL.H < 0)
             {
             MulSubWk.HL.L = MulSubWk.HL.H;
             MulSubWk.HL.H = mIntHBBaseM1;
             c -= MulSubWk.I;
            }
           //printf("c=%4x  \n", c);
           }
       QD->mIdgt[mIntHBIndexMax-M+j] = (unsigned int)QHAT;

       if(c != 0)  // Ex. in radix 10  u=8640  v=433,  q=20  --> q=19
           {                           /*  kuwae-gaeshi */
           //printf("kuwae-gaesi c=%16Lx\n", c);
           QD->mIdgt[mIntHBIndexMax-M+j]--;
           MulSubWk.I = 0;
           for(i=mIntHBIndexMax; i>=VleftPos-1; i--)    /* V */
               {
               iPj = i+j-M;
               IHLu.HL.L = RD->mIdgt[iPj];
               MulSubWk.I  += IHLu.I;
               IHLv.HL.L = V.mIdgt[i];
               MulSubWk.I += IHLv.I;
               RD->mIdgt[iPj] = MulSubWk.HL.L;
               MulSubWk.I >>= mIntHBBaseBits;
               }
           }
       }                            /* end of loop j */

    /* adjust remainder */
    if (D != 0)
        {
        for (i=mIntHBIndexMax*2; i>=mIntHBIndexMin; i--)
            {
            RD->mIdgt[i] =
                 (unsigned int)((RD->mIdgt[i]>>D) | (RD->mIdgt[i-1]<<D));
            }
        RD->mIdgt[mIntHBIndexMin-1] >>= D;
        }
    return(0);
    }

/*================================================================*/
/**************/
void MMSIniValidityCheck(mIntHBD *UD, mIntHB *Vcl, mIntHBD *QD, mIntHBD *RD, char ChkId)
    {
    mIntHB   U;
    mIntHBD  UVD, wkD;
    int    i, err=0;
    uiLLHLHB LLHLV, LLHLR;

    memcpy(&U, &QD->mIdgt[mIntHBIndexMax], sizeof(mIntHB));
    U.mIdgt[mIntHBIndexMin-1] = 0;
    mIntHBMUL_HL(&U, Vcl, &UVD);
    mIntHBADD_HL(&UVD, RD, &wkD);
    if (memcmp((char *)&wkD, (char *)UD, sizeof(mIntHBD)) != 0) {err=1;}

    LLHLV.HL.H = Vcl->mIdgt[mIntHBIndexMax-1];
    LLHLV.HL.L = Vcl->mIdgt[mIntHBIndexMax];
    LLHLR.HL.H = RD->mIdgt[mIntHBIndexMax*2-1];
    LLHLR.HL.L = RD->mIdgt[mIntHBIndexMax*2];
    if (LLHLV.I<=LLHLR.I) {err=2;}

    if (err != 0)
        {
        printf("Validity-Error detected by MMSIniValidityCheck() [%ck, err#=%d]\n", ChkId, err);
        printf("\n[UD] ");
        for (i=0; i<=mIntHBIndexMax*2; i++) {printf("%08x ", UD->mIdgt[i]);}
        printf("\n[Vcl]");
        for (i=0; i<=mIntHBIndexMax; i++) {printf("%08x ", Vcl->mIdgt[i]);}
        printf("\n[QD] ");
        for (i=0; i<=mIntHBIndexMax*2; i++) {printf("%08x ", QD->mIdgt[i]);}
        printf("\n[RD] ");
        for (i=0; i<=mIntHBIndexMax*2; i++) {printf("%08x ", RD->mIdgt[i]);}
        printf("\n[UVD]");
        for (i=0; i<=mIntHBIndexMax*2; i++) {printf("%08x ", UVD.mIdgt[i]);}
        printf("\n[wkD]");
        for (i=0; i<=mIntHBIndexMax*2; i++) {printf("%08x ", wkD.mIdgt[i]);}
        printf("\n\nIf your compiler is icc, use the compiler option -O0 and try again.\n\n");
        }
    }

//*********************************//
/**************/
unsigned long long int MMS64IniComLP_sub(unsigned long long int P,  // (P,R)= (p,r), (q,s)
                                         unsigned long long int R)  //     (pp,rr), (qq,ss)
// compute R*(i=MMS64LP_Ini_InitialNo) mod P
     {
     mIntHB   V, Vcl;
     mIntHBD  UVD, QD, RD;
     int   c, mIntResult;
     uiLLHLHB LLHLwk;

     memset(&V, 0, sizeof(mIntHB));
     memset(&Vcl, 0, sizeof(mIntHB));
     memset(&UVD, 0, sizeof(mIntHBD));
     memset(&QD, 0, sizeof(mIntHBD));
     memset(&RD, 0, sizeof(mIntHBD));

     LLHLwk.I = R;  
     V.mIdgt[mIntHBIndexMax-1] = LLHLwk.HL.H;
     V.mIdgt[mIntHBIndexMax] = LLHLwk.HL.L;
     mIntResult = mIntHBMUL_HL(&MMS64LP_Ini_InitialNo, &V, &UVD);  // R*i
     //DumpMintD(&UVD, 'm');  //debug
     if (mIntResult != 0)
         {
         printf("mIntHBMUL_HL(n*r) != 0 : %d\n", mIntResult); //error
         return(-1);
         }

     LLHLwk.I = P;  
     Vcl.mIdgt[mIntHBIndexMax-1] = LLHLwk.HL.H;
     Vcl.mIdgt[mIntHBIndexMax] = LLHLwk.HL.L;
     mIntResult = mIntHBDIV_HL(&UVD, &Vcl, &QD, &RD);  // R*i mod p
     //DumpMintD(&QD, 'Q');  //debug
     //DumpMintD(&RD, 'R');  //debug
     if (mIntResult != 0)
         {
         printf("mIntHBDIV_HL(UVD/p) != 0 : %d\n", mIntResult); //error
         return(-2);
         }
     MMSIniValidityCheck(&UVD, &Vcl, &QD, &RD, 'r');

     LLHLwk.HL.H = RD.mIdgt[mIntHBIndexMax*2-1];
     LLHLwk.HL.L = RD.mIdgt[mIntHBIndexMax*2];
     return(LLHLwk.I);   // return r*i mod p
     }

/**************/
void MMS64IniComLP(MMSParaLP *SIParaLLP, mIntHB *N)
// compute rk(P_i), sk(Q_i), rrk((PP)_i) and ssk((QQ)_i) 
//      which correspond to the initialize-number N(=i)
     {
     memcpy(&MMS64LP_Ini_InitialNo, N, sizeof(mIntHB));  //copy N as i

     SIParaLLP->rk = MMS64IniComLP_sub(SIParaLLP->p, SIParaLLP->r);
     // P_i = r*i mod p
	 //MMSPrintRkSkLP();	//debug 

     SIParaLLP->sk = MMS64IniComLP_sub(SIParaLLP->q, SIParaLLP->s);
     // Q_i = s*i mod q
	 //MMSPrintRkSkLP();	//debug 

     SIParaLLP->rrk = MMS64IniComLP_sub(SIParaLLP->pp, SIParaLLP->rr);
     // (PP)_i =rr*i mod pp
	 //MMSPrintRkSkLP();	//debug
 
     SIParaLLP->ssk = MMS64IniComLP_sub(SIParaLLP->qq, SIParaLLP->ss);
     // (QQ)_i =ss*i mod qq
	 //MMSPrintRkSkLP();	//debug 

  #ifndef testMMSIni
     clear_MMS_RN_counter();
  #endif
     }

/**************/
void MMSIni(unsigned long long int n)
     {
     uiLLHLHB LLHLn;
     mIntHB  U;

     memset(&U, 0, sizeof(mIntHB));
     LLHLn.I =n;  
     U.mIdgt[mIntHBIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntHBIndexMax] = LLHLn.HL.L;

     MMS64IniComLP(&MMSWParaLP, &U);
     }

/**************/
void MMSIni_setNM(unsigned long long int n, 
                                   unsigned long long int m)
     {
     uiLLHLHB LLHLn;
     mIntHB  U, V;
     mIntHBD UVD;
     int   mIntHBResult;

     memset(&U, 0, sizeof(mIntHB));
     memset(&V, 0, sizeof(mIntHB));
     memset(&UVD, 0, sizeof(mIntHBD));

     LLHLn.I = n;  
     U.mIdgt[mIntHBIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntHBIndexMax] = LLHLn.HL.L;
     LLHLn.I = m;  
     V.mIdgt[mIntHBIndexMax-1] = LLHLn.HL.H;
     V.mIdgt[mIntHBIndexMax] = LLHLn.HL.L;
     mIntHBResult = mIntHBMUL_HL(&U, &V, &UVD);
     if (mIntHBResult != 0)
         {
         printf("mIntHBMUL_HL(setNM) != 0 : %d\n", mIntHBResult); //error
         return;
         }
     memcpy(&U, &UVD.mIdgt[mIntHBIndexMax], sizeof(mIntHB));

     MMS64IniComLP(&MMSWParaLP, &U);
     }

/**************/
void MMSIni_setNMplusL(unsigned long long int n, 
                  unsigned long long int m, unsigned long long int l)
     {
     uiLLHLHB LLHLn;
     mIntHB  U, V;
     mIntHBD UVD;
     int   mIntResult;
     mIntHBD UD, UVD2;

     memset(&U, 0, sizeof(mIntHB));
     memset(&V, 0, sizeof(mIntHB));
     memset(&UVD, 0, sizeof(mIntHBD));
     memset(&UD, 0, sizeof(mIntHBD));
     memset(&UVD2, 0, sizeof(mIntHBD));

     LLHLn.I = n;  
     U.mIdgt[mIntHBIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntHBIndexMax] = LLHLn.HL.L;
     LLHLn.I = m;  
     V.mIdgt[mIntHBIndexMax-1] = LLHLn.HL.H;
     V.mIdgt[mIntHBIndexMax] = LLHLn.HL.L;
     mIntResult = mIntHBMUL_HL(&U, &V, &UVD);
     if (mIntResult != 0)
         {
         printf("mIntHBMUL_HL(setNMplusL) != 0 : %d\n", mIntResult); //error
         return;
         }
     LLHLn.I = l;  
     UD.mIdgt[mIntHBIndexMax*2-1] = LLHLn.HL.H;
     UD.mIdgt[mIntHBIndexMax*2] = LLHLn.HL.L;
     mIntResult = mIntHBADD_HL(&UD, &UVD, &UVD2);
     if (mIntResult != 0)
         {
         printf("mIntHBADD_HL(setNMplusL) != 0 : %d\n", mIntResult); //error
         return;
         }
     memcpy(&U, &UVD2.mIdgt[mIntHBIndexMax], sizeof(mIntHB));

     MMS64IniComLP(&MMSWParaLP, &U);
     }

/**************/
void MMS64Ini_compNMLK(unsigned long long int n, unsigned long long int m,
               unsigned long long int l,  unsigned long long int k, mIntHBD *NMLK)
     {
     uiLLHLHB LLHLn;
     mIntHB  U, V, W;
     mIntHBD UVD;
     int   mIntHBResult;

     memset(&U, 0, sizeof(mIntHB));
     memset(&V, 0, sizeof(mIntHB));
     memset(&UVD, 0, sizeof(mIntHBD));

     LLHLn.I = n;  
     U.mIdgt[mIntHBIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntHBIndexMax] = LLHLn.HL.L;
     //DumpMint(&U, 'n');  //debug
     LLHLn.I = m;  
     V.mIdgt[mIntHBIndexMax-1] = LLHLn.HL.H;
     V.mIdgt[mIntHBIndexMax] = LLHLn.HL.L;
     //DumpMint(&V, 'm');  //debug
     mIntHBResult = mIntHBMUL_HL(&U, &V, &UVD);
     //DumpMintD(&UVD, 'M');  //debug
     if (mIntHBResult != 0)
         {
         printf("mIntHBMUL_HL(compNMLK_1) != 0 : %d\n", mIntHBResult); //error
         return;
         }
     memcpy(&W, &UVD.mIdgt[mIntHBIndexMax], sizeof(mIntHB));
     //DumpMint(&W, 'W');  //debug

     LLHLn.I = l;  
     U.mIdgt[mIntHBIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntHBIndexMax] = LLHLn.HL.L;
     //DumpMint(&U, 'l');  //debug
     mIntHBResult = mIntHBMUL_HL(&U, &W, &UVD);
     //DumpMintD(&UVD, 'M');  //debug
     if (mIntHBResult != 0)
         {
         printf("mIntHBMUL_HL(compNMLK_2) != 0 : %d\n", mIntHBResult); //error
         return;
         }
     memcpy(&W, &UVD.mIdgt[mIntHBIndexMax], sizeof(mIntHB));
     //DumpMint(&W, 'W');  //debug

     LLHLn.I = k;  
     U.mIdgt[mIntHBIndexMax-1] = LLHLn.HL.H;
     U.mIdgt[mIntHBIndexMax] = LLHLn.HL.L;
     //DumpMint(&U, 'k');  //debug
     mIntHBResult = mIntHBMUL_HL(&U, &W, &UVD);
     //DumpMintD(&UVD, 'M');  //debug
     if (mIntHBResult != 0)
         {
         printf("mIntHBMUL_HL(compNMLK_3) != 0 : %d\n", mIntHBResult); //error
         return;
         }

     memcpy(NMLK, &UVD, sizeof(mIntHBD));
     //DumpMint(&W, 'W');  //debug
     }

/**************/
void MMSIni_setNMLK(unsigned long long int n, unsigned long long int m,
                      unsigned long long int l,  unsigned long long int k)
     {
     mIntHB  W;
     mIntHBD NMLKvalD;
     
     MMS64Ini_compNMLK(n,m,l,k,&NMLKvalD);
     memcpy(&W, &NMLKvalD.mIdgt[mIntHBIndexMax], sizeof(mIntHB));
     //DumpMint(&W, 'W');  //debug

     MMS64IniComLP(&MMSWParaLP, &W);
     }

/**************/
void MMSIni_plusNMLK(unsigned long long int n, unsigned long long int m,
                      unsigned long long int l,  unsigned long long int k)
     {
     mIntHB  W;
     mIntHBD NMLKvalD, currIniValD, nextIniValD;
     int   mIntHBResult;

     
     MMS64Ini_compNMLK(n,m,l,k,&NMLKvalD);
     //DumpMintD(&NMLKvalD, 'p');  //debug

     memset(&currIniValD, 0, sizeof(mIntHBD));
     memcpy(&currIniValD.mIdgt[mIntHBIndexMax], &MMS64LP_Ini_InitialNo, sizeof(mIntHB));
     //DumpMintD(&currIniValD, 'c');  //debug
     mIntHBResult = mIntHBADD_HL(&NMLKvalD, &currIniValD, &nextIniValD);
     //DumpMintD(&nextIniValD, 'a');  //debug
     if (mIntHBResult != 0)
         {
         printf("mIntHBADD_HL(plusNMLK) != 0 : %d\n", mIntHBResult); //error
         return;
         }
     memcpy(&W, &nextIniValD.mIdgt[mIntHBIndexMax], sizeof(mIntHB));

     MMS64IniComLP(&MMSWParaLP, &W);
     }

/**************/
void MMSIni_setBin32x8(unsigned int *Bin32x8)
     {
     uiLLHLHB LLHLn;
     mIntHB  U;

     memset(&U, 0, sizeof(mIntHB));
     memcpy(&U.mIdgt[mIntHBIndexMax-7], Bin32x8, sizeof(int)*8);
     //DumpMint(&U, 'u');  //debug
     MMS64IniComLP(&MMSWParaLP, &U);
     }

/**************/


/*******************/
#ifdef testMMSIni

int main()
    {	
    unsigned long long int N, M, L, K;
	uiLLHL uiLLHLwk;
    unsigned int Bin32x8[8];

	MMSshowRkSkLP();
	printf("\n* MMSIni(0)\n");
    MMSIni(0);
	MMSshowRkSkLP();

	printf("\n* MMSIni(1)\n");
    MMSIni(1);
	MMSshowRkSkLP();
	
	printf("\n* MMSIni(2)\n");
    MMSIni(2);
	MMSshowRkSkLP();
	
	printf("\n* MMSIni(3)\n");
    MMSIni(3);
	MMSshowRkSkLP();
	
	printf("\nMMSIni_setNM(101,2)  N*M=101*2=202\n");
    N = 101; M = 2;
    MMSIni_setNM(N,M);
    MMSshowRkSkLP();

	printf("\nMMSIni_setNMplusL(50,4,2)  N*M+L=50*4+2=202\n");
    N = 50; M = 4; L=2;
    MMSIni_setNMplusL(N,M,L);
	MMSshowRkSkLP();
	
    //printf("\n======== using MMSIni_setNMLK() ========\n");
    N=0x8000000000000001; M=N; L=N; K=N;
	printf("\n  N = M = L = K = 0x8000000000000001\n");
 	printf("MMSIni_setNMLK(N,M,L,K)  // set to generate NxMxLxK-th RN\n");
    MMSIni_setNMLK(N,M,L,K);
	MMSshowRkSkLP();

    N=0x8000000000000001; M=N; L=N; K=5;
	printf("\n  N = M = L = 0x8000000000000001,  k = 5\n");
 	printf("MMSIni_setNMLK(N,M,L,5)  // set to generate NxMxLx(K=5)-th RN\n");
    MMSIni_setNMLK(N,M,L,K);
	MMSshowRkSkLP();

    N=0x8000000000000001; M=N; L=N; K=3;
	printf("\n  N = M = L = 0x8000000000000001,  k = 3\n");
 	printf("MMSIni_setNMLK(N,M,L,3)  // set to generate NxMxLx(K=3)-th RN\n");
    MMSIni_setNMLK(N,M,L,K);
	MMSshowRkSkLP();

    N=0x8000000000000001; M=N; L=N; K=2;
	printf("\n  N = M = L = 0x8000000000000001,  k = 2\n");
    printf(" // set to generate (previous MMSIni_** No)+NxMxLx(K=2)-th RN\n");
 	printf("MMSIni_plusNMLK(N,M,L,2)\n");
    MMSIni_plusNMLK(N,M,L,K);
	MMSshowRkSkLP();
	
    memset(&Bin32x8, 0, sizeof(Bin32x8));
    Bin32x8[0] = 0xffffffff;  Bin32x8[7] = 0x11111111;
	printf("\n  Bin32x8[0]=0xffffffff; Bin32x8[1]...[6]=0; Bin32x8[7] = 0x11111111;\n");
 	printf("MMSIni_setBin32x8(Bin32x8)\n");
    MMSIni_setBin32x8(Bin32x8);
	MMSshowRkSkLP();

    Bin32x8[7] = 0x11111110;
	printf("\n  Bin32x8[0]=0xffffffff; Bin32x8[1]...[6]=0; Bin32x8[7] = 0x11111110;\n");
	printf("MMSIni_setBin32x8(Bin32x8)\n");
    MMSIni_setBin32x8(Bin32x8);
	MMSshowRkSkLP();

    N=1; M=1; L=1; K=1;
	printf("\n  N = M = L = k = 1\n");
    printf(" // set to generate (previous MMSIni_** No)+NxMxLxK -th RN\n");
 	printf("MMSIni_plusNMLK(1,1,1,1)\n");
    MMSIni_plusNMLK(N,M,L,K);
	MMSshowRkSkLP();

    return(0);
    }
#endif

///////// NOTE //////////////////////////////////////////
// The code above is not refined; and
//    should be tested by many users.
// If you find bugs, please mail to
//    hiroshimayaguchi at-mark yahoo.co.jp .
// (At that time, include the code-name (such as
//   TORANOSUKE-20260119) in the subject of the mail.)
//
// MMSIniFuncs : Last updated at 2026.01.19
//      (Code Name : TORANOSUKE-20260119)
// This NOTE : Last updated at 2026.01.19
/////////////////////////////////////////////////////////
