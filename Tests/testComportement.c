#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "CUnit/Automated.h"
#include "CUnit/Console.h"
#include "../Headers/Comportement.h"

void true_toto_equal_toto2(void)
{
	FILE *file1;
	FILE *file2;
	char test1[200];
	char test2[200];

	file1 = fopen("toto", "r");
	file2 = fopen("toto2", "r");

	while (1)
	{
		fgets(test1, 180, file1);
		fgets(test2, 180, file2);

		if (feof(file1) && feof(file2))
			break;
		CU_ASSERT_TRUE(strcmp(test1, test2) == 0);

	}
}

void false_toto_equal_toto2(void)
{
	FILE *file1;
	FILE *file2;
	char test1[200];
	char test2[200];

	file1 = fopen("toto", "r");
	file2 = fopen("toto2", "r");

	while (1)
	{
		fgets(test1, 180, file1);
		fgets(test2, 180, file2);
		if (feof(file1) || feof(file2))
			break;

		if (strcmp(test1, test2) != 0)
		{
			CU_ASSERT_FALSE(strcmp(test1, test2) == 0);
			break;
		}
	}
}

void ligne_4_date_different_2_fichier(void)
{
	char nomFichier1[20] = "toto";
	char nomFichier2[20] = "totoDiff";
	CU_ASSERT_DOUBLE_EQUAL(detecterDateDiff(nomFichier1,nomFichier2),4,0.1);
}

void ligne_4_date_identique_2_fichier(void)
{
	char nomFichier1[20] = "toto";
	char nomFichier2[20] = "toto2";
	CU_ASSERT_DOUBLE_EQUAL(detecterDateDiff(nomFichier1,nomFichier2),0,0.1);
}

void ligne_3_chemin_identique_2_fichier(void)
{
	char nomFichier1[20] = "toto";
	char nomFichier2[20] = "toto2";
	CU_ASSERT_DOUBLE_EQUAL(detecterCheminDiff(nomFichier1,nomFichier2),0,0.1);
}

void ligne_3_chemin_different_2_fichier(void)
{
	char nomFichier1[20] = "toto";
	char nomFichier2[20] = "totoDiff";
	CU_ASSERT_DOUBLE_EQUAL(detecterCheminDiff(nomFichier1,nomFichier2),3,0.1);
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

	if ((NULL == CU_add_test(pSuite, "true_toto_equal_toto2", true_toto_equal_toto2)) ||
		(NULL == CU_add_test(pSuite, "false_toto_equal_toto2", false_toto_equal_toto2)) ||
		(NULL == CU_add_test(pSuite, "ligne_4_date_different_2_fichier", ligne_4_date_different_2_fichier))||
		(NULL == CU_add_test(pSuite, "ligne_4_date_identique_2_fichier", ligne_4_date_identique_2_fichier))||
		(NULL == CU_add_test(pSuite, "ligne_3_chemin_identique_2_fichier", ligne_3_chemin_identique_2_fichier))||
		(NULL == CU_add_test(pSuite, "ligne_3_chemin_different_2_fichier", ligne_3_chemin_different_2_fichier)))
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
