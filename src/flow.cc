//
// Created by mikhail on 8/6/20.
//

#include "correlation_builder.h"
#include "functions.h"

int main(){
  Computation::CorrelationBuilder::OpenFile("/home/mikhail/Correlations/au123_fw3_rs_rescale.root");

  Computation::CorrelationConfig u_w1{"u_RESCALED_W1_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {{"y_cm", 1, -0.25, -0.15}}};
  Computation::CorrelationConfig u_w2{"u_RESCALED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {{"y_cm", 1, -0.25, -0.15}}};
  Computation::CorrelationConfig u_w3{"u_RESCALED_W3_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {{"y_cm", 1, -0.25, -0.15}}};
  Computation::CorrelationConfig u_f{"u_RESCALED_F_RECENTERED", {"u1x_Q1x_EP", "u1y_Q1y_EP"},
                                       {"mdc_vtx_tracks_pT"}, {
                                         {"Centrality", 1, 20.0, 30.0},
                                         {"y_cm", 1, -0.25, -0.15}
                                     }};


  Computation::CorrelationConfig r1_r2{"R1_RECENTERED_R2_RECENTERED", {"Q1x_Q1x_EP", "Q1y_Q1y_EP"},
                                       {}, {{"Centrality", 1, 20.0, 30.0}}};
  Computation::CorrelationConfig w1_w2{"W1_RECENTERED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {}, {}};
  Computation::CorrelationConfig w1_w3{"W1_RECENTERED_W3_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {}, {}};
  Computation::CorrelationConfig w2_w3{"W2_RECENTERED_W3_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {}, {}};
  Computation::CorrelationConfig mf_w1{"M_RESCALED_W1_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {{"y_cm", 2, 0.35, 0.55}}};
  Computation::CorrelationConfig mf_w2{"M_RESCALED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {{"y_cm", 2, 0.35, 0.55}}};
  Computation::CorrelationConfig mf_w3{"M_RESCALED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {{"y_cm", 2, 0.35, 0.55}}};
  Computation::CorrelationConfig mb_w1{"M_RESCALED_W1_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {{"y_cm", 2, -0.55, -0.35}}};
  Computation::CorrelationConfig mb_w2{"M_RESCALED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {{"y_cm", 2, -0.55, -0.35}}};
  Computation::CorrelationConfig mb_w3{"M_RESCALED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {{"y_cm", 2, -0.55, -0.35}}};
  Computation::CorrelationConfig mf_mb{"M_RESCALED_M_RESCALED", {"Q1x_Q1x", "Q1y_Q1y"},
                                       {"Centrality"}, {
                                           {"M_RESCALED_0_y_cm", 2, 0.35, 0.55},
                                           {"M_RESCALED_1_y_cm", 2, -0.55, -0.35}}};

  std::vector< std::pair<Computation::Correlation, Computation::Correlation> > results;

  results.emplace_back( Computation::ComputeFlowRS("RND", u_f,r1_r2) );

  results.emplace_back( Computation::ComputeFlow3S("W1(W2,W3)", u_w1,{w1_w2, w1_w3, w2_w3}) );
  results.emplace_back( Computation::ComputeFlow3S("W1(Mf,W2)", u_w1,{mf_w1, w1_w2, mf_w2}) );
  results.emplace_back( Computation::ComputeFlow3S("W1(Mf,W3)", u_w1,{mf_w1, w1_w3, mf_w3}) );
  results.emplace_back( Computation::ComputeFlow3S("W1(Mb,W2)", u_w1,{mb_w1, w1_w2, mb_w2}) );
  results.emplace_back( Computation::ComputeFlow3S("W1(Mb,W3)", u_w1,{mb_w1, w1_w3, mb_w3}) );
  results.emplace_back( Computation::ComputeFlow3S("W1(Mf,Mb)", u_w1,{mf_w1, mb_w1, mf_mb}) );

  results.emplace_back( Computation::ComputeFlow3S("W2(W1,W3)", u_w2,{w1_w2, w2_w3, w1_w3}) );
  results.emplace_back( Computation::ComputeFlow3S("W2(Mf,W1)", u_w2,{mf_w2, w1_w2, mf_w1}) );
  results.emplace_back( Computation::ComputeFlow3S("W2(Mf,W3)", u_w2,{mf_w2, w2_w3, mf_w3}) );
  results.emplace_back( Computation::ComputeFlow3S("W2(Mb,W1)", u_w2,{mb_w2, w1_w2, mb_w1}) );
  results.emplace_back( Computation::ComputeFlow3S("W2(Mb,W3)", u_w2,{mb_w2, w2_w3, mb_w3}) );
  results.emplace_back( Computation::ComputeFlow3S("W2(Mf,Mb)", u_w2,{mf_w2, mb_w2, mf_mb}) );

  results.emplace_back( Computation::ComputeFlow3S("W3(W1,W2)", u_w3,{w1_w3, w2_w3, w1_w2}) );
  results.emplace_back( Computation::ComputeFlow3S("W3(Mf,W1)", u_w3,{mf_w3, w1_w3, mf_w1}) );
  results.emplace_back( Computation::ComputeFlow3S("W3(Mf,W2)", u_w3,{mf_w3, w2_w3, mf_w2}) );
  results.emplace_back( Computation::ComputeFlow3S("W3(Mb,W1)", u_w3,{mb_w3, w1_w3, mb_w1}) );
  results.emplace_back( Computation::ComputeFlow3S("W3(Mb,W2)", u_w3,{mb_w3, w2_w3, mb_w2}) );
  results.emplace_back( Computation::ComputeFlow3S("W3(Mf,Mb)", u_w3,{mf_w3, mb_w3, mf_mb}) );

  auto file_out = TFile::Open("fuck.root", "recreate");
  file_out->cd();
  for( const auto& result : results){
    auto [flow, res] = result;
    flow.Merge();
    flow.Write();
    res.Merge();
    res.Write();
  }
  file_out->Close();
  return 0;
}