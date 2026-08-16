// PathUtils.h
#pragma once
#include <string>
#include <filesystem>
#include <Windows.h>

namespace PathUtils {
    inline std::filesystem::path GetExecutableDir() {
        wchar_t buffer[MAX_PATH];
        GetModuleFileNameW(nullptr, buffer, MAX_PATH);
        return std::filesystem::path(buffer).parent_path();
    }

    // Resolves a path relative to the exe's directory, e.g. "Resources/res/JNWhite.png"
    inline std::string ResolveAssetPath(const std::string& relativePath) {
        static const std::filesystem::path base = GetExecutableDir();
        return (base / relativePath).string();
    }
}
