#include "uniform.h"

archt::Uniform::Uniform() {}

archt::Uniform::Uniform(const std::string& name, int size) : name(name), size(size) {}

archt::Uniform::~Uniform() {}




archt::UniformFloat1::UniformFloat1() {}

archt::UniformFloat1::UniformFloat1(const std::string& name, float uniform) {}

archt::UniformFloat1::~UniformFloat1() {}






archt::UniformFloat2::UniformFloat2() {}

archt::UniformFloat2::UniformFloat2(const std::string& name, const glm::vec2& uniform) {}

archt::UniformFloat2::~UniformFloat2() {}





archt::UniformFloat3::UniformFloat3() {}

archt::UniformFloat3::UniformFloat3(const std::string& name, const glm::vec3& uniform) {}

archt::UniformFloat3::~UniformFloat3() {}








archt::UniformFloat4::UniformFloat4() {}

archt::UniformFloat4::UniformFloat4(const std::string& name, const glm::vec4& uniform) {}

archt::UniformFloat4::~UniformFloat4() {}
