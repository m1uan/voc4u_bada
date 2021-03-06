/*
 * Dictionary.h
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "../BaseWordForm.h"
#include <FGraphics.h>
#include "setting/LangSetting.h"
#include "dialogs/information/Information.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;
using namespace Osp::Base;

class Dictionary: public BaseWordForm, public Osp::Ui::Controls::IListViewItemEventListener, public Osp::Ui::Controls::IListViewItemProvider, public ILessonWorkerLissener
{
public:
	static const int ID_MENU_ADD_WORD = 1101;
	static const int ID_MENU_RESETDB = 1102;

	static const int ID_MENU_ADD_WORD_SUCCCES = 1105;
private:
	ListView * __pList;

	Information *__info;


	bool __progressState[LangSetting::NUM_LESSON];
	bool saveState[LangSetting::NUM_LESSON];


    void GetLessonsInProgress();
    void InitLessonState();
	void SetupInitSetting();


public:

	static const int ID_FORMAT_STRING = 1;
	static const int ID_FORMAT_EXAMPLES = 2;
	static const int ID_FORMAT_PREPARING = 3;

	static const int ITEM_HEIGHT = 180;
	static const int EXAMPLES_MAX = 30;
public:
	Dictionary();
	virtual ~Dictionary();
	String GetResourceID()
	{
		return L"IDF_DICTIONARY";
	}

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView & listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus status);
	virtual void OnListViewItemLongPressed(Osp::Ui::Controls::ListView & listView, int index, int elementId, bool & invokeListViewItemCallback);
	virtual void OnListViewItemStateChanged(Osp::Ui::Controls::ListView & listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Osp::Ui::Controls::ListView & listView, int index, Osp::Ui::Controls::SweepDirection direction);
	virtual Osp::Ui::Controls::ListItemBase *CreateItem(int index, int itemWidth);
	virtual bool DeleteItem(int index, Osp::Ui::Controls::ListItemBase *pItem, int itemWidth);
	virtual int GetItemCount(void);
	void OnActionPerformed(const Osp::Ui::Control & source, int actionId);
public:
	virtual void OnLessonTask(const int lesson);

	bool Init();

protected:
	virtual void PrepareFooter();
	virtual void PrepareContextMenu();
	virtual wchar_t* GetShowInfoCode(){ return IDS_DICTIONARY;};
private:
	CustomItem *CreateLessonItem(int itemWidth, int lesson);
	CustomItem *CreateCustomWordItem(int itemWidth);
	void AddItemPreparing(CustomItem *& pItem, int itemWidth);
	void AddItemTitle(CustomItem *& pItem, String name, int itemWidth);
	void AddItemExamples(CustomItem *& pItem, int itemWidth, String examples);
};

#endif /* DICTIONARY_H_ */
