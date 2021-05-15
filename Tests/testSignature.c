#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "CUnit/Automated.h"
#include "CUnit/Console.h"
#include "../Headers/Signature.h"

void chaine_sans_espaces_sans_majuscules(void)
{
	CU_ASSERT_STRING_EQUAL(string_treatment("I WANT SOME NUGGIES"),"iwantsomenuggies");
}

void recherche_6_chaine_dans_fichier(void)
{
	CU_ASSERT_DOUBLE_EQUAL(search_in_File("toto","home"),6,0.000001);
}

void recherche_0_chaine_dans_fichier(void)
{
	CU_ASSERT_DOUBLE_EQUAL(search_in_File("toto","hedfed"),0,0.000001);
}

void retourne_ligne_1_fichier(void)
{
	CU_ASSERT_STRING_EQUAL(search_and_keep_line("toto",1),"/home/mk/Bureau");
}

void retourne_ligne_50_fichier(void)
{
	CU_ASSERT_STRING_EQUAL(search_and_keep_line("toto",50),"");
}



int main(void)
{
	CU_pSuite pSuite = NULL;


	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("toto_egal_toto2", NULL, NULL);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite, "chaine_sans_espaces_sans_majuscules", chaine_sans_espaces_sans_majuscules)) ||
		(NULL == CU_add_test(pSuite, "recherche_6_chaine_dans_fichier", recherche_6_chaine_dans_fichier)) ||
		(NULL == CU_add_test(pSuite, "recherche_0_chaine_dans_fichier", recherche_0_chaine_dans_fichier)) ||
		(NULL == CU_add_test(pSuite, "retourne_ligne_1_fichier", retourne_ligne_1_fichier)) ||
		(NULL == CU_add_test(pSuite, "retourne_ligne_50_fichier", retourne_ligne_50_fichier)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	printf("\n\n");
	// Run all tests using the automated interface
	CU_automated_run_tests();
	CU_list_tests_to_file();
	// Run all tests using the console interface      
	CU_console_run_tests();
}
