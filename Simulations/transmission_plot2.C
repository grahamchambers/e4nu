void transmission_plot2(){

TFile *input1 = TFile::Open("transmission_plots_lead_proton_C12_2261_NCEL_G18_10a_02_11a_FSI.root");
TFile *input2 = TFile::Open("transmission_plots_lead_proton_C12_2261_NCEL_G18_10a_02_11a_noFSI.root");

TFile *input3 = TFile::Open("transmission_plots_lead_proton_C12_2261_NCEL_G18_10b_02_11a_FSI.root");
TFile *input4 = TFile::Open("transmission_plots_lead_proton_C12_2261_NCEL_G18_10b_02_11a_noFSI.root");

TFile *input5 = TFile::Open("transmission_plots_lead_proton_C12_2261_NCEL_G18_02b_02_11a_FSI.root");
TFile *input6 = TFile::Open("transmission_plots_lead_proton_C12_2261_NCEL_G18_02b_02_11a_noFSI.root");


TH1D* h1 = (TH1D*)input1->Get(TString::Format("Tp_SuSav2"));
TH1D* h2 = (TH1D*)input2->Get(TString::Format("Tp_SuSav2"));
TH1D* h12 = (TH1D*)h1->Clone("h12");

TH1D* h3 = (TH1D*)input3->Get(TString::Format("Tp_SuSav2"));
TH1D* h4 = (TH1D*)input4->Get(TString::Format("Tp_SuSav2"));
TH1D* h34 = (TH1D*)h3->Clone("h34");

TH1D* h5 = (TH1D*)input5->Get(TString::Format("Tp_SuSav2"));
TH1D* h6 = (TH1D*)input6->Get(TString::Format("Tp_SuSav2"));
TH1D* h56 = (TH1D*)h5->Clone("h56");

TCanvas* c;
c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

c->SetLeftMargin(0.13);
c->Update();

h12->Sumw2();
h12->Divide(h2);
h12->Scale(.99);
h12->GetXaxis()->SetTitle("Proton Kinetic Energy [GeV]");
h12->GetXaxis()->CenterTitle(true);
h12->GetYaxis()->SetTitle("Transparency");
h12->GetYaxis()->SetRangeUser(0,1.2);
h12->GetYaxis()->CenterTitle(true);
//h12->SetTitle("2.261 GeV #nu_{e} Beam (NCEL)");
h12->SetStats(0);
h12->SetLineColor(kBlue);
h12->Draw("hist");
h12->Draw("e same");

h34->Sumw2();
h34->Divide(h4);
h34->GetXaxis()->SetTitle("Proton Kinetic Energy [GeV]");
h34->GetXaxis()->CenterTitle(true);
h34->GetYaxis()->SetTitle("Transparency");
h34->GetYaxis()->SetRangeUser(0,1.2);
h34->GetYaxis()->CenterTitle(true);
//h34->SetTitle("2.261 GeV #nu_{e} Beam (NCEL)");
h34->SetStats(0);
h34->SetLineColor(kRed);
h34->Draw("hist same");
h34->Draw("e same");

h56->Sumw2();
h56->Divide(h6);
//h56->Scale(.99);
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

TLegend *legend = new TLegend(0.15, 0.425, 0.5, 0.58);
//TLegend *legend = new TLegend(0.65, 0.775, 0.9, 0.88);
legend->AddEntry(h12,"C-12","l");
legend->AddEntry(h34,"Fe-56","l");
legend->AddEntry(h56,"He-4","l");
legend->SetBorderSize(0);
legend->SetFillStyle(0);
legend->Draw();

c->SaveAs(TString::Format("prot_KE_2261_G18_02a_00_000.pdf"));

}
