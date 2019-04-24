#ifndef PlottingTools_h
#define PlottingTools_h

#include <stdarg.h>
#include <iostream>
#include <sstream>

#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "THStack.h"
#include "TH2.h"



class PlottingTools
{
  public:

    PlottingTools() {SetStyle();};

    struct LegendDefinition
    {
      std::string title;
      std::vector<std::string> labels;
      std::string position;
    };

//   private:

    void SetStyle();
    
    

    template <typename T> T* Create1DHistogram(const char* hName, const char* hTitle, const unsigned int xNBins, const double xMin, const double xMax, const char* xTitle, const char* yTitle)
    {
      T* h = new T(hName, hTitle, xNBins, xMin, xMax);
      h->GetXaxis()->SetTitle(xTitle);
      h->GetYaxis()->SetTitle(yTitle);
      h->Sumw2();
      return h;
    };
    
    
    
    template <typename T> T* Create1DHistogram(const char* hName, const char* hTitle, const unsigned int xNBins, const double* xBins, const char* xTitle, const char* yTitle)
    {
      T* h = new T(hName, hTitle, xNBins, xBins);
      h->GetXaxis()->SetTitle(xTitle);
      h->GetYaxis()->SetTitle(yTitle);
      h->Sumw2();
      return h;
    };
    
    
    
//   template <typename T> std::vector<T*> CreateVectorOf1DHistograms(const char* hName, const char* hTitle, const unsigned int xNBins, const double xMin, const double xMax, const char* xTitle, const char* yTitle, const std::string binningVariable, const std::vector<double> vLowBins);
    template <typename T> std::vector<T*>* CreateVectorOf1DHistograms(const char* hName, const char* hTitle, const unsigned int xNBins, const double xMin, const double xMax, const char* xTitle, const char* yTitle, const std::string binningVariable, const std::vector<double> vLowBins)
    {
      std::vector<T*>* vResults = new std::vector<T*>();
      // std::cout << "vLowBins.size() = " << vLowBins.size() << std::endl;
      if(vLowBins.size() == 0)
      {
        T* result = Create1DHistogram<TH1D>(hName, hTitle, xNBins, xMin, xMax, xTitle, yTitle);
        vResults->push_back(result);
        return vResults;
      }
      
      std::vector<std::string> vTitleLabels;
      std::vector<std::string> vNameLabels;
      std::string lowest = "-Inf";
      std::string highest = "Inf";
      //   std::string lowestName = "mInf";
      //   std::string highestName = "Inf";
      
      std::ostringstream oss;
      oss.str("");
      oss << " (" << lowest << " <= " << binningVariable << " < " << vLowBins[0] << ")";
      vTitleLabels.push_back(oss.str());
      oss.str("");
      oss << "_" << binningVariable << "_" << lowest << "_" << vLowBins[0];
      vNameLabels.push_back(oss.str());
      for(unsigned int i = 0; i < vLowBins.size() - 1; i++)
      {
        oss.str("");
        oss << " (" << vLowBins[i] << " <= " << binningVariable << " < " << vLowBins[i+1] << ")";
        vTitleLabels.push_back(oss.str());
        oss.str("");
        oss << "_" << binningVariable << "_" << vLowBins[i] << "_" << vLowBins[i+1];
        vNameLabels.push_back(oss.str());
      }
      oss.str("");
      oss << " (" << vLowBins[vLowBins.size()-1] << " <= " << binningVariable << " < " << highest << ")";
      vTitleLabels.push_back(oss.str());
      oss.str("");
      oss << "_" << binningVariable << "_" << vLowBins[vLowBins.size()-1] << "_" << highest;
      vNameLabels.push_back(oss.str());
      
      
      for(unsigned int iBin = 0; iBin < vTitleLabels.size(); iBin++)
      {
        std::string hNewName = hName + vNameLabels[iBin];
        std::string hNewTitle = hTitle + vTitleLabels[iBin];
        T* result = Create1DHistogram<TH1D>(hNewName.c_str(), hNewTitle.c_str(), xNBins, xMin, xMax, xTitle, yTitle);
        vResults->push_back(result);
      }
      return vResults;
    };
    
    
    
