//This script calculates (data/mc in sector i) / (data/mc in sector 1) for the the three ranges. You must input the data and mc files. The output is printed to the terminal.

#include "myFunctions.cpp"

void sectors_error() {

      	const int N_RANGES = 3; // number of Ranges; see similarities in thetaEl arguments in file_names below
        const int N_FILES = N_RANGES * 2 * 2; 
	const int N_SECTORS = 6; // number of sectors
        const int N_INT = 4; // number of interactions 

	TFile *input_data_sector1;
	TFile *input_data_sector2;
	TFile *input_data_sector6;
	TFile *input_mc_sector1;
	TFile *input_mc_sector2;
	TFile *input_mc_sector6;

        std::string data_sector1[N_RANGES];
        std::string data_sector2[N_RANGES];
        std::string data_sector6[N_RANGES];
        std::string mc_sector1[N_RANGES];
        std::string mc_sector2[N_RANGES];
        std::string mc_sector6[N_RANGES];
	
	//MC files are not necessary anymore. The new sector uncertainty just uses data
        mc_sector1[0] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis32/Exclusive/Exclusive_Sector1_Range1_Genie_1_C12_2.261000.root";
        mc_sector1[1] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis32/Exclusive/Exclusive_Sector1_Range2_Genie_1_C12_2.261000.root";
        mc_sector1[2] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis32/Exclusive/Exclusive_Sector1_Range3_Genie_1_C12_2.261000.root";
        mc_sector2[0] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis32/Exclusive/Exclusive_Sector2_Range1_Genie_1_C12_2.261000.root";
        mc_sector2[1] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis32/Exclusive/Exclusive_Sector2_Range2_Genie_1_C12_2.261000.root";
        mc_sector2[2] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis32/Exclusive/Exclusive_Sector2_Range3_Genie_1_C12_2.261000.root";
        mc_sector6[0] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis32/Exclusive/Exclusive_Sector6_Range1_Genie_1_C12_2.261000.root";
        mc_sector6[1] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis32/Exclusive/Exclusive_Sector6_Range2_Genie_1_C12_2.261000.root";
        mc_sector6[2] = "/genie/app/users/gchamber/e4nu_2022/e4nu/output/output2022/Analysis32/Exclusive/Exclusive_Sector6_Range3_Genie_1_C12_2.261000.root";

	data_sector1[0] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis21/Exclusive/Exclusive_Range1_Data__C12_2.261000.root";
	data_sector1[1] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis21/Exclusive/Exclusive_Range2_Data__C12_2.261000.root";
	data_sector1[2] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis21/Exclusive/Exclusive_Range3_Data__C12_2.261000.root";
	data_sector2[0] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis20/Exclusive/Exclusive_Range1_Data__C12_2.261000.root";
	data_sector2[1] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis20/Exclusive/Exclusive_Range2_Data__C12_2.261000.root";
	data_sector2[2] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis20/Exclusive/Exclusive_Range3_Data__C12_2.261000.root";
	data_sector6[0] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis19/Exclusive/Exclusive_Range1_Data__C12_2.261000.root";
	data_sector6[1] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis19/Exclusive/Exclusive_Range2_Data__C12_2.261000.root";
	data_sector6[2] = "/pnfs/genie/persistent/users/gchamber/output2022/Analysis19/Exclusive/Exclusive_Range3_Data__C12_2.261000.root";

       
	//exclusive histograms: proton momenta
	TH1D* h1_prot_mom_sector1_data[N_RANGES][N_SECTORS];
	TH1D* h1_prot_mom_sector2_data[N_RANGES][N_SECTORS];
	TH1D* h1_prot_mom_sector6_data[N_RANGES][N_SECTORS];
	TH1D* h1_prot_mom_sector1_interactions_mc[N_RANGES][N_SECTORS][N_INT];
	TH1D* h1_prot_mom_sector2_interactions_mc[N_RANGES][N_SECTORS][N_INT];
	TH1D* h1_prot_mom_sector6_interactions_mc[N_RANGES][N_SECTORS][N_INT];

	 for (int file_i = 0; file_i < N_RANGES; file_i++){
		input_data_sector1 = TFile::Open( TString::Format("%s", data_sector1[file_i].c_str()));	
		input_data_sector2 = TFile::Open( TString::Format("%s", data_sector2[file_i].c_str()));	
		input_data_sector6 = TFile::Open( TString::Format("%s", data_sector6[file_i].c_str()));	
		
		input_mc_sector1 = TFile::Open( TString::Format("%s", mc_sector1[file_i].c_str()));
		input_mc_sector2 = TFile::Open( TString::Format("%s", mc_sector2[file_i].c_str()));
		input_mc_sector6 = TFile::Open( TString::Format("%s", mc_sector6[file_i].c_str()));

		// loop over sectors
                for (int sector = 0; sector < N_SECTORS; sector++) {
			 h1_prot_mom_sector1_data[file_i][sector] = (TH1D*)input_data_sector1->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", sector));
			 h1_prot_mom_sector2_data[file_i][sector] = (TH1D*)input_data_sector2->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", sector));
			 h1_prot_mom_sector6_data[file_i][sector] = (TH1D*)input_data_sector6->Get( TString::Format("h1_0_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", sector));
                        // loop over interactions for MC
                        for (int interaction = 0; interaction < N_INT; interaction++) {
				h1_prot_mom_sector1_interactions_mc[file_i][sector][interaction] = (TH1D*)input_mc_sector1->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interaction+1, sector));
				h1_prot_mom_sector2_interactions_mc[file_i][sector][interaction] = (TH1D*)input_mc_sector2->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interaction+1, sector));
				h1_prot_mom_sector6_interactions_mc[file_i][sector][interaction] = (TH1D*)input_mc_sector6->Get( TString::Format("h1_%i_Omega_FullyInclusive_NoQ4Weight_Theta_Slice_InSector_prot_mom_QE__%i", interaction+1, sector));

                                if (interaction == 0) {


                        if(sector == 0 && interaction == 0) continue;
				
			else {
				h1_prot_mom_sector1_interactions_mc[file_i][0][0]->Add(h1_prot_mom_sector1_interactions_mc[file_i][sector][interaction]);
				h1_prot_mom_sector2_interactions_mc[file_i][0][0]->Add(h1_prot_mom_sector2_interactions_mc[file_i][sector][interaction]);
				h1_prot_mom_sector6_interactions_mc[file_i][0][0]->Add(h1_prot_mom_sector6_interactions_mc[file_i][sector][interaction]);

                                }
                        }}
			if(sector == 0) continue;
                        else {
                                h1_prot_mom_sector1_data[file_i][0]->Add(h1_prot_mom_sector1_data[file_i][sector]);
                                h1_prot_mom_sector2_data[file_i][0]->Add(h1_prot_mom_sector2_data[file_i][sector]);
                                h1_prot_mom_sector6_data[file_i][0]->Add(h1_prot_mom_sector6_data[file_i][sector]);
                        }
                        
}}




