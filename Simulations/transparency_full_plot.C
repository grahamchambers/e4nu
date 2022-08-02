void transparency_full_plot(){

	TFile *input1 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000.root");
	TFile *input2 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_noFSI.root");

	TFile *input3 = TFile::Open("transmission_C12_2261_EMQE_GEM21_11b_00_000.root");
	TFile *input4 = TFile::Open("transmission_C12_2261_EMQE_GEM21_11b_00_000_noFSI.root");

	TH1D* h1 = (TH1D*)input1->Get(TString::Format("prot_p"));
	TH1D* h2 = (TH1D*)input2->Get(TString::Format("prot_p"));
	TH1D* h12 = (TH1D*)h1->Clone("h12");
	
	TH1D* h3 = (TH1D*)input3->Get(TString::Format("prot_p"));
	TH1D* h4 = (TH1D*)input4->Get(TString::Format("prot_p"));
	TH1D* h34 = (TH1D*)h3->Clone("h34");

	TCanvas* c;
	c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

	c->SetLeftMargin(0.13);
	c->Update();

	h34->Sumw2();
	h34->Divide(h4);
	//h34->Scale(0.99);
	h34->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
	//h12->GetXaxis()->CenterTitle(true);
	h34->GetYaxis()->SetTitle("Transparency");
	h34->GetYaxis()->SetRangeUser(0,1.2);
	//h34->GetYaxis()->CenterTitle(true);
	h34->SetTitle("2.261 GeV e^{-} Beam");
	h34->SetStats(0);
	h34->SetLineColor(kMagenta);
	//h34->Draw("hist same");
	//h34->Draw("e same");

        h12->Sumw2();
        h12->Divide(h2);
        h12->Scale(0.99);
        h12->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
        //h12->GetXaxis()->CenterTitle(true);
        h12->GetYaxis()->SetTitle("Transparency");
        h12->GetYaxis()->SetRangeUser(0,1.2);
        //h12->GetYaxis()->CenterTitle(true);
        h12->SetTitle("2.261 GeV e^{-} Beam");
        h12->SetStats(0);
        h12->SetLineColor(kBlue);
        h12->Draw("hist same");
        //h12->Draw("e same");

	///////////////////////////////////////////////////////////////////////////////////////
       
	const double leg_x1 = 0.35; // x-axis lower bound for the legend
        const double leg_x2 = 0.88; // x-axis upper bound for the legend
        const double leg_y1 = 0.65; // y-axis lower bound for the legend
        const double leg_y2 = 0.875; // y-axis upper bound for the legend

	double MC_carbon_Prot_mom[6] = {0.483663,0.562727,0.6986,0.970783,1.26892,1.59718};
	double MC2_carbon_Prot_mom[3] = {0.691048,0.973994,1.28357};
        double MC2_carbon_T[3] = {0.688279,0.687456,0.602466};
        double MC2_carbon_Prot_mom_err[3] = {0.0,0.0,0.0};
        double MC2_carbon_T_err[3] = {0.00987185,0.0162972,0.0311129};
	//double Data_carbon_Prot_mom[4] = {0.685877,0.958285,1.276,1.57715};        
	double Data_carbon_Prot_mom[6] = {0.463961,0.568751,0.685877,0.958285,1.276,1.57715};        
	double Data_accept_carbon_Prot_mom[5] = {0.464165,0.568503,0.685974,0.958433,1.27629};        
	double MC_carbon_T[6] = {0.68212896,0.695419022,0.728697956,0.640915467,0.629852109,0.606475282};
        //double Data_carbon_T_corrected2[4] = {0.537166,0.579962,0.608834,0.407401};
        double Data_carbon_T_corrected2[6] = {0.443807,0.467783,0.537166,0.579962,0.608834,0.407401};
        double Data_accept_carbon_T[5] = {0.503204,0.409485,0.674,0.691,0.649};
        double MC_carbon_Prot_mom_err[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
        //double Data_carbon_Prot_mom_err[4] = {0.0,0.0,0.0,0.0};
        double Data_carbon_Prot_mom_err[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
        double Data_accept_carbon_Prot_mom_err[5] = {0.0,0.0,0.0,0.0,0.0};
        double MC_carbon_T_err[6] = {0.0182518,0.0392536,0.0176548,0.0217961,0.0504141,0.0345369};
        //double Data_corr2_carbon_T_err[4] = {0.0144094,0.0224156,0.0559788,0.0332968};
        double Data_corr2_carbon_T_err[6] = {0.0132781,0.0302293,0.0144094,0.0224156,0.0559788,0.0332968};
        double Data_accept_carbon_T_err[5] = {0.0107,0.018,0.009,0.011,0.0192};

        TGraph *g_MC_Carbon = new TGraph(6, MC_carbon_Prot_mom, MC_carbon_T);
        //TGraphErrors *g_MC_Carbon = new TGraphErrors(6, MC_carbon_Prot_mom, MC_carbon_T, MC_carbon_Prot_mom_err, MC_carbon_T_err);
        //TGraphErrors *g_MC2_Carbon = new TGraphErrors(3, MC2_carbon_Prot_mom, MC2_carbon_T, MC2_carbon_Prot_mom_err, MC2_carbon_T_err);
        TGraph *g_MC2_Carbon = new TGraph(3, MC2_carbon_Prot_mom, MC2_carbon_T);
        //TGraphErrors *g_Data_Carbon_corrected2 = new TGraphErrors(4, Data_carbon_Prot_mom, Data_carbon_T_corrected2, Data_carbon_Prot_mom_err, Data_corr2_carbon_T_err);
        TGraphErrors *g_Data_Carbon_corrected2 = new TGraphErrors(6, Data_carbon_Prot_mom, Data_carbon_T_corrected2, Data_carbon_Prot_mom_err, Data_corr2_carbon_T_err);
        TGraphErrors *g_Data_accept_Carbon = new TGraphErrors(5, Data_accept_carbon_Prot_mom, Data_accept_carbon_T, Data_accept_carbon_Prot_mom_err, Data_accept_carbon_T_err);
        g_MC_Carbon->SetLineColor(kViolet);
        //g_MC_Carbon->SetMarkerColor(kViolet);
        g_MC2_Carbon->SetLineColor(kOrange-3);
        //g_MC2_Carbon->SetMarkerColor(kBlue);
        g_Data_Carbon_corrected2->SetMarkerColor(kGreen-6);
        g_Data_accept_Carbon->SetMarkerColor(kOrange+1);
        g_MC_Carbon->SetMarkerStyle(20);
        g_MC2_Carbon->SetMarkerStyle(22);
        g_Data_Carbon_corrected2->SetMarkerStyle(21);
        g_Data_accept_Carbon->SetMarkerStyle(21);

        Double_t dutta_Tp_C[4] = {.350, .700, .970, 1.8};
        Double_t dutta_Trans_C[4] = {.61, .60, .57, .58};
        Double_t dutta_Tp_err_C[4] = {0.0,0.0,0.0,0.0};
        Double_t dutta_Trans_err_C[4] = {.05*.61, .60*.05, .57*.05,.58*.05};
        TGraphErrors *dutta_C = new TGraphErrors(4, dutta_Tp_C, dutta_Trans_C, dutta_Tp_err_C, dutta_Trans_err_C);
        dutta_C->SetMarkerColor(kBlack);
        dutta_C->SetMarkerSize(2.0);
        dutta_C->SetMarkerStyle(33);
        TLegend *legend = new TLegend( leg_x1, leg_y1, leg_x2, leg_y2);
        legend->AddEntry( g_Data_Carbon_corrected2, "C-12 - CLAS (e, p) / (e)","p");
        legend->AddEntry( g_Data_accept_Carbon, "C-12 - CLAS (e, p) / (e) Corrected for Acceptance and Rad","p");
        legend->AddEntry( dutta_C, "C-12 - Dutta 03","p");
        legend->AddEntry( g_MC_Carbon, "C-12 - SuSav2 (e, p) / (e)","l");
 //       legend->AddEntry( g_MC2_Carbon, "C-12 - GENIE [(e, p) with FSI] / [(e, p) without FSI]","l");

        g_MC_Carbon->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
        g_MC_Carbon->GetYaxis()->SetTitle("Transparency");
        g_MC_Carbon->GetXaxis()->SetLimits(0.2,2.0);
        g_MC_Carbon->GetYaxis()->SetRangeUser(0.2,1);
        g_MC_Carbon->SetTitle("Proton transparency");

	h12->Draw("hist same");
	//h12->Draw("e same");
	//h34->Draw("hist same");
	//h34->Draw("e same");
        g_MC_Carbon->Draw("l same");
//        g_Data_Carbon_corrected2->Draw("p same");
//	g_MC2_Carbon->Draw("l same");
        dutta_C->Draw("p same");
        g_Data_Carbon_corrected2->Draw("p same");
        g_Data_accept_Carbon->Draw("p same");

	///////////////////////////////////////////////////////////////////////////////////////

	legend->AddEntry(h12,"C-12 - True GENIE @ 2.261 GeV (FSI / no FSI)","L");
	//legend->AddEntry(h34,"C-12 - True SuSav2 @ 2.261 GeV (FSI / no FSI)","L");
	legend->SetFillStyle(0);
	legend->Draw();

	c->SaveAs(TString::Format("transparency_C12_2261_full_plot_no1161.pdf"));

}