    template <typename T> std::vector<T*>* CreateVectorOf2DHistograms(const char* hName, const char* hTitle, const unsigned int xNBins, const double xMin, const double xMax, const unsigned int yNBins, const double yMin, const double yMax, const char* xTitle, const char* yTitle, const std::string binningVariable, const std::vector<double> vLowBins)
    {
      std::vector<T*>* vResults = new std::vector<T*>();
      if(vLowBins.size() == 0)
      {
        T* result = Create2DHistogram<TH2D>(hName, hTitle, xNBins, xMin, xMax, yNBins, yMin, yMax, xTitle, yTitle);
        vResults->push_back(result);
        return vResults;
      }
      
      std::vector<std::string> vTitleLabels;
      std::vector<std::string> vNameLabels;
      std::string lowest = "-Inf";
      std::string highest = "Inf";
      //   std::string lowestName = "mInf";
      //   std::string highestName = "Inf";
      
      std::ostringstream oss;
      oss.str("");
      oss << " (" << lowest << " <= " << binningVariable << " < " << 
      vLowBins[0] << ")";
      vTitleLabels.push_back(oss.str());
      oss.str("");
      oss << "_" << binningVariable << "_" << lowest << "_" << vLowBins[0];
      vNameLabels.push_back(oss.str());
      for(unsigned int i = 0; i < vLowBins.size() - 1; i++)
      {
        oss.str("");
        oss << " (" << vLowBins[i] << " <= " << binningVariable << " < " << 
        vLowBins[i+1] << ")";
        vTitleLabels.push_back(oss.str());
        oss.str("");
        oss << "_" << binningVariable << "_" << vLowBins[i] << "_" << 
        vLowBins[i+1];
        vNameLabels.push_back(oss.str());
      }
      oss.str("");
      oss << " (" << vLowBins[vLowBins.size()-1] << " <= " << 
      binningVariable << " < " << highest << ")";
      vTitleLabels.push_back(oss.str());
      oss.str("");
      oss << "_" << binningVariable << "_" << vLowBins[vLowBins.size()-1] 
      << "_" << highest;
      vNameLabels.push_back(oss.str());
      
      for(unsigned int iBin = 0; iBin < vTitleLabels.size(); iBin++)
      {
        std::string hNewName = hName + vNameLabels[iBin];
        std::string hNewTitle = hTitle + vTitleLabels[iBin];
        T* result = Create2DHistogram<TH2D>(hNewName.c_str(), hNewTitle.c_str(), xNBins, xMin, xMax, yNBins, yMin, yMax, xTitle, yTitle);
        vResults->push_back(result);
      }
      return vResults;
    };

    
    
    // for variable-binning x axis of histogram
    template <typename T> std::vector<T*>* CreateVectorOf1DHistograms(const char* hName, const char* hTitle, const unsigned int xNBins, const double* xBins, const char* xTitle, const char* yTitle, const std::string binningVariable, const std::vector<double> vLowBins)
    {
      std::vector<T*>* vResults = new std::vector<T*>();
      // std::cout << "vLowBins.size() = " << vLowBins.size() << std::endl;
      if(vLowBins.size() == 0)
      {
        T* result = Create1DHistogram<TH1D>(hName, hTitle, xNBins, xBins, xTitle, yTitle);
        vResults->push_back(result);
        return vResults;
      }
      
      std::vector<std::string> vTitleLabels;
      std::vector<std::string> vNameLabels;
      std::string lowest = "-Inf";
      std::string highest = "Inf";
      //   std::string lowestName = "mInf";
      //   std::string highestName = "Inf";
      
      std::ostringstream oss;
      oss.str("");
      oss << " (" << lowest << " <= " << binningVariable << " < " << vLowBins[0] << ")";
      vTitleLabels.push_back(oss.str());
      oss.str("");
      oss << "_" << binningVariable << "_" << lowest << "_" << vLowBins[0];
      vNameLabels.push_back(oss.str());
      for(unsigned int i = 0; i < vLowBins.size() - 1; i++)
      {
        oss.str("");
        oss << " (" << vLowBins[i] << " <= " << binningVariable << " < " << vLowBins[i+1] << ")";
        vTitleLabels.push_back(oss.str());
        oss.str("");
        oss << "_" << binningVariable << "_" << vLowBins[i] << "_" << vLowBins[i+1];
        vNameLabels.push_back(oss.str());
      }
      oss.str("");
      oss << " (" << vLowBins[vLowBins.size()-1] << " <= " << binningVariable << " < " << highest << ")";
      vTitleLabels.push_back(oss.str());
      oss.str("");
      oss << "_" << binningVariable << "_" << vLowBins[vLowBins.size()-1] << "_" << highest;
      vNameLabels.push_back(oss.str());
      
      
      for(unsigned int iBin = 0; iBin < vTitleLabels.size(); iBin++)
      {
        std::string hNewName = hName + vNameLabels[iBin];
        std::string hNewTitle = hTitle + vTitleLabels[iBin];
        T* result = Create1DHistogram<TH1D>(hNewName.c_str(), hNewTitle.c_str(), xNBins, xBins, xTitle, yTitle);
        vResults->push_back(result);
      }
      return vResults;
    };
    
    
    
