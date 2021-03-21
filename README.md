# clang-plugins

[![Build Status](https://travis-ci.com/bright-tools/clang-plugins.svg?branch=main)](https://travis-ci.com/bright-tools/clang-plugins)

Custom Plugins for [clang](https://clang.llvm.org/)

| Plugin | Purpose |
|--------|---------|
| include-path-checker-plugin | Check for (and raise an error upon) instances of paths being used in include directives (e.g. `#include "../something/file.h"` ) |
| ban-pp-tokens-plugin | Check for (and raise an error upon) banned tokens being found during source lexing.  This means that an error will be raised for banned tokens even if they do not actually end up being used. |
| ban-token-update-plugin | Check for (and rais an error upon) banned tokens being utilised.  In constast to _ban-pp-tokens-plugin_, banned tokens may exist within the source files so long as they are not referenced. |

## Building

```bash
git clone https://github.com/bright-tools/clang-plugins.git
cd clang-plugins
mkdir build && cd build
cmake -G "Unix Makefiles"  ..
make
```

## Testing:

```bash
make test
```

To manually execute a plug-in, a command such as the following can be used:
```bash
clang-11 -c -fplugin=lib/libinclude-path-checker-plugin.so files.c -Xclang -plugin-arg-include-path-checker
```

```bash
clang-11 -fsyntax-only -fplugin=lib/libban-pp-token-usage-plugin.so files.c -Xclang -analyze -Xclang -analyzer-checker=brighttools.ban-token-usage
```

## Packaging (.deb)

```bash
make
cpack
```
