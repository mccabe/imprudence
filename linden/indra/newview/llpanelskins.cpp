/** 
 * @file llpanelskins.cpp
 * @brief General preferences panel in preferences floater
 *
 * $LicenseInfo:firstyear=2001&license=viewergpl$
 * 
 * Copyright (c) 2001-2009, Linden Research, Inc.
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

#include "llviewerprecompiledheaders.h"

#include "llpanelskins.h"

// linden library includes
#include "llradiogroup.h"
#include "llbutton.h"
#include "llscrolllistctrl.h"
#include "lliconctrl.h"
#include "lluictrlfactory.h"

// project includes
#include "llviewercontrol.h"
#include "llviewerwindow.h"
#if LL_WINDOWS
#include <direct.h>
#include <stdlib.h>
#endif

LLPanelSkins::LLPanelSkins()
{
	LLUICtrlFactory::getInstance()->buildPanel(this, "panel_preferences_skins.xml");
	populateSkins();
}

LLPanelSkins::~LLPanelSkins()
{
}

BOOL LLPanelSkins::postBuild()
{
	mSkinsList = getChild<LLScrollListCtrl>("SkinsList");

	mSkinsList->setCommitCallback(onSelectSkin);
	mSkinsList->setCallbackUserData(this);

	getChild<LLIconCtrl>("preview_image")->setImage("default_no_skin_preview.png");

	return TRUE;
}

void LLPanelSkins::refresh()
{
	std::string skin_selection = mSkinsList->getValue().asString();
	std::string preview_filename = "skin_thumbnail_" + skin_selection + ".png";
	
	std::string full_path = gDirUtilp->findSkinnedFilename("textures", preview_filename);
	if (full_path.empty())
	{
		getChild<LLIconCtrl>("preview_image")->setImage("default_no_skin_preview.png");
	}
	else
	{
		getChild<LLIconCtrl>("preview_image")->setImage(preview_filename);
	}
}

void LLPanelSkins::apply()
{
	if (mSkinsList->getSelectedValue().asString() != gSavedSettings.getString("SkinCurrent"))
	{
		LLNotifications::instance().add("ChangeSkin");
		gSavedSettings.setString("SkinCurrent", mSkinsList->getSelectedValue().asString());
	}
}

void LLPanelSkins::cancel()
{
}

void LLPanelSkins::populateSkins()
{
	std::string imp_dir = "";
	std::vector<std::string> skin_names;

	// Get the current working directory: 
#if LL_WINDOWS
	char* raw_dir;
	raw_dir = _getcwd(NULL,0);
	if( raw_dir != NULL )
	{
		imp_dir = std::string( raw_dir );
	}
#elif LL_DARWIN
	CFBundleRef main_bundle = CFBundleGetMainBundle();
	if( main_bundle != NULL )
	{
		CFURLRef bundle_url = CFBundleCopyBundleURL( main_bundle );
		if( bundle_url != NULL )
		{
			#ifndef MAXPATHLEN
			#define MAXPATHLEN 1024
			#endif
			char raw_dir[MAXPATHLEN];
			if( CFURLGetFileSystemRepresentation( bundle_url, true, (UInt8 *)raw_dir, MAXPATHLEN) )
			{
				imp_dir = std::string( raw_dir ) + "/Contents/MacOS/";
			}
			CFRelease(bundle_url);
		}
	}
#elif LL_LINUX
	// TODO: find cwd for linux here
#endif

	if( imp_dir == "" )
	{
		LL_WARNS("PanelSkins") << "Could not get application directory, viewer skins can't be found."
		                      << LL_ENDL;
		return;
	}

	imp_dir.append("\\skins");
	LL_DEBUGS("PanelSkins") << "Viewer skin directory is "
	                       << imp_dir << LL_ENDL;

	// check for various skin directories:
#ifdef LL_WINDOWS
	std::string check_dir = imp_dir + "\\*.*";
	std::wstring w_check_dir(check_dir.length(), L' ');
	std::copy(check_dir.begin(), check_dir.end(), w_check_dir.begin());

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(w_check_dir.c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
	  LL_WARNS("PanelSkins") << "Skins directory contains no skins!" << LL_ENDL;
	  return;
	} 
	else 
	{
		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (FindFileData.cFileName[0] != '.') // ignore the '.' and '..' directories
				{
					skin_names.push_back(ll_convert_wide_to_string(FindFileData.cFileName));
				}
			}
		}
		while (FindNextFile(hFind, &FindFileData) != FALSE);
		FindClose(hFind);
	}
#else
	//TODO: Add linux and mac implementations
#endif

	// verify it's a skin directory and check if we can preview
	struct stat fileInfo;
	int result;
	
	for (int i = 0; i < (int)skin_names.size(); ++i)
	{
		std::string texture_path = imp_dir + "\\" + skin_names[i] + "\\textures\\textures.xml";

		// check if textures.xml exists by trying to get its attributes
		result = stat(texture_path.c_str(), &fileInfo);
		if(result == 0)
		{
			LL_DEBUGS("PanelSkins") << "Found skin: "
									<< skin_names[i] << LL_ENDL;

			// add names to ui list
			LLSD element;
			element["id"] = skin_names[i];
			element["columns"][0]["column"] = "skin_name";
			element["columns"][0]["type"] = "text";
			element["columns"][0]["value"] = skin_names[i];
			mSkinsList->addElement(element, ADD_BOTTOM);
		}
	}

	mSkinsList->setSelectedByValue(gSavedSettings.getString("SkinCurrent"), TRUE);
	refresh();
}

//static
void LLPanelSkins::onSelectSkin(LLUICtrl* ctrl, void* data)
{
	LLPanelSkins* self = (LLPanelSkins*)data;
	self->refresh();
}