    template <typename T> T* Create2DHistogram(const char* hName, const char* hTitle, const unsigned int xNBins, const double xMin, const double xMax, const unsigned int yNBins, const double yMin, const double yMax, const char* xTitle, const char* yTitle)
    {
      T* h = new T(hName, hTitle, xNBins, xMin, xMax, yNBins, yMin, yMax);
      h->GetXaxis()->SetTitle(xTitle);
      h->GetYaxis()->SetTitle(yTitle);
      h->Sumw2();
      return h;
    };
    
    
    
    template <typename T> T* Create2DHistogram(const char* hName, const char* hTitle, const unsigned int xNBins, const double xMin, const double xMax, const unsigned int yNBins, const double yMin, const double yMax, const char* xTitle, const char* yTitle, const char* zTitle)
    {
      T* h = Create2DHistogram<T>(hName, hTitle, xNBins, xMin, xMax, yNBins, yMin, yMax, xTitle, yTitle);
      h->GetZaxis()->SetTitle(zTitle);
      
      return h;
    };
    
    
    
    // For variable-size bins
    template <typename T> T* Create2DHistogram(const char* hName, const char* hTitle, const unsigned int xNBins, const std::vector<double> xBins, const unsigned int yNBins, const std::vector<double> yBins, const char* xTitle, const char* yTitle)
    {
      if(xBins.size() != xNBins+1 || yBins.size() != yNBins+1)
      {
        std::cout << "E R R O R ! Create2DHistogram: vector of bin sizes must have nbins+1 entries!\n";
        std::cout << "            Exiting...\n";
        exit(1);
      }
      T* h = new T(hName, hTitle, xNBins, &xBins[0], yNBins, &yBins[0]);
      h->GetXaxis()->SetTitle(xTitle);
      h->GetYaxis()->SetTitle(yTitle);
      h->Sumw2();
      return h;
    };
    
    
    
    template <typename T> T* CreateGraph(const char* gName, const char* gTitle, const char* xTitle, const char* yTitle, const int nPoints = 0)
    {
      T* g;
      if(nPoints == 0)
        g = new T();
      else
        g = new T(nPoints);
      // Dummy histogram
      g->SetHistogram(new TH1F("","",nPoints!=0?nPoints:10,0.,1.));
      g->SetName(gName);
      g->SetTitle(gTitle);
      g->GetHistogram()->GetXaxis()->SetTitle(xTitle);
      g->GetHistogram()->GetYaxis()->SetTitle(yTitle);
      return g;
    };
    
    
    
