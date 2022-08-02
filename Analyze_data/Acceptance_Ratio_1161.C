#include "myFunctions.cpp"


void Acceptance_Ratio_1161() {

//////////////////////////////////////////////////////////////////////////////////////

      	const int N_RANGES = 3; // number of Ranges; see similarities in thetaEl arguments in file_names below
        const int N_FILES = N_RANGES * 2 * 2; 
	const int N_SECTORS = 6; // number of sectors
        const int N_INT = 4; // number of interactions 

	TFile *input_mc_excl;
	TFile *input_mc_excl_susa;
	TFile *input_mc_excl1;
	TFile *input_mc_excl1_susa;

        std::string mc_excl[N_RANGES];
        std::string mc_excl_susa[N_RANGES];
        std::string mc_excl1[N_RANGES];
        std::string mc_excl1_susa[N_RANGES];

//        mc_excl[0] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_FSI_Range1_Genie_2_C12_1.161000.root";
//        mc_excl[0] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_FSI_Range2_Genie_2_C12_1.161000.root";
//        mc_excl[1] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis17/fixed_Q2_2/Exclusive/Exclusive_FSI_Range3_Genie_2_C12_1.161000.root";

	
//        mc_excl[0] = "../output/output2022/Analysis26/Genie_2_C12_2.261000.root";
 //       mc_excl1[0] = "../output/output2022/Analysis26/true_Genie_2_C12_2.261000.root";

            
/*        mc_excl_susa[0] = "../output/output2022/Analysis26/Exclusive/Exclusive_reco_Range1_Genie_1_C12_2.261000.root";
        mc_excl_susa[1] = "../output/output2022/Analysis26/Exclusive/Exclusive_reco_Range2_Genie_1_C12_2.261000.root";
        mc_excl_susa[2] = "../output/output2022/Analysis26/Exclusive/Exclusive_reco_Range3_Genie_1_C12_2.261000.root";

        mc_excl1_susa[0] = "../output/output2022/Analysis26/Exclusive/Exclusive_Range1_Genie_1_C12_2.261000.root";
        mc_excl1_susa[1] = "../output/output2022/Analysis26/Exclusive/Exclusive_Range2_Genie_1_C12_2.261000.root";
        mc_excl1_susa[2] = "../output/output2022/Analysis26/Exclusive/Exclusive_Range3_Genie_1_C12_2.261000.root";
  
	mc_excl[0] = "../output/output2022/Analysis26/Exclusive/Exclusive_reco_accept_Range1_Genie_2_C12_2.261000.root";
        mc_excl[1] = "../output/output2022/Analysis26/Exclusive/Exclusive_reco_accept_Range2_Genie_2_C12_2.261000.root";
        mc_excl[2] = "../output/output2022/Analysis26/Exclusive/Exclusive_reco_accept_Range3_Genie_2_C12_2.261000.root";

        mc_excl1[0] = "../output/output2022/Analysis26/Exclusive/Exclusive_Range1_Genie_2_C12_2.261000.root";
        mc_excl1[1] = "../output/output2022/Analysis26/Exclusive/Exclusive_Range2_Genie_2_C12_2.261000.root";
        mc_excl1[2] = "../output/output2022/Analysis26/Exclusive/Exclusive_Range3_Genie_2_C12_2.261000.root";
 */

        mc_excl_susa[1] = "../output/output2022/Analysis31/Exclusive/Exclusive_1p0pi_reco_Range2_Genie_1_C12_1.161000.root";
        mc_excl_susa[2] = "../output/output2022/Analysis31/Exclusive/Exclusive_1p0pi_reco_Range3_Genie_1_C12_1.161000.root";

        mc_excl1_susa[1] = "../output/output2022/Analysis31/Exclusive/Exclusive_1p0pi_true_Range2_Genie_1_C12_1.161000.root";
        mc_excl1_susa[2] = "../output/output2022/Analysis31/Exclusive/Exclusive_1p0pi_true_Range3_Genie_1_C12_1.161000.root";

        mc_excl[1] = "../output/output2022/Analysis31/Exclusive/Exclusive_1p0pi_reco_Range2_Genie_2_C12_1.161000.root";
        mc_excl[2] = "../output/output2022/Analysis31/Exclusive/Exclusive_1p0pi_reco_Range3_Genie_2_C12_1.161000.root";

        mc_excl1[1] = "../output/output2022/Analysis31/Exclusive/Exclusive_1p0pi_true_Range2_Genie_2_C12_1.161000.root";
        mc_excl1[2] = "../output/output2022/Analysis31/Exclusive/Exclusive_1p0pi_true_Range3_Genie_2_C12_1.161000.root";
/* 
       mc_excl_susa[0] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range1_Genie_1_C12_2.261000.root";
        mc_excl_susa[1] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range2_Genie_1_C12_2.261000.root";
        mc_excl_susa[2] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range3_Genie_1_C12_2.261000.root";

        mc_excl1_susa[0] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_true_Range1_Genie_1_C12_2.261000.root";
        mc_excl1_susa[1] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_true_Range2_Genie_1_C12_2.261000.root";
        mc_excl1_susa[2] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_true_Range3_Genie_1_C12_2.261000.root";

        mc_excl[0] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range1_Genie_2_C12_2.261000.root";
        mc_excl[1] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range2_Genie_2_C12_2.261000.root";
        mc_excl[2] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range3_Genie_2_C12_2.261000.root";

        mc_excl1[0] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_true_Range1_Genie_2_C12_2.261000.root";
        mc_excl1[1] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_true_Range2_Genie_2_C12_2.261000.root";
        mc_excl1[2] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_true_Range3_Genie_2_C12_2.261000.root";
 */  
	//exclusive histograms: proton momenta
        TH1D* h1_prot_mom_sectors_interactions_mc[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc_susa[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc1[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc1_susa[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc2[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc2_susa[N_RANGES][N_SECTORS][N_INT];
        
	TH1D* h1_prot_mom_sectors_interactions_mc3[N_RANGES][N_SECTORS][N_INT];

	 for (int file_i = 1; file_i < N_RANGES; file_i++){
	 //for (int file_i = 0; file_i < 1; file_i++){
                input_mc_excl = TFile::Open( TString::Format("%s", mc_excl[file_i].c_str()));
                input_mc_excl_susa = TFile::Open( TString::Format("%s", mc_excl_susa[file_i].c_str()));
                input_mc_excl1 = TFile::Open( TString::Format("%s", mc_excl1[file_i].c_str()));
                input_mc_excl1_susa = TFile::Open( TString::Format("%s", mc_excl1_susa[file_i].c_str()));
		// loop over sectors
                for (int sector = 0; sector < N_SECTORS; sector++) {

                        // loop over interactions for MC
                        for (int interaction = 0; interaction < N_INT; interaction++) {
                                h1_prot_mom_sectors_interactions_mc[file_i][sector][interaction] = (TH1D*)input_mc_excl->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interaction+1, sector));
                                h1_prot_mom_sectors_interactions_mc_susa[file_i][sector][interaction] = (TH1D*)input_mc_excl_susa->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interaction+1, sector));
                                h1_prot_mom_sectors_interactions_mc1[file_i][sector][interaction] = (TH1D*)input_mc_excl1->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interaction+1, sector));
                                h1_prot_mom_sectors_interactions_mc1_susa[file_i][sector][interaction] = (TH1D*)input_mc_excl1_susa->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interaction+1, sector));

                                if (interaction == 0) {


                        if(sector == 0 && interaction == 0) continue;

			else {
                                        h1_prot_mom_sectors_interactions_mc[file_i][0][0]->Add(h1_prot_mom_sectors_interactions_mc[file_i][sector][interaction]);
                                        h1_prot_mom_sectors_interactions_mc_susa[file_i][0][0]->Add(h1_prot_mom_sectors_interactions_mc_susa[file_i][sector][interaction]);
                                        h1_prot_mom_sectors_interactions_mc1[file_i][0][0]->Add(h1_prot_mom_sectors_interactions_mc1[file_i][sector][interaction]);
                                        h1_prot_mom_sectors_interactions_mc1_susa[file_i][0][0]->Add(h1_prot_mom_sectors_interactions_mc1_susa[file_i][sector][interaction]);
                                }
                        }

                        }
}}




