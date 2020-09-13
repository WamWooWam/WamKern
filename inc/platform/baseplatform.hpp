#pragma once

namespace WamKern::Platform {
class BasePlatform {
   public:
    BasePlatform() = default;
    BasePlatform(const BasePlatform&) = delete;
};
}  // namespace WamKern::Platform