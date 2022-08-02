#include "myFunctions.cpp"

void xsec_data() {

//	TFile *input1 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range1_Data__C12_1.161000.root");
//	TFile *input2 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range2_Data__C12_1.161000.root");
//	TFile *input3 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range3_Data__C12_1.161000.root");

//	TFile *input1 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range1_Genie_2_C12_1.161000.root");
//	TFile *input2 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range2_Genie_2_C12_1.161000.root");
//	TFile *input3 = TFile::Open("/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_Range3_Genie_2_C12_1.161000.root");
	
//	TFile *input1 = TFile::Open("/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis24/Exclusive/Exclusive_mine_Range1_Genie_2_C12_1.161000.root");
//	TFile *input2 = TFile::Open("/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis24/Exclusive/Exclusive_mine_Range2_Genie_2_C12_1.161000.root");
//	TFile *input3 = TFile::Open("/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis24/Exclusive/Exclusive_mine_Range3_Genie_2_C12_1.161000.root");
	
//	TFile *input1 = TFile::Open("/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis24/Exclusive/Exclusive_Range1_Genie_2_C12_1.161000.root");
//	TFile *input2 = TFile::Open("/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis24/Exclusive/Exclusive_Range2_Genie_2_C12_1.161000.root");
//	TFile *input3 = TFile::Open("/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis24/Exclusive/Exclusive_Range3_Genie_2_C12_1.161000.root");

/*
	TH2D* h1_prot_momentum1[3];
	TH1D* h1_prot_momentum[3];
//	h1_prot_momentum[0] = (TH1D*)input1->Get(TString::Format("h1_prot_mom"));
//	h1_prot_momentum[1] = (TH1D*)input2->Get(TString::Format("h1_prot_mom"));
//	h1_prot_momentum[2] = (TH1D*)input3->Get(TString::Format("h1_prot_mom"));

	h1_prot_momentum1[0] = (TH2D*)input1->Get(TString::Format("h2_el_prot_mom"));
	h1_prot_momentum1[1] = (TH2D*)input2->Get(TString::Format("h2_el_prot_mom"));
	h1_prot_momentum1[2] = (TH2D*)input3->Get(TString::Format("h2_el_prot_mom"));
	
	h1_prot_momentum[0] = h1_prot_momentum1[0]->ProjectionY("0");
	h1_prot_momentum[1] = h1_prot_momentum1[1]->ProjectionY("1");
	h1_prot_momentum[2] = h1_prot_momentum1[2]->ProjectionY("2");*/

//////////////////////////////////////////////////////////////////////////////////////
      	const int N_RANGES = 3; // number of Ranges; see similarities in thetaEl arguments in file_names below
        const int N_FILES = N_RANGES * 2 * 2; 
	const int N_SECTORS = 6; // number of sectors
        const int N_INT = 4; // number of interactions 

	TFile *input_data_excl;

        std::string data_excl[N_RANGES];

        data_excl[0] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Exclusive_Range1_Data__C12_2.261000.root";
        data_excl[1] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Exclusive_Range2_Data__C12_2.261000.root";
        data_excl[2] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Exclusive_Range3_Data__C12_2.261000.root";
       
	//exclusive histograms: proton momenta
	TH1D* h1_prot_mom_sectors_data[N_RANGES][N_SECTORS];

	 for (int file_i = 0; file_i < N_RANGES; file_i++){
		input_data_excl = TFile::Open( TString::Format("%s", data_excl[file_i].c_str()));	
		// loop over sectors
                for (int sector = 0; sector < N_SECTORS; sector++) {
			 h1_prot_mom_sectors_data[file_i][sector] = (TH1D*)input_data_excl->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", sector));
                        // loop over interactions for MC
                        for (int interaction = 0; interaction < N_INT; interaction++) {

                                if (interaction == 0) {


                        if(sector == 0 && interaction == 0) continue;

			else {
                                }
                        }}
			if(sector == 0) continue;
                        else {
                                h1_prot_mom_sectors_data[file_i][0]->Add(h1_prot_mom_sectors_data[file_i][sector]);
                        }
                        
}}




//////////////////////////////////////////////////////////////////////////////////////

	
	double integral[3];	
	double err[3];

	TCanvas* c;
	c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);
	const int color_options[3] = {kBlue, kRed, kBlack};
	const char * draw_options[3] = {"HIST","HIST SAME","HIST SAME"};

	UniversalE4vFunction(h1_prot_mom_sectors_data[0][0],"Pinned Data","12C","2_261","h1_prot_mom");
	UniversalE4vFunction(h1_prot_mom_sectors_data[1][0],"Pinned Data","12C","2_261","h1_prot_mom");
	UniversalE4vFunction(h1_prot_mom_sectors_data[2][0],"Pinned Data","12C","2_261","h1_prot_mom");
	
