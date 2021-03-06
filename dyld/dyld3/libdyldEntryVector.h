/*
 * Copyright (c) 2017 Apple Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */



#ifndef __DYLD_ENTRY_VECTOR_H__
#define __DYLD_ENTRY_VECTOR_H__

#include <mach-o/loader.h>

#include "LaunchCache.h"
#include "Loading.h"

struct dyld_all_image_infos;

namespace dyld3 {

struct LibDyldEntryVector
{
    enum { kCurrentVectorVersion = 4 };

    uint32_t    vectorVersion;              // should be kCurrentVectorVersion
    uint32_t    binaryFormatVersion;        // should be launch_cache::binary_format::kFormatVersion
    void        (*setVars)(const mach_header* mainMH, int argc, const char* argv[], const char* envp[], const char* apple[]);
    void        (*setHaltFunction)(void (*func)(const char* message) __attribute__((noreturn)) );
    void        (*setOldAllImageInfo)(dyld_all_image_infos*);
    void        (*setInitialImageList)(const launch_cache::BinaryClosureData* closure,
                                        const void* dyldCacheLoadAddress, const char* dyldCachePath,
                                        const dyld3::launch_cache::DynArray<loader::ImageInfo>& initialImages,
                                        const mach_header* libSystemMH, const launch_cache::BinaryImageData* libSystemImage);
    void        (*runInitialzersBottomUp)(const mach_header* topImageLoadAddress);
    void        (*startFunc)();
    // added in version 3
    void        (*setChildForkFunction)(void (*func)());
    // added in version 4
    void        (*setLogFunction)(void (*logFunction)(const char* format, va_list list));
};

extern const LibDyldEntryVector entryVectorForDyld;

} // namespace dyld3


#endif // __DYLD_ENTRY_VECTOR_H__




