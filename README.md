# clang-plugins

[![Build Status](https://travis-ci.com/bright-tools/clang-plugins.svg?branch=main)](https://travis-ci.com/bright-tools/clang-plugins)

Custom Plugins for clang

| Plugin | Purpose |
|--------|---------|
| include-path-checker-plugin | Check for (and raise an error upon) instances of paths being used in include directives (e.g. `#include "../something/file.h"` ) |

## Building

```
git clone https://github.com/bright-tools/clang-plugins.git
cd clang-plugins
mkdir build && cd build
cmake -G "Unix Makefiles"  ..
make
```

## Testing:

```
make test
```

To manually execute a plug-in, a command such as the following can be used:
```
clang-10 -c -fplugin=lib/libinclude-pack-checker-plugin.so files.c -Xclang -plugin-arg-include-path-checker -Xclang -disallow-parent-dir-include-references
```

## Packaging (.deb)

```
make
cpack
```