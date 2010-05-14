/** 
 * @file llversionviewer.h
 * @brief
 *
 * $LicenseInfo:firstyear=2002&license=viewergpl$
 * 
 * Copyright (c) 2002-2009, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlifegrid.net/programs/open_source/licensing/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#ifndef LL_LLVERSIONVIEWER_H
#define LL_LLVERSIONVIEWER_H

// Version info should be accessed using newview\viewerversion.h -- MC

const S32 LL_VERSION_MAJOR = 1;
const S32 LL_VERSION_MINOR = 23;
const S32 LL_VERSION_PATCH = 5;
const S32 LL_VERSION_BUILD = 136262;

const char * const LL_VIEWER_NAME = "Second Life";

// These aren't used anymore. 
// The channel is ViewerChannelName in settings.xml
// The Imprudence version is set in app_settings\viewerversion.xml -- MC

/*const char * const LL_CHANNEL = "Imprudence";

const char * const IMP_VIEWER_NAME = "Imprudence";

const S32 IMP_VERSION_MAJOR = 1;
const S32 IMP_VERSION_MINOR = 3;
const S32 IMP_VERSION_PATCH = 0;
const char * const IMP_VERSION_TEST = "beta 4";*/

#endif
