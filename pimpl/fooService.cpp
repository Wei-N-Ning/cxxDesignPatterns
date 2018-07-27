//
// Created by Wei on 13/04/2016.
//

#include "fooService.hpp"


class FooService::FooServiceImpl {
public:
  std::string stripSuffix(const std::string &text);
};

std::string FooService::FooServiceImpl::stripSuffix(const std::string &text) {
  return std::string{"asd"};
}


FooService::FooService()
  : pImpl(new FooService::FooServiceImpl()){
}

FooService::~FooService() = default;


std::string FooService::stripSuffix(const std::string &text) {
  return pImpl->stripSuffix(text);
}