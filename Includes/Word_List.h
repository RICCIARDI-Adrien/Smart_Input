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
	int Is_Items_String_Word_Shared; //!< Tell whether the "Pointer_String_Word" field of each item is shared with another list, so it must not be freed when the list is destroyed.
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
TWordList *WordListGetWordsFromPrefix(TWordList *Pointer_List_Base, wchar_t *Pointer_String_Word_Prefix);

/** Copy an item into a new one.
 * @param Pointer_Source_List_Item The item to copy from.
 * @param Is_String_Word_Duplicated Set to 1 to also copy the word string content. Set to 0 to share the pointer. Do not forget to indicate that the list is shared if sharing the pointer.
 * @return NULL if an error occurred,
 * @return a valid pointer on the duplicated item on success.
 */
TWordListItem *WordListDuplicateItem(TWordListItem *Pointer_Source_List_Item, int Is_String_Word_Duplicated);

/** Free a list resources.
 * @param Pointer_List The list to delete.
 * @param Is_String_Word_Removed Set to 1 to also free the "Pointer_String_Word" field in list items (useful for a deep-copied list), set to 0 to keep the strings (useful for a list that shares the words with another one).
 */
void WordListRemoveList(TWordList *Pointer_List/*, int Is_String_Word_Removed*/);

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
