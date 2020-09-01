void draw_fr_axb()
{
TFile *f = new TFile("run3/run3.root");
TH2F * h1 = new TH2F("h1","h1 title", 200,-150,150,200,-150,150);
h1 = (TH2F*)f->Get("TTHitMonitor/201");
TH1D *h2, *h22;
TH1D *h3 =new TH1D("hrl", "response vs sensor(6x9 cm^{2}) right&left edge position, Run3 TT; |x_{min}| coordinate [cm]; Sensor response, kHz", 140, 0, 70);
TH1D *h33 =new TH1D("left", "response vs sensor(6x9 cm^{2}) right&left edge position, Run3 TT; |x_{min}| coordinate [cm]; Sensor response, kHz", 140, 0, 70);
TH1D *h8, *h88;
TH1D *h9 =new TH1D("htl", "response vs sensor(9x6 cm^{2}) bottom&top edge position, Run3 TT; |y_{min}| coordinate [cm]; Sensor response, kHz", 140, 0, 70);
TH1D *h99 =new TH1D("bot", "response vs sensor(9x6 cm^{2}) bottom&top edge position, Run3 TT; |y_{min}| coordinate [cm]; Sensor response, kHz", 140, 0, 70);

TCutG *cutg= new TCutG("cut",4);
TCutG *cutg_inv= new TCutG("cut_inv",4);
TCutG *cutg_inv2= new TCutG("cutinv2",4);
TCutG *cutg2= new TCutG("cut2",4);
TCutG *cutg3= new TCutG("cut3",4);
TCutG *cutg4= new TCutG("cut4",4);
//TCutG *cutg5= new TCutG("cut5",4);

TCanvas *c1 = new TCanvas("c1","c1");
//TCanvas *c2 = new TCanvas("c2","c2");
//TCanvas *c3 = new TCanvas("c3","c3");
TCanvas *c4 = new TCanvas("c4","c4");


gStyle->SetPaintTextFormat("3.2e");

//right 
for(double i=3;i<60;i+=1.5){
cutg->SetPoint(0, i, -4.5);
cutg->SetPoint(1, i+6, -4.5);
cutg->SetPoint(2, i+6, 4.5);
cutg->SetPoint(3, i, 4.5);

 cutg_inv->SetPoint(0, -i, -4.5);
 cutg_inv->SetPoint(1, -i-6, -4.5);
 cutg_inv->SetPoint(2, -i-6, 4.5);
 cutg_inv->SetPoint(3, -i, 4.5);
	
h2= h1->ProjectionX("h2", 1, -1, "[cut]");
h22 = h1->ProjectionX("h22", 1, -1, "[cut_inv]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
double k=i*2;
h3->SetBinContent(k+1,(h2->GetEntries())*4.1/1000);
h33->SetBinContent(k+1,h22->GetEntries()*4.1/1000);
}
c1->cd();

h33->SetFillColor(kRed-9);
h33->SetBarWidth(0.85);
h33->SetBarOffset(0.43);
h33->SetStats(0);
h33->Draw("hist&b3"); //text

h3->SetFillColor(kBlue-3);
h3->SetBarWidth(0.85);
h3->SetBarOffset(-0.42);
h3->SetStats(0);
h3->Draw("same&hist&b3");


TLegend *leg = new TLegend(0.65,0.65,0.90,0.90);
  leg->AddEntry("hrl", "right sensor", "f");
  leg->AddEntry("left", "left sensor", "f");
  leg->Draw("same");

//h3->GetXaxis()->SetTitle("left edge position, cm");
h3->GetXaxis()->SetTitleOffset(1.3);
//h3->GetYaxis()->SetTitle("Sensor response, kHz");
h3->GetYaxis()->SetTitleOffset(1.3);











//top 
for(double i=3;i<59;i+=1.5){
cutg4->SetPoint(0, -4.5, i);
cutg4->SetPoint(1, 4.5, i);
cutg4->SetPoint(2, 4.5, i+6);
cutg4->SetPoint(3, -4.5, i+6);

cutg_inv2->SetPoint(0, -4.5, -i);
cutg_inv2->SetPoint(1, 4.5, -i);
cutg_inv2->SetPoint(2, 4.5, -i-6);
cutg_inv2->SetPoint(3, -4.5, -i-6);

h8= h1->ProjectionX("h8", 1, -1, "[cut4]");
h88= h1->ProjectionX("h88", 1, -1, "[cutinv2]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
double k=i*2;
h9->SetBinContent(k+1,(h8->GetEntries())*4.1/1000);
h99->SetBinContent(k+1,(h88->GetEntries())*4.1/1000);
}
c4->cd();
h9->SetFillColor(kBlue-3);
h9->SetBarWidth(0.85);
h9->SetBarOffset(-0.42);
h9->SetStats(0);
h9->Draw("hist&b3");

h99->SetFillColor(kRed-9);
h99->SetBarWidth(0.85);
h99->SetBarOffset(0.43);
h99->SetStats(0);
h99->Draw("same&hist&b3");

TLegend *leg1 = new TLegend(0.65,0.65,0.90,0.90);
  leg1->AddEntry("htl", "top sensor", "f");
  leg1->AddEntry("bot", "bottom sensor", "f");
  leg1->Draw("same");

//h9->GetXaxis()->SetTitle("left edge position, sm");
h9->GetXaxis()->SetTitleOffset(1.3);
//h9->GetYaxis()->SetTitle("Sensor response, kHz");
h9->GetYaxis()->SetTitleOffset(1.3);

//printf("NoE=%f", h3->GetEntries());
 
}