    template <typename T> std::vector<T*>* CreateVectorOfGraphs(const char* gName, const char* gTitle, const char* xTitle, const char* yTitle, const std::string binningVariable, const std::vector<double> vLowBins, const unsigned int nPoints = 0)
    {
      std::vector<T*>* vResults = new std::vector<T*>();
      // std::cout << "vLowBins.size() = " << vLowBins.size() << std::endl;
      if(vLowBins.size() == 0)
      {
        T* result = CreateGraph<T>(gName, gTitle, xTitle, yTitle, nPoints);
        vResults->push_back(result);
        return vResults;
      }
      std::vector<std::string> vTitleLabels;
      std::vector<std::string> vNameLabels;
      std::string lowest = "-Inf";
      std::string highest = "Inf";
      //   std::string lowestName = "mInf";
      //   std::string highestName = "Inf";
      
      std::ostringstream oss;
      oss.str("");
      oss << " (" << lowest << " <= " << binningVariable << " < " << vLowBins[0] << ")";
      vTitleLabels.push_back(oss.str());
      oss.str("");
      oss << "_" << binningVariable << "_" << lowest << "_" << vLowBins[0];
      vNameLabels.push_back(oss.str());
      for(unsigned int i = 0; i < vLowBins.size() - 1; i++)
      {
        oss.str("");
        oss << " (" << vLowBins[i] << " <= " << binningVariable << " < " << vLowBins[i+1] << ")";
        vTitleLabels.push_back(oss.str());
        oss.str("");
        oss << "_" << binningVariable << "_" << vLowBins[i] << "_" << vLowBins[i+1];
        vNameLabels.push_back(oss.str());
      }
      oss.str("");
      oss << " (" << vLowBins[vLowBins.size()-1] << " <= " << binningVariable << " < " << highest << ")";
      vTitleLabels.push_back(oss.str());
      oss.str("");
      oss << "_" << binningVariable << "_" << vLowBins[vLowBins.size()-1] << "_" << highest;
      vNameLabels.push_back(oss.str());
      
      
      for(unsigned int iBin = 0; iBin < vTitleLabels.size(); iBin++)
      {
        std::string gNewName = gName + vNameLabels[iBin];
        std::string gNewTitle = gTitle + vTitleLabels[iBin];
        T* result = CreateGraph<T>(gNewName.c_str(), gNewTitle.c_str(), xTitle, yTitle, nPoints);
        vResults->push_back(result);
      }
      return vResults;
    };
    

    // Finds the bin division to be used to compare histograms with different binning
    // Just for 2D histograms for the moment
    // I.e. histo 1 has bin edges [0,1,2,3,5,7] and histo2 has bin edges [1,2,4,6,8]
    // Resulting binning will be [1,2,3,4,5,6]
    std::pair<std::vector<double>,std::vector<double> > FindDifferenceBinDivision(const TH2* hFirst, const TH2* hSecond);
    
    // Checks that the two histograms have same bins along x and y
    bool SameBins(const TH1* hFirst, const TH1* hSecond);
    
    // Only for 2D histograms and only around the X axis for the time being
    TH2D* SymmetrizeHistogramInX(const TH2D* histo, bool aroundLowEdge = true);
    
    // To overcome stupid bug in ROOT
    void BayesDivide(const TH1* pass, const TH1* total, TGraphAsymmErrors* graph);
    void ClopperPearsonDivide(const TH1* pass, const TH1* total, TGraphAsymmErrors* graph);
    void FeldmanCousinsDivide(const TH1* pass, const TH1* total, TGraphAsymmErrors* graph);
    
    void SetCanvasStyle(TPad* c, const bool logScaleX, const bool logScaleY);
    void SetCanvasStyle(TPad* c, const bool logScaleX, const bool logScaleY, const bool logScaleZ);
    void SetProfileStyle(TProfile* p);
    void SetHistoStyle(TH1* h, const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int lineColor);
    void SetStackHistoStyle(TH1* h, const unsigned int color);
    void SetGraphStyle(TGraph* g, const unsigned int markerStyle, const unsigned int lineColor);
    
    
    
    template <typename T>
    std::vector<TCanvas*>* CreateCanvases(const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, std::vector<T*> vHistos)
    {
      std::vector<TCanvas*>* vTCanvases = new(std::vector<TCanvas*>);
      if(vHistos.size() == 0)
      {
        std::cout << "\nW A R N I N G ! PlottingTools::CreateAndWriteCanvases(...) : vector of histograms to be plotted is empty!\n";
        std::cout << "                No canvases will be created!\n";
      }
      else
      {
        for(unsigned int iHisto = 0; iHisto < vHistos.size(); iHisto++)
        {
          std::string canvasName = vHistos[iHisto]->GetName();
          //       std::cout << "before: canvasName = " << canvasName << std::endl;
          if(canvasName.substr(0,1) == "h")
          {
            canvasName.replace(0,1,"c");
            //         std::cout << "after:  canvasName = " << canvasName << std::endl;
          }
          else
          {
            canvasName = "c" + canvasName;
          }
          vTCanvases->push_back(CreateCanvas(canvasName.c_str(),lineStyle,markerStyle,color,logScaleX,logScaleY,vHistos[iHisto]));
        }
      }
      return vTCanvases;
    };
    
    
    
