#ifndef ALIANALYSISTASKJETBACKGROUNDSUBTRACT_H
#define ALIANALYSISTASKJETBACKGROUNDSUBTRACT_H
 
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

// **************************************
// task used for background subtration of all jets found with clustering algos
// *******************************************

#include  "AliAnalysisTaskSE.h"
#include  "TObjString.h"
#include  "TString.h"
#include  "TObjArray.h"


////////////////
class AliJetHeader;
class AliESDEvent;
class AliAODEvent;
class AliAODExtension;
class AliAODJet;
class AliAODJetEventBackground;
class AliJetFinder;
class TList;
class TChain;
class TH2F;
class TH1F;
class TH3F;
class TProfile;
class TRandom3;
class TRefArray;


class AliAnalysisTaskJetBackgroundSubtract : public AliAnalysisTaskSE
{
 public:
    AliAnalysisTaskJetBackgroundSubtract();
    AliAnalysisTaskJetBackgroundSubtract(const char* name);
    virtual ~AliAnalysisTaskJetBackgroundSubtract();
    // Implementation of interface methods
    virtual void UserCreateOutputObjects();
    virtual void Init();
    virtual void LocalInit() { Init(); }
    virtual void UserExec(Option_t *option);
    virtual void Terminate(Option_t *option);
    virtual Bool_t Notify();

    // Task specific methods...
    virtual void   AddJetBranch(const char* c){fJBArray->Add(new TObjString(c));}
    virtual void   SetSubtractionMethod(Int_t i){fSubtraction = i;}
    virtual Int_t  GetSubtractionMethod(){return fSubtraction;}
    virtual void   SetBackgroundBranch(char* c){fBackgroundBranch = c;}  
    virtual void   SetNonStdFile(char* c){fNonStdFile = c;}  
    virtual void   SetToReplace(char* c){fReplaceString1 = c;}  
    const char*    GetToReplace(){return fReplaceString1.Data();}  
    virtual void   SetReplacementMask(char* c){fReplaceString2 = c;}  
    const char*   GetReplacementMask(){fReplaceString2.Data();}  
   
    enum {kNoSubtract = 0,kArea,k4Area};
 
 private:

    

    AliAnalysisTaskJetBackgroundSubtract(const AliAnalysisTaskJetBackgroundSubtract&);
    AliAnalysisTaskJetBackgroundSubtract& operator=(const AliAnalysisTaskJetBackgroundSubtract&);
    Bool_t RescaleJetMomentum(AliAODJet *jet,Float_t pT);
    void ResetOutJets();


    AliAODEvent     *fAODOut;                // ! where we take the jets from and they are modified
    AliAODEvent     *fAODIn;                 // ! where we may take the background from, only in case we do not find it in the output
    AliAODExtension *fAODExtension;          // ! where we take the jets from can be input or output AOD
    TObjArray       *fJBArray;               // Array that stores the name of all jet branches to be subtracted   
    TString         fBackgroundBranch;       // name of the branch used for background subtraction
    //
    TString         fNonStdFile;        // The optional name of the output file the non-std brnach is written to
    TString         fReplaceString1;     // To construct the new output name  
    TString         fReplaceString2;     // To construct the new output name   
    Int_t           fSubtraction;       // Parameter for subtraction mode 
    TList *fInJetArrayList; //! transient list to make ease the handling of input jets
    TList *fOutJetArrayList; //! transient list to make ease the reset of output jets
    TList *fHistList; //! the histograms output list
   
    ClassDef(AliAnalysisTaskJetBackgroundSubtract, 1) 
};
 
#endif
