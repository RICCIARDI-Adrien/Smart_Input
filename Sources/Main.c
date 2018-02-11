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
	TWordList *Pointer_List_All_Words;
	
	setlocale(LC_ALL, "");
	
	Pointer_List_All_Words = WordListLoadFromFile("Resources/Words.txt");
	if (Pointer_List_All_Words == NULL) return EXIT_FAILURE;
	
	WordListDisplay(Pointer_List_All_Words);
}
