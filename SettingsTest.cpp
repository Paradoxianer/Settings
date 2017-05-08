/*
 * Copyright 2017 Paradoxon <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */


#include "SettingsTest.h"
#include "SettingTypes.h"
#include <StringList.h>
#include <Message.h>

//#include <DriverSettingsMessageAdapter.h>

SettingsTest::SettingsTest(){
	/*	BDriverSettings	*settings	= new BDriverSettings();
	 *	settings->Load("/boot/home/config/settings/SettingsTest/DriveSettingsTest");
	 */
	
	// Testing settings
	StringValueSetting* sValue		= new StringValueSetting("MyStringSetting", "StringValue",
								  	  "server address expected");
	BooleanValueSetting*	sBool	= new BooleanValueSetting("BooleanSetting", true);
	
	BStringList *pathList			= new BStringList();
	pathList->Add(BString("/boot/home"));
	pathList->Add(BString("/boot/home/config"));
	StringListSetting *sStringList	= new StringListSetting("MyPaths",pathList);
	
	mySettings = new Settings("SettingsTest","SettingsTest");
	mySettings->Add(sValue);
	mySettings->Add(sBool);
	
	mySettings->Add(sStringList);
	mySettings->TryReadingSettings();
	BString tmpString(pathList->StringAt(1));
	mySettings->SaveSettings(false);
}


int main() {
	SettingsTest app=SettingsTest();
	return 0;
}

