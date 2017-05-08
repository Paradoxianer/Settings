#ifndef SETTINGS_H
#define SETTINGS_H

#include "SettingsHandler.h"

class BDirectory;


class Settings {
	public:
		Settings(const char* filename, const char* settingsDirName);
		~Settings();
		void TryReadingSettings();
		void SaveSettings(bool onlyIfNonDefault = true);


		Settings* SettingsHandler()
		{
			return this;
		}

		bool Add(SettingsArgvDispatcher *);

		void Write(const char* format, ...);
		void VSWrite(const char*, va_list);
static const char* ParseUserSettings(int, const char *const *argv, void*);

	private:
		void _MakeSettingsDirectory(BDirectory*);

		SettingsArgvDispatcher* _Find(const char*);
		void _SaveCurrentSettings(bool onlyIfNonDefault);

		const char* fFileName;
		const char* fSettingsDir;
		SettingsArgvDispatcher** fList;
		int32 fCount;
		int32 fListSize;
		BFile* fCurrentSettings;
};

#endif //SETTINGS_H
