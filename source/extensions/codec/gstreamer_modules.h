//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
// gstreamer_modules.cpp
//

#pragma once

#include <gst/gst.h>

// The following list has to be maintained same as the one in $(SourceRoot)/ci/android/gstreamer/Android.mk
// Please search for base_gstreamer.h or base_gstreamer.cpp

#if defined(ANDROID) || defined(_ANDROID_)
extern "C"
{
#if defined(TARGET_OS_IPHONE)
#define GST_G_IO_MODULE_DECLARE(name) \
    extern void G_PASTE(g_io_module_, G_PASTE(name, _load_static)) (void)

#define GST_G_IO_MODULE_LOAD(name) \
    G_PASTE(g_io_module_, G_PASTE(name, _load_static)) ()
#endif

    GST_PLUGIN_STATIC_DECLARE(coreelements);
    GST_PLUGIN_STATIC_DECLARE(app);
    GST_PLUGIN_STATIC_DECLARE(audioconvert);
    GST_PLUGIN_STATIC_DECLARE(mpg123);
    GST_PLUGIN_STATIC_DECLARE(audioresample);
    GST_PLUGIN_STATIC_DECLARE(audioparsers);
    GST_PLUGIN_STATIC_DECLARE(ogg);
    GST_PLUGIN_STATIC_DECLARE(opusparse);
    GST_PLUGIN_STATIC_DECLARE(opus);
}
#endif

namespace Microsoft {
namespace CognitiveServices {
namespace Speech {
namespace Impl {

__attribute__((visibility ("default"))) void spx_gst_init();

} } } } // Microsoft::CognitiveServices::Speech::Impl
