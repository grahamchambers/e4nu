void transmission_plot3_4He(){

TFile *input1 = TFile::Open("transmission_4He_2261_EMQE_G18_02a_00_000.root");
TFile *input2 = TFile::Open("transmission_4He_2261_EMQE_G18_02a_00_000_noFSI.root");
//TFile *input1 = TFile::Open("transmission_56Fe_2261_EMQE_G18_02a_00_000.root");
//TFile *input2 = TFile::Open("transmission_56Fe_2261_EMQE_G18_02a_00_000_noFSI.root");

TH1D* h1 = (TH1D*)input1->Get(TString::Format("prot_p"));
TH1D* h2 = (TH1D*)input2->Get(TString::Format("prot_p"));
TH1D* h12 = (TH1D*)h1->Clone("h12");
/*
TH1D* h3 = (TH1D*)input3->Get(TString::Format("prot_p"));
TH1D* h4 = (TH1D*)input4->Get(TString::Format("prot_p"));
TH1D* h34 = (TH1D*)h3->Clone("h34");

TH1D* h5 = (TH1D*)input5->Get(TString::Format("prot_p"));
TH1D* h6 = (TH1D*)input6->Get(TString::Format("prot_p"));
TH1D* h56 = (TH1D*)h5->Clone("h56");
*/
TCanvas* c;
c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

c->SetLeftMargin(0.13);
c->Update();

h12->Sumw2();
h12->Divide(h2);
//h12->Scale(0.99);
h12->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
//h12->GetXaxis()->CenterTitle(true);
h12->GetYaxis()->SetTitle("Transparency");
h12->GetYaxis()->SetRangeUser(0,1.2);
h12->GetXaxis()->SetRangeUser(0,2);
//h12->GetYaxis()->CenterTitle(true);
h12->SetTitle("2.261 GeV e^{-} Beam");
h12->SetStats(0);
h12->SetLineColor(kBlue);
h12->Draw("hist same");
//h12->Draw("e same");

///////////////////////////////////////////////////////////////////////////////////////
        const double leg_x1 = 0.39; // x-axis lower bound for the legend
        const double leg_x2 = 0.88; // x-axis upper bound for the legend
        const double leg_y1 = 0.7; // y-axis lower bound for the legend
        const double leg_y2 = 0.875; // y-axis upper bound for the legend

	double MC_helium_Prot_mom[4] = {0.796537,0.994214,1.29024,1.62017};
	double Data_helium_Prot_mom[4] = {0.791774,0.975688,1.28832,1.61297};
	double Data_helium3_Prot_mom[2] = {0.509158,0.623969};
        double MC_helium_T[4] = {0.759443,0.715179,0.722361,0.686845};
        double Data_helium_T[4] = {0.671198,0.624083,0.620322,0.549419};
        double Data_helium3_T[2] = {0.784719,0.756849};
        //double Data_helium3_T[2] = {0.651194,0.60022};
        double MC_helium_Prot_mom_err[4] = {0.0,0.0,0.0,0.0};
        double Data_helium_Prot_mom_err[4] = {0.0,0.0,0.0,0.0};
        double Data_helium3_Prot_mom_err[2] = {0.0,0.0};
        double MC_helium_T_err[4] = {0.0221907,0.0469882,0.080143,0.111586};
        double Data_helium_T_err[4] = {0.0200272,0.0419392,0.0712653,0.0935748};
        double Data_helium3_T_err[2] = {0.027,0.063};
        //double Data_helium3_T_err[2] = {0.0218572,0.047791};
        
	TGraphErrors *g_Data_Iron = new TGraphErrors(4, Data_helium_Prot_mom, Data_helium_T, Data_helium_Prot_mom_err, Data_helium_T_err);
	TGraphErrors *g_Data_Iron3 = new TGraphErrors(2, Data_helium3_Prot_mom, Data_helium3_T, Data_helium3_Prot_mom_err, Data_helium3_T_err);
	TGraph *g_MC_Iron = new TGraph(4, MC_helium_Prot_mom, MC_helium_T);
	//TGraphErrors *g_MC_Iron = new TGraphErrors(4, MC_helium_Prot_mom, MC_helium_T, MC_helium_Prot_mom_err, MC_helium_T_err);
        g_MC_Iron->SetLineColor(kViolet);
        //g_MC_Iron->SetMarkerColor(kViolet);
        g_Data_Iron->SetMarkerColor(kGreen-6);
        g_Data_Iron3->SetMarkerColor(kOrange+1);
        g_MC_Iron->SetMarkerStyle(20);
        g_Data_Iron->SetMarkerStyle(21);
        g_Data_Iron3->SetMarkerStyle(21);
        ///c_mc->SetMarkerSize(1);
        //c_data->SetMarkerSize(1.5);


        TLegend *legend = new TLegend( leg_x1, leg_y1, leg_x2, leg_y2);
        legend->AddEntry( g_Data_Iron, "He-4 - CLAS (e, p) / (e)","p");
        legend->AddEntry( g_Data_Iron3, "He-3 - CLAS (e, p) / (e) without MEC Corrections","p");
        legend->AddEntry( g_MC_Iron, "He-4 - SuSAv2 (e, p) / (e)","l");
        legend->AddEntry( h12, "He-4 - True Genie @ 2.261 GeV (FSI / no FSI)","l");
        //legend->AddEntry( g_Data_Iron_corrected, "56Fe - CLAS (Genie neutron corrections)","p");
        g_MC_Iron->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
        g_MC_Iron->GetYaxis()->SetTitle("Transparency");
        g_MC_Iron->GetXaxis()->SetLimits(0,2.0);
        g_MC_Iron->GetYaxis()->SetRangeUser(0,1.2);
        g_MC_Iron->SetTitle("Proton transparency");


	g_MC_Iron->Draw("al same");
	g_Data_Iron->Draw("p same");
	g_Data_Iron3->Draw("p same");

	h12->Draw("hist same");
//	h12->Draw("e same");
///////////////////////////////////////////////////////////////////////////////////////

legend->SetFillStyle(0);
legend->Draw();

c->SaveAs(TString::Format("transparency_4He_2261_full_plot.pdf"));

}
