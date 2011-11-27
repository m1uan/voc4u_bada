/*
 * Train.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef TRAIN_H_
#define TRAIN_H_

#include "../BaseWordForm.h"

class Train: public BaseWordForm
{
private:
	Word *__word;
	Label *__lblTest;
    bool GetFirstWord();
    void UpdateWord(bool know);

public:
	static const int ID_BTN_KNOW = 5001;
	static const int ID_BTN_DONTKNOW = 5002;


public:
	Train();
	virtual ~Train();


	virtual String GetResourceID();
	virtual result OnInitializing(void);
protected:
	virtual void PrepareContextMenu();
	virtual void PrepareFooter();

	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
};

#endif /* TRAIN_H_ */
