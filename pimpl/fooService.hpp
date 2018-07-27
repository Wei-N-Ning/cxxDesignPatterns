//
// Created by Wei on 13/04/2016.
//

#ifndef CPPRECIPES_FOOSERVICE_HPP
#define CPPRECIPES_FOOSERVICE_HPP

#include <memory>
#include <string>

class FooService {

public:
  FooService();
  ~FooService();
  std::string stripSuffix(const std::string &text);

private:
  class FooServiceImpl;
  std::unique_ptr<FooService::FooServiceImpl> pImpl;
};


#endif //CPPRECIPES_FOOSERVICE_HPP
