#include "myFunctions.cpp"

double weighted_average(TH1D* h1) {
        double num_sum = 0.0;
        double den_sum = 0.0;
        for (int i = 0; i < h1->GetNbinsX(); i++) {
                if (h1->GetBinContent(i) == 0) continue;
                num_sum += h1->GetBinCenter(i)*h1->GetBinContent(i);
                den_sum += h1->GetBinContent(i);
        }

        return num_sum/den_sum;
}

void xsec_data_corr2() {

      	const int N_RANGES = 3; // number of Ranges; see similarities in thetaEl arguments in file_names below
        const int N_FILES = N_RANGES * 2 * 2; 
	const int N_SECTORS = 6; // number of sectors
        const int N_INT = 4; // number of interactions 

	TFile *input_data_excl;
	TFile *input_data_incl;

        std::string data_excl[N_RANGES];
        std::string data_incl[N_RANGES];

        data_excl[0] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Exclusive_Range1_Data__C12_2.261000.root";
        data_excl[1] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Exclusive_Range2_Data__C12_2.261000.root";
        data_excl[2] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Exclusive_Range3_Data__C12_2.261000.root";
      
        data_incl[0] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Inclusive_Range1_Data__C12_2.261000.root";
        data_incl[1] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Inclusive_Range2_Data__C12_2.261000.root";
        data_incl[2] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Inclusive_Range3_Data__C12_2.261000.root";

	double neutron_corr[3] = {0.75832654,0.72603164,0.66924105};
	double neutron_corr_err[3] = {0.,0.,0.};

	double mec_corr[3] = {0.923233,0.906029,0.893632};
	double mec_corr_err[3] = {0.00201456,0.00352721,0.00952721};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//histograms for acceptance correction

	TFile *input_mc_excl;
        TFile *input_mc_excl_susa;
        TFile *input_mc_excl1;
        TFile *input_mc_excl1_susa;

        std::string mc_excl[N_RANGES];
        std::string mc_excl_susa[N_RANGES];
        std::string mc_excl1[N_RANGES];
        std::string mc_excl1_susa[N_RANGES];
	
        TFile *input_mc_excl_radcorr;
        TFile *input_mc_excl_susa_radcorr;
        TFile *input_mc_excl1_radcorr;
        TFile *input_mc_excl1_susa_radcorr;

//histograms for rad correction
        std::string mc_excl_radcorr[N_RANGES];
        std::string mc_excl_susa_radcorr[N_RANGES];
        std::string mc_excl1_radcorr[N_RANGES];
        std::string mc_excl1_susa_radcorr[N_RANGES];

//load histograms for acceptance
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

//load histograms for rad correction
	mc_excl_susa_radcorr[0] = "../output/output2022/Analysis28/Exclusive/Rad_Exclusive_e4v_reco_Range1_Genie_2_C12_2.261000.root";
        mc_excl_susa_radcorr[1] = "../output/output2022/Analysis28/Exclusive/Rad_Exclusive_e4v_reco_Range2_Genie_2_C12_2.261000.root";
        mc_excl_susa_radcorr[2] = "../output/output2022/Analysis28/Exclusive/Rad_Exclusive_e4v_reco_Range3_Genie_2_C12_2.261000.root";
	//mc_excl_susa_radcorr[0] = "../output/output2022/Analysis27/Exclusive/Exclusive_Rad_Range1_Genie_2_C12_2.261000.root";
        //mc_excl_susa_radcorr[1] = "../output/output2022/Analysis27/Exclusive/Exclusive_Rad_Range2_Genie_2_C12_2.261000.root";
        //mc_excl_susa_radcorr[2] = "../output/output2022/Analysis27/Exclusive/Exclusive_Rad_Range3_Genie_2_C12_2.261000.root";

        mc_excl1_susa_radcorr[0] = "../output/output2022/Analysis28/Exclusive/noRad_Exclusive_e4v_reco_Range1_Genie_2_C12_2.261000.root";
        mc_excl1_susa_radcorr[1] = "../output/output2022/Analysis28/Exclusive/noRad_Exclusive_e4v_reco_Range2_Genie_2_C12_2.261000.root";
        mc_excl1_susa_radcorr[2] = "../output/output2022/Analysis28/Exclusive/noRad_Exclusive_e4v_reco_Range3_Genie_2_C12_2.261000.root";
       // mc_excl1_susa_radcorr[0] = "../output/output2022/Analysis27/Exclusive/Exclusive_Range1_Genie_2_C12_2.261000.root";
       // mc_excl1_susa_radcorr[1] = "../output/output2022/Analysis27/Exclusive/Exclusive_Range2_Genie_2_C12_2.261000.root";
       // mc_excl1_susa_radcorr[2] = "../output/output2022/Analysis27/Exclusive/Exclusive_Range3_Genie_2_C12_2.261000.root";
	
//histograms for acceptance
	TH1D* h1_prot_mom_sectors_interactions_mc[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc_susa[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc1[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc1_susa[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc2[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc2_susa[N_RANGES][N_SECTORS][N_INT];

        TH1D* h1_prot_mom_sectors_interactions_mc3[N_RANGES][N_SECTORS][N_INT];

//histograms for rad
	TH1D* h1_prot_mom_sectors_interactions_mc_radcorr[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc_susa_radcorr[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc1_radcorr[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc1_susa_radcorr[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc2_radcorr[N_RANGES][N_SECTORS][N_INT];
        TH1D* h1_prot_mom_sectors_interactions_mc2_susa_radcorr[N_RANGES][N_SECTORS][N_INT];

        TH1D* h1_prot_mom_sectors_interactions_mc3_radcorr[N_RANGES][N_SECTORS][N_INT];

//for loop for rad correction
         for (int file_i = 0; file_i < N_RANGES; file_i++){
         //for (int file_i = 0; file_i < 1; file_i++){
                input_mc_excl_susa_radcorr = TFile::Open( TString::Format("%s", mc_excl_susa_radcorr[file_i].c_str()));
                input_mc_excl1_susa_radcorr = TFile::Open( TString::Format("%s", mc_excl1_susa_radcorr[file_i].c_str()));
                // loop over sectors
                for (int sector = 0; sector < N_SECTORS; sector++) {

                        // loop over interactions for MC
                        for (int interaction = 0; interaction < N_INT; interaction++) {
                                h1_prot_mom_sectors_interactions_mc_susa_radcorr[file_i][sector][interaction] = (TH1D*)input_mc_excl_susa_radcorr->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interaction+1, sector));
                                h1_prot_mom_sectors_interactions_mc1_susa_radcorr[file_i][sector][interaction] = (TH1D*)input_mc_excl1_susa_radcorr->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interaction+1, sector));

                                if (interaction == 0) {


                        if(sector == 0 && interaction == 0) continue;

                        else {
                                        h1_prot_mom_sectors_interactions_mc_susa_radcorr[file_i][0][0]->Add(h1_prot_mom_sectors_interactions_mc_susa_radcorr[file_i][sector][interaction]);
                                        h1_prot_mom_sectors_interactions_mc1_susa_radcorr[file_i][0][0]->Add(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[file_i][sector][interaction]);
                                }
                        }

                        }
}}

//for loop for acceptance correction
	for (int file_i = 0; file_i < N_RANGES; file_i++){
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//for loop for data 
	//exclusive histograms: proton momenta
	TH1D* h1_prot_mom_sectors_data[N_RANGES][N_SECTORS];
	TH1D* h1_prot_mom_sectors_data_incl[N_RANGES][N_SECTORS];

	 for (int file_i = 0; file_i < N_RANGES; file_i++){
		input_data_excl = TFile::Open( TString::Format("%s", data_excl[file_i].c_str()));	
		input_data_incl = TFile::Open( TString::Format("%s", data_incl[file_i].c_str()));	
		// loop over sectors
                for (int sector = 0; sector < N_SECTORS; sector++) {
			 h1_prot_mom_sectors_data[file_i][sector] = (TH1D*)input_data_excl->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", sector));
			 h1_prot_mom_sectors_data_incl[file_i][sector] = (TH1D*)input_data_incl->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_el_mom__%i", sector));
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
                                h1_prot_mom_sectors_data_incl[file_i][0]->Add(h1_prot_mom_sectors_data_incl[file_i][sector]);
                        }
                        
}}




//////////////////////////////////////////////////////////////////////////////////////

	
	double integral[3] = {0.0,0.0,0.0};	
	double integral_incl[3] = {0.0,0.0,0.0};	
	double err[3] = {0.0,0.0,0.0};
	double err_incl[3] = {0.0,0.0,0.0};

	TCanvas* c;
	c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);
	const int color_options[3] = {kBlue, kRed, kBlack};
	const char * draw_options[3] = {"HIST","HIST SAME","HIST SAME"};
//////////////////////////////////////////////////////////////////////////////////////


	h1_prot_mom_sectors_interactions_mc2[0][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1[0][0][0]->Clone("h21");
        h1_prot_mom_sectors_interactions_mc2[1][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1[1][0][0]->Clone("h22");
        h1_prot_mom_sectors_interactions_mc2[2][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1[2][0][0]->Clone("h23");
        h1_prot_mom_sectors_interactions_mc2_susa[0][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1_susa[0][0][0]->Clone("h21susa");
        h1_prot_mom_sectors_interactions_mc2_susa[1][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1_susa[1][0][0]->Clone("h22susa");
        h1_prot_mom_sectors_interactions_mc2_susa[2][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc1_susa[2][0][0]->Clone("h23susa");
	
	//SuSav2 true (for acceptance) 	
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2_susa[0][0][0],"SuSav2 QE Only","12C","2_261","h1_prot_mom1"); 
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2_susa[1][0][0],"SuSav2 QE Only","12C","2_261","h1_prot_mom2");
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2_susa[2][0][0],"SuSav2 QE Only","12C","2_261","h1_prot_mom3"); 
	//SuSav2 reco (for acceptance)
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc_susa[0][0][0],"SuSav2 QE Only","12C","2_261","h1_prot_mom4"); 
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc_susa[1][0][0],"SuSav2 QE Only","12C","2_261","h1_prot_mom5");
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc_susa[2][0][0],"SuSav2 QE Only","12C","2_261","h1_prot_mom6");
	//Genie true (for acceptance) 	
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2[0][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom7"); 
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2[1][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom8");
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc2[2][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom9"); 
	//Genie reco (for acceptance)
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc[0][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom10"); 
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc[1][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom11");
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc[2][0][0],"G2018 QE Only","12C","2_261","h1_prot_mom12");
	//SuSav2 Rad
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc_susa_radcorr[0][0][0],"SuSav2 Rad Updated Schwinger","12C","2_261","h1_prot_mom13"); 
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc_susa_radcorr[1][0][0],"SuSav2 Rad Updated Schwinger","12C","2_261","h1_prot_mom14");
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc_susa_radcorr[2][0][0],"SuSav2 Rad Updated Schwinger","12C","2_261","h1_prot_mom15"); 
        //SuSav2 No Rad 
	UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[0][0][0],"SuSav2 NoRad","12C","2_261","h1_prot_mom16"); 
	UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[1][0][0],"SuSav2 NoRad","12C","2_261","h1_prot_mom16"); 
        UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[2][0][0],"SuSav2 NoRad","12C","2_261","h1_prot_mom17");
       // UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[0][0][0],"SuSav2","12C","2_261","h1_prot_mom18"); 
       // UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[1][0][0],"SuSav2","12C","2_261","h1_prot_mom17");
       // UniversalE4vFunction(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[2][0][0],"SuSav2","12C","2_261","h1_prot_mom18"); 

	//data scaling
	UniversalE4vFunction(h1_prot_mom_sectors_data[0][0],"Pinned Data","12C","2_261","h1_prot_mom19");
	UniversalE4vFunction(h1_prot_mom_sectors_data[1][0],"Pinned Data","12C","2_261","h1_prot_mom20");
	UniversalE4vFunction(h1_prot_mom_sectors_data[2][0],"Pinned Data","12C","2_261","h1_prot_mom21");
	UniversalE4vFunction(h1_prot_mom_sectors_data_incl[0][0],"Pinned Data","12C","2_261","h1_prot_mom22");
	UniversalE4vFunction(h1_prot_mom_sectors_data_incl[1][0],"Pinned Data","12C","2_261","h1_prot_mom23");
	UniversalE4vFunction(h1_prot_mom_sectors_data_incl[2][0],"Pinned Data","12C","2_261","h1_prot_mom24");
	
	double data_avg_prot_mom[N_RANGES];
	double ratio[3] = {0.,0.,0.};
	double ratio_err[3] = {0.,0.,0.};	
	double tot_xsec = 0;
	double tot_xsec_incl = 0;
	for (int i=0;i<3;i++){
		
		data_avg_prot_mom[i] = weighted_average(h1_prot_mom_sectors_data[i][0]);	
		
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->Rebin(40);
                h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Rebin(40);
                //h1_prot_mom_sectors_interactions_mc1[i][0][0]->Rebin(10);
                h1_prot_mom_sectors_interactions_mc[i][0][0]->Rebin(40);
                h1_prot_mom_sectors_interactions_mc_susa[i][0][0]->Rebin(40);
                h1_prot_mom_sectors_interactions_mc2[i][0][0]->Divide(h1_prot_mom_sectors_interactions_mc[i][0][0]);
                h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Divide(h1_prot_mom_sectors_interactions_mc_susa[i][0][0]);
		
                h1_prot_mom_sectors_interactions_mc3[i][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Clone("a");
                h1_prot_mom_sectors_interactions_mc3[i][0][0]->Add(h1_prot_mom_sectors_interactions_mc2[i][0][0]);
                h1_prot_mom_sectors_interactions_mc3[i][0][0]->Scale(0.5);	

		h1_prot_mom_sectors_data[i][0]->SetStats(0);
		h1_prot_mom_sectors_data_incl[i][0]->SetStats(0);
		h1_prot_mom_sectors_data[i][0]->Rebin(40);
		h1_prot_mom_sectors_data_incl[i][0]->Rebin(40);

		h1_prot_mom_sectors_interactions_mc_susa_radcorr[i][0][0]->Rebin(40);
                h1_prot_mom_sectors_interactions_mc1_susa_radcorr[i][0][0]->Rebin(40);
		
		h1_prot_mom_sectors_data[i][0]->Multiply(h1_prot_mom_sectors_interactions_mc3[i][0][0]);
		//h1_prot_mom_sectors_data_incl[i][0]->Multiply(h1_prot_mom_sectors_interactions_mc3[i][0][0]);
		h1_prot_mom_sectors_data[i][0]->Divide(h1_prot_mom_sectors_interactions_mc_susa_radcorr[i][0][0]);
		//h1_prot_mom_sectors_data_incl[i][0]->Divide(h1_prot_mom_sectors_interactions_mc_susa_radcorr[i][0][0]);
		h1_prot_mom_sectors_data[i][0]->Multiply(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[i][0][0]);
		//h1_prot_mom_sectors_data_incl[i][0]->Multiply(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[i][0][0]);

		//h1_prot_mom_sectors_data[i][0]->Divide(h1_prot_mom_sectors_data_incl[i][0]);
	
		h1_prot_mom_sectors_data[i][0]->SetLineColor(color_options[i]);
		h1_prot_mom_sectors_data[i][0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
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
		//h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Draw(draw_options[i]);
		//h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Draw("Hist");
		//integral[i] = h1_prot_mom_sectors_data[i][0]->IntegralAndError(1,h1_prot_mom_sectors_data[i][0]->GetNbinsX(),err[i]);
		integral[i] = h1_prot_mom_sectors_data[i][0]->IntegralAndError(1,h1_prot_mom_sectors_data[i][0]->GetNbinsX(),err[i],"width");
		integral_incl[i] = h1_prot_mom_sectors_data_incl[i][0]->IntegralAndError(1,h1_prot_mom_sectors_data_incl[i][0]->GetNbinsX(),err[i],"width");
		//std::cout << "Range " << i+1 << " cross section: " << integral[i] << " +/- " << err[i] << std::endl; 

                ratio[i] = integral[i]/integral_incl[i];
                ratio_err[i] = ratio[i] * sqrt(pow((err[i]/integral[i]),2) + pow((err_incl[i]/integral_incl[i]),2));

                ratio_err[i] = (ratio[i]/neutron_corr[i]) * sqrt(pow((ratio_err[i]/ratio[i]),2) + pow((neutron_corr_err[i]/neutron_corr[i]),2));
                ratio[i] = ratio[i]/neutron_corr[i];

                ratio_err[i] = (ratio[i]/mec_corr[i]) * sqrt(pow((ratio_err[i]/ratio[i]),2) + pow((mec_corr_err[i]/mec_corr[i]),2));
                ratio[i] = ratio[i]/mec_corr[i];

                std::cout << "Range " << i+1 << " P: " << data_avg_prot_mom[i] << std::endl;
                std::cout << "Range " << i+1 << " ratio: " << ratio[i] << " +/- " << ratio_err[i] << std::endl;

		//std::cout << "Range " << i+1 << " ratio: " << integral[i]/integral_incl[i] << " +/- " << integral[i]/integral_incl[i] * sqrt(pow((err[i]/integral[i]),2) + pow((err_incl[i]/integral_incl[i]),2)) << std::endl; 
		tot_xsec += integral[i];
		tot_xsec_incl += integral_incl[i];
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

	c->SaveAs(TString::Format("data_excl_C12_2261_xsec_corrections.pdf"));

}
