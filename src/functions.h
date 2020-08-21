//
// Created by mikhail on 8/18/20.
//

#ifndef FLOWCOMPUTATION_SRC_FUNCTIONS_H_
#define FLOWCOMPUTATION_SRC_FUNCTIONS_H_

#include "correlation.h"
#include "correlation_builder.h"

namespace Computation {
std::pair<Correlation, Correlation> ComputeFlow3S(const std::string& name,
                                                  const CorrelationConfig& un_qn_config,
                                                  const std::array<CorrelationConfig, 3>& qn_qn_configs){
  auto un_qn = CorrelationBuilder::Build(un_qn_config);
  std::vector<Correlation> qn_qns;
  qn_qns.reserve(qn_qn_configs.size());
  for( const auto& config : qn_qn_configs )
    qn_qns.emplace_back( CorrelationBuilder::Build(config) );
  auto resolution = Resolution3S( qn_qns.at(0), qn_qns.at(1), qn_qns.at(2) );
  resolution.SetName("res_"+name);
  auto flow = un_qn/resolution;
  flow.SetName("flow_"+name);
  return std::make_pair(flow, resolution);
}

std::pair<Correlation, Correlation> ComputeFlowRS(const std::string& name,
                                                  const CorrelationConfig& un_qn_config,
                                                  const CorrelationConfig& qn_qn_config){
  auto un_qn = CorrelationBuilder::Build(un_qn_config);
  auto qn_qn = CorrelationBuilder::Build(qn_qn_config);
  auto resolution = Ollitrault( qn_qn, 1 );
  resolution.SetName("res_"+name);
  auto flow = un_qn/resolution;
  flow.SetName("flow_"+name);
  return std::make_pair(flow, resolution);
}

}
#endif // FLOWCOMPUTATION_SRC_FUNCTIONS_H_
