void transmission_plot3(){

//TFile *input1 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_redo.root");
//TFile *input2 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_noFSI_redo.root");
TFile *input1 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000.root");
TFile *input2 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_noFSI.root");

//TFile *input3 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_redo_el_mom_1.9.root");
//TFile *input4 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_redo_noFSI_el_mom_1.9.root");

//TFile *input3 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000.root");
//TFile *input4 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_noFSI.root");

//TFile *input5 = TFile::Open("transmission_4He_2261_EMQE_G18_02a_00_000.root");
//TFile *input6 = TFile::Open("transmission_4He_2261_EMQE_G18_02a_00_000_noFSI.root");


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
//h12->GetYaxis()->CenterTitle(true);
h12->SetTitle("2.261 GeV e^{-} Beam");
h12->SetStats(0);
h12->SetLineColor(kBlue);
h12->Draw("hist");
h12->Draw("e same");

///////////////////////////////////////////////////////////////////////////////////////
        const double leg_x1 = 0.39; // x-axis lower bound for the legend
        const double leg_x2 = 0.88; // x-axis upper bound for the legend
        const double leg_y1 = 0.7; // y-axis lower bound for the legend
        const double leg_y2 = 0.875; // y-axis upper bound for the legend

	double MC_carbon_Prot_mom[6] = {0.483663,0.562727,0.6986,0.970783,1.26892,1.59718};
//      double Data_carbon_Prot_mom[3] = {.6842,.948755,1.34975};
        double Data_carbon_Prot_mom[6] = {0.464293,0.573408,0.683966,0.95041,1.28034,1.56123};
        //double Data_carbon_Prot_mom_Em[3] = {0.707191,0.997259,1.31695};
        //double Data_carbon_Prot_mom[7] = {.468075,.476217,.640039,.746834, 1.07375, 1.37888,1.36918};
        double MC_carbon_T[6] = {0.68212896,0.695419022,0.728697956,0.640915467,0.629852109,0.606475282};
//      double Data_carbon_T[3] = {.376828,.41648,.349001};
        double Data_carbon_T[6] = {0.351285,0.345308,0.379938,0.410314,0.376437,0.264368};
        //double Data_carbon_T_Em[3] = {0.330226,0.330226,0.33908};
        //double Data_carbon_T[7] = {.31632,.33844,.34814,.38347, .34374, .354396,.360809};
        //double Data_carbon_T_corrected[3] = {.49692,.573639,.493938};
        double Data_carbon_T_corrected[6] = {0.423315,0.435417,0.501021,0.565146,0.562483,0.365491};
        double Data_carbon_T_corrected2[6] = {0.443156,0.462911,0.542681,0.623761,0.629435,0.427182};
        //double Data_carbon_T_corrected_Em[3] = {0.435467,0.471727,0.506664};;
        //double Data_carbon_T_corrected[7] = {.370329,.41675,.458837,.510605,.478003,.492514,.501597};
        //double Data_carbon_T_corrected[6] = {.334004,.378732,.418191,.461572,.475562,.546148,.572431};
        double MC_carbon_Prot_mom_err[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
        double Data_carbon_Prot_mom_err[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
        //double Data_carbon_Prot_mom_err_Em[3] = {0.0,0.0,0.0};
        double MC_carbon_T_err[6] = {0.014253912,0.035949302,0.017032723,0.025804418,0.055731699,0.061941422};
        //double Data_carbon_T_err[3] = {.0107209,.0181846,.023421};
        double Data_carbon_T_err[6] = {0.0082787,0.0184547,0.0107867,0.0180102,0.0385864,0.0253049};
        //double Data_carbon_T_err_Em[3] = {0.00987354,0.0160539,0.0361215};
        //double Data_carbon_T_err[7] = {.005514,.00931460,.01604,.0103969, .0238122, .0639012,.0276331};
        //double Data_corr_carbon_T_err[3] = {.0155014,.0281568,.0373593};
        double Data_corr_carbon_T_err[6] = {0.0105462,0.0249704,0.0156045,0.0278561,0.0666714,0.0381723};
        double Data_corr2_carbon_T_err[6] = {0.0110558,0.026605,0.0169434,0.030841,0.0749084,0.0448565};
        //double Data_corr_carbon_T_err_Em[3] = {0.0141642,0.0245119,0.0618264};
        //double Data_corr_carbon_T_err[7] = {.00673677,.0121956,.0230661,.0100146,.0223715,.05628,.0429035};

        TGraphErrors *g_MC_Carbon = new TGraphErrors(6, MC_carbon_Prot_mom, MC_carbon_T, MC_carbon_Prot_mom_err, MC_carbon_T_err);
        TGraphErrors *g_Data_Carbon = new TGraphErrors(6, Data_carbon_Prot_mom, Data_carbon_T, Data_carbon_Prot_mom_err, Data_carbon_T_err);
        //TGraphErrors *g_Data_Carbon_Em = new TGraphErrors(3, Data_carbon_Prot_mom_Em, Data_carbon_T_Em, Data_carbon_Prot_mom_err_Em, Data_carbon_T_err_Em);
        TGraphErrors *g_Data_Carbon_corrected = new TGraphErrors(6, Data_carbon_Prot_mom, Data_carbon_T_corrected, Data_carbon_Prot_mom_err, Data_corr_carbon_T_err);
        TGraphErrors *g_Data_Carbon_corrected2 = new TGraphErrors(6, Data_carbon_Prot_mom, Data_carbon_T_corrected2, Data_carbon_Prot_mom_err, Data_corr2_carbon_T_err);
        //TGraphErrors *g_Data_Carbon_corrected_Em = new TGraphErrors(3, Data_carbon_Prot_mom_Em, Data_carbon_T_corrected_Em, Data_carbon_Prot_mom_err_Em, Data_corr_carbon_T_err_Em);
        g_MC_Carbon->SetMarkerColor(kViolet);
        g_Data_Carbon->SetMarkerColor(kRed);
        //g_Data_Carbon_Em->SetMarkerColor(kBlack);
        g_Data_Carbon_corrected->SetMarkerColor(kBlack);
        g_Data_Carbon_corrected2->SetMarkerColor(kGreen);
        //g_Data_Carbon_corrected_Em->SetMarkerColor(kBlack); 
        g_MC_Carbon->SetMarkerStyle(20);
        g_Data_Carbon->SetMarkerStyle(21);
        //g_Data_Carbon_Em->SetMarkerStyle(21);
        g_Data_Carbon_corrected->SetMarkerStyle(21);
        g_Data_Carbon_corrected2->SetMarkerStyle(21);

        Double_t dutta_Tp_C[4] = {.350, .700, .970, 1.8};
        Double_t dutta_Trans_C[4] = {.61, .60, .57, .58};
        Double_t dutta_Tp_err_C[4] = {0.0,0.0,0.0,0.0};
        Double_t dutta_Trans_err_C[4] = {.05*.61, .60*.05, .57*.05,.58*.05};
        TGraphErrors *dutta_C = new TGraphErrors(4, dutta_Tp_C, dutta_Trans_C, dutta_Tp_err_C, dutta_Trans_err_C);
        dutta_C->SetMarkerColor(kBlue);
        dutta_C->SetMarkerSize(2.0);
        dutta_C->SetMarkerStyle(33);
        TLegend *legend = new TLegend( leg_x1, leg_y1, leg_x2, leg_y2);
        legend->AddEntry( g_Data_Carbon, "C12 - CLAS","p");
        legend->AddEntry( g_Data_Carbon_corrected, "C12 - CLAS (neutron corrections)","p");
        legend->AddEntry( g_Data_Carbon_corrected2, "C12 - CLAS (neutron + mec corrections)","p");
        //legend->AddEntry( g_Data_Carbon_Em, "C12 - CLAS (Em cut)","p");
        //legend->AddEntry( g_Data_Carbon_corrected_Em, "C12 - CLAS (EM cut and Genie corrections)","p");
        legend->AddEntry( dutta_C, "C12 - Dutta 03","p");
        legend->AddEntry( g_MC_Carbon, "C12- GENIE SuSav2 (neutron + mec corrections)","p");
        /*
        g_MC_Carbon->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        g_MC_Carbon->GetYaxis()->SetTitle("Transparency");
        g_MC_Carbon->GetXaxis()->SetLimits(0.2,2.0);
        g_MC_Carbon->GetYaxis()->SetRangeUser(0.2,0.9);
        g_MC_Carbon->SetTitle("Proton transparency");
        */

        g_Data_Carbon->GetXaxis()->SetTitle("Proton Momentum (GeV)");
        g_Data_Carbon->GetYaxis()->SetTitle("Transparency");
        g_Data_Carbon->GetXaxis()->SetLimits(0.2,2.0);
        g_Data_Carbon->GetYaxis()->SetRangeUser(0.2,1);
        g_Data_Carbon->SetTitle("Proton transparency");


        g_Data_Carbon->Draw("ap same");
        g_Data_Carbon_corrected->Draw("p same");
        g_Data_Carbon_corrected2->Draw("p same");
        //g_Data_Carbon_Em->Draw("p same");
        //g_Data_Carbon_corrected_Em->Draw("p same");
        dutta_C->Draw("p same");
        g_MC_Carbon->Draw("p same");







///////////////////////////////////////////////////////////////////////////////////////

/*
h34->Sumw2();
h34->Divide(h4);
h34->GetXaxis()->SetTitle("Proton Kinetic Energy [GeV]");
h34->GetXaxis()->CenterTitle(true);
h34->GetYaxis()->SetTitle("Transparency");
h34->GetYaxis()->SetRangeUser(0,1.2);
h34->GetYaxis()->CenterTitle(true);
h34->SetStats(0);
h34->SetLineColor(kRed);
h34->Draw("hist same");
h34->Draw("e same");

h56->Sumw2();
h56->Divide(h6);
h56->Scale(.98);
h56->GetXaxis()->SetTitle("Proton Kinetic Energy [GeV]");
h56->GetXaxis()->CenterTitle(true);
h56->GetYaxis()->SetTitle("Transparency");
h56->GetYaxis()->SetRangeUser(0,1.2);
h56->GetYaxis()->CenterTitle(true);
//h56->SetTitle("C-12 with 2.261 GeV #nu_{e} Beam (NCEL)");
h56->SetStats(0);
h56->SetLineColor(kBlack);
h56->Draw("hist same");
h56->Draw("e same");
*/
//TLegend *legend = new TLegend(0.65, 0.775, 0.9, 0.88);
legend->AddEntry(h12,"C-12 - GENIE","l");
//legend->AddEntry(h34,"C-12 with p_{e} > 1.9 GeV","l");
//legend->AddEntry(h12,"C-12","l");
//legend->AddEntry(h34,"Fe-56","l");
//legend->SetBorderSize(0);
legend->SetFillStyle(0);
legend->Draw();

//c->SaveAs(TString::Format("transparency_C12_2261_G18_02a_00_000.pdf"));

}
