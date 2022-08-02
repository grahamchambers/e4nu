void plot2() {

	TFile *input1 = TFile::Open("C12_2261_all_nocuts.root");
	
	TH1D* h1 = (TH1D*)input1->Get(TString::Format("Thetap_sector6"));

	TCanvas* c;
	c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

	h1->Rebin(4);
	h1->Sumw2();
	h1->GetXaxis()->SetTitle("Proton Theta [degrees]");
	h1->GetYaxis()->SetTitle("Events");
	h1->GetXaxis()->SetRangeUser(0,200);
	h1->SetTitle("SuSav2 C12 @ 2.261 GeV, 300 < #phi_{e} < 360");
	h1->SetStats(0);
	h1->Draw("hist");
	h1->Draw("e same"); 

	c->SaveAs(TString::Format("SuSav2_C12_2261_proton_theta_el_sector6.pdf"));

}
