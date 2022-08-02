void transmission_plot4(){
TFile *input1 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000.root");
TFile *input2 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_noFSI.root");

TFile *input3 = TFile::Open("transmission_56Fe_2261_EMQE_G18_02a_00_000.root");
TFile *input4 = TFile::Open("transmission_56Fe_2261_EMQE_G18_02a_00_000_noFSI.root");

//TFile *input5 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_el_mom_1.9_el_theta_20_25.root");
//TFile *input6 = TFile::Open("transmission_C12_2261_EMQE_G18_02a_00_000_noFSI_el_mom_1.9_el_theta_20_25.root");


TH1D* h1 = (TH1D*)input1->Get(TString::Format("prot_p"));
TH1D* h2 = (TH1D*)input2->Get(TString::Format("prot_p"));
TH1D* h12 = (TH1D*)h1->Clone("h12");

TH1D* h3 = (TH1D*)input3->Get(TString::Format("prot_p"));
TH1D* h4 = (TH1D*)input4->Get(TString::Format("prot_p"));
TH1D* h34 = (TH1D*)h3->Clone("h34");
//TH1D* h34 = (TH1D*)h3->Clone("h34");

//TH1D* h5 = (TH1D*)input5->Get(TString::Format("prot_p"));
//TH1D* h6 = (TH1D*)input6->Get(TString::Format("prot_p"));
//TH1D* h56 = (TH1D*)h5->Clone("h56");

TCanvas* c;
c = new TCanvas(TString::Format("c"), TString::Format("c"), 800, 600);

c->SetLeftMargin(0.13);
c->Update();

h12->Sumw2();
h12->Divide(h2);
h12->Scale(.99);
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

h34->Sumw2();
h34->Divide(h4);
h34->GetXaxis()->SetTitle("Proton Momentum [GeV/c]");
//h34->GetXaxis()->CenterTitle(true);
h34->GetYaxis()->SetTitle("Transparency");
h34->GetYaxis()->SetRangeUser(0,1.2);
//h34->GetYaxis()->CenterTitle(true);
h34->SetStats(0);
h34->SetLineColor(kRed);
h34->Draw("hist same");
h34->Draw("e same");
/*
h56->Sumw2();
h56->Divide(h6);
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
const double leg_x1 = 0.6; // x-axis lower bound for the legend
const double leg_x2 = 0.88; // x-axis upper bound for the legend
const double leg_y1 = 0.74; // y-axis lower bound for the legend
const double leg_y2 = 0.875; // y-axis upper bound for the legend

TLegend *legend = new TLegend( leg_x1, leg_y1, leg_x2, leg_y2) ;
//TLegend *legend = new TLegend(0.65, 0.775, 0.9, 0.88);
legend->AddEntry(h12,"C-12 - GENIE","l");
legend->AddEntry(h34,"Fe-56 - GENIE","l");
//legend->AddEntry(h56,"C-12 with #theta_{e} and p_{e} cuts","l");
//legend->SetBorderSize(0);
legend->SetFillStyle(0);
legend->Draw();

c->SaveAs(TString::Format("transparency_prot_p_2261_G18_02a_00_000.pdf"));

}
