/**
 * Name        : voc4u
 * Version     : 
 * Vendor      : 
 * Description : 
 */

#include "voc4u.h"
#include "forms/dashboard/Dashboard.h"
#include "forms/init/Init.h"
#include "forms/dictionary/Dictionary.h"
#include "setting/CommonSetting.h"
#include "forms/trainforms/speaker/Speaker.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

voc4u::voc4u()
{
}

voc4u::~voc4u()
{
}

Application*
voc4u::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new voc4u();
}

bool voc4u::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize UI resources and application specific data.
	// The application's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the application will be terminated.

	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	Form *pForm;

	ArrayList str1;
	str1.Construct();
	String lern = "ahoj jak je?!.";
	Utils::SplitString(lern, " ", str1);
	str1.RemoveAll(true);

	lern = "jedna;;;dva;;;tri;;;.!?";
	Utils::SplitString(lern, ";;;", str1);

	Utils::RemovePunctuationFromEnd(lern);
	AppLog("RemovePunctuationFromEnd: %S", lern.GetPointer());
	// if setting currently initialized
	// you can continue normaly
	if (CommonSetting::GetInstance().IsInitialized())
	{
		// when app exit before finish lesson task
		// try continue
		int lesson, word;
		CommonSetting &cs = CommonSetting::GetInstance();
		if (cs.IsContinueLesson(lesson, word))
			WordCtrl::GetInstance()->LoadLesson(lesson);

		// Create a form
		Dashboard *pDashboard = new Dashboard();
		pDashboard->Init();
		pForm = pDashboard;
	}
	else
	{
		// if not, is probably first start
		// make init setting
		InitFrm * init = new InitFrm();
		init->Initialize();
		pForm = init;
	}
	// Add the form to the frame
	Frame *pFrame = GetAppFrame()->GetFrame();
	pFrame->AddControl(*pForm);

	// Set the current form
	pFrame->SetCurrentForm(*pForm);

	// Draw and Show the form
	pForm->Draw();
	pForm->Show();

	return true;
}

bool voc4u::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	WordCtrl * wctrl = WordCtrl::GetInstance();
	int num;
	int * c = wctrl->GetWorkerTaskLessonInProgressN(num);

	if (!num)
	{
		return true;
	}

	AppLogDebug("still on work (last:%d)", c[0]);

	CommonSetting &cs = CommonSetting::GetInstance();
	wctrl->LoadLesson(c[0], true);
	cs.AddContinueLesson(c[0], wctrl->GetCurrentWordAdding());

	delete[] c;
	return true;
}

void voc4u::OnForeground(void)
{
	// back to foreground
	Speaker::CanPlay();
}

void voc4u::OnBackground(void)
{
	// after push to middle button
	// the app work in background
	Speaker::Pause();
}

void voc4u::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void voc4u::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void voc4u::OnScreenOn(void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void voc4u::OnScreenOff(void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
