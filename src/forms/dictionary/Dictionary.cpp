/*
 * Dictionary.cpp
 *
 *  Created on: 1.11.2011
 *      Author: m1uan
 */

#include "Dictionary.h"

Dictionary::Dictionary()
{
	// TODO Auto-generated constructor stub

}

Dictionary::~Dictionary()
{
	// TODO Auto-generated destructor stub
}

result Dictionary::OnInitializing(void)
{
	__pList = static_cast<ListView *> (GetControl(L"IDC_LESSON"));
	__pList->SetItemProvider(*this);
	return E_SUCCESS;
}

// ListViewItemEvents
void OnListViewContextItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListContextItemStatus status)
{
}

void OnListViewItemLongPressed(Osp::Ui::Controls::ListView &listView, int index, int elementId, bool &invokeListViewItemCallback)
{
}

void OnListViewItemStateChanged(Osp::Ui::Controls::ListView &listView, int index, int elementId, Osp::Ui::Controls::ListItemStatus status)
{
}

void OnListViewItemSwept(Osp::Ui::Controls::ListView &listView, int index, Osp::Ui::Controls::SweepDirection direction)
{
}

CustomItem *Dictionary::CreateLessonItem(int itemWidth, int lesson)
{
    ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
    CustomItem *pItem = new CustomItem();
    pItem->Construct(Osp::Graphics::Dimension(itemWidth, 100), style);
    String name = LangSetting::GetNameOfLesson(lesson);
    pItem->AddElement(Rectangle(5, 5, 250, 50), ID_FORMAT_STRING, name, true);
    return pItem;
}

// list item provider
Osp::Ui::Controls::ListItemBase * Dictionary::CreateItem(int index, int itemWidth)
{
    CustomItem *pItem = CreateLessonItem(itemWidth, index + 1);

	return pItem;
}

bool Dictionary::DeleteItem(int index, Osp::Ui::Controls::ListItemBase *pItem, int itemWidth)
{
	return false;
}

int Dictionary::GetItemCount(void)
{
	return LangSetting::NUM_LESSON;
}
