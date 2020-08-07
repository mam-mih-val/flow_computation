//
// Created by mikhail on 8/6/20.
//

#ifndef FLOWCOMPUTATION_SRC_CORRELATION_BUILDER_H_
#define FLOWCOMPUTATION_SRC_CORRELATION_BUILDER_H_

#include <TFile.h>

#include "correlation.h"

namespace Computation {
class CorrelationBuilder {
public:
  CorrelationBuilder() = default;
  ~CorrelationBuilder() = default;
  void OpenFile(const std::string& name){
    file_=TFile::Open(name.c_str(), "READ");
    if( !file_ ){
      throw std::runtime_error("CorrelationBuilder::OpenFile(): no such a file ");
    }
  }
  [[nodiscard]] Correlation Build( const std::string&name, const std::string&prefix,
                    const std::vector<std::string>& components_names){
    if( !file_ ){
      throw std::runtime_error("CorrelationBuilder::Build(): file is not specified");
    }
    Qn::DataContainerStats* container;
    std::vector<Qn::DataContainerStats> components;
    for (const auto& component: components_names){
      std::string path = prefix +"_"+component;
      file_->GetObject(path.data(), container);
      if( !container ){
        throw std::runtime_error("CorrelationBuilder::Build(): no such container "+path);
      }
      components.push_back( *container );
    }
    Correlation result;
    result.SetName(name);
    result.SetComponents(components);
    result.SetComponentsNames(components_names);
    return result;
  }
private:
  TFile *file_{nullptr};
};
} // namespace Computation
#endif // FLOWCOMPUTATION_SRC_CORRELATION_BUILDER_H_
