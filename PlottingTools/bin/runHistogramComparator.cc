#include <string>
#include <vector>

#include "MGTools/PlottingTools/interface/HistogramComparator.h"

int main( int argc, char* argv[] )
{

  // List of input files
  std::vector<std::string> inputFileNames;
  inputFileNames.push_back("../../../PDAnalysis/Ntu/bin/his__analyzeElectronEfficiency__BsToJpsiPhi_2018_LOCAL__All.root");
//   inputFileNames.push_back("../../../PDAnalysis/Ntu/bin/his__analyzeElectronEfficiency__BsToJpsiPhi_2018_LOCAL__HZZID.root");
  inputFileNames.push_back("../../../PDAnalysis/Ntu/bin/his__analyzeElectronEfficiency__BsToJpsiPhi_2018_LOCAL__NILID.root");
  
  // Output file
  std::string outputFileName("his-BsToJpsiPhi_2018_LOCAL-AllVsNILID-Norm0.root");
  
  // How to normalize
  // Normalization method can be
  // 0 - No normalization
  // 1 - Same area
  // 2 - Use the ratio of entries of a given histogram for all the histograms
  // 3 - Use the ratio of counts (= sum of bin entries times bin x-value) of a
  //     given histogram for all the histograms
  //     (In cases 2 and 3 the name of an histogram must be provided in the constructor)
  // 4 - Normalized to unity
  unsigned short int normalizationMethod = 0;
  std::string normalizationHistoName("");

  // Graphics definition
  unsigned int lineStyles[10] = {0,0,0,0};
//   unsigned int markerStyles[10] = {21,20,22,23};
//   unsigned int colors[10] = {1,2,4,3};
  unsigned int markerStyles[10] = {21,22};
  unsigned int colors[10] = {1,4};
  std::vector<std::string> legendLabels;
  legendLabels.push_back("All electrons");
//   legendLabels.push_back("HZZ ID");
  legendLabels.push_back("Non-Iso Loose MVA ID");
  
  std::string canvasTitle("CMS Run 2 Simulation");

  HistogramComparator hc(inputFileNames, outputFileName, normalizationMethod, normalizationHistoName, lineStyles, markerStyles, colors, canvasTitle, legendLabels);
  hc.LoopOverHistograms();
  hc.LoopOverGraphs();
  return 0;
}
