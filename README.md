# clang-plugins

Custom Plugins for clang

| Plugin | Purpose |
|--------|---------|
| include-path-checker-plugin | Check for (and raise an error upon) instances of paths being used in include directives (e.g. `#include "../something/file.h"` ) |

# Building

```
git clone https://github.com/bright-tools/clang-plugins.git
cd clang-plugins
mkdir build && cd build
cmake -G "Unix Makefiles"  ..
make
```

Testing:

```
clang-10 -fplugin=lib/libinclude-pack-checker-plugin.so ../../plugin/clang-plugins-demo/test/files.c
```