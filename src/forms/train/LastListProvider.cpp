/*
 * LastListProvider.cpp
 *
 *  Created on: 27.11.2011
 *      Author: miuan
 */

#include "LastListProvider.h"

LastListProvider::LastListProvider()
{
	array.Construct();
}

LastListProvider::~LastListProvider()
{
	array.RemoveAll(true);
}

void LastListProvider::AddWord(Word &word)
{
	array.Add(word);

	if(array.GetCount() > MAX_IN_LAST_LIST)
	{
		array.RemoveAt(0, true);
	}
}



void LastListProvider::OnListViewContextItemStateChanged(ListView &listView, int index, int elementId, ListContextItemStatus status)
{
}

void LastListProvider::OnListViewItemLongPressed(ListView &listView, int index, int elementId, bool &invokeListViewItemCallback)
{
}

void LastListProvider::OnListViewItemStateChanged(ListView &listView, int index, int elementId, ListItemStatus status)
{
}

void LastListProvider::OnListViewItemSwept(ListView &listView, int index, SweepDirection direction)
{
}

EnrichedText *LastListProvider::PrepareText(String text, bool know, bool bold)
{
    //pItem->SetBackgroundColor(LIST_ITEM_DRAWING_STATUS_NORMAL, LangSetting::LESSON_COLORS[lesson - 1]);
    result r;
    EnrichedText *pEnrichedText = new EnrichedText();
    r = pEnrichedText->Construct(Dimension(200, 200));

    TextElement *pTextElement = new TextElement();
    r = pTextElement->Construct(text);
    if(!pTextElement)
    	return null;

    Font font;
    if(bold)
    	font.Construct(FONT_STYLE_BOLD, 30);
    else
    	font.Construct(FONT_STYLE_PLAIN, 30);
    pTextElement->SetFont(font);
    pTextElement->SetTextColor(know ? Color::COLOR_BLUE : Color::COLOR_RED);
    pEnrichedText->Add(*pTextElement);

    return pEnrichedText;
}

Word *LastListProvider::GetWordAt(int index)
{
	int count = array.GetCount();
	int pos = count - (index % count) -1;

	if(count < 1)
		return null;

    return static_cast<Word*>(array.GetAt(pos));
}

ListItemBase * LastListProvider::CreateItem(int index, int itemWidth)
{
	ListAnnexStyle style = LIST_ANNEX_STYLE_NORMAL;
	CustomItem *pItem = new CustomItem();
	pItem->Construct(Osp::Graphics::Dimension(itemWidth, 100), style);

	Word *word = GetWordAt(index);

	EnrichedText *pELern = PrepareText(word->__lern, word->__type || word->__know, true);
	EnrichedText *pENative = PrepareText(word->__native, !word->__type || word->__know, false);


	int columnWidth = itemWidth;
	//AddToDestructList(pTextElement);
	//AddToDestructList(pEnrichedText);

	if(pELern)
		pItem->AddElement(Rectangle(10, 5, columnWidth, 50), 1, *pELern);

	if(pENative)
		pItem->AddElement(Rectangle(10, 55, columnWidth, 50), 2, *pENative);

	pItem->SetElementTextHorizontalAlignment(1, ALIGNMENT_CENTER );
	pItem->SetElementTextHorizontalAlignment(2, ALIGNMENT_CENTER );
	return pItem;
}

bool LastListProvider::DeleteItem(int index, ListItemBase *pItem, int itemWidth)
{
	return false;
}

int LastListProvider::GetItemCount(void)
{
	return array.GetCount();
}