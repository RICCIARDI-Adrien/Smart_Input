/** @file Word_List.c
 * @see Word_List.h for description.
 * @author Adrien RICCIARDI
 */
#include <assert.h>
#include <Log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <Word_List.h>

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
TWordList *WordListCreate(int Is_Items_String_Word_Shared)
{
	TWordList *Pointer_List;
	
	// Allocate list memory
	Pointer_List = malloc(sizeof(TWordList));
	if (Pointer_List == NULL)
	{
		LOG_ERROR("Could not allocate list memory.");
		return NULL;
	}
	
	// Initialize relevant internal fields
	Pointer_List->Items_Count = 0;
	Pointer_List->Is_Items_String_Word_Shared = Is_Items_String_Word_Shared;
	
	return Pointer_List;
}

void WordListDelete(TWordList *Pointer_List)
{
	TWordListItem *Pointer_Current_Item, *Pointer_Next_Item;
	int i;
	
	assert(Pointer_List != NULL);
	
	// Remove all items
	Pointer_Current_Item = Pointer_List->Pointer_First_Item;
	for (i = 0; i < Pointer_List->Items_Count; i++)
	{
		// Keep next item pointer before removing the item to avoid a "use-after-free" problem
		Pointer_Next_Item = Pointer_Current_Item->Pointer_Next_Item;
		
		// Remove word string if required to
		if (!Pointer_List->Is_Items_String_Word_Shared) free(Pointer_Current_Item->Pointer_String_Word);
		
		// Safely remove the current item
		free(Pointer_Current_Item);
		
		Pointer_Current_Item = Pointer_Next_Item;
	}
	
	// Remove the list itself
	free(Pointer_List);
}

TWordListItem *WordListDuplicateItem(TWordListItem *Pointer_Source_List_Item, int Is_Item_String_Word_Shared)
{
	TWordListItem *Pointer_Destination_List_Item;
	
	assert(Pointer_Source_List_Item != NULL);
	
	// Allocate next word item
	Pointer_Destination_List_Item = malloc(sizeof(TWordListItem));
	if (Pointer_Destination_List_Item == NULL)
	{
		LOG_ERROR("Could not allocate list item memory.");
		return NULL;
	}
	
	// Duplicate fields
	Pointer_Destination_List_Item->Word_Usage_Statistics = Pointer_Source_List_Item->Word_Usage_Statistics;
	if (Is_Item_String_Word_Shared) Pointer_Destination_List_Item->Pointer_String_Word = Pointer_Source_List_Item->Pointer_String_Word;
	else
	{
		// TODO
		LOG_ERROR("Not implemented.");
	}
	
	return Pointer_Destination_List_Item;
}

TWordList *WordListGetWordsFromPrefix(TWordList *Pointer_List_Base, wchar_t *Pointer_String_Word_Prefix)
{
	TWordList *Pointer_List;
	TWordListItem *Pointer_List_Base_Item, *Pointer_List_Duplicated_Item;
	int i, Prefix_Word_Length;
	
	assert(Pointer_List_Base != NULL);
	assert(Pointer_String_Word_Prefix != NULL);

	// Initialize the new list
	Pointer_List = WordListCreate(1);
	if (Pointer_List == NULL)
	{
		LOG_ERROR("Could not create list.");
		return NULL;
	}
	
	// Cache prefix word length to avoid computing it several times
	Prefix_Word_Length = wcslen(Pointer_String_Word_Prefix);
	LOG_DEBUG("Searched prefix : '%ls', prefix length : %d.", Pointer_String_Word_Prefix, Prefix_Word_Length);
	
	// Search in the whole base list for words beginning with the same prefix
	Pointer_List_Base_Item = Pointer_List_Base->Pointer_First_Item;
	for (i = 0; i < Pointer_List_Base->Items_Count; i++)
	{
		// Is the word matching (do not take characters case into account) ?
		if (wcsncasecmp(Pointer_List_Base_Item->Pointer_String_Word, Pointer_String_Word_Prefix, Prefix_Word_Length) == 0)
		{
			LOG_DEBUG("Found match with word '%ls'.", Pointer_List_Base_Item->Pointer_String_Word);
			
			// Duplicate the item but not the word string to save some memory
			Pointer_List_Duplicated_Item = WordListDuplicateItem(Pointer_List_Base_Item, 1);
			if (Pointer_List_Duplicated_Item == NULL)
			{
				LOG_ERROR("Failed to duplicate item word '%ls'.", Pointer_List_Base_Item->Pointer_String_Word);
				return NULL;
			}
			
			WordListAppendItem(Pointer_List, Pointer_List_Duplicated_Item);
		}
		
		Pointer_List_Base_Item = Pointer_List_Base_Item->Pointer_Next_Item;
	}
	
	return Pointer_List;
}

