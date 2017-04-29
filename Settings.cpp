#include "Settings.h"
#include "SettingsHandler.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Catalog.h>
#include <Debug.h>
#include <Directory.h>
#include <Entry.h>
#include <File.h>
#include <FindDirectory.h>
#include <Locale.h>
#include <Path.h>
#include <StopWatch.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "Setting"


//	#pragma mark -


/*!	\class Settings
	this class represents a list of all the settings handlers, reads and
	saves the settings file
*/


Settings::Settings(const char* filename, const char* settingsDirName)
	:
	fFileName(filename),
	fSettingsDir(settingsDirName),
	fList(0),
	fCount(0),
	fListSize(30),
	fCurrentSettings(0)
{
#ifdef SINGLE_SETTING_FILE
	settingsHandler = this;
#endif
	fList = (SettingsArgvDispatcher**)calloc(fListSize, sizeof(SettingsArgvDispatcher *));
}


Settings::~Settings()
{
	for (int32 index = 0; index < fCount; index++)
		delete fList[index];

	free(fList);
}


const char*
Settings::_ParseUserSettings(int, const char* const *argv, void* castToThis)
{
	if (!*argv)
		return 0;

#ifdef SINGLE_SETTING_FILE
	Settings* settings = settingsHandler;
#else
	Settings* settings = (Settings*)castToThis;
#endif

	SettingsArgvDispatcher* handler = settings->_Find(*argv);
	if (!handler)
		return B_TRANSLATE("unknown command");
	return handler->Handle(argv);
}


/*!
	Returns false if argv dispatcher with the same name already
	registered
*/
bool
Settings::Add(SettingsArgvDispatcher* setting)
{
	// check for uniqueness
	if (_Find(setting->Name()))
		return false;

	if (fCount >= fListSize) {
		fListSize += 30;
		fList = (SettingsArgvDispatcher **)realloc(fList,
			fListSize * sizeof(SettingsArgvDispatcher *));
	}
	fList[fCount++] = setting;
	return true;
}


SettingsArgvDispatcher*
Settings::_Find(const char* name)
{
	for (int32 index = 0; index < fCount; index++)
		if (strcmp(name, fList[index]->Name()) == 0)
			return fList[index];

	return 0;
}


void
Settings::TryReadingSettings()
{
	BPath prefsPath;
	if (find_directory(B_USER_SETTINGS_DIRECTORY, &prefsPath, true) == B_OK) {
		prefsPath.Append(fSettingsDir);

		BPath path(prefsPath);
		path.Append(fFileName);
		ArgvParser::EachArgv(path.Path(), Settings::_ParseUserSettings, this);
	}
}


void
Settings::SaveSettings(bool onlyIfNonDefault)
{
	ASSERT(SettingsHandler());
	SettingsHandler()->_SaveCurrentSettings(onlyIfNonDefault);
}


void
Settings::_MakeSettingsDirectory(BDirectory *resultingSettingsDir)
{
	BPath path;
	if (find_directory(B_USER_SETTINGS_DIRECTORY, &path, true) != B_OK)
		return;

	// make sure there is a directory
	path.Append(fSettingsDir);
	mkdir(path.Path(), 0777);
	resultingSettingsDir->SetTo(path.Path());
}


void
Settings::_SaveCurrentSettings(bool onlyIfNonDefault)
{
	BDirectory fSettingsDir;
	_MakeSettingsDirectory(&fSettingsDir);

	if (fSettingsDir.InitCheck() != B_OK)
		return;

	printf("+++++++++++ Settings::_SaveCurrentSettings %s\n", fFileName);
	// nuke old settings
	BEntry entry(&fSettingsDir, fFileName);
	entry.Remove();

	BFile prefs(&entry, O_RDWR | O_CREAT);
	if (prefs.InitCheck() != B_OK)
		return;

	fCurrentSettings = &prefs;
	for (int32 index = 0; index < fCount; index++) {
		fList[index]->SaveSettings(this, onlyIfNonDefault);
	}

	fCurrentSettings = 0;
}


void
Settings::Write(const char* format, ...)
{
	va_list args;

	va_start(args, format);
	VSWrite(format, args);
	va_end(args);
}


void
Settings::VSWrite(const char* format, va_list arg)
{
	char buffer[2048];
	vsprintf(buffer, format, arg);
	ASSERT(fCurrentSettings && fCurrentSettings->InitCheck() == B_OK);
	fCurrentSettings->Write(buffer, strlen(buffer));
}


#ifdef SINGLE_SETTING_FILE
Settings* Settings::settingsHandler = 0;
#endif
