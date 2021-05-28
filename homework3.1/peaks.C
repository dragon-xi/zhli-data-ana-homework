//ROOT
#include <TH1.h>
#include <TSpectrum.h>
#include <TList.h>
#include <TPolyMarker.h>
#include <TLatex.h>
//C++
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

    TH1F *h=NULL,*hb=NULL;
    Int_t nfound;
    Double_t *xpeaks=NULL, *ypeaks=NULL;
    TSpectrum *s=NULL;

void peaks(TString hname, vector<Double_t> &pe, Double_t thres=0.05,int backsub=0)
{
    pe.clear();//清空pe
    multimap<Int_t,Double_t> me;//用于排序
    h=(TH1F*)gROOT->FindObject(hname);
    if(!s)    s=new TSpectrum(500);
    
    if(backsub)
    {
        hb=(TH1F*)s->Background(h,80,"same");//80-本底光滑程度
        h->Add(h,hb,1,-1);   
    }
    
    nfound=s->Search(h,2,"",thres); 
    
    TList *functions = h->GetListOfFunctions();//added by xi
    TPolyMarker *pm=(TPolyMarker *)h->GetListOfFunctions()->FindObject("TPolyMarker");
    pm->SetMarkerStyle(32);
    pm->SetMarkerColor(kGreen);
    pm->SetMarkerSize(0.4);
    xpeaks=s->GetPositionX();
    ypeaks=s->GetPositionY();
    
    TString sout;
    for(int j=0;j<nfound;j++) 
    {
        stringstream ss;
        ss<<xpeaks[j];
        TString s1=ss.str();
        TLatex *tex=new TLatex(xpeaks[j],ypeaks[j],s1);
        //sout.Form("%2d. %4d %d",j,xpeaks[j],ypeaks[j]);
        //cout<<sout.Data()<<endl;
        me.insert(make_pair(int(ypeaks[j]),xpeaks[j]));//map自动按照key大小排序（key，value）
        tex->SetTextFont(13);
        tex->SetTextSize(14);
        tex->SetTextAlign(12);
        tex->SetTextAngle(90);
        tex->SetTextColor(kRed);
	h->GetListOfFunctions()->Add(tex);
        tex->Draw();
    }
    
    Int_t pnumber = 1;
    for(auto ie=me.rbegin(); ie!=me.rend(); ie++) 
    {
        cout<<"Num of Peaks: "<<setw(2)<<pnumber<<"  x: "<<setw(7)<<ie->second<<"  y: "<<setw(7)<<ie->first<<endl;//peak,count;
        pe.push_back(ie->second);//按照计数由大到小填入
	pnumber++;
    }
  me.clear();
}
