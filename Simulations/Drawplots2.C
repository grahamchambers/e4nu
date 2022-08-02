#include<iostream>
#include<iomanip>
//#include<stdio>
#include<fstream>
//#include<math>
using namespace std;

void Drawplots2()
{
  
  TFile * output_file = new TFile("transmission_4He_2261_EMQE_G18_02a_00_000_noFSI.root","RECREATE");
  //TFile * output_file = new TFile("transmission_C12_2261_EMQE_GEM21_11b_00_000.root","RECREATE");
   
  //The file io section:
  string fileName1 = "/pnfs/genie/persistent/users/gchamber/Simulations/4He_2261_EMQE_G18_02a_00_000_noFSI.root";
  //string fileName1 = "/pnfs/genie/persistent/users/gchamber/output2022/C12_2261_EMQE_GEM21_11b_00_000.root";
  //string fileName1 = "/pnfs/genie/persistent/users/apapadop/e4v_G2018/Exclusive/electrons/C12_2261GeV/apapadop_G2018_C12_2261GeV_master.root";

  //string fileName1 = "Jun_12_17_numu_1_Pb_v290_CCQE_nof-fsi.gst.root";
  
  TH1D * prot_p = new TH1D("prot_p","",200,0,2); 
  TH1D * Tp = new TH1D("Tp","",200,0,2); 
  TH1D * Ep = new TH1D("Ep","",200,0,2); 
  TH1D * Thetap = new TH1D("Thetap","",7200,-360,360); 
  TH2D * Theta_Phi_p = new TH2D("Theta_Phi_p","",7200,-360,360,7200,-360,360); 
  TH1D * Thetap_sector1 = new TH1D("Thetap_sector1","",7200,-360,360); 
  TH1D * Thetap_sector2 = new TH1D("Thetap_sector2","",7200,-360,360); 
  TH1D * Thetap_sector6 = new TH1D("Thetap_sector6","",7200,-360,360); 
  TH2D * Theta_Phi_el = new TH2D("Theta_Phi_el","",7200,-360,360,7200,-360,360); 
  TH1D * Theta_el = new TH1D("Theta_el","",7200,-360,360); 
  TH1D * Phi_el = new TH1D("Phi_el","",7200,-360,360); 

  TFile * file1 = new TFile(fileName1.c_str(),"fileName1");
  TTree * gst1 = (TTree*)file1->Get("gst");
  const long NEntries1 = gst1->GetEntries();

  const double Mp=0.9382720813; //Rest energy of a proton.  Subtract from total energy to get kinetic energy.
  //const double Mp=0.9383; //Rest energy of a proton.  Subtract from total energy to get kinetic energy.

  int ni1,ni2,ni3,ni4,resc1[500],resc2[500],resc3[500],resc4[500],pdgi1[500],pdgi2[500],pdgi3[500],pdgi4[500];
  double Ei1[500],Ei2[500],Ei3[500],Ei4[500],pxi1[500], pyi1[500], pzi1[500], pxf1[500], pyf1[500], pzf1[500], pxl1[500], pyl1[500], pzl1[500];

  gst1->SetBranchAddress("ni",&ni1);  //Doing initial Energy, as the rescattering is correlated to the initial pdg list of particles, not final, and for non-rescattering particles, Ef and Ei should be percisely the same value.
  gst1->SetBranchAddress("Ei",&Ei1[0]);
  gst1->SetBranchAddress("pdgi",&pdgi1[0]);
  gst1->SetBranchAddress("resc",&resc1);
  gst1->SetBranchAddress("pxi",&pxi1[0]);
  gst1->SetBranchAddress("pyi",&pyi1[0]);
  gst1->SetBranchAddress("pzi",&pzi1[0]);
  gst1->SetBranchAddress("pxl",&pxl1[0]);
  gst1->SetBranchAddress("pyl",&pyl1[0]);
  gst1->SetBranchAddress("pxl",&pxl1[0]);
  gst1->SetBranchAddress("pzi",&pzi1[0]);
  gst1->SetBranchAddress("pyf",&pyf1[0]);
  gst1->SetBranchAddress("pzf",&pzf1[0]);
                 
  //The data manipulation section:
  cout << "NEntries1 = " << NEntries1 << endl;
  cout << "ni1 = " << ni1 << endl;
  
  //for ( int j = 0 ; j < 1000000 ; ++j ) 
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
	

	if ( pdgi1[jj] == 2212) //Slicing to obtain only protons
	{

  	TVector3 V3_prot(pxf1[jj],pyf1[jj],pzf1[jj]);
  	TVector3 V3_el(pxl1[jj],pyl1[jj],pzl1[jj]);
  
	double prot_theta = V3_prot.Theta() * 180./  TMath::Pi(); 
  	double prot_phi = (V3_prot.Phi() + TMath::Pi()) * 180. / TMath::Pi(); 
	
	double el_theta = V3_el.Theta() * 180. / TMath::Pi(); 
  	double el_phi = (V3_el.Phi() + TMath::Pi()) * 180. / TMath::Pi(); 

	if (prot_phi > 360) {prot_phi -= 360;}
	if (prot_phi < 0) {prot_phi += 360;}
	if (el_phi > 360) {el_phi -= 360;}
	if (el_phi < 0) {el_phi += 360;}
	
	Theta_Phi_el->Fill(el_theta,el_phi);	
	Theta_el->Fill(el_theta);
	Phi_el->Fill(el_phi);
	Thetap->Fill(prot_theta);
	Theta_Phi_p->Fill(prot_theta,prot_phi);

	if (el_phi > 0 && el_phi < 60) {Thetap_sector1->Fill(prot_theta);}
	if (el_phi > 60 && el_phi < 120) {Thetap_sector2->Fill(prot_theta);}
	if (el_phi > 300 && el_phi < 360) {Thetap_sector6->Fill(prot_theta);}
	
	}

	  if ( pdgi1[jj] == 2212 && abs(resc1[jj]) == 1 ) //Slicing to obtain only protons that did not re-scatter.
	    {
	      Tp->Fill(Ei1[jj]-Mp); //Subtract off the rest energy of a proton to get its Ke.
	      Ep->Fill(Ei1[jj]); 
	      //prot_p->Fill(pow(pow(Ei1[jj], 2) - pow(Mp, 2), 0.5)); //proton momentum
	      prot_p->Fill(sqrt(pow(Ei1[jj], 2) - pow(Mp, 2)));
	    }
	}
    }
  
  cout << "Finished the first loop." << endl;
  
  prot_p->Rebin(4); 
  Tp->Rebin(4); 
  Ep->Rebin(4); 

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

  prot_p->Write();
  Tp->Write();
  Ep->Write();
  Thetap->Write();
  Theta_Phi_p->Write();
  Thetap_sector1->Write();
  Thetap_sector2->Write();
  Thetap_sector6->Write();
  Theta_Phi_el->Write();
  Theta_el->Write();
  Phi_el->Write();

  //The clean-up section:
  file1->Close();

  output_file->Close();

  cout << "Execution complete." << endl;
}

