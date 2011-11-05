/*
 * Dashboard.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef DASHBOARD_H_
#define DASHBOARD_H_

#include <FBase.h>
#include <FUi.h>
#include <FGraphics.h>
#include <FApp.h>

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::App;

class Dashboard :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{
public:
	Dashboard();
	virtual ~Dashboard();

	bool Initialize();
	result OnInitializing(void);

	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
};

#endif /* DASHBOARD_H_ */