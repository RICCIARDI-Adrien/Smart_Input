/** @file Word_List.h
 * A simple implementation of chained lists containing all needed data to handle words.
 * @author Adrien RICCIARDI
 */
#ifndef H_WORD_LIST_H
#define H_WORD_LIST_H

#include <wchar.h>

//-------------------------------------------------------------------------------------------------
// Types
//-------------------------------------------------------------------------------------------------
/** A list link. */
typedef struct WordListItem
{
	wchar_t *Pointer_String_Word; //!< The word data.
	int Word_Usage_Statistics; //!< The more this value is high, the more the word is used and must appear first when searching.
	struct WordListItem *Pointer_Next_Item; //!< The next link in the chain (or NULL when the chain's end has been reached).
} TWordListItem;

/** Contain a variable amount of items. */
typedef struct
{
	TWordListItem *Pointer_First_Item; //!< The list head.
	TWordListItem *Pointer_Last_Item; //!< The list tail.
	int Items_Count; //!< How many elements currently in the list.
} TWordList;

//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
/** TODO */
void WordListInitialize(TWordList *Pointer_List);

/** Add a new word to the list and make sure the list keeps being sorted.
 * @param Pointer_List The list to add the word to.
 * @param Pointer_String_Word The word to add.
 * @return -1 if an error occurred,
 * @return 0 if the word was successfully added.
 * @note Default usage statistics is automatically associated to the newly added word.
 */
int WordListAddSortedWord(TWordList *Pointer_List, wchar_t *Pointer_String_Word);

/** TODO */
int WordListGetWordsFromPrefix(TWordList *Pointer_List_Base, wchar_t *Pointer_String_Word_Prefix, TWordList *Pointer_List_Found_Words);

/** Append an item at the end of the specified list.
 * @param Pointer_List The list to append item to.
 * @param Pointer_List_Item The item to append.
 */
void WordListAppendItem(TWordList *Pointer_List, TWordListItem *Pointer_List_Item);

/** Load words and related data from a file.
 * @param Pointer_String_File_Name The data file.
 * @return NULL if an error occurred,
 * @return A valid list containing all file words if the function succeeded.
 * @warning Words must be sorted in the file.
 */
TWordList *WordListLoadFromFile(char *Pointer_String_File_Name);

/** TODO */
int WordListSaveToFile(char *Pointer_String_File_Name, TWordList *Pointer_List);

/** Display a list content.
 * @param Pointer_List The list to display.
 * @note This function is made for debugging purposes only.
 */
void WordListDisplay(TWordList *Pointer_List);

#endif