//	UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc[0][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom_sectors_interactions_mc");
//	UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc[1][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom_sectors_interactions_mc");
//	UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc[2][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom_sectors_interactions_mc");
	
//	UniversalE4vFunction(h1_prot_momentum[0],"G2018 QE Only","12C","2_261","h1_prot_mom");
//	UniversalE4vFunction(h1_prot_momentum[1],"G2018 QE Only","12C","2_261","h1_prot_mom");
//	UniversalE4vFunction(h1_prot_momentum[2],"G2018 QE Only","12C","2_261","h1_prot_mom");

//	UniversalE4vFunction(h1_prot_momentum[0],"G2018 NoRad","12C","2_261","h1_prot_mom");
//	UniversalE4vFunction(h1_prot_momentum[1],"G2018 NoRad","12C","2_261","h1_prot_mom");
//	UniversalE4vFunction(h1_prot_momentum[2],"G2018 NoRad","12C","2_261","h1_prot_mom");
	double tot_xsec = 0;
	for (int i=0;i<3;i++){
		h1_prot_mom_sectors_data[i][0]->SetStats(0);
		h1_prot_mom_sectors_data[i][0]->SetLineColor(color_options[i]);
		h1_prot_mom_sectors_data[i][0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
		h1_prot_mom_sectors_data[i][0]->Rebin(10);	
		//h1_prot_momentum[i]->GetYaxis()->SetTitle("d^{2}#sigma/dEd#Omega");
		h1_prot_mom_sectors_data[i][0]->GetYaxis()->SetTitle("absolute double differential cross section");
		h1_prot_mom_sectors_data[i][0]->GetXaxis()->SetRangeUser(0,2);
	//	h1_prot_momentum[i]->SetMaximum(.1);
		//h1_prot_multiplicity[i]->SetMinimum(1);
		//h1_prot_momentum[i]->GetXaxis()->CenterTitle(true);
		//h1_prot_momentum[i]->GetYaxis()->CenterTitle(true);
		h1_prot_mom_sectors_data[i][0]->SetTitle("C-12 @ 2.261 GeV e^{-} Beam (CLAS with exclusive cuts)");
		//h1_prot_momentum[i]->SetTitle("C-12 @ 1.161 GeV e^{-} Beam (CLAS with exclusive cuts)");
		h1_prot_mom_sectors_data[i][0]->Draw(draw_options[i]);
		integral[i] = h1_prot_mom_sectors_data[i][0]->IntegralAndError(1,h1_prot_mom_sectors_data[i][0]->GetNbinsX(),err[i],"width");
		std::cout << "Range " << i+1 << " cross section: " << integral[i] << " +/- " << err[i] << std::endl; 
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
	legend->AddEntry(h1_prot_mom_sectors_data[0][0],"Range 1","l");
	legend->AddEntry(h1_prot_mom_sectors_data[1][0],"Range 2","l");
	legend->AddEntry(h1_prot_mom_sectors_data[2][0],"Range 3","l");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->Draw();

	c->SaveAs(TString::Format("data_excl_C12_2261_xsec.pdf"));

}
