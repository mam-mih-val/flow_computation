//
// Created by mikhail on 8/6/20.
//

#include "correlation_builder.h"
namespace Computation {
CorrelationBuilder* CorrelationBuilder::instance_= nullptr;

Correlation CorrelationBuilder::Build(const std::string &name,
                  const std::vector<std::string> &components_names) {
  if (!Instance()->file_) {
    throw std::runtime_error(
        "CorrelationBuilder::Build(): file is not specified");
  }
  Qn::DataContainerStats *container;
  std::vector<Qn::DataContainerStats> components;
  for (const auto &component : components_names) {
    std::string path = name + "_" + component;
    Instance()->file_->GetObject(path.data(), container);
    if (!container) {
      throw std::runtime_error(
          "CorrelationBuilder::Build(): no such container " + path);
    }
    components.push_back(*container);
  }
  Correlation result;
  result.SetName(name);
  result.SetComponents(components);
  result.SetComponentsNames(components_names);
  return result;
}
Correlation CorrelationBuilder::Build(const CorrelationConfig& config) {
  if (!Instance()->file_) {
    throw std::runtime_error(
        "CorrelationBuilder::Build(): file is not specified");
  }
  Qn::DataContainerStats *container;
  std::vector<Qn::DataContainerStats> components;
  for (const auto &component : config.components_names) {
    std::string path = config.name + "_" + component;
    Instance()->file_->GetObject(path.data(), container);
    if (!container) {
      throw std::runtime_error(
          "CorrelationBuilder::Build(): no such container " + path);
    }
    components.push_back(*container);
  }
  Correlation result;
  result.SetName(config.name);
  result.SetComponents(components);
  result.SetComponentsNames(config.components_names);
  for( const auto& axis : config.rebin_axis  )
    result.Rebin(axis);
  if( !std::empty( config.proj_axis ) )
    result.Projection(config.proj_axis);
  return result;
}
} // namespace Computation