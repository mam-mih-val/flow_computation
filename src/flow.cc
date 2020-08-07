//
// Created by mikhail on 8/6/20.
//

#include "correlation_builder.h"

int main(){
  Computation::CorrelationBuilder builder;
  builder.OpenFile("/home/mikhail/Correlations/ag123_fw3_rs.root");
  auto un_qn = builder.Build("(u,F)","u_RESCALED_F_RECENTERED", {"u1x_Q1x_EP", "u1y_Q1y_EP"});
  auto r1_r2 = builder.Build("(R1,R2)","R1_RECENTERED_R2_RECENTERED", {"Q1x_Q1x_EP", "Q1y_Q1y_EP"});
  auto w1_w2 = builder.Build("(W1,W2)","W1_RECENTERED_W2_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  auto w1_w3 = builder.Build("(W1,W3)","W1_RECENTERED_W3_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});
  auto w2_w3 = builder.Build("(W2,W3)","W2_RECENTERED_W3_RECENTERED", {"Q1x_Q1x", "Q1y_Q1y"});

  un_qn.Projection({"Centrality"});
  auto resolution = Ollitrault(r1_r2, 1);
  resolution.SetName("res_RND");
  auto res3 = Resolution3S( w1_w2, w1_w3, w2_w3 );
  res3.SetName("res_W1(W2,W3)");
  auto flow = un_qn/resolution;
  flow.SetName("flow_RND");

  auto file_out = TFile::Open("fuck.root", "recreate");
  file_out->cd();
  resolution.Write(file_out);
  flow.Write(file_out);
  res3.Write(file_out);
  file_out->Close();
  return 0;
}