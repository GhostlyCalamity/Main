void draw2()
{
TFile *f = new TFile("run2/run2.root");
TH2F * h1 = new TH2F("h1","h1 title", 200,-150,150,200,-150,150);
h1 = (TH2F*)f->Get("ITHitMonitor/201");
TH1D *h2;
TH1D *h3 =new TH1D("hrl", "right long", 70, 0, 70);
TH1D *h21;
TH1D *h31 =new TH1D("hll", "left long", 70, 0, 70);
TH1D *h4;
TH1D *h5 =new TH1D("hrs", "right short", 70, 0, 70);
TH1D *h6;
TH1D *h7 =new TH1D("hts", "top short", 70, 0, 70);
TH1D *h8;
TH1D *h9 =new TH1D("htl", "top long", 70, 0, 70);
TH1D *h10;
TH1D *h11 =new TH1D("&&&", "???", 70, 0, 70);
TCutG *cutg= new TCutG("cut",4);
TCutG *cutg11= new TCutG("cut11",4);
TCutG *cutg2= new TCutG("cut2",4);
TCutG *cutg3= new TCutG("cut3",4);
TCutG *cutg4= new TCutG("cut4",4);
//TCutG *cutg5= new TCutG("cut5",4);

TCanvas *c1 = new TCanvas("c1","c1");
TCanvas *c2 = new TCanvas("c2","c2");
TCanvas *c3 = new TCanvas("c3","c3");
TCanvas *c4 = new TCanvas("c4","c4");
//TCanvas *c5 = new TCanvas("c5","c5");

gStyle->SetPaintTextFormat("3.2e");

//right long
for(int i=18;i<19;i+=1.5){
cutg->SetPoint(0, i, -6.);
cutg->SetPoint(1, i+7.5, -6.);
cutg->SetPoint(2, i+7.5, 6);
cutg->SetPoint(3, i, 6);
	
h2= h1->ProjectionX("h2", 1, -1, "[cut]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
h3->SetBinContent(i+1,(h2->GetEntries()));
}
/*for(int i=3;i<61;i++){
cutg11->SetPoint(0, -i, -3.75);
cutg11->SetPoint(1, -i-11., -3.75);
cutg11->SetPoint(2, -i, 3.75);
cutg11->SetPoint(3, -i-11, 3.75);	
h21= h1->ProjectionX("h21", 1, -1, "[cut11]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
h31->SetBinContent(i,(h21->GetEntries()));
}*/
c1->cd();
//c1->Divide(1,2);
//c1->cd(1);
h3->Draw("hist&text");
//c1->cd(2);
//h1->Draw("[cut]");
//h31->Draw("hist&text");
h3->GetXaxis()->SetTitle("left edge position, sm");
h3->GetXaxis()->SetTitleOffset(1.3);
h3->GetYaxis()->SetTitle("MIPs per sensor");
h3->GetYaxis()->SetTitleOffset(1.3);

//right short
for(int i=3;i<65;i++){
cutg2->SetPoint(0, i, -5.5);
cutg2->SetPoint(1, i+7.5, -5.5);
cutg2->SetPoint(2, i+7.5, 5.5);
cutg2->SetPoint(3, i, 5.5);
h4= h1->ProjectionX("h4", 1, -1, "[cut2]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
h5->SetBinContent(i,(h4->GetEntries()));
}
c2->cd();
h5->Draw("hist&text");
h5->GetXaxis()->SetTitle("left edge position, sm");
h5->GetXaxis()->SetTitleOffset(1.3);
h5->GetYaxis()->SetTitle("MIPs per sensor");
h5->GetYaxis()->SetTitleOffset(1.3);

//bot short
for(int i=10.5;i<11;i+=1.5){
cutg3->SetPoint(0, 3, -i);
cutg3->SetPoint(1, 10.5, -i);
cutg3->SetPoint(2, 10.5, -i-10.5);
cutg3->SetPoint(3, 3, -i-10.5);
h6= h1->ProjectionX("h6", 1, -1, "[cut3]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
h7->SetBinContent(i+1,(h6->GetEntries()));
}
c3->cd();
h7->Draw("hist&text");
//h1->Draw("[cut3]");
h7->GetXaxis()->SetTitle("left edge position, sm");
h7->GetXaxis()->SetTitleOffset(1.3);
h7->GetYaxis()->SetTitle("MIPs per sensor");
h7->GetYaxis()->SetTitleOffset(1.3);

//top long
for(int i=3;i<59;i++){
cutg4->SetPoint(0, -3.75, i);
cutg4->SetPoint(1, 3.75, i);
cutg4->SetPoint(2, -3.75, i+11);
cutg4->SetPoint(3, 3.75, i+11);
h8= h1->ProjectionX("h8", 1, -1, "[cut4]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
h9->SetBinContent(i,(h8->GetEntries()));
}
c4->cd();
h9->Draw("hist&text");
h9->GetXaxis()->SetTitle("left edge position, sm");
h9->GetXaxis()->SetTitleOffset(1.3);
h9->GetYaxis()->SetTitle("MIPs per sensor");
h9->GetYaxis()->SetTitleOffset(1.3);

/*
for(int i=3;i<65;i++){
cutg5->SetPoint(0, 0, i);
cutg5->SetPoint(1, 3, i+15);
cutg5->SetPoint(2, -3, i+15);
//cutg5->SetPoint(3, 5, i+10);
h10= h1->ProjectionX("h10", 1, -1, "[cut5]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
h11->SetBinContent(i,h10->GetEntries());
}
c5->cd();
h11->Draw("hist&text");
*/

//h1->Draw("[cut2]"); 
//printf("NoE=%f", h3->GetEntries());
 
}