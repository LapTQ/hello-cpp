#ifndef SQUARE_H     // can be any name you want, but by convention is set to the full filename of the header file
#define SQUARE_H

int getSquareSides()
{
    return 4;
}

#endif

/*
- All of your header files should have header guards on them.

- In large programs, it’s possible to have two separate header files (from different directories) that have the same filename 
  (e.g. directoryA\config.h and directoryB\config.h). If only the filename is used for the include guard (e.g. CONFIG_H),
  any file that includes (directly or indirectly) both config.h will not receive the contents of the second file. 
  This will probably cause a compilation error.
- many developers recommend using a more complex/unique name in your header guards. Some good suggestions are a naming 
  convention of PROJECT_PATH_FILE_H, FILE_LARGE-RANDOM-NUMBER_H, or FILE_CREATION-DATE_H.
*/


/* #pragma once

- Modern compilers support a simpler, alternate form of header guards using the #pragma preprocessor directive:
#pragma once
// your code here

- However, there is one known case where `#pragma once` will typically fail. 
  If a header file is copied somewhere on the file system, and if somehow both copies of the header get included, 
  header guards will successfully de-dupe the identical headers, 
  but #pragma once won’t (because the compiler won’t realize they are actually identical content).
- For most projects, `#pragma once` works fine, and many developers now prefer it because it is easier and less error-prone.
- WARNING: #pragma directive was designed for "compiler implementers" to use. It means those pragmas's meaning is completely implementation-specific.
  With the exception of #pragma once, do not expect a pragma that works on one compiler to be supported by another.
*/