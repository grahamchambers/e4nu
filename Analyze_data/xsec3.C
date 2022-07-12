#include "myFunctions.cpp"


void xsec3() {

	TFile *input1 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range1_Data__C12_2.261000.root");
	TFile *input2 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range2_Data__C12_2.261000.root");
	TFile *input3 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range3_Data__C12_2.261000.root");

//	TFile *input1 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range1_Genie_2_C12_2.261000.root");
//	TFile *input2 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range2_Genie_2_C12_2.261000.root");
//	TFile *input3 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range3_Genie_2_C12_2.261000.root");

	TH2D* h1_prot_momentum1[3];
	TH1D* h1_prot_momentum[3];
	h1_prot_momentum[0] = (TH1D*)input1->Get(TString::Format("h1_prot_mom"));
	h1_prot_momentum[1] = (TH1D*)input2->Get(TString::Format("h1_prot_mom"));
	h1_prot_momentum[2] = (TH1D*)input3->Get(TString::Format("h1_prot_mom"));

//	h1_prot_momentum1[0] = (TH2D*)input1->Get(TString::Format("h2_el_prot_mom"));
//	h1_prot_momentum1[1] = (TH2D*)input2->Get(TString::Format("h2_el_prot_mom"));
//	h1_prot_momentum1[2] = (TH2D*)input3->Get(TString::Format("h2_el_prot_mom"));
	
//	h1_prot_momentum[0] = h1_prot_momentum1[0]->ProjectionY("0");
//	h1_prot_momentum[1] = h1_prot_momentum1[1]->ProjectionY("1");
//	h1_prot_momentum[2] = h1_prot_momentum1[2]->ProjectionY("2");
	
	double integral[3];	
	double err[3];

	TCanvas* c;
	c= new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);
	const int color_options[3] = {kBlue, kRed, kBlack};
	const char * draw_options[3] = {"HIST","HIST SAME","HIST SAME"};

	UniversalE4vFunction(h1_prot_momentum[0],"Data","12C","2_261","h1_prot_mom");
	UniversalE4vFunction(h1_prot_momentum[1],"Data","12C","2_261","h1_prot_mom");
	UniversalE4vFunction(h1_prot_momentum[2],"Data","12C","2_261","h1_prot_mom");
	
//	UniversalE4vFunction(h1_prot_momentum[0],"G2018 QE Only","12C","2_261","h1_prot_mom");
//	UniversalE4vFunction(h1_prot_momentum[1],"G2018 QE Only","12C","2_261","h1_prot_mom");
//	UniversalE4vFunction(h1_prot_momentum[2],"G2018 QE Only","12C","2_261","h1_prot_mom");

//	UniversalE4vFunction(h1_prot_momentum[0],"G2018","12C","2_261","h1_prot_mom");
//	UniversalE4vFunction(h1_prot_momentum[1],"G2018","12C","2_261","h1_prot_mom");
//	UniversalE4vFunction(h1_prot_momentum[2],"G2018","12C","2_261","h1_prot_mom");
	double tot_xsec = 0;
	for (int i=0;i<3;i++){
		h1_prot_momentum[i]->SetStats(0);
		h1_prot_momentum[i]->SetLineColor(color_options[i]);
		h1_prot_momentum[i]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
		h1_prot_momentum[i]->Rebin(10);	
		//h1_prot_momentum[i]->GetYaxis()->SetTitle("d^{2}#sigma/dEd#Omega");
		h1_prot_momentum[i]->GetYaxis()->SetTitle("absolute double differential cross section [#mub]");
		h1_prot_momentum[i]->GetXaxis()->SetRangeUser(0,2);
	//	h1_prot_momentum[i]->SetMaximum(.1);
		//h1_prot_multiplicity[i]->SetMinimum(1);
		//h1_prot_momentum[i]->GetXaxis()->CenterTitle(true);
		//h1_prot_momentum[i]->GetYaxis()->CenterTitle(true);
		h1_prot_momentum[i]->SetTitle("C-12 @ 2.261 GeV e^{-} Beam (CLAS with exclusive cuts)");
		//h1_prot_momentum[i]->SetTitle("C-12 @ 2.261 GeV e^{-} Beam (CLAS with exclusive cuts)");
		h1_prot_momentum[i]->Draw(draw_options[i]);
		integral[i] = h1_prot_momentum[i]->IntegralAndError(1,h1_prot_momentum[i]->GetNbinsX(),err[i],"width");
		std::cout << "Range 1 cross section: " << integral[i] << " +/- " << err[i] << std::endl; 
		tot_xsec += integral[i];
	}
	std::cout << tot_xsec << std::endl;
	c->SetLeftMargin(0.13);
	//c->SetLogy();
	c->Update();

	TLegend *legend = new TLegend(0.75, 0.7, 0.9, 0.88);
	//legend->AddEntry(h1_prot_momentum[0],"SuSav2","l");
	//legend->AddEntry(h1_prot_momentum[1],"CLAS","l");
	//legend->AddEntry(h1_prot_momentum[2],"SuSav2, No Background Weight","l");
	//legend->AddEntry(h1_prot_momentum[3],"CLAS, No Background Weight","l");
	legend->AddEntry(h1_prot_momentum[0],"Range 1","l");
	legend->AddEntry(h1_prot_momentum[1],"Range 2","l");
	legend->AddEntry(h1_prot_momentum[2],"Range 3","l");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->Draw();

	c->SaveAs(TString::Format("prot_xsec_C12_2261_data_allranges.pdf"));

}