    template <typename T>
    std::vector<TCanvas*>* CreateAndWriteCanvases(const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, std::vector<T*> vHistos)
    {
      std::vector<TCanvas*>* vTCanvases = CreateCanvases(lineStyle, markerStyle, color, logScaleX, logScaleY, vHistos);
      for(unsigned int iCanvas = 0; iCanvas < vTCanvases->size(); iCanvas++)
      {
        vTCanvases->at(iCanvas)->Update();
        vTCanvases->at(iCanvas)->Write();
      }
      
      return vTCanvases;
    };
    
    
    
    template <typename T>
    std::vector<TCanvas*>* CreateCanvases(const char* plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, std::vector<T*> vHistos)
    {
      std::vector<TCanvas*>* vTCanvases = new(std::vector<TCanvas*>);
      if(vHistos.size() == 0)
      {
        std::cout << "\nW A R N I N G ! PlottingTools::CreateAndWriteCanvases(...) : vector of histograms to be plotted is empty!\n";
        std::cout << "                No canvases will be created!\n";
      }
      else
      {
        for(unsigned int iHisto = 0; iHisto < vHistos.size(); iHisto++)
        {
          std::string canvasName = vHistos[iHisto]->GetName();
          std::cout << "before: canvasName = " << canvasName << std::endl;
          if(canvasName.substr(0,1) == "h")
          {
            canvasName.replace(0,1,"c");
            std::cout << "after:  canvasName = " << canvasName << std::endl;
          }
          else
          {
            canvasName = "c" + canvasName;
          }
          vTCanvases->push_back(CreateCanvas(canvasName.c_str(),plotOptions,logScaleX,logScaleY,logScaleZ,vHistos[iHisto]));
        }
      }
      return vTCanvases;
    };
    
    
    
    template <typename T>
    std::vector<TCanvas*>* CreateAndWriteCanvases(const char* plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, std::vector<T*> vHistos)
    {
      std::vector<TCanvas*>* vTCanvases = CreateCanvases(plotOptions, logScaleX, logScaleY, logScaleZ, vHistos);
      for(unsigned int iCanvas = 0; iCanvas < vTCanvases->size(); iCanvas++)
      {
        vTCanvases->at(iCanvas)->Update();
        vTCanvases->at(iCanvas)->Write();
      }
      
      return vTCanvases;
    };
    
    
    
    template <typename T>
    std::vector<TCanvas*>* CreateCanvases(const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, std::vector<T*> vGraphs)
    {
      std::vector<TCanvas*>* vTCanvases = new(std::vector<TCanvas*>);
      if(vGraphs.size() == 0)
      {
        std::cout << "\nW A R N I N G ! PlottingTools::CreateAndWriteCanvases(...) : vector of graphs to be plotted is empty!\n";
        std::cout << "                No canvases will be created!\n";
      }
      else
      {
        for(unsigned int iGraph = 0; iGraph < vGraphs.size(); iGraph++)
        {
          std::string canvasName = vGraphs[iGraph]->GetName();
          //       std::cout << "before: canvasName = " << canvasName << std::endl;
          if(canvasName.substr(0,1) == "g")
          {
            canvasName.replace(0,1,"c");
            //         std::cout << "after:  canvasName = " << canvasName << std::endl;
          }
          else
          {
            canvasName = "c" + canvasName;
          }
          vTCanvases->push_back(CreateCanvas(canvasName.c_str(),markerStyle,color,logScaleX,logScaleY,vGraphs[iGraph]));
        }
      }
      return vTCanvases;
    };
    
    
    
    template <typename T>
    std::vector<TCanvas*>* CreateAndWriteCanvases(const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, std::vector<T*> vGraphs)
    {
      std::vector<TCanvas*>* vTCanvases = CreateCanvases(markerStyle, color, logScaleX, logScaleY, vGraphs);
      for(unsigned int iCanvas = 0; iCanvas < vTCanvases->size(); iCanvas++)
      {
        vTCanvases->at(iCanvas)->Update();
        vTCanvases->at(iCanvas)->Write();
      }
      
      return vTCanvases;
    };
    
    

    template <typename T, typename U> void Fill(std::vector<T*>* vHistos, const U value, const double binningValue, std::vector<double> vLowBins)
    {
      unsigned int i = 0;
      for(/* */; i < vLowBins.size(); i++)
      {
        if(binningValue < vLowBins[i])
        {
          break;
        }
      }
      vHistos->at(i)->Fill(value);
    };
    


