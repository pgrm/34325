/*
 ============================================================================
 Name        : DynamicComputing.c
 Author      : Peter Grman
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUCKET_SIZE 70
#define MAX_ITEM_SIZE 25
#define MAX_ITEM_VALUE 10
#define ITEM_COUNT 9

typedef struct
{
	int size;
	int value;
} ItemStruct;

typedef struct
{
	int valueSum;
	int* selection;
	int selectedItemsCount;
} OptimumRet;

OptimumRet* calculateValue(ItemStruct* items, int* selection, int selectedItemsCount);

OptimumRet* findOptimum(ItemStruct* items,
		int curItem, int itemsCount,
		int usedSpace, int maxSpace,
		int* selection, int selectedItemsCount);

OptimumRet* findOptimumWithCurrentItem(ItemStruct* items,
		int curItem, int itemsCount,
		int usedSpace, int maxSpace,
		int* selection, int selectedItemsCount);

int main(void)
{
	int i;
	ItemStruct items[ITEM_COUNT];

	srand(time(NULL));

	for (i = 0; i < ITEM_COUNT; i++)
	{
		items[i].size = (rand() % MAX_ITEM_SIZE);
		items[i].value = (rand() % MAX_ITEM_VALUE);
		printf("item %d with size %d and value %d was created \n", i, items[i].size, items[i].value);
	}

	OptimumRet* ret = findOptimum(items, 0, ITEM_COUNT, 0, BUCKET_SIZE, NULL, 0);

	printf("The best value achieved was %d\n", ret->valueSum);

	for (i = 0; i < ret->selectedItemsCount; ++i)
	{
		printf("Item %d with size %d and value %d\n", ret->selection[i], items[ret->selection[i]].size, items[ret->selection[i]].value);
	}

	return EXIT_SUCCESS;
}


OptimumRet* findOptimum(ItemStruct* items,
		int curItem, int itemsCount,
		int usedSpace, int maxSpace,
		int* selection, int selectedItemsCount)
{
	if (curItem >= itemsCount)
		return calculateValue(items, selection, selectedItemsCount);

	OptimumRet* without = findOptimum(items, curItem + 1, itemsCount, usedSpace, maxSpace, selection, selectedItemsCount);
	OptimumRet* with = findOptimumWithCurrentItem(items, curItem, itemsCount, usedSpace, maxSpace, selection, selectedItemsCount);
	OptimumRet* useRet = NULL;
	OptimumRet* freeRet = NULL;


	if (with->valueSum > without->valueSum)
	{
		useRet = with;
		freeRet = without;
	}
	else
	{
		useRet = without;
		freeRet = with;
	}

	/*
	if (freeRet->selection != selection)
		free(freeRet->selection);
	free(freeRet);
	*/

	return useRet;
}

OptimumRet* findOptimumWithCurrentItem(ItemStruct* items,
		int curItem, int itemsCount,
		int usedSpace, int maxSpace,
		int* selection, int selectedItemsCount)
{
	int usedSpaceWithCurItem = items[curItem].size + usedSpace;
	int* newSelection = NULL;

	if (usedSpaceWithCurItem > maxSpace)
		return calculateValue(items, selection, selectedItemsCount);
	else
	{
		newSelection = malloc(sizeof(char)*(selectedItemsCount + 1));

		memcpy(newSelection, selection, selectedItemsCount * sizeof(int));
		newSelection[selectedItemsCount] = curItem;

		return findOptimum(items, curItem + 1, itemsCount, usedSpaceWithCurItem, maxSpace, newSelection, selectedItemsCount + 1);
	}
}

OptimumRet* calculateValue(ItemStruct* items, int* selection, int selectedItemsCount)
{
	int i;
	int value = 0;

	for (i = 0; i < selectedItemsCount; i++)
	{
		value += items[selection[i]].value;
	}

	OptimumRet* ret = (OptimumRet*)malloc(sizeof(OptimumRet));

	ret->valueSum = value;
	ret->selection = selection;
	ret->selectedItemsCount = selectedItemsCount;

	return ret;
}
