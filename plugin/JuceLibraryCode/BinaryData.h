/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_126200976_INCLUDED
#define BINARYDATA_H_126200976_INCLUDED

namespace BinaryData
{
    extern const char*   DejaVuSansMono_ttf;
    const int            DejaVuSansMono_ttfSize = 335068;

    extern const char*   lock_icon_png;
    const int            lock_icon_pngSize = 480;

    extern const char*   mute_icon_png;
    const int            mute_icon_pngSize = 602;

    extern const char*   default_hrirs_wav;
    const int            default_hrirs_wavSize = 737324;

    extern const char*   listener_png;
    const int            listener_pngSize = 8084;

    extern const char*   listener_background_png;
    const int            listener_background_pngSize = 7444;

    extern const char*   listener_shadow_png;
    const int            listener_shadow_pngSize = 4428;

    extern const char*   pause_button_png;
    const int            pause_button_pngSize = 367;

    extern const char*   pause_button_pressed_png;
    const int            pause_button_pressed_pngSize = 238;

    extern const char*   play_button_png;
    const int            play_button_pngSize = 390;

    extern const char*   play_button_pressed_png;
    const int            play_button_pressed_pngSize = 249;

    extern const char*   processing_button_png;
    const int            processing_button_pngSize = 323;

    extern const char*   processing_button_pressed_png;
    const int            processing_button_pressed_pngSize = 182;

    extern const char*   scene_menu_item_png;
    const int            scene_menu_item_pngSize = 202;

    extern const char*   scene_menu_item_selected_png;
    const int            scene_menu_item_selected_pngSize = 323;

    extern const char*   skip_back_button_png;
    const int            skip_back_button_pngSize = 391;

    extern const char*   skip_back_button_pressed_png;
    const int            skip_back_button_pressed_pngSize = 258;

    extern const char*   source_shadow_png;
    const int            source_shadow_pngSize = 2135;

    extern const char*   ssr_logo_png;
    const int            ssr_logo_pngSize = 2131;

    extern const char*   ssr_logo_large_png;
    const int            ssr_logo_large_pngSize = 9075;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 20;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