//////////////////////////////////////////////////////////////////////////////////////

	double data_mc_ratio_sector1[3];
	double data_mc_ratio_sector2[3];
	double data_mc_ratio_sector6[3];
		
	double seci_sec1_difference_squared_sum[3] = {0.,0.,0.}; 

	for (int i=0;i<3;i++){
		h1_prot_mom_sector1_data[i][0]->Rebin(40);	
		h1_prot_mom_sector2_data[i][0]->Rebin(40);	
		h1_prot_mom_sector6_data[i][0]->Rebin(40);	
		/*data_mc_ratio_sector1[i] = (h1_prot_mom_sector1_data[i][0]->Integral() / h1_prot_mom_sector1_interactions_mc[i][0][0]->Integral()) / (h1_prot_mom_sector1_data[i][0]->Integral() / h1_prot_mom_sector1_interactions_mc[i][0][0]->Integral());
		data_mc_ratio_sector2[i] = (h1_prot_mom_sector2_data[i][0]->Integral() / h1_prot_mom_sector2_interactions_mc[i][0][0]->Integral()) / (h1_prot_mom_sector1_data[i][0]->Integral() / h1_prot_mom_sector1_interactions_mc[i][0][0]->Integral());
		data_mc_ratio_sector6[i] = (h1_prot_mom_sector6_data[i][0]->Integral() / h1_prot_mom_sector6_interactions_mc[i][0][0]->Integral()) / (h1_prot_mom_sector1_data[i][0]->Integral() / h1_prot_mom_sector1_interactions_mc[i][0][0]->Integral());
		std::cout << "Range " << i+1 << ", (data/mc in sector 1)/(data/mc in sector 1): " << data_mc_ratio_sector1[i] << std::endl;	
		std::cout << "Range " << i+1 << ", (data/mc in sector 2)/(data/mc in sector 1): " << data_mc_ratio_sector2[i] << std::endl;	
		std::cout << "Range " << i+1 << ", (data/mc in sector 6)/(data/mc in sector 1): " << data_mc_ratio_sector6[i] << std::endl;
		*/
			
		seci_sec1_difference_squared_sum[i] += pow(h1_prot_mom_sector1_data[i][0]->Integral() - h1_prot_mom_sector1_data[i][0]->Integral(),2);
		std::cout << h1_prot_mom_sector2_data[i][0]->Integral() - h1_prot_mom_sector1_data[i][0]->Integral() << std::endl;
		seci_sec1_difference_squared_sum[i] += pow(h1_prot_mom_sector2_data[i][0]->Integral() - h1_prot_mom_sector1_data[i][0]->Integral(),2);
		seci_sec1_difference_squared_sum[i] += pow(h1_prot_mom_sector6_data[i][0]->Integral() - h1_prot_mom_sector1_data[i][0]->Integral(),2);
	}
	std::cout << "Sector uncertainty for range 1: " << sqrt(seci_sec1_difference_squared_sum[0])/sqrt(3.) << std::endl;
//	std::cout << seci_sec1_difference_squared_sum[0] << std::endl;
	std::cout << "Sector uncertainty for range 2: " << sqrt(seci_sec1_difference_squared_sum[1])/sqrt(3.) << std::endl;
	std::cout << "Sector uncertainty for range 3: " << sqrt(seci_sec1_difference_squared_sum[2])/sqrt(3.) << std::endl;
}
