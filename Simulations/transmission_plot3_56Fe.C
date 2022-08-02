void transmission_plot3_56Fe(){

//TFile *input1 = TFile::Open("transmission_56Fe_2261_EMQE_G18_02a_00_000_redo.root");
//TFile *input2 = TFile::Open("transmission_56Fe_2261_EMQE_G18_02a_00_000_noFSI_redo.root");
TFile *input1 = TFile::Open("transmission_56Fe_2261_EMQE_G18_02a_00_000.root");
TFile *input2 = TFile::Open("transmission_56Fe_2261_EMQE_G18_02a_00_000_noFSI.root");

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
h12->Scale(0.99);
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

	double MC_iron_Prot_mom[4] = {0.677197,0.932846,1.20497,1.53878};
	double Data_iron_Prot_mom[4] = {0.671924,0.919122,1.2506,1.51019};
        double MC_iron_T[4] = {0.57013,0.516324,0.449707,0.425372};
        double Data_iron_T[4] = {0.405086,0.428878,0.407548,0.474252};
        double MC_iron_Prot_mom_err[4] = {0.0,0.0,0.0,0.0};
        double Data_iron_Prot_mom_err[4] = {0.0,0.0,0.0,0.0};
        double MC_iron_T_err[4] = {0.0131247,0.0153689,0.0283794,0.0210728};
        double Data_iron_T_err[4] = {0.0154405,0.0255499,0.0557256,0.0711309};
        
	TGraphErrors *g_Data_Iron = new TGraphErrors(4, Data_iron_Prot_mom, Data_iron_T, Data_iron_Prot_mom_err, Data_iron_T_err);
	TGraph *g_MC_Iron = new TGraph(4, MC_iron_Prot_mom, MC_iron_T);
	//TGraphErrors *g_MC_Iron = new TGraphErrors(4, MC_iron_Prot_mom, MC_iron_T, MC_iron_Prot_mom_err, MC_iron_T_err);
        g_MC_Iron->SetLineColor(kViolet);
        //g_MC_Iron->SetMarkerColor(kViolet);
        g_Data_Iron->SetMarkerColor(kGreen-6);
        g_MC_Iron->SetMarkerStyle(20);
        g_Data_Iron->SetMarkerStyle(21);
        ///c_mc->SetMarkerSize(1);
        //c_data->SetMarkerSize(1.5);
        Double_t dutta_Tp_Fe[4] = {.35,.7,.97,1.8};
        Double_t dutta_Trans_Fe[4] = {.47,.44,.4,.42};
        Double_t dutta_Tp_err_Fe[4] = {0.0,0.0,0.0,0.0};
        Double_t dutta_Trans_err_Fe[4] = {.05*.47, .44*.05, .4*.05,.42*.05};
        TGraphErrors *dutta_Fe = new TGraphErrors(4, dutta_Tp_Fe, dutta_Trans_Fe, dutta_Tp_err_Fe, dutta_Trans_err_Fe);
        dutta_Fe->SetMarkerColor(kBlack);
        dutta_Fe->SetMarkerSize(2.0);
        dutta_Fe->SetMarkerStyle(33);
        TLegend *legend = new TLegend( leg_x1, leg_y1, leg_x2, leg_y2);
        legend->AddEntry( g_Data_Iron, "Fe-56 - CLAS (e, p) / (e)","p");
        //legend->AddEntry( g_Data_Iron_corrected, "56Fe - CLAS (Genie neutron corrections)","p");
        legend->AddEntry( dutta_Fe, "Fe-56 - Dutta 03","p");
        legend->AddEntry( g_MC_Iron, "Fe-56 - SuSAv2 (e, p) / (e)","l");
        g_MC_Iron->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
        g_MC_Iron->GetYaxis()->SetTitle("Transparency");
        g_MC_Iron->GetXaxis()->SetLimits(0,2.0);
        g_MC_Iron->GetYaxis()->SetRangeUser(0,1.2);
        g_MC_Iron->SetTitle("Proton transparency");


	g_MC_Iron->Draw("al same");
	g_Data_Iron->Draw("p same");
        dutta_Fe->Draw("p same");

	h12->Draw("hist same");
	//h12->Draw("e same");
///////////////////////////////////////////////////////////////////////////////////////

legend->AddEntry(h12,"Fe-56 - True GENIE @ 2.261 GeV (FSI / no FSI)","l");
legend->SetFillStyle(0);
legend->Draw();

c->SaveAs(TString::Format("transparency_56Fe_2261_full_plot.pdf"));

}