//////////////////////////////////////////////////////////////////////////////////////

	
	double integral[3];	
	double err[3];

	TCanvas* c;
	c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);
	const int color_options[3] = {kBlue, kRed, kBlack};
	const char * draw_options[4] = {"HIST","HIST SAME","HIST SAME","HIST SAME"};

	h1_prot_mom_sectors_interactions_mc2[1][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1[1][0][0]->Clone("h22");
	h1_prot_mom_sectors_interactions_mc2[2][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1[2][0][0]->Clone("h23");
	h1_prot_mom_sectors_interactions_mc2_susa[1][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1_susa[1][0][0]->Clone("h22susa");
	h1_prot_mom_sectors_interactions_mc2_susa[2][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1_susa[2][0][0]->Clone("h23susa");
        //SuSav2 true (for acceptance)  
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2_susa[1][0][0],"SuSav2 QE Only","12C","1_161","h1_prot_mom2");
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2_susa[2][0][0],"SuSav2 QE Only","12C","1_161","h1_prot_mom3");
        //SuSav2 reco (for acceptance)
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc_susa[1][0][0],"SuSav2 QE Only","12C","1_161","h1_prot_mom5");
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc_susa[2][0][0],"SuSav2 QE Only","12C","1_161","h1_prot_mom6");
        //Genie true (for acceptance)   
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2[1][0][0],"G2018 QE Only","12C","1_161","h1_prot_mom8");
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2[2][0][0],"G2018 QE Only","12C","1_161","h1_prot_mom9");
        //Genie reco (for acceptance)
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc[1][0][0],"G2018 QE Only","12C","1_161","h1_prot_mom11");
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc[2][0][0],"G2018 QE Only","12C","1_161","h1_prot_mom12");
	//h1_prot_mom_sectors_interactions_mc2[0][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1[0][0][0]->Clone("h21");

	double tot_xsec = 0;
