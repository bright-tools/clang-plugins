#if !defined CONFIG_BASE_HPP
#define CONFIG_BASE_HPP

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Path.h>

namespace brighttools {

template<class T> llvm::Optional<T> findConfigInDirectoryHeirachy(llvm::StringRef fileName) {
    llvm::Optional<T> config = llvm::None;

    llvm::SmallString<128> cwd;
    llvm::sys::fs::current_path(cwd);
    llvm::sys::fs::make_absolute(cwd);

    llvm::StringRef Path = cwd;
    for (llvm::StringRef CurrentPath = Path; !CurrentPath.empty() && !config.hasValue();
        CurrentPath = llvm::sys::path::parent_path(CurrentPath)) {
        llvm::SmallString<128> configFile(CurrentPath);
        llvm::sys::path::append(configFile, fileName);
        config = T::readConfig(configFile);
    }
    return config;
}

} // namespace brighttools

#endif // CONFIG_BASE_HPP