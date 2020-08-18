//
// Created by mikhail on 7/17/20.
//

#ifndef FLOW_DRAWING_TOOLS_SRC_CORRELATION_H_
#define FLOW_DRAWING_TOOLS_SRC_CORRELATION_H_

#include <Axis.hpp>
#include <DataContainer.hpp>
#include <string>
#include <utility>
#include <vector>

namespace Computation {

class Correlation {
public:
  Correlation() = default;
  explicit Correlation(std::vector<Qn::DataContainerStats> components)
      : components_(std::move(components)) {}
  virtual ~Correlation() = default;
  [[nodiscard]] const Qn::DataContainerStats &
  GetComponent(unsigned long component) {
    return components_.at(component);
  }
  [[nodiscard]] const std::string &GetComponentName(unsigned long component) {
    return components_names_.at(component);
  }
  [[nodiscard]] const std::vector<std::string> &GetComponentNames() {
    return components_names_;
  }
  [[nodiscard]] unsigned long GetNcomponents() {
    return std::size(components_names_);
  }
  void SetName(const std::string &name) { name_ = name; }
  void SetComponentsNames(const std::vector<std::string> &components_names) {
    components_names_ = components_names;
  }
  void SetComponents(const std::vector<Qn::DataContainerStats> &components) {
    components_ = components;
  }
  void Rebin(const Qn::AxisD &axis) {
    for (auto &component : components_) {
      auto result = component;
      result = result.Rebin(axis);
      component = result;
    }
  }
  void Projection(const std::vector<std::string> &axis_names) {
    for (auto &component : components_) {
      auto result = component;
      result = result.Projection(axis_names);
      component = result;
    }
  }
  void Merge();
  void Write(TFile *file) {
    if (std::empty(name_)) {
      std::cout << "Correlation::Write(): Name is not specified" << std::endl;
    }
    if( is_merged_ ){
      merged_.Write(name_.c_str());
      return;
    }
    if (std::empty(components_names_)) {
      std::cerr << "Correlation::Write(): Component names are not specified"
                << std::endl;
    }
    try {
      for (size_t i = 0; i < std::size(components_names_); ++i) {
        std::string name = name_ + "_" + components_names_.at(i);
        components_.at(i).Write(name.c_str());
      }
    } catch (const std::exception &e) {
      std::cerr << "Correlation::Write(): Components names' size and "
                   "components vector size' are not equal"
                << std::endl;
      std::cerr << e.what() << std::endl;
      throw;
    }
  }
  // operations on Correlations
  friend Correlation operator/(const Correlation &, const Correlation &);
  friend Correlation operator*(const Correlation &, const Correlation &);
  friend Correlation operator*(const Correlation &, const double &);
  friend Correlation Resolution3S(const Correlation &, const Correlation &,
               const Correlation &); // R = sqrt <Qa,Qb>*<Qa,Qc>/<Qb,Qc>
  friend Correlation Ollitrault(const Correlation &,
                                int); // R = Ollitrault Extrapolation of <Qa,Qb>
  friend Correlation Sqrt(const Correlation &);

private:
  std::string name_;
  std::vector<std::string> components_names_;
  std::vector<Qn::DataContainerStats> components_;
  Qn::DataContainerStats merged_;
  bool is_merged_{false};
};

} // namespace Computation
#endif // FLOW_DRAWING_TOOLS_SRC_CORRELATION_H_