TWordList *WordListLoadFromFile(char *Pointer_String_File_Name)
{
	FILE *Pointer_File;
	TWordList *Pointer_List;
	TWordListItem *Pointer_List_Item;
	wchar_t *Pointer_String_Word, String_Word[128]; // Should be enough for a single word
	int Word_Usage_Statistics, Result;
	
	// Initialize the new list
	Pointer_List = WordListCreate(0);
	if (Pointer_List == NULL)
	{
		LOG_ERROR("Could not allocate list memory.");
		return NULL;
	}
	
	// Try to open the file
	Pointer_File = fopen(Pointer_String_File_Name, "r");
	if (Pointer_File == NULL)
	{
		LOG_ERROR("Could not open the file to load words from.");
		return NULL;
	}
	
	while (1)
	{
		// Start by reading the next word record in order to determine whether the end of the file has been reached
		// Get word string
		Result = fscanf(Pointer_File, "%ls", String_Word); // TODO handle maximum string size => buffer overflow is possible here
		if (feof(Pointer_File)) break; // End of file is reached
		if (Result == 0)
		{
			LOG_ERROR("Failed to read word string from current file record.");
			return NULL;
		}
		// Get word usage statistics
		if (fscanf(Pointer_File, "%d", &Word_Usage_Statistics) != 1) // TODO handle maximum string size => buffer overflow is possible here
		{
			LOG_ERROR("Failed to read word usage statistics from current file record.");
			return NULL;
		}
		
		// Allocate next word item
		Pointer_List_Item = malloc(sizeof(TWordListItem));
		if (Pointer_List_Item == NULL)
		{
			LOG_ERROR("Could not allocate list item memory.");
			return NULL;
		}
		
		// Allocate space for the word string itself
		Pointer_String_Word = malloc((wcslen(String_Word) + 1) * sizeof(wchar_t)); // Add 1 more character for the terminating zero
		if (Pointer_String_Word == NULL)
		{
			LOG_ERROR("Could not allocate word string memory.");
			return NULL;
		}
		wcscpy(Pointer_String_Word, String_Word);
		
		// Fill list item
		Pointer_List_Item->Pointer_String_Word = Pointer_String_Word;
		Pointer_List_Item->Word_Usage_Statistics = Word_Usage_Statistics;
		
		// Add item to the list
		WordListAppendItem(Pointer_List, Pointer_List_Item);
	}
	
	return Pointer_List;
}

void WordListAppendItem(TWordList *Pointer_List, TWordListItem *Pointer_List_Item)
{
	assert(Pointer_List != NULL);
	assert(Pointer_List_Item != NULL);
	
	// Special handling if the list is empty
	if (Pointer_List->Items_Count == 0)
	{
		Pointer_List->Pointer_First_Item = Pointer_List_Item;
		Pointer_List->Pointer_Last_Item = Pointer_List_Item;
	}
	else
	{
		Pointer_List->Pointer_Last_Item->Pointer_Next_Item = Pointer_List_Item; // Append the item at the end of the currently last item
		Pointer_List->Pointer_Last_Item = Pointer_List_Item;
	}
	
	Pointer_List->Items_Count++;
}

void WordListDisplay(TWordList *Pointer_List)
{
	int i;
	TWordListItem *Pointer_List_Item;
	
	assert(Pointer_List != NULL);

	// Display all items
	Pointer_List_Item = Pointer_List->Pointer_First_Item;
	for (i = 0; i < Pointer_List->Items_Count; i++)
	{
		printf("[%d]\tWord : \"%ls\", usage statistics : %d\n", i, Pointer_List_Item->Pointer_String_Word, Pointer_List_Item->Word_Usage_Statistics);
		Pointer_List_Item = Pointer_List_Item->Pointer_Next_Item;
	}
}
