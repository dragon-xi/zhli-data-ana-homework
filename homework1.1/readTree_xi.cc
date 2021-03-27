//将下列代码保存到readTree.cc
//在ROOT环境下 .x readTree.cc

//TH1D *hTOF;//如果将hTOF定义写在函数体内 hTOF->Draw()将不会显示
//TH1D *ntof;
void readTree_xi()
{
// 1.打开文件，得到TTree指针
  TFile *ipf=new TFile("tree.root");//打开ROOT文件
  if (ipf->IsZombie()) {
   cout << "Error opening file" << endl;
   exit(-1);
  }
  ipf->cd();
  TTree *tree=(TTree*)ipf->Get("tree");//得到名字为“tree”的TTree指针

//2. 声明tree的Branch变量

  Double_t x;
  Double_t e;
  int pid;
  Double_t tof, ctof;
  Double_t tu, td;
  Double_t qu, qd;

//3. 将变量指向对应Branch的地址
  tree->SetBranchAddress("ctof",&ctof);//将ROOT文件内tree内名为"ctof"的branch的数据的指针指向ctof的变量。
  tree->SetBranchAddress("tof",&tof);  
  tree->SetBranchAddress("pid",&pid);
  tree->SetBranchAddress("tu",&tu);   
  tree->SetBranchAddress("td",&td);
  tree->SetBranchAddress("qu",&qu);   
  tree->SetBranchAddress("qd",&qd);
  tree->SetBranchAddress("e",&e);
  tree->SetBranchAddress("x",&x);



  //Histogram
 // hTOF=new TH1D("hTOF","Time of flight", 1000,0,100);
  // ntof = new TH1D("ntof","ntof",100,0,20);
  //将新数据写入新的ROOT文件 -对应的代码用 ////标出
  //// //calibration parameters
  //// Double_t a,b;
  //// ... ... ...
  //// //new tree parameters
  Double_t tx,qx,ce,ntof;
  //// ... ... ...    
   TFile *opf=new TFile("tree2.root","recreate");
   opf->cd();
   TTree *opt=new TTree("tree","tree");

   //tree中数据指向变量指针
   //继承原有tree.root数据
   opt->Branch("x",&x,"x/D");
   opt->Branch("e",&e,"e/D");
   opt->Branch("tu",&tu,"tu/D");
   opt->Branch("td",&td,"td/D");
   opt->Branch("qu",&qu,"qu/D");
   opt->Branch("qd",&qd,"qd/D");
   opt->Branch("pid",&pid,"pid/D");
   opt->Branch("tof",&tof,"tof/D");
   opt->Branch("ctof",&ctof,"ctof/D");

   //tree中填加新的变量
   opt->Branch("tx",&tx,"tx/D");
   opt->Branch("qx",&qx,"qx/D");
   opt->Branch("ce",&ce,"ce/D");
   opt->Branch("ntof",&ntof,"ntof/D");
  // TH1D *ntof = new TH1D("ntof","ntof",200,0,20);
  //// ... ... ...


  //4. 逐事件读取tree的branch数据
  Long64_t nentries=tree->GetEntries();//得到tree的事件总数
  for(Long64_t jentry=0; jentry<nentries; jentry++) {//对事件进行遍历
    tree->GetEntry(jentry);//将第jentry个事件数据填入对应变量(步骤3.中指向的变量)，每次变量值会变成当前事件对应的数据。
    ////hTOF->Fill(ctof);
    //// // calculate new parameters
     tx = 3.742*(td-tu-14.915);
     qx = 190.4*(log(qu/qd)+0.003);
     Double_t d=TMath::Sqrt(502.5*502.5+tx*tx);
     ntof=(ctof-26.2096)/d*100.;
    // Double_t corr_ctof=(ctof-26.2096)/d*100.;
    // ntof->Fill(corr_ctof);
     if(pid == 1)
	{
	//ce = (939.56563*100.*100.)/(2.*30.*30.*corr_ctof*corr_ctof);
	ce = (939.56563*100.*100.)/(2.*30.*30.*ntof*ntof);
	}
    //// ... ... ...

     opt->Fill();//fill new parameter to TTree* opt

    if(jentry%1000==0) cout<<"process "<<jentry<<" of "<<nentries<<endl;
  }

  //hTOF->Draw();
  ipf->Close();
  opt->Write();
  opf->Close();
}
