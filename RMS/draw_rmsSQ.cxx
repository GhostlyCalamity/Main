void draw_rmsSQ()
{
	char buf[100];
TFile *f = new TFile("run3/run3.root");
TH2F *h1;
//h->SetBins(100, 0, 1);
//TH2F *h2;

//TH2F *h1 = new TH2F(buf,"h title", 200,-70,70,200,-70,70);
//h1 = (TH2F*)f->Get("ITHitMonitor/201");

TString OutFileName = "SQ.pdf";
//OutFileName = "1.pdf";

TCutG *cutg= new TCutG("cut",4);
TCutG *cutg1= new TCutG("cut1",4);
TCutG *cutg2= new TCutG("cut2",4);
TCutG *cutg3= new TCutG("cut3",4);
//TCutG *cutg1= new TCutG("cut1",4);
TCanvas *c1 = new TCanvas("c1","c1");
//TCanvas *c2 = new TCanvas("c2","c2");
//Style->SetPaintTextFormat("3.2e");


OutFileName.ReplaceAll(".pdf",".pdf[");
c1->SaveAs(OutFileName);

for(double i=10.5;i<65;i+=1.5){
	cutg->SetPoint(0, i, -4.5);
	cutg->SetPoint(1, i+9, -4.5);
	cutg->SetPoint(2, i+9, 4.5);
	cutg->SetPoint(3, i, 4.5);

	cutg1->SetPoint(0, -i, -4.5);
	cutg1->SetPoint(1, -i-9, -4.5);
	cutg1->SetPoint(2, -i-9, 4.5);
	cutg1->SetPoint(3, -i, 4.5);

	cutg2->SetPoint(0, -4.5, i);
	cutg2->SetPoint(1, 4.5, i);
	cutg2->SetPoint(2, 4.5, i+9);
	cutg2->SetPoint(3, -4.5, i+9);

	cutg3->SetPoint(0, -4.5, -i);
	cutg3->SetPoint(1, 4.5, -i);
	cutg3->SetPoint(2, 4.5, -i-9);
	cutg3->SetPoint(3, -4.5, -i-9);
	sprintf(buf, "h%i", i);	
	h1 = new TH2F(buf,"h title", 200,0.,50.,200,0.,50.);
	h1 = (TH2F*)f->Get("TTHitMonitor/201");
	h1->SetAxisRange(-70., 70., "Y");
	h1->SetAxisRange(-70., 75., "X");
	  
	c1->cd();
	h1->Draw( "[cut]");
	h1->Draw("[cut1]&same");
	h1->Draw("[cut2]&same");
	h1->Draw("[cut3]&same");
	//c2->cd();
	//h2->Draw("[cut1]");

	gPad->Update();
	OutFileName.ReplaceAll(".pdf[",".pdf");
	c1->SaveAs(OutFileName);
	delete h1;
 }
 OutFileName.ReplaceAll(".pdf",".pdf]");
 c1->SaveAs(OutFileName);
}