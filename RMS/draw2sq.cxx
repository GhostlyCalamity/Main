void draw2sq()
{
TFile *f = new TFile("run3/run3.root");
TH2F * h1 = new TH2F("h1","h1 title", 200,-150,150,200,-150,150);
h1 = (TH2F*)f->Get("TTHitMonitor/201");
TH1D *h2, *h22;
TH1D *h3 =new TH1D("hrl", "hits vs sensor(6x6 cm^{2}) right&left edge position, Run3/TT; |x_{min}| coordinate [cm]; MIPs/s per sensor", 70, 0, 70);
TH1D *h33 =new TH1D("left", "hits vs sensor(6x6 cm^{2}) right&left edge position, Run3/TT; |x_{min}| coordinate [cm]; MIPs/s per sensor", 70, 0, 70);
TH1D *h8, *h88;
TH1D *h9 =new TH1D("htl", "hits vs sensor(6x6 cm^{2}) bottom&top edge position, Run3/TT; |y_{min}| coordinate [cm]; MIPs/s per sensor", 70, 0, 70);
TH1D *h99 =new TH1D("bot", "hits vs sensor(6x6 cm^{2}) bottom&top edge position, Run3/TT; |y_{min}| coordinate [cm]; MIPs/s per sensor ", 70, 0, 70);

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
for(int i=3;i<60;i+=1.5){
cutg->SetPoint(0, i, -3);
cutg->SetPoint(1, i+6, -3);
cutg->SetPoint(2, i+6, 3);
cutg->SetPoint(3, i, 3);

 cutg_inv->SetPoint(0, -i, -3);
 cutg_inv->SetPoint(1, -i-6, -3);
 cutg_inv->SetPoint(2, -i-6, 3);
 cutg_inv->SetPoint(3, -i, 3);
	
h2= h1->ProjectionX("h2", 1, -1, "[cut]");
h22 = h1->ProjectionX("h22", 1, -1, "[cut_inv]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
h3->SetBinContent(i+1,(h2->GetEntries()));
h33->SetBinContent(i+1,h22->GetEntries());
}
c1->cd();

h33->SetFillColor(kGreen-3);
h33->SetBarWidth(0.35);
h33->SetBarOffset(0.5);
h33->SetStats(0);
h33->Draw("hist&text&b3");

h3->SetFillColor(kBlue+3);
h3->SetBarWidth(0.35);
h3->SetBarOffset(0.15);
h3->SetStats(0);
h3->Draw("same&hist&b3");





TLegend *leg = new TLegend(0.65,0.65,0.90,0.90);
  leg->AddEntry("hrl", "right sensor", "f");
  leg->AddEntry("left", "left sensor", "f");
  leg->Draw("same");

//h3->GetXaxis()->SetTitle("left edge position, cm");
h3->GetXaxis()->SetTitleOffset(1.3);
////h3->GetYaxis()->SetTitle("MIPs/s per sensor (9x9 cm^{2})");
h3->GetYaxis()->SetTitleOffset(1.3);


//top 
for(int i=3;i<59;i+=1.5){
cutg4->SetPoint(0, -3, i);
cutg4->SetPoint(1, 3, i);
cutg4->SetPoint(2, 3, i+6);
cutg4->SetPoint(3, -3, i+6);

cutg_inv2->SetPoint(0, -3, -i);
cutg_inv2->SetPoint(1, 3, -i);
cutg_inv2->SetPoint(2, 3, -i-6);
cutg_inv2->SetPoint(3, -3, -i-6);

h8= h1->ProjectionX("h8", 1, -1, "[cut4]");
h88= h1->ProjectionX("h88", 1, -1, "[cutinv2]");
//cout<<"i="<<i<<", NoH="<<h4->GetEntries()<<"\n";
h9->SetBinContent(i+1,(h8->GetEntries()));
h99->SetBinContent(i+1,(h88->GetEntries()));
}
c4->cd();
h9->SetFillColor(kBlue+3);
h9->SetBarWidth(0.35);
h9->SetBarOffset(0.15);
h9->SetStats(0);
h9->Draw("hist&b3");

h99->SetFillColor(kGreen-3);
h99->SetBarWidth(0.35);
h99->SetBarOffset(0.5);
h99->SetStats(0);
h99->Draw("same&hist&text&b3");

TLegend *leg1 = new TLegend(0.65,0.65,0.90,0.90);
  leg1->AddEntry("htl", "top sensor", "f");
  leg1->AddEntry("bot", "bottom sensor", "f");
  leg1->Draw("same");

//h9->GetXaxis()->SetTitle("left edge position, sm");
h9->GetXaxis()->SetTitleOffset(1.3);
//h9->GetYaxis()->SetTitle("MIPs/s per sensor (9x9 cm^{2})");
h9->GetYaxis()->SetTitleOffset(1.3);

//printf("NoE=%f", h3->GetEntries());
 
}