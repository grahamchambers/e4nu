Graham Chambers-Wall, 8/1/2022

This files lists the (important) files I added to e4nu for our transparency analysis. The most comprehensive one for our data calculation is xsec_data_corr2.C (calculates data transparency with all corrections). Files with a "*" before them are files whose main pupose is just to plot something.


important /Analyze_data/ files:

	* Acceptance_Ratio.C - plots acceptance ratio (true/reco) for SuSav2, Genie, and their average
	* Acceptance_Ratio_1161.C - same as above but for 1.161 GeV (only two ranges)
	* Acceptance_Ratio2.C - plots radiative corrections (without rad / with rad) for SuSav2
	* Acceptance_Ratio2_1161.C - same as above but for 1.161 GeV (only two ranges)
	
	xsec_interpolate.C - interpolates from cross section values from spline
	xsec_mc.C - plots cross section for MC using Afro's UniversalE4vFunction
	xsec_data.C - same as above but for data
	xsec_data_corr2.C - makes exclusive proton / inclusive proton ratio with corrections for mec and neutron contamination (inputs as array) and acceptance and radiative corrections (inputs are root files with exclusive cuts. these are scaled using UniversalE4vFunction)
	

important /Scripts/ files:

	trans_calc_3_ranges.C - calculates transparency for exclusive proton / inclusive proton. Neutron correction is input and MEC correction is calculed from the input MC files (also calculates MC transparency). For only 1 or 2 ranges (for 1.161 or 4.461 GeV), use trans_calc_1_range.C or trans_calc_2_ranges.C 


important /Simulations/ files:

	Drawplots2.C - inputs gst file from simulation and gives proton kinetic energy and momentum with cuts applied on line 104 (currently set to select protons that did not rescatter). Used this file for true MC studies using FSI / no FSI
	* transparency_full_plot.C - plots C-12 data, truth, SuSav2 analysis, and Dutta
	* transmission_plot3_56Fe.C - same as above but for Fe-56
	* transmission_plot3_4He.C - same as above but for He-4
	* transmission_plot3_copy2.C - plots the C-12 validation plot with all of the different MC calculations as well as Dutta 03
