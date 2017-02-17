/*
 * Copyright 2017 Paradoxon <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */


#include "SettingsTest.h"
#include <StringList.h>
#include <Message.h>
//#include <DriverSettingsMessageAdapter.h>

SettingsTest::SettingsTest(){
	/*	BDriverSettings	*settings	= new BDriverSettings();
	 *	settings->Load("/boot/home/config/settings/SettingsTest/DriveSettingsTest");
	 */
	int32	*b;
	ssize_t *numBytes;
	BMessage settingsTestMessage = BMessage();
	settingsTestMessage.AddInt32("MyInt",32);
	settingsTestMessage.PrintToStream();
	settingsTestMessage.FindData("MyInt",B_INT32_TYPE,(const void**)&b,numBytes);
	*b = 5;
	settingsTestMessage.PrintToStream();
	
	/** Testing Codycam settings
	StringValueSetting* sValue		= new StringValueSetting("MyStringSetting", "StringValue",
								  	  "server address expected");
	BooleanValueSetting*	sBool	= new BooleanValueSetting("BooleanSetting", true);
	
	BStringList *pathList			= new BStringList();
	StringListSetting *sStringList	= new StringListSetting("MyPaths",pathList);
	
	mySettings = new Settings("SettingsTest","SettingsTest");
	mySettings->Add(sValue);
	mySettings->Add(sBool);
	
	mySettings->Add(sStringList);
	mySettings->TryReadingSettings();
	mySettings->SaveSettings(false);
	*/
	

}


int main() {
	SettingsTest app=SettingsTest();
	return 0;
}