    template <typename T, typename U> void Fill(std::vector<T*>* vHistos, const U valueX, const U valueY, const double binningValue, std::vector<double> vLowBins)
    {
      unsigned int i = 0;
      for(/* */; i < vLowBins.size(); i++)
      {
        if(binningValue < vLowBins[i])
        {
          break;
        }
      }
      vHistos->at(i)->Fill(valueX, valueY);
    };



    TCanvas* CreateCanvas(const char* cName, const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, TH1* histo);
    TCanvas* CreateAndWriteCanvas(const char* cName, const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, TH1* histo);
    TCanvas* CreateCanvas(const char* cName, const char* cTitle, const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, TH1* histo);
    TCanvas* CreateAndWriteCanvas(const char* cName, const char* cTitle, const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, TH1* histo);
    TCanvas* CreateCanvas(const char* cName, const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const TH1* histo);
    TCanvas* CreateAndWriteCanvas(const char* cName, const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const TH1* histo);
    TCanvas* CreateCanvas(const char* cName, const char* cTitle, const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, TH1* histo);
    TCanvas* CreateAndWriteCanvas(const char* cName, const char* cTitle, const unsigned int lineStyle, const unsigned int markerStyle, const unsigned int color, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, TH1* histo);
    TCanvas* CreateCanvas(const char* cName, const std::string plotOptions, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo);
    TCanvas* CreateAndWriteCanvas(const char* cName, const std::string plotOptions, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo);
    TCanvas* CreateCanvas(const char* cName, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo);
    TCanvas* CreateAndWriteCanvas(const char* cName, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo);
    TCanvas* CreateCanvas(const char* cName, const char* cTitle, const std::string plotOptions, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo);
    TCanvas* CreateAndWriteCanvas(const char* cName, const char* cTitle, const std::string plotOptions, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo);
    TCanvas* CreateCanvas(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo);
    TCanvas* CreateAndWriteCanvas(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo);
    TCanvas* CreateCanvas3D(const char* cName, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const bool logScaleZ, const double phi, const double theta, TH2* histo);
    TCanvas* CreateAndWriteCanvas3D(const char* cName, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const bool logScaleZ, const double phi, const double theta, TH2* histo);
    TCanvas* CreateCanvas3D(const char* cName, const bool logScaleX, const bool logScaleY, const bool logScaleZ, const double phi, const double theta, TH2* histo);
    TCanvas* CreateAndWriteCanvas3D(const char* cName, const bool logScaleX, const bool logScaleY, const bool logScaleZ, const double phi, const double theta, TH2* histo);
    TCanvas* CreateCanvas3D(const char* cName, const char* cTitle, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const bool logScaleZ, const double phi, const double theta, TH2* histo);
    TCanvas* CreateAndWriteCanvas3D(const char* cName, const char* cTitle, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, const bool logScaleZ, const double phi, const double theta, TH2* histo);
    TCanvas* CreateCanvas3D(const char* cName, const char* cTitle, const bool logScaleX, const bool logScaleY, const bool logScaleZ, const double phi, const double theta, TH2* histo);
    TCanvas* CreateAndWriteCanvas3D(const char* cName, const char* cTitle, const bool logScaleX, const bool logScaleY, const bool logScaleZ, const double phi, const double theta, TH2* histo);

//     void CreateAndWriteCanvas(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvas(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvas(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvas(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvas(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvas(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteCanvas(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateCanvas(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteCanvas(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);

