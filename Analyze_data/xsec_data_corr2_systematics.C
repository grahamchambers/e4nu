//This script calculates the corrected transparency from data. The corrections include MEC & neutron contamination (inputs as arrays -- calculate these factors using trans_calc_3.C or by hand), acceptance correction, and radiative corrections. Afro's UniversalE4vFunction() is used to scale the proton momentum distributions to convert event number to absolute double differential cross section (so if you change the files, you need to change myFunctions.cpp and AfroConstants.h). Often the scaling is not necessary because the scaling cancels in a ratio, but the scaling is important for the acceptance, radiative, etc. The acceptance uncertainty is calculated as a function of proton momentum and the bin averaged uncertainty can be printed to the terminal. Different acceptance uncertainties are possible (weighted average, bin-by-bin average, etc. -- just comment out which one you don't want). The end of the script plots one of the proton momentum distributions created. This script uses all three ranges, so if you need only one or two ranges, you must modify this script or make a new one. The script xsec_data_corr2.C was a previous version that does not include the systematic uncertainty calculations.

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

void xsec_data_corr2_systematics() {

      	const int N_RANGES = 3; // number of Ranges; see similarities in thetaEl arguments in file_names below
        const int N_FILES = N_RANGES * 2 * 2; 
	const int N_SECTORS = 6; // number of sectors
        const int N_INT = 4; // number of interactions 

	TFile *input_data_excl;
	TFile *input_data_incl;

        std::string data_excl[N_RANGES];
        std::string data_incl[N_RANGES];
	
	//exclusive data input
        data_excl[0] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Exclusive_Range1_Data__C12_2.261000.root";
        data_excl[1] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Exclusive_Range2_Data__C12_2.261000.root";
        data_excl[2] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Exclusive_Range3_Data__C12_2.261000.root";
     	//inclusive data input 
        data_incl[0] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Inclusive_Range1_Data__C12_2.261000.root";
        data_incl[1] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Inclusive_Range2_Data__C12_2.261000.root";
        data_incl[2] = "/genie/app/users/nsteinbe/e4nu/CLAS/DATA/Full_Data_Sample/C12/Inclusive_Range3_Data__C12_2.261000.root";
	
	double neutron_corr[3] = {0.75832654,0.72603164,0.66924105}; //neutron correction factors (calculated from SuSav2)
	double neutron_corr_err[3] = {0.,0.,0.};

	double mec_corr[3] = {0.923233,0.906029,0.893632}; //mec correction factors (calculated from SuSav2 using trans_calc_3.C)
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

	//SuSav2 1p0pi reco
        mc_excl_susa[0] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range1_Genie_1_C12_2.261000.root";
        mc_excl_susa[1] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range2_Genie_1_C12_2.261000.root";
        mc_excl_susa[2] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range3_Genie_1_C12_2.261000.root";
	//SuSav2 1p0pi true
        mc_excl1_susa[0] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_true_Range1_Genie_1_C12_2.261000.root";
        mc_excl1_susa[1] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_true_Range2_Genie_1_C12_2.261000.root";
        mc_excl1_susa[2] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_true_Range3_Genie_1_C12_2.261000.root";
	//G2018 1p0pi reco
        mc_excl[0] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range1_Genie_2_C12_2.261000.root";
        mc_excl[1] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range2_Genie_2_C12_2.261000.root";
        mc_excl[2] = "../output/output2022/Analysis28/Exclusive/Exclusive_1p0pi_reco_Range3_Genie_2_C12_2.261000.root";
	//G2018 1p0pi true
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
	//without Rad
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
        TH1D* systematics_acceptance[N_RANGES][N_SECTORS][N_INT];

	TH1D* h1_prot_mom_sectors_interactions_mc_susa_systematic[N_RANGES][N_SECTORS][N_INT];
	TH1D* h1_prot_mom_sectors_interactions_mc_systematic[N_RANGES][N_SECTORS][N_INT];
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

	//clone of reco for weights later on in uncertainty analysis
	h1_prot_mom_sectors_interactions_mc_susa_systematic[0][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc_susa[0][0][0]->Clone("h1sys");
	h1_prot_mom_sectors_interactions_mc_susa_systematic[1][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc_susa[1][0][0]->Clone("h1sys");
	h1_prot_mom_sectors_interactions_mc_susa_systematic[2][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc_susa[2][0][0]->Clone("h1sys");
	h1_prot_mom_sectors_interactions_mc_systematic[0][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc[0][0][0]->Clone("h2sys");	
	h1_prot_mom_sectors_interactions_mc_systematic[1][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc[1][0][0]->Clone("h2sys");	
	h1_prot_mom_sectors_interactions_mc_systematic[2][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc[2][0][0]->Clone("h2sys");	

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
	
		h1_prot_mom_sectors_interactions_mc_systematic[i][0][0]->Rebin(40);
		h1_prot_mom_sectors_interactions_mc_susa_systematic[i][0][0]->Rebin(40);
	
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

////////////////////////////////////////////////////////////////////////////
		//get average acceptance factor value for each range
		double sum_average_acc_correction = 0.;
		int nonzero_counter_acc_correction = 0;
		for (int l=0;l<h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetNbinsX();l++){
			sum_average_acc_correction += h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetBinContent(l);
			if (h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetBinContent(l) > 0) {nonzero_counter_acc_correction += 1;}	
		}
		
		//get |SuSav2 - G2018| for each range
                systematics_acceptance[i][0][0] = (TH1D*)h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Clone("b");
                systematics_acceptance[i][0][0]->Add(h1_prot_mom_sectors_interactions_mc2[i][0][0],-1);
		for (int j=0;j<systematics_acceptance[i][0][0]->GetNbinsX();j++){
			double temp_val = systematics_acceptance[i][0][0]->GetBinContent(j);
			systematics_acceptance[i][0][0]->SetBinContent(j,TMath::Abs(temp_val));
		}
		
		//weighted average
		/*	
		double weighted_average_num = 0.;
		double weighted_average_denom = 0.;
		//std::cout << "system no. bin: " << systematics_acceptance[i][0][0]->GetNbinsX() << ", other: " << h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetNbinsX() << std::endl;	
		for (int m=0;m<h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetNbinsX();m++){
				//weighted_average_num += (systematics_acceptance[i][0][0]->GetBinContent(m)) * (h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetBinContent(m));
				//weighted_average_denom += h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetBinContent(m);
				//std::cout << h1_prot_mom_sectors_interactions_mc[i][0][0]->GetBinContent(m) << std::endl; 
			}
		//std::cout << h1_prot_mom_sectors_interactions_mc_susa_systematic[i][0][0]->Integral() << std::endl;	
		*/		
		//systematics_acceptance[i][0][0]->Scale(weighted_average_denom / weighted_average_num);	
		//std::cout << "Weighted average = " << weighted_average_num/weighted_average_denom << std::endl;
	
		//get |SuSav2 - G2018|/sqrt(12) and then divide by average from acceptance factor histogram and multiply by 100%
		systematics_acceptance[i][0][0]->Scale(1./sqrt(12));
		systematics_acceptance[i][0][0]->Scale(100);
		//systematics_acceptance[i][0][0]->Scale(nonzero_counter_acc_correction/sum_average_acc_correction);
		systematics_acceptance[i][0][0]->Divide(h1_prot_mom_sectors_interactions_mc3[i][0][0]);
		
		//get average of acceptance error
		double sum_temp_val = 0.;
		int nonzero_counter = 0;
		for (int k=0;k<systematics_acceptance[i][0][0]->GetNbinsX();k++){
			//sum_temp_val += (systematics_acceptance[i][0][0]->GetBinContent(k));
			sum_temp_val += (systematics_acceptance[i][0][0]->GetBinContent(k)) * (h1_prot_mom_sectors_interactions_mc_susa_systematic[i][0][0]->GetBinContent(k)+h1_prot_mom_sectors_interactions_mc_systematic[i][0][0]->GetBinContent(k)) / 2;
			//std::cout << systematics_acceptance[i][0][0]->GetBinContent(k) << std::endl;
			if (systematics_acceptance[i][0][0]->GetBinContent(k) > 0) {nonzero_counter += (h1_prot_mom_sectors_interactions_mc_susa_systematic[i][0][0]->GetBinContent(k)+h1_prot_mom_sectors_interactions_mc_systematic[i][0][0]->GetBinContent(k)) / 2;}	
			//if (systematics_acceptance[i][0][0]->GetBinContent(k) > 0) {nonzero_counter += 1;}	
		}
	
		std::cout << "Mean acceptance factor uncertainty for range " << i+1 << ": " << sum_temp_val / nonzero_counter << std::endl;
		//std::cout << "Bin count = " << nonzero_counter << std::endl;
///////////////////////////////////////////////////////////////////////////

		h1_prot_mom_sectors_data[i][0]->SetStats(0);
		h1_prot_mom_sectors_interactions_mc3[i][0][0]->SetStats(0);
		h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->SetStats(0);
		h1_prot_mom_sectors_interactions_mc2[i][0][0]->SetStats(0);
		systematics_acceptance[i][0][0]->SetStats(0);
		h1_prot_mom_sectors_data_incl[i][0]->SetStats(0);
		h1_prot_mom_sectors_data[i][0]->Rebin(40);
		h1_prot_mom_sectors_data_incl[i][0]->Rebin(40);

		h1_prot_mom_sectors_interactions_mc_susa_radcorr[i][0][0]->Rebin(40);
                h1_prot_mom_sectors_interactions_mc1_susa_radcorr[i][0][0]->Rebin(40);
		
		h1_prot_mom_sectors_data[i][0]->Multiply(h1_prot_mom_sectors_interactions_mc3[i][0][0]); //multiply acceptance correction
	//	h1_prot_mom_sectors_data[i][0]->Divide(h1_prot_mom_sectors_interactions_mc_susa_radcorr[i][0][0]); //multiply by SuSav2 w/o Rad
	//	h1_prot_mom_sectors_data[i][0]->Multiply(h1_prot_mom_sectors_interactions_mc1_susa_radcorr[i][0][0]); //multiply by SuSav2 w/ Rad

		//h1_prot_mom_sectors_data[i][0]->Divide(h1_prot_mom_sectors_data_incl[i][0]);
	
		h1_prot_mom_sectors_data[i][0]->SetLineColor(color_options[i]);
		systematics_acceptance[i][0][0]->SetLineColor(color_options[i]);
		h1_prot_mom_sectors_interactions_mc_susa_systematic[i][0][0]->SetLineColor(color_options[i]);
		//h1_prot_mom_sectors_interactions_mc3[i][0][0]->SetLineColor(color_options[i]);
		//h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->SetLineColor(color_options[i]);
		//h1_prot_mom_sectors_interactions_mc2[i][0][0]->SetLineColor(color_options[i]);
		//h1_prot_mom_sectors_data[i][0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
		systematics_acceptance[i][0][0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
		//h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
		//h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
		//h1_prot_mom_sectors_interactions_mc2[i][0][0]->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
		//h1_prot_momentum[i]->GetYaxis()->SetTitle("d^{2}#sigma/dEd#Omega");
		//h1_prot_mom_sectors_data[i][0]->GetYaxis()->SetTitle("Scaled Data with Acceptance Correction");
	//	systematics_acceptance[i][0][0]->GetYaxis()->SetTitle("|SuSav2 - G2018| * 100/#sqrt{12} / Weighted Average");
		systematics_acceptance[i][0][0]->GetYaxis()->SetTitle("Acceptance Correction Error [%]");
		//h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetYaxis()->SetTitle("|SuSav2 + G2018| / 2");
		//h1_prot_mom_sectors_interactions_mc2[i][0][0]->GetYaxis()->SetTitle("G2018 Scaled Events");
		//h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->GetYaxis()->SetTitle("SuSav2 Scaled Events");
		//h1_prot_mom_sectors_data[i][0]->GetXaxis()->SetRangeUser(0,2);
		systematics_acceptance[i][0][0]->GetXaxis()->SetRangeUser(0,2);
		//h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetXaxis()->SetRangeUser(0,2);
		//h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->GetYaxis()->SetRangeUser(0,7);
		//h1_prot_mom_sectors_interactions_mc2[i][0][0]->GetYaxis()->SetRangeUser(0,3);
		//h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->GetXaxis()->SetRangeUser(0,2);
		//h1_prot_mom_sectors_interactions_mc2[i][0][0]->GetXaxis()->SetRangeUser(0,2);
		systematics_acceptance[i][0][0]->GetYaxis()->SetRangeUser(0,100);
		//h1_prot_mom_sectors_interactions_mc3[i][0][0]->GetYaxis()->SetRangeUser(0,4);
	//	h1_prot_momentum[i]->SetMaximum(.1);
		//h1_prot_multiplicity[i]->SetMinimum(1);
		//h1_prot_momentum[i]->GetXaxis()->CenterTitle(true);
		//h1_prot_momentum[i]->GetYaxis()->CenterTitle(true);
		//h1_prot_mom_sectors_data[i][0]->SetTitle("C-12 @ 2.261 GeV e^{-} Beam (CLAS with exclusive cuts)");
		//h1_prot_momentum[i]->SetTitle("C-12 @ 1.161 GeV e^{-} Beam (CLAS with exclusive cuts)");
		h1_prot_mom_sectors_interactions_mc_susa_systematic[i][0][0]->Draw(draw_options[i]);
		//systematics_acceptance[i][0][0]->Draw(draw_options[i]);
		//h1_prot_mom_sectors_interactions_mc3[i][0][0]->Draw(draw_options[i]);
		//h1_prot_mom_sectors_data[i][0]->Draw(draw_options[i]);
		//h1_prot_mom_sectors_interactions_mc2_susa[i][0][0]->Draw(draw_options[i]);
		//h1_prot_mom_sectors_interactions_mc2[i][0][0]->Draw(draw_options[i]);
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

                std::cout << "Range " << i+1 << " P: " << data_avg_prot_mom[i] << ", T: " << ratio[i] << " +/- " << ratio_err[i] << std::endl;

		//std::cout << "Range " << i+1 << " ratio: " << integral[i]/integral_incl[i] << " +/- " << integral[i]/integral_incl[i] * sqrt(pow((err[i]/integral[i]),2) + pow((err_incl[i]/integral_incl[i]),2)) << std::endl; 
		tot_xsec += integral[i];
		tot_xsec_incl += integral_incl[i];
	}
	//std::cout << tot_xsec << std::endl;
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

	c->SaveAs(TString::Format("test_C12_2261.pdf"));

}
