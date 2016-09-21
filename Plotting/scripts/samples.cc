using namespace std;

class plotterInput{

 public :
  
  int lineColor, lineWidth, lineStyle, fillColor, fillStyle, scale;
  TString drawOptions, histoTag, legLabel;
  bool stack,norm;
  TH1F* histo;

  plotterInput(int lineColor_ = 1 , 
	       int lineWidth_ = 2 ,
	       int lineStyle_ = 1 , 
	       int fillColor_ = 0 , 
	       int fillStyle_ = 1 , 
	       TString drawOptions_ = "" , 
	       TString histoTag_ = "" , 
	       bool stack_ = false , 
	       int scale_ = 1.0 , 
	       bool norm_ = false , 
	       TString legLabel_ = "" ){

    lineColor = lineColor_;
    lineWidth = lineWidth_;
    lineStyle = lineStyle_;
    fillColor = fillColor_;
    fillStyle = fillStyle_;
    drawOptions = drawOptions_;
    histoTag = histoTag_;
    stack = stack_;
    scale = scale_;
    norm = norm_;
    legLabel = legLabel_;
    histo = 0;

  };

  void setStyle(){

    histo->SetLineColor(lineColor);
    histo->SetLineStyle(lineStyle);
    histo->SetLineWidth(lineWidth);
    histo->SetFillColor(fillColor);
    //histo->SetFillStyle(fillStyle);

  };
  
  void drawHisto(TString options=""){

    if( histo == 0 ){
      cout << "Problem with null histogram" << endl;
      return ;
    }
    histo->Draw(drawOptions+","+options);

  };

};

