/** @file Main.c
 * Entry point and test loop.
 * @author Adrien RICCIARDI
 */
#include <locale.h>
#include <Log.h>
#include <stdlib.h>
#include <Word_List.h>

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main(void)
{
	TWordList *Pointer_List_All_Words, *Pointer_List_Words;
	
	setlocale(LC_ALL, "");
	
	Pointer_List_All_Words = WordListLoadFromFile("Resources/Words.txt");
	if (Pointer_List_All_Words == NULL) return EXIT_FAILURE;
	
	WordListDisplay(Pointer_List_All_Words);
	
	Pointer_List_Words = WordListGetWordsFromPrefix(Pointer_List_All_Words, L"a");
	WordListDisplay(Pointer_List_Words);
	Pointer_List_Words = WordListGetWordsFromPrefix(Pointer_List_All_Words, L"test");
	WordListDisplay(Pointer_List_Words);
	Pointer_List_Words = WordListGetWordsFromPrefix(Pointer_List_All_Words, L"introuvable");
	WordListDisplay(Pointer_List_Words);
	Pointer_List_Words = WordListGetWordsFromPrefix(Pointer_List_All_Words, L"sal");
	WordListDisplay(Pointer_List_Words);

	return 0;
}
