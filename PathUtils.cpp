// PathUtils.cpp
#include "PathUtils.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <filesystem>

namespace PathUtils {
    static std::filesystem::path GetExecutableDir() {
        wchar_t buffer[MAX_PATH];
        GetModuleFileNameW(nullptr, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path();
    }

    std::string ResolveAssetPath(const std::string& relativePath) {
        static const std::filesystem::path base = GetExecutableDir();
        return (base / relativePath).string();
    }
}