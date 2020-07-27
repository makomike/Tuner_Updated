/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   arrleft_png;
    const int            arrleft_pngSize = 486;

    extern const char*   arrleft_green_png;
    const int            arrleft_green_pngSize = 415;

    extern const char*   arrleft_orange_png;
    const int            arrleft_orange_pngSize = 463;

    extern const char*   arrright_png;
    const int            arrright_pngSize = 941;

    extern const char*   arrright_green_png;
    const int            arrright_green_pngSize = 875;

    extern const char*   arrright_orange_png;
    const int            arrright_orange_pngSize = 956;

    extern const char*   flat_png;
    const int            flat_pngSize = 591;

    extern const char*   power_svg;
    const int            power_svgSize = 320;

    extern const char*   sharp_png;
    const int            sharp_pngSize = 535;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 9;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
