/*
 * Copyright 2017 Paradoxon <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef Settings_Test_H
#define Settings_Test_H


#include <SupportDefs.h>
#include "Settings.h"
#include "SettingsHandler.h"

const char* kStringList[] = {
	"FirstString",
	"SecondString",
	"ThirdString"
};


class SettingsTest {
public:
	SettingsTest();
								
private:
	Settings *mySettings;

};


#endif // _H


