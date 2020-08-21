//
// Created by mikhail on 8/6/20.
//

#ifndef FLOWCOMPUTATION_SRC_CORRELATION_BUILDER_H_
#define FLOWCOMPUTATION_SRC_CORRELATION_BUILDER_H_

#include <Axis.hpp>
#include <TFile.h>

#include "correlation.h"

namespace Computation {

struct CorrelationConfig{
  std::string name;
  std::vector<std::string> components_names;
  std::vector<std::string> proj_axis;
  std::vector<Qn::AxisD> rebin_axis;
};

class CorrelationBuilder {
public:
  static void OpenFile(const std::string& name){
    Instance()->file_=TFile::Open(name.c_str(), "READ");
    if( !Instance()->file_ ){
      throw std::runtime_error("CorrelationBuilder::OpenFile(): no such a file ");
    }
  }
  [[nodiscard]] static Correlation Build( const std::string&, const std::vector<std::string>&);
  [[nodiscard]] static Correlation Build( const CorrelationConfig& );

private:
  static CorrelationBuilder* instance_;
  CorrelationBuilder() = default;
  ~CorrelationBuilder() = default;
  static CorrelationBuilder* Instance(){
    if(!instance_){
      instance_ = new CorrelationBuilder;
    }
    return instance_;
  }
  TFile *file_{nullptr};

};
} // namespace Computation
#endif // FLOWCOMPUTATION_SRC_CORRELATION_BUILDER_H_
