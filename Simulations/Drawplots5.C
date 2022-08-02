#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

void Drawplots5()
{
  
  TFile * output_file = new TFile("truecuts_C12_2261_EMQE_G18_02a_00_000_elmom_1.95_eltheta_21_23_elsector_elphi_prottheta_45_80.root","RECREATE");
   
  //The file io section:
  //string fileName1 = "/pnfs/genie/scratch/users/gchamber/C12_2261_NCEL_nuel_G18_02b_02_11a_noFSI_redo/C12_2261_NCEL_G18_02b_02_11a_noFSI.root";
  string fileName1 = "/genie/app/users/gchamber/e4nu_2022/e4nu/Simulations/output/C12_2261/C12_2261_EMQE_G18_02a_00_000_noFSI_bigstat.root";
  //string fileName1 = "/pnfs/genie/persistent/users/apapadop/e4v_Sav2/Exclusive/electrons/C12_1161GeV/apapadop_SuSav2_C12_1161GeV_master.root";

  //string fileName1 = "Jun_12_17_numu_1_Pb_v290_CCQE_nof-fsi.gst.root";
  
  TH1D * Tp = new TH1D("Tp","",100,0,1); 
  TH1D * el_theta = new TH1D("el_theta","",180,0,180); 

  TFile * file1 = new TFile(fileName1.c_str(),"fileName1");
  TTree * gst1 = (TTree*)file1->Get("gst");
  const long NEntries1 = gst1->GetEntries();

  double El1[500], pxl1[500], pyl1[500], pzl1[500], pxi1[500], pyi1[500], pzi1[500];

  double electron_mom_cut = 1.95; //electron momentum cut in GeV
  double electron_theta_min = 21; //electron theta min in deg
  double electron_theta_max = 23;
  double electron_delta_phi = 12; //electron delta phi in deg
  double prot_theta_min = 45; //proton theta min in deg 
  double prot_theta_max = 80; 

  const double Mp=0.9383; //Rest energy of a proton.  Subtract from total energy to get kinetic energy.
  const double Me=0.000511; //rest energy of electron

  int ni1,ni2,ni3,ni4,resc1[500],resc2[500],resc3[500],resc4[500],pdgi1[500],pdgi2[500],pdgi3[500],pdgi4[500];
  double Ei1[500],Ei2[500],Ei3[500],Ei4[500];

  gst1->SetBranchAddress("ni",&ni1);  //Doing initial Energy, as the rescattering is correlated to the initial pdg list of particles, not final, and for non-rescattering particles, Ef and Ei should be percisely the same value.
  gst1->SetBranchAddress("Ei",&Ei1[0]);
  gst1->SetBranchAddress("pdgi",&pdgi1[0]);
  gst1->SetBranchAddress("resc",&resc1);
  gst1->SetBranchAddress("El",&El1[0]);
  gst1->SetBranchAddress("pxl",&pxl1[0]);
  gst1->SetBranchAddress("pyl",&pyl1[0]);
  gst1->SetBranchAddress("pzl",&pzl1[0]);
  gst1->SetBranchAddress("pxf",&pxi1[0]);
  gst1->SetBranchAddress("pyf",&pyi1[0]);
  gst1->SetBranchAddress("pzf",&pzi1[0]);
	 
  //The data manipulation section:
  cout << "NEntries1 = " << NEntries1 << endl;
  cout << "ni1 = " << ni1 << endl;
  
  //for ( int j = 0 ; j < 10000 ; ++j ) 
  for ( int j = 0 ; j < NEntries1 ; ++j ) 
    {
      if (j%100000 == 0) {cout << "\r" << double(j)/double(NEntries1)*100. << " %" << flush;}
      //cout << "got into the loop." << endl;
      gst1->GetEntry(j);
      //cout << nf1 << endl;
      //cout << "j = " << j << endl;
      
      for ( int jj = 0 ; jj < ni1 ; ++jj )
      //for ( int jj = 0 ; jj < 1 ; ++jj )
      {
	TVector3 V3_el(pxl1[jj], pyl1[jj], pzl1[jj]);
	TVector3 V3_prot(pxi1[jj], pyi1[jj], pzi1[jj]);
	
	//if (pdgi1[jj] != 2212 && abs(resc1[jj]) != 1) {continue;} //Slicing to obtain only protons that did not re-scatter and electron momentum cut
	//if (V3_el.Mag() < electron_mom_cut) {continue;} //electron momentum cut
	//if (V3_el.Theta() * 180 / TMath::Pi() < electron_theta_min || V3_el.Theta() * 180 / TMath::Pi() > electron_theta_max) {continue;} //electron theta cut
	//if ((V3_el.Phi() * 180 / TMath::Pi() - 30 ))
	//if ((V3_el.Phi() * 180 / TMath::Pi() > 36 || V3_el.Phi() * 180 / TMath::Pi() < 24) && (V3_el.Phi() * 180 / TMath::Pi() > 96 || V3_el.Phi() * 180 / TMath::Pi() < 84) && (V3_el.Phi() * 180 / TMath::Pi() > 336 || V3_el.Phi() * 180 / TMath::Pi() < 324)) {continue;} //electron sector and phi cut
//	if (V3_prot.Theta() * 180 / TMath::Pi() < prot_theta_min || V3_prot.Theta() * 180 / TMath::Pi() > prot_theta_max) {continue;} //proton theta cut 	

	Tp->Fill(Ei1[jj]-Mp); //Subtract off the rest energy of a proton to get its Ke.
	el_theta->Fill(V3_el.Theta() * 180 / TMath::Pi()); //Subtract off the rest energy of a proton to get its Ke.
	    
	}
    }
  
  cout << "Finished the first loop." << endl;
  
  Tp->Rebin(4); 

  output_file->cd();

  Tp->Write();
  el_theta->Write();

  //The clean-up section:
  file1->Close();

  output_file->Close();

  cout << "Execution complete." << endl;
}

