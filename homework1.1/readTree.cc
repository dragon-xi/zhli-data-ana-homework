//将下列代码保存到readTree.cc
//在ROOT环境下 .x readTree.cc

TH1D *hTOF;//如果将hTOF定义写在函数体内 hTOF->Draw()将不会显示
void readTree()
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

  //Histogram
  hTOF=new TH1D("hTOF","Time of flight", 1000,0,100);

  //将新数据写入新的ROOT文件 -对应的代码用 ////标出
  //// //calibration parameters
  //// Double_t a,b;
  //// ... ... ...
  //// //new tree parameters
  //// Double_t tx,qx,ce;
  //// ... ... ...    
  //// TFile *opf=new TFile("tree2.root","recreate");
  //// opt->cd();
  //// TTree *opt=new TTree("tree","tree");
  //// opt->SetBrach("tx",&tx,"tx/D");
  //// ... ... ...


  //4. 逐事件读取tree的branch数据
  Long64_t nentries=tree->GetEntries();//得到tree的事件总数
  for(Long64_t jentry=0; jentry<nentries; jentry++) {//对事件进行遍历
    tree->GetEntry(jentry);//将第jentry个事件数据填入对应变量(步骤3.中指向的变量)，每次变量值会变成当前事件对应的数据。
    hTOF->Fill(ctof);
    //// // calculate new parameters
    //// tx=tu-td;
    //// ... ... ...

    //// opt->Fill();//fill new parameter to TTree* opt

    if(jentry%100000==0) cout<<"process "<<jentry<<" of "<<nentries<<endl;
  }

  hTOF->Draw();
  ipt->Close();
  //// opt->Write();
  //// opf->Close();
}