    TCanvas* CreateCanvasWithDifferences(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvasWithDifferences(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvasWithDifferences(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvasWithDifferences(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvasWithDifferences(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteCanvasWithDifferences(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateCanvasWithDifferences(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteCanvasWithDifferences(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);

    TCanvas* CreateCanvasWithPulls(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvasWithPulls(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvasWithPulls(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvasWithPulls(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvasWithPulls(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteCanvasWithPulls(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateCanvasWithPulls(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteCanvasWithPulls(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);

    TCanvas* CreateCanvasWithRatios(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvasWithRatios(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvasWithRatios(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvasWithRatios(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvasWithRatios(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteCanvasWithRatios(const char* cName, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateCanvasWithRatios(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteCanvasWithRatios(const char* cName, const char* cTitle, const unsigned int* lineStyles, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    
    // These canvases are plotted by default with the first histogram as points and the others stacked as fill area
    TCanvas* CreateStackCanvasWithDifferences(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteStackCanvasWithDifferences(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateStackCanvasWithDifferences(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteStackCanvasWithDifferences(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateStackCanvasWithDifferences(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteStackCanvasWithDifferences(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateStackCanvasWithDifferences(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteStackCanvasWithDifferences(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    
    TCanvas* CreateStackCanvasWithPulls(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteStackCanvasWithPulls(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateStackCanvasWithPulls(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteStackCanvasWithPulls(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateStackCanvasWithPulls(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteStackCanvasWithPulls(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateStackCanvasWithPulls(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteStackCanvasWithPulls(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    
    TCanvas* CreateStackCanvasWithRatios(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteStackCanvasWithRatios(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateStackCanvasWithRatios(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteStackCanvasWithRatios(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateStackCanvasWithRatios(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteStackCanvasWithRatios(const char* cName, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateStackCanvasWithRatios(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    TCanvas* CreateAndWriteStackCanvasWithRatios(const char* cName, const char* cTitle, const unsigned int markerStyle, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, std::vector<TH1*> histos);
    
    TCanvas* CreateCanvasWith2DDifference(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo1, TH2* histo2);
    TCanvas* CreateAndWriteCanvasWith2DDifference(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo1, TH2* histo2);
    TCanvas* CreateCanvasWith2DRelDifference(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo1, TH2* histo2);
    TCanvas* CreateAndWriteCanvasWith2DRelDifference(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo1, TH2* histo2);
    TCanvas* CreateCanvasWith2DRatio(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* hNumerator, TH2* hDenominator);
    TCanvas* CreateAndWriteCanvasWith2DRatio(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* hNumerator, TH2* hDenominator);
    TCanvas* CreateCanvasWith2DPull(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo1, TH2* histo2);
    TCanvas* CreateAndWriteCanvasWith2DPull(const char* cName, const char* cTitle, const std::string plotOptions, const bool logScaleX, const bool logScaleY, const bool logScaleZ, TH2* histo1, TH2* histo2);
    
    // To use with TGraphs
    TCanvas* CreateCanvas(const char* cName, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvas(const char* cName, const unsigned int* markerStyles, const unsigned int* colors, const LegendDefinition leg, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvas(const char* cName, const unsigned int* markerStyles, const unsigned int* colors, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateAndWriteCanvas(const char* cName, const unsigned int* markerStyles, const unsigned int* colors, const bool logScaleX, const bool logScaleY, ...);
    TCanvas* CreateCanvas(const char* cName, const LegendDefinition leg, const unsigned int* markerStyles, const unsigned int* colors, const bool logScaleX, const bool logScaleY, std::vector<TGraph*> graphs);
    TCanvas* CreateAndWriteCanvas(const char* cName, const LegendDefinition leg, const unsigned int* markerStyles, const unsigned int* colors, const bool logScaleX, const bool logScaleY, std::vector<TGraph*> graphs);
    TCanvas* CreateCanvas(const char* cName, const unsigned int* markerStyles, const unsigned int* colors, const bool logScaleX, const bool logScaleY, std::vector<TGraph*> graphs);
    TCanvas* CreateAndWriteCanvas(const char* cName, const unsigned int* markerStyles, const unsigned int* colors, const bool logScaleX, const bool logScaleY, std::vector<TGraph*> graphs);
    TCanvas* CreateCanvas(const char* cName, const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, TGraph* graph);
    TCanvas* CreateAndWriteCanvas(const char* cName, const unsigned int markerStyle, const unsigned int color, const bool logScaleX, const bool logScaleY, TGraph* graph);

    void PlotLegend(TPad* c, const std::vector<TObject*> histos, std::vector<std::string> plotOptions, const LegendDefinition leg);
    void PlotLegend(TPad* c, const std::vector<TH1*> histos, std::vector<std::string> plotOptions, const LegendDefinition leg);
    void PlotLegend(TPad* c, TH1* histo, THStack* stack, std::vector<std::string> plotOptions, const LegendDefinition leg);
    void PlotLegend(TPad* c, const std::vector<TGraph*> graphs, std::vector<std::string> plotOptions, const LegendDefinition leg);
    void PlotLegend(TPad* c, const TH2* histo, std::string plotOptions, const LegendDefinition leg);
};

#endif // PlottingTools_h
