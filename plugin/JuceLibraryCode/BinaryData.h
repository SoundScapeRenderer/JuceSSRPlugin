/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_126200976_INCLUDED
#define BINARYDATA_H_126200976_INCLUDED

namespace BinaryData
{
    extern const char*   listener_png;
    const int            listener_pngSize = 8084;

    extern const char*   listener_shadow_png;
    const int            listener_shadow_pngSize = 4428;

    extern const char*   source_shadow_png;
    const int            source_shadow_pngSize = 2135;

    extern const char*   ssr_logo_png;
    const int            ssr_logo_pngSize = 2131;

    extern const char*   ssr_logo_large_png;
    const int            ssr_logo_large_pngSize = 9075;

    extern const char*   hrirs_fabian_wav;
    const int            hrirs_fabian_wavSize = 737324;

    extern const char*   DejaVuSansMono_ttf;
    const int            DejaVuSansMono_ttfSize = 335068;

    extern const char*   lock_icon_png;
    const int            lock_icon_pngSize = 374;

    extern const char*   mute_icon_png;
    const int            mute_icon_pngSize = 952;

    extern const char*   plus_icon_png;
    const int            plus_icon_pngSize = 91;

    extern const char*   settings_icon_png;
    const int            settings_icon_pngSize = 595;

    extern const char*   soxHrir48000_wav;
    const int            soxHrir48000_wavSize = 802160;

    extern const char*   soxHrir96000_wav;
    const int            soxHrir96000_wavSize = 1605680;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 13;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
