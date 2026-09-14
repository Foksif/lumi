#pragma once

namespace lumi {

class Module {
public:
  virtual ~Module();

  virtual void initialize() = 0;
  virtual void shutdown() = 0;
};

} // namespace lumi