//	for (int i=0;i<1;i++){
	for (int i=1;i<3;i++){
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->Rebin(40);
		h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Rebin(40);
		//h1_prot_mom_sectors_interactions_mc1[i][0][0]->Rebin(40);
		h1_prot_mom_sectors_interactions_mc[i][0][0]->Rebin(40);
		h1_prot_mom_sectors_interactions_mc_susa[i][0][0]->Rebin(40);
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->Divide(h1_prot_mom_sectors_interactions_mc[i][0][0]);
		h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Divide(h1_prot_mom_sectors_interactions_mc_susa[i][0][0]);
		
		h1_prot_mom_sectors_interactions_mc3[i][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Clone("a");
		h1_prot_mom_sectors_interactions_mc3[i][0][0]->Add(h1_prot_mom_sectors_interactions_mc2[i][0][0]);
		h1_prot_mom_sectors_interactions_mc3[i][0][0]->Scale(0.5);
	
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->SetStats(0);
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->SetLineColor(color_options[i]);
		h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->SetLineColor(color_options[i]);
		h1_prot_mom_sectors_interactions_mc3[i][0][0]->SetLineColor(color_options[i]);
		h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->SetLineStyle(kDashed);
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->SetLineStyle(kDotted);
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
		//h1_prot_mom_sectors_interactions_mc2[i][0][0]->Rebin(10);	
		//h1_prot_momentum[i]->GetYaxis()->SetTitle("d^{2}#sigma/dEd#Omega");
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->GetYaxis()->SetTitle("Ratio (true/reco)");
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->GetXaxis()->SetRangeUser(0,2);
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->GetYaxis()->SetRangeUser(0,3);
	//	h1_prot_momentum[i]->SetMaximum(.1);
		//h1_prot_multiplicity[i]->SetMinimum(1);
		//h1_prot_momentum[i]->GetXaxis()->CenterTitle(true);
		//h1_prot_momentum[i]->GetYaxis()->CenterTitle(true);
		//h1_prot_mom_sectors_interactions_mc[i][0][0]->SetTitle("C-12 @ 1.161 GeV e^{-} Beam (GENIE QE only with no FSI and exclusive cuts)");
		//h1_prot_mom_sectors_interactions_mc[i][0][0]->SetTitle("C-12 @ 1.161 GeV e^{-} Beam (GENIE QE only with no FSI and exclusive cuts)");
		//h1_prot_momentum[i]->SetTitle("C-12 @ 1.161 GeV e^{-} Beam (CLAS with exclusive cuts)");
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->Draw(draw_options[i]);
		h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Draw(draw_options[i+1]);
		h1_prot_mom_sectors_interactions_mc3[i][0][0]->Draw(draw_options[i+1]);
		//integral[i] = h1_prot_mom_sectors_interactions_mc[i][0][0]->IntegralAndError(1,h1_prot_mom_sectors_interactions_mc[i][0][0]->GetNbinsX(),err[i],"width");
		//std::cout << "Range " << i+1 << " cross section: " << integral[i] << " +/- " << err[i] << std::endl; 
		//tot_xsec += integral[i];
	}
	//std::cout << tot_xsec << std::endl;
	c->SetLeftMargin(0.13);
	//c->SetLogy();
	c->Update();

	TLegend *legend = new TLegend(0.7, 0.6, 0.875, 0.88);
	//legend->AddEntry(h1_prot_momentum[0],"SuSav2","l");
	//legend->AddEntry(h1_prot_momentum[1],"CLAS","l");
	//legend->AddEntry(h1_prot_momentum[2],"SuSav2, No Background Weight","l");
	//legend->AddEntry(h1_prot_momentum[3],"CLAS, No Background Weight","l");
	legend->AddEntry(h1_prot_mom_sectors_interactions_mc2[1][0][0],"Genie Range 2","l");
	legend->AddEntry(h1_prot_mom_sectors_interactions_mc2[2][0][0],"Genie Range 3","l");
	legend->AddEntry(h1_prot_mom_sectors_interactions_mc2_susa[1][0][0],"SuSav2 Range 2","l");
	legend->AddEntry(h1_prot_mom_sectors_interactions_mc2_susa[2][0][0],"SuSav2 Range 3","l");
	legend->AddEntry(h1_prot_mom_sectors_interactions_mc3[1][0][0],"Average Range 2","l");
	legend->AddEntry(h1_prot_mom_sectors_interactions_mc3[2][0][0],"Average Range 3","l");
	legend->SetBorderSize(0);
	legend->SetFillStyle(0);
	legend->Draw();

	c->SaveAs(TString::Format("Acceptance_xsec_ratios_combined_avg_C12_1161.pdf"));

}
