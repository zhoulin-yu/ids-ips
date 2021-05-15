#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "CUnit/Automated.h"
#include "CUnit/Console.h"
#include "../Headers/Blocage.h"

void nom_fichier_dans_chemin(void)
{
	char test[200] = "ripissou";
	CU_ASSERT_STRING_EQUAL(search_name_of_file_in_path(test),"ripissou");
	
}

void fichier_existe_pas(void)
{
	CU_ASSERT_DOUBLE_EQUAL(checkIfFileExists("jhuel"),0,0.000001);
}

void fichier_existe(void)
{
	CU_ASSERT_DOUBLE_EQUAL(checkIfFileExists("testBlocage.c"),1,0.0000001);
}

void blocage_fichier_existant(void)
{
	char test[20] = "menfou";
	block_file(test);
	CU_ASSERT_DOUBLE_EQUAL(checkIfFileExists(test),0,0.000001);
}

void quarantaine_deplacement_valide(void)
{
	char test[20] = "ripissou";
	quarantine_placement(test);
	CU_ASSERT_DOUBLE_EQUAL(checkIfFileExists(test),0,0.000001);
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

	if ((NULL == CU_add_test(pSuite, "nom_fichier_dans_chemin", nom_fichier_dans_chemin)) ||
		(NULL == CU_add_test(pSuite, "fichier_existe_pas", fichier_existe_pas)) ||
		(NULL == CU_add_test(pSuite, "fichier_existe", fichier_existe)) ||
		(NULL == CU_add_test(pSuite, "blocage_fichier_existant", blocage_fichier_existant)) ||
		(NULL == CU_add_test(pSuite, "quarantaine_deplacement_valide", quarantaine_deplacement_valide)))
		
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
