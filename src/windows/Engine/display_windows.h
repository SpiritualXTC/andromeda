#pragma once



#include <andromeda/Engine/display.h>



namespace andromeda
{
	namespace windows
	{
		class DisplayWindows : public Display
		{
		public:
			DisplayWindows(const DisplayParameters & dp);
			virtual ~DisplayWindows();

			/*

			*/
			Int32 getNumDisplays() override;


			/*
			
			*/
			Boolean enumDisplayDevices() override;


			/*
				Get Display Settings Available
			*/
			std::set<DisplayFormat> enumDisplaySettings() override;


			/*
				Get Current Screen Resolution
			*/
			Boolean getScreenResolution(Int32 & width, Int32 & height) override;


			/*
				Change Screen Resolution
			*/
			Boolean changeScreenResolution(const Int32 width, const Int32 height) override;


			/*
				Restore to Native Resolution
			*/
			Boolean restoreScreenResolution() override;


		protected:

			

		private:
			Int32 _nativeWidth;		// Resolution at launch of app
			Int32 _nativeHeight;	// Resolution at launch of app
		};
	}
}