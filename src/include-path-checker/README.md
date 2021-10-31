# include-path-checker plugin

## Description

This plugin verifies the files being include by `#include` directives against configurable rules.

Two rules are provided to detect where include directives contain a directory element in addition to a file-name.  Using these rules may help to enforce "good hygene" with regard to setting appropriate include paths within the build system and not relying on the `#include` to have knowledge of the directory structure.

The plugin also allows include files to be "banned" based on their filename.  This is intended to prevent undesired dependencies from being introduced.  A combination of black and white listing provides flexibility in how this is applied.

## Configuration

The plugin searches the directory heriarchy upward from the current working directory for a file named `.include-path-checker.yml`.  The first matching file is read & the search ends.

The file may contain the following keys:

| Key | Description | Default |
|-----|-------------|---------|
| DisallowParentDirIncludeReferences | If set to `true`, an error will be raised if files are included via parent directory (ie. `..`) references.  e.g. `#include "..\some_file.h"` | false |
| DisallowChildDirIncludeReferences | If set to `true`, an error will be raised if files are included via child director references.  e.g. `#include "some_dir\some_file.h` | false |
| BannedIncludes | An error will be raised if any of the files in this list are `#include`d.  An optional `Reason` can be specified and `WhiteListRegex` and `BlackListRegex` fields can be used to control which files checks are applied to.  In addition, if the `EnableFilenameRegex` field is set to `true` then `Filename` will be treated as a regular expression when matching included files. | |

### Example Configuration

```yml
DisallowParentDirIncludeReferences: false
DisallowChildDirIncludeReferences: true
BannedIncludes:
  - Filename: stdio.h
    Reason: Don't use stdio.h directly, use one of the wrappers
    WhiteListRegex: io_wrappers/.*\.c
```