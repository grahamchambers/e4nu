#include<iostream>
#include<iomanip>
//#include<stdio>
#include<fstream>
//#include<math>
using namespace std;

void Drawplots3()
{
  
  TFile * output_file = new TFile("transmission_C12_2261_EMQE_G18_02a_00_000_el_theta_20_25.root","RECREATE");
   
  //The file io section:
  //string fileName1 = "/pnfs/genie/scratch/users/gchamber/C12_2261_NCEL_nuel_G18_02b_02_11a_noFSI_redo/C12_2261_NCEL_G18_02b_02_11a_noFSI.root";
  string fileName1 = "/genie/app/users/gchamber/e4nu_2022/e4nu/Simulations/output/C12_2261/C12_2261_EMQE_G18_02a_00_000_bigstat.root";
  //string fileName1 = "/pnfs/genie/persistent/users/apapadop/e4v_SuSav2/Exclusive/electrons/C12_1161GeV/apapadop_SuSav2_C12_1161GeV_master.root";

  //string fileName1 = "Jun_12_17_numu_1_Pb_v290_CCQE_nof-fsi.gst.root";
  
  TH1D * Tp_SuSav2 = new TH1D("Tp_SuSav2","",100,0,1); 

  TFile * file1 = new TFile(fileName1.c_str(),"fileName1");
  TTree * gst1 = (TTree*)file1->Get("gst");
  const long NEntries1 = gst1->GetEntries();

  double El1[500], pxl1[500], pyl1[500], pzl1[500];
 
  double electron_mom_cut = 1.9; //electron momentum cut in GeV

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
	 
  //The data manipulation section:
  cout << "NEntries1 = " << NEntries1 << endl;
  cout << "ni1 = " << ni1 << endl;
  
  //for ( int j = 0 ; j < 10 ; ++j ) 
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
	TVector3 V3_el(pxl1[jj],pyl1[jj],pzl1[jj]);
	  if ( pdgi1[jj] == 2212 && abs(resc1[jj]) == 1 && V3_el.Theta() * 180 / TMath::Pi() > 20 && V3_el.Theta() * 180 / TMath::Pi() < 25) //Slicing to obtain only protons that did not re-scatter and electron momentum cut
	    {
	     	//std::cout << El1[jj] << std::endl;	
		//std::cout << pow(pow(El1[jj],2)-pow(Me,2),0.5) << std::endl;
		//std::cout << pow(pow(pxl1[jj],2)+pow(pyl1[jj],2)+pow(pzl1[jj],2),0.5) << std::endl; 
		Tp_SuSav2->Fill(Ei1[jj]-Mp); //Subtract off the rest energy of a proton to get its Ke.
	    }
	}
    }
  
  cout << "Finished the first loop." << endl;
  
  Tp_SuSav2->Rebin(4); 

  /*
  Hist2->Divide(Hist1);
  Hist3->Divide(Hist1);
  //The plotting section:
  gStyle->SetPalette(1);
  TLegend * leg1 = new TLegend(.7,.8,1.0,1.0,"");
  leg1->AddEntry( Hist2,"hA ","l");
  leg1->AddEntry( Hist3,"hN2015 (no corrections)","1");  //Should this still be a 1?  Or a 2 or something?
  TCanvas * c1 = new TCanvas("c2", "c2", 800, 600 );
  Hist2->SetStats(111111);
  Hist3->SetStats(111111);
  //Hist2->SetTitle("Iron (Fe)"); // temporary
  Hist3->SetTitle("Carbon (C)");
  Hist2->SetLineColor(4);
  Hist3->SetLineColor(2);
  Hist2->GetXaxis()->SetTitle("energy (GeV)");
  Hist2->GetYaxis()->SetTitle("ratio");  
  //Hist2->Draw();
  //Hist3->Draw("same");
  Hist3->Draw();
  Hist2->Draw("same");  //temporary 
  leg1->Draw("same");
  c1->SaveAs("output.png");  
  */
  
  output_file->cd();

  Tp_SuSav2->Write();

  //The clean-up section:
  file1->Close();

  output_file->Close();

  cout << "Execution complete." << endl;
}

