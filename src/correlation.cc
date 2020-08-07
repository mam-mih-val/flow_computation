//
// Created by mikhail on 7/17/20.
//

#include "correlation.h"

namespace Computation {

Correlation Resolution3S(const Correlation &first, const Correlation &second,
                         const Correlation &third) {
  Correlation result;
  for (size_t i = 0; i < first.components_names_.size(); ++i) {
    auto arg1 = first.components_.at(i);
    auto arg2 = second.components_.at(i);
    auto arg3 = third.components_.at(i);
    auto res = Sqrt(arg1 * arg2 / arg3);
    result.components_.emplace_back(res);
  }
  result.components_names_ = first.components_names_;
  return result;
}
Correlation Sqrt(const Correlation &argument) {
  Correlation result;
  for (size_t i = 0; i < argument.components_names_.size(); ++i) {
    auto arg1 = argument.components_.at(i);
    auto res = Sqrt(arg1);
    result.components_.emplace_back(res);
  }
  result.components_names_ = argument.components_names_;
  return result;
}
Correlation Ollitrault(const Correlation &argument, int order) {
  Correlation result;
  for (size_t i = 0; i < argument.components_names_.size(); ++i) {
    auto arg1 = argument.components_.at(i);
    auto res = OllitraultExtrapolation(arg1, order);
    result.components_.emplace_back(res);
  }
  result.components_names_ = argument.components_names_;
  return result;
}
Correlation operator/(const Correlation &num, const Correlation &den) {
  Correlation result;
  for (size_t i = 0; i < num.components_.size(); ++i) {
    auto arg1 = num.components_.at(i);
    auto arg2 = den.components_.at(i);
    auto res = arg1 / arg2;
    result.components_.emplace_back(res);
  }
  result.components_names_ = num.components_names_;
  return result;
}
Correlation operator*(const Correlation &first,const Correlation &second) {
  Correlation result;
  for (size_t i = 0; i < first.components_.size(); ++i) {
    auto arg1 = first.components_.at(i);
    auto arg2 = second.components_.at(i);
    auto res = arg1 * arg2;
    result.components_.emplace_back(res);
  }
  result.components_names_ = first.components_names_;
  return result;
}
Correlation operator*(const Correlation &corr, const double &num) {
  Correlation result;
  for (auto &container : corr.components_) {
    const auto& arg1 = container;
    auto res = arg1 * num;
    result.components_.emplace_back(res);
  }
  result.components_names_ = corr.components_names_;
  return result;
}
} // namespace Computation