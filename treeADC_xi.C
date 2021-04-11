#define treeADC_xi_cxx
#include "treeADC_xi.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void treeADC_xi::Loop()
{
//   In a ROOT session, you can do:
//      root> .L treeADC_xi.C
//      root> treeADC_xi t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
	//声明新的root文件以及tree
	TFile *opf = new TFile("treeADC_xi.root","recreate");
	opf->cd();
	TTree *opt = new TTree("tree","tree");
    	//声明tree中Branch变量
    	Double_t xa,xb;
	Double_t ea,eb;
	Double_t tofa,tofb;
	Double_t ctofa,ctofb;
	Double_t tua,tub;
	Double_t tda,tdb;
	Double_t qua,qub;
	Double_t qda,qdb;
	Int_t    itua,itub;
	UInt_t   itda,itdb;
	UInt_t   iqua,iqub;
	UInt_t   iqda,iqdb;
	Double_t diffa,diffb;
	//ADC，TDC常量
	const Double_t ADCgain=60;//1MeV=60ch.
	const Double_t ADCuPed=140;//baseline of ADC for upper side
	const Double_t ADCdPed=130;//                for bottom side
	const Double_t ADCnoise=50;//sigma of noise
	const Int_t    ADCoverflow=4095;

 //TDC
 	const Double_t TriggerDelay=15;//ns, trigger延迟,将感兴趣的时间信号放在TDC量程以内。
 	const Double_t TDCch2ns=40.;//1ns=40ch.
 	const Int_t TDCoverflow=4095;
	//tree中数据指向变量指针
	//继承原有root文件数据
	opt->Branch("x", &x, "x/D");//position
	opt->Branch("e", &e, "e/D");//energy
	opt->Branch("tof", &tof, "tof/D");//time of flight
        opt->Branch("ctof",&ctof,"ctof/D");//TOF from exp. data
        opt->Branch("pid", &pid, "pid/I");
        // raw time and energy
        opt->Branch("tu", &tu, "tu/D");
        opt->Branch("td", &td, "td/D");
        opt->Branch("qu", &qu, "qu/D");
        opt->Branch("qd", &qd, "qd/D");
        // energy in ADC, time in TDC 注意，以下Branch变量声明的类型为 Integer，
        opt->Branch("itu", &itu, "itu/I");
        opt->Branch("itd", &itd, "itd/i");
        opt->Branch("iqu", &iqu, "iqu/i");
        opt->Branch("iqd", &iqd, "iqd/i");
	opt->Branch("diff",&diff,"diff/D");

	//Wall A (BACK)数据
	opt->Branch("xa", &xa, "xa/D");//position
	opt->Branch("ea", &ea, "ea/D");//energy
	opt->Branch("tofa", &tofa, "tofa/D");//time of flight
        opt->Branch("ctofa",&ctofa,"ctofa/D");//TOF from exp. data
        // raw time and energy
        opt->Branch("tua", &tua, "tua/D");
        opt->Branch("tda", &tda, "tda/D");
        opt->Branch("qua", &qua, "qua/D");
        opt->Branch("qda", &qda, "qda/D");
        // energy in ADC, time in TDC 注意，以下Branch变量声明的类型为 Integer，
        opt->Branch("itua", &itua, "itua/I");
        opt->Branch("itda", &itda, "itda/i");
        opt->Branch("iqua", &iqua, "iqua/i");
        opt->Branch("iqda", &iqda, "iqda/i");
	opt->Branch("diffa",&diffa,"diffa/D");

	//Wall B (Front)veto墙
	//由于WallB厚度为1 cm,仅对带点粒子有作用，为了简便，假设打在WallB的位置与打在WallA的位置相同；
	opt->Branch("xb", &xb, "xb/D");//position
	opt->Branch("eb", &eb, "eb/D");//energy
	opt->Branch("tofb", &tofb, "tofb/D");//time of flight
        opt->Branch("ctofb",&ctofb,"ctofb/D");//TOF from exp. data
        // raw time and energy
        opt->Branch("tub", &tub, "tub/D");
        opt->Branch("tdb", &tdb, "tdb/D");
        opt->Branch("qub", &qub, "qub/D");
        opt->Branch("qdb", &qdb, "qdb/D");
        // energy in ADC, time in TDC 注意，以下Branch变量声明的类型为 Integer，
        opt->Branch("itub", &itub, "itub/I");
        opt->Branch("itdb", &itdb, "itdb/i");
        opt->Branch("iqub", &iqub, "iqub/i");
        opt->Branch("iqdb", &iqdb, "iqdb/i");
	opt->Branch("diffb",&diffb,"diffb/D");
	TRandom3 *gr = new TRandom3(0);
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	xa=x;xb=x;
     	if(pid == 2)//proton
	{
	eb=e*0.1;	ea=e*0.9;
	tofb=tof;	tofa=tof;
	tub=tu;		tua=tu;
	tdb=td;		tda=td;
	qub=0.1*qu;	qua=0.9*qu;//为了简便此处直接做成，导致pedo随着变小，实际中pedo应该保持不变；
	qdb=0.1*qd;	qda=0.9*qd;
	itub=Int_t(tub);itua=Int_t(tua);
	itdb=Int_t(tdb);itda=Int_t(tda);
	iqub=Int_t(qub);iqua=Int_t(qua);
	iqdb=Int_t(qdb);iqda=Int_t(qda);
	diffb=tub-itub;diffa=tua-itua;
	} 
     	if(pid == 0||pid == 1)//gamma,neutron
	{
	eb=-1;		ea=e;
	tofb=-1;	tofa=tof;
	tub=TDCoverflow;tua=tu;
	tdb=TDCoverflow;tda=td;
	qub=ADCuPed+gr->Gaus(0,ADCnoise);qua=qu;
	qdb=ADCdPed+gr->Gaus(0,ADCnoise);qda=qd;
	itub=Int_t(tub);itua=Int_t(tua);
	itdb=Int_t(tdb);itda=Int_t(tda);
	iqub=Int_t(qub);iqua=Int_t(qua);
	iqdb=Int_t(qdb);iqda=Int_t(qda);
	diffb=tub-itub;diffa=tua-itua;
	} 
     	if(pid == 3)//other
	{
	eb=-1;		ea=-1;
	tofb=-1;	tofa=-1;
	tub=tu;		tua=tu;
	tdb=td;		tda=td;
	qub=ADCuPed+gr->Gaus(0,ADCnoise);qua=ADCuPed+gr->Gaus(0,ADCnoise);
	qdb=ADCdPed+gr->Gaus(0,ADCnoise);qda=ADCdPed+gr->Gaus(0,ADCnoise);
	itub=Int_t(tub);itua=Int_t(tua);
	itdb=Int_t(tdb);itda=Int_t(tda);
	iqub=Int_t(qub);iqua=Int_t(qua);
	iqdb=Int_t(qdb);iqda=Int_t(qda);
	diffb=tub-itub;diffa=tua-itua;
	} 
       opt->Fill(); 
     // if (Cut(ientry) < 0) continue;
   }
	opt->Write();
	opf->Close();
}
