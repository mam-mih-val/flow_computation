//
// Created by mikhail on 8/6/20.
//

#include "correlation_builder.h"

int main(){
  Computation::CorrelationBuilder builder;
  builder.OpenFile("/home/mikhail/Correlations/ag123_fw3_rs.root");
  auto un_qn = builder.Build("(u,F)","u_RESCALED_F_RECENTERED", {"u1x_Q1x_EP", "u1y_Q1y_EP"});
  auto r1_r2 = builder.Build("(R1,R2)","R1_RECENTERED_R2_RECENTERED", {"Q1x_Q1x_EP", "Q1y_Q1y_EP"});

  auto mf_w1 = builder.Build("(Mf,W1)","M_RESCALED_W1_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  mf_w1.Rebin({"mdc_vtx_tracks_rapidity", 1, 1.09, 1.29});
  mf_w1.Projection({"Centrality"});
  auto mf_w2 = builder.Build("(Mf,W2)","M_RESCALED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  mf_w2.Rebin({"mdc_vtx_tracks_rapidity", 1, 1.09, 1.29});
  mf_w2.Projection({"Centrality"});
  auto mf_w3 = builder.Build("(Mf,W3)","M_RESCALED_W3_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  mf_w3.Rebin({"mdc_vtx_tracks_rapidity", 1, 1.09, 1.29});
  mf_w3.Projection({"Centrality"});

  auto mb_w1 = builder.Build("(Mb,W1)","M_RESCALED_W1_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  mb_w1.Rebin({"mdc_vtx_tracks_rapidity", 1, 0.19, 0.39});
  mb_w1.Projection({"Centrality"});
  auto mb_w2 = builder.Build("(Mb,W2)","M_RESCALED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  mb_w2.Rebin({"mdc_vtx_tracks_rapidity", 1, 0.19, 0.39});
  mb_w2.Projection({"Centrality"});
  auto mb_w3 = builder.Build("(Mb,W3)","M_RESCALED_W3_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  mb_w3.Rebin({"mdc_vtx_tracks_rapidity", 1, 0.19, 0.39});
  mb_w3.Projection({"Centrality"});

  auto mf_mb = builder.Build("(Mf,Mb)","M_RESCALED_M_RESCALED", {"Q1x_Q1x", "Q1y_Q1y"});
  mf_mb.Rebin({"M_RESCALED_0_mdc_vtx_tracks_rapidity", 1, 1.09, 1.29});
  mf_mb.Rebin({"M_RESCALED_1_mdc_vtx_tracks_rapidity", 1, 0.19, 0.39});
  mf_mb.Projection({"Centrality"});

  auto w1_w2 = builder.Build("(W1,W2)","W1_RECENTERED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  auto w1_w3 = builder.Build("(W1,W3)","W1_RECENTERED_W3_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  auto w2_w3 = builder.Build("(W2,W3)","W2_RECENTERED_W3_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});

  std::vector<Computation::Correlation> resolutions;

  // W1(...,...)
  resolutions.push_back( Resolution3S( w1_w3, w1_w2, w2_w3 ) );
  resolutions.back().SetName("res_W1(W2,W3)");
  resolutions.push_back( Resolution3S( w1_w2, mf_w1, mf_w2 ) );
  resolutions.back().SetName("res_W1(Mf,W2)");
  resolutions.push_back( Resolution3S( w1_w3, mf_w1, mf_w3 ) );
  resolutions.back().SetName("res_W1(Mf,W3)");
  resolutions.push_back( Resolution3S( w1_w2, mb_w1, mb_w2 ) );
  resolutions.back().SetName("res_W1(Mb,W2)");
  resolutions.push_back( Resolution3S( w1_w3, mb_w1, mb_w3 ) );
  resolutions.back().SetName("res_W1(Mb,W3)");
  resolutions.push_back( Resolution3S( mf_w3, mb_w1, mf_mb ) );
  resolutions.back().SetName("res_W1(Mf,Mb)");
  // W2(...,...)
  resolutions.push_back( Resolution3S( w1_w3, w1_w2, w1_w3 ) );
  resolutions.back().SetName("res_W2(W1,W3)");
  resolutions.push_back( Resolution3S( w1_w2, mf_w2, mf_w1 ) );
  resolutions.back().SetName("res_W2(Mf,W1)");
  resolutions.push_back( Resolution3S( w2_w3, mf_w2, mf_w3 ) );
  resolutions.back().SetName("res_W2(Mf,W3)");
  resolutions.push_back( Resolution3S( w1_w2, mb_w2, mb_w1 ) );
  resolutions.back().SetName("res_W2(Mb,W1)");
  resolutions.push_back( Resolution3S( w2_w3, mb_w2, mb_w3 ) );
  resolutions.back().SetName("res_W2(Mb,W3)");
  resolutions.push_back( Resolution3S( mf_w2, mb_w2, mf_mb ) );
  resolutions.back().SetName("res_W2(Mf,Mb)");
  // W3(...,...)
  resolutions.push_back( Resolution3S( w1_w3, w2_w3, w1_w2 ) );
  resolutions.back().SetName("res_W3(W1,W2)");
  resolutions.push_back( Resolution3S( w1_w3, mf_w3, mf_w1 ) );
  resolutions.back().SetName("res_W3(Mf,W1)");
  resolutions.push_back( Resolution3S( w2_w3, mf_w3, mf_w2 ) );
  resolutions.back().SetName("res_W3(Mf,W2)");
  resolutions.push_back( Resolution3S( w1_w3, mb_w3, mb_w1 ) );
  resolutions.back().SetName("res_W3(Mb,W1)");
  resolutions.push_back( Resolution3S( w2_w3, mb_w3, mb_w2 ) );
  resolutions.back().SetName("res_W3(Mb,W2)");
  resolutions.push_back( Resolution3S( mf_w3, mb_w3, mf_mb ) );
  resolutions.back().SetName("res_W3(Mf,Mb)");
  // F(R1,R2) --- random-sub method
  resolutions.push_back( Ollitrault( r1_r2, 1 ) );
  resolutions.back().SetName("res_F(R1,R2)");

  auto file_out = TFile::Open("fuck.root", "recreate");
  file_out->cd();
  for (auto corr : resolutions){
    corr.Write(file_out);
  }
  file_out->Close();
  return 0;
}