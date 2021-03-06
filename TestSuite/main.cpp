/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#include "header.h"
#include "testutils.h"

#include "backtrace.h"
#include "compare.h"
#include "datatypes.h"
#include "darray.h"
#include "dstack.h"
#include "llist.h"
#include "splaytree.h"
#include "stltree.h"
#include "avltree.h"
#include "rbtree.h"
#include "hashtable.h"
#include "heapsort.h"
#include "quicksort.h"
#include "sanity.h"
#include "shellsort.h"
#include "insertionsort.h"
#include "combsort.h"
#include "stopwatch.h"
#include "md4.h"
#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "sha512.h"
#include "tiger.h"

using namespace CrissCross;

CrissCross::IO::Console *g_console;

int RunApplication(int argc, char * *argv)
{
	g_console = new IO::Console();

	g_console->SetColour(IO::Console::FG_RED | IO::Console::FG_INTENSITY);
	g_console->WriteLine("CrissCross Test Suite v%s", CrissCross::Version::LongVersion());
	g_console->SetColour();
	g_console->WriteLine();

	int retval = 0;

	System::SeedRandom();
	g_console->WriteLine("Testing PrintStackTrace()");
	TestBacktrace();

	WritePrefix("Size of cc_uint8_t"); retval |= WriteResult(TestDatatypes_Uint8());
	WritePrefix("Size of cc_uint16_t"); retval |= WriteResult(TestDatatypes_Uint16());
	WritePrefix("Size of cc_uint32_t"); retval |= WriteResult(TestDatatypes_Uint32());
	WritePrefix("Size of cc_uint64_t"); retval |= WriteResult(TestDatatypes_Uint64());
	WritePrefix("Size of cc_ulong_t"); retval |= WriteResult(TestDatatypes_Ulong());
	WritePrefix("Size of cc_bool_t"); retval |= WriteResult(TestDatatypes_Bool());
	WritePrefix("Size of cc_float_t"); retval |= WriteResult(TestDatatypes_Float());
	WritePrefix("Size of cc_double_t"); retval |= WriteResult(TestDatatypes_Double());
	WritePrefix("Size of cc_ptr_t"); retval |= WriteResult(TestDatatypes_Pointer());

#ifdef TARGET_LITTLE_ENDIAN
	WritePrefix("Type-based aliasing sanity"); retval |= WriteResult(TestSanity_TypeBasedAliasing());
#endif

#ifdef ENABLE_MD4
	WritePrefix("MD4"); retval |= WriteResult(TestMD4());
#endif
#ifdef ENABLE_MD5
	WritePrefix("MD5"); retval |= WriteResult(TestMD5());
#endif
#ifdef ENABLE_SHA1
	WritePrefix("SHA-1"); retval |= WriteResult(TestSHA1());
#endif
#ifdef ENABLE_SHA256
	WritePrefix("SHA-256"); retval |= WriteResult(TestSHA256());
#endif
#ifdef ENABLE_SHA512
	WritePrefix("SHA-512"); retval |= WriteResult(TestSHA512());
#endif
#ifdef ENABLE_TIGER
	WritePrefix("Tiger"); retval |= WriteResult(TestTiger());
#endif

	WritePrefix("Stopwatch"); retval |= WriteResult(TestStopwatch());

	WritePrefix("char* Compare"); retval |= WriteResult(TestComparison_CString());
	WritePrefix("std::string Compare"); retval |= WriteResult(TestComparison_String());
	WritePrefix("Integer Compare"); retval |= WriteResult(TestComparison_Integer());

	WritePrefix("LList"); retval |= WriteResult(TestLList());
	WritePrefix("DArray"); retval |= WriteResult(TestDArray());
	WritePrefix("DStack"); retval |= WriteResult(TestDStack());

	WritePrefix("SplayTree<const char *, const char *>"); retval |= WriteResult(TestSplayTree_CString());
	WritePrefix("SplayTree<std::string, std::string>"); retval |= WriteResult(TestSplayTree_String());
	WritePrefix("SplayTree<int, int>"); retval |= WriteResult(TestSplayTree_Int());

#ifdef ENABLE_STLTREE
	WritePrefix("STLTree<const char *, const char *>"); retval |= WriteResult(TestSTLTree_CString());
	WritePrefix("STLTree<std::string, std::string>"); retval |= WriteResult(TestSTLTree_String());
	WritePrefix("STLTree<int, int>"); retval |= WriteResult(TestSTLTree_Int());
#endif

	WritePrefix("AVLTree<const char *, const char *>"); retval |= WriteResult(TestAVLTree_CString());
	WritePrefix("AVLTree<std::string, std::string>"); retval |= WriteResult(TestAVLTree_String());
	WritePrefix("AVLTree<int, int>"); retval |= WriteResult(TestAVLTree_Int());

	WritePrefix("RedBlackTree<const char *, const char *>"); retval |= WriteResult(TestRedBlackTree_CString());
	WritePrefix("RedBlackTree<std::string, std::string>"); retval |= WriteResult(TestRedBlackTree_String());
	WritePrefix("RedBlackTree<int, int>"); retval |= WriteResult(TestRedBlackTree_Int());

	WritePrefix("HashTable<const char *, const char *>"); retval |= WriteResult(TestHashTable_CString());

#ifdef ENABLE_SORTS
	WritePrefix("CombSort (integer array)"); retval |= WriteResult(TestCombSort_IntArray());
	WritePrefix("CombSort (integer DArray)"); retval |= WriteResult(TestCombSort_DArray());
	WritePrefix("CombSort (integer LList)"); retval |= WriteResult(TestCombSort_LList());

	WritePrefix("HeapSort (integer array)"); retval |= WriteResult(TestHeapSort_IntArray());
	WritePrefix("HeapSort (integer DArray)"); retval |= WriteResult(TestHeapSort_DArray());
	WritePrefix("HeapSort (integer LList)"); retval |= WriteResult(TestHeapSort_LList());

#if !defined (DISABLE_DEPRECATED_CODE)
	WritePrefix("InsertionSort (integer array)"); retval |= WriteResult(TestInsertionSort_IntArray());
	WritePrefix("InsertionSort (integer DArray)"); retval |= WriteResult(TestInsertionSort_DArray());
	WritePrefix("InsertionSort (integer LList)"); retval |= WriteResult(TestInsertionSort_LList());
#endif

	WritePrefix("ShellSort (integer array)"); retval |= WriteResult(TestShellSort_IntArray());
	WritePrefix("ShellSort (integer DArray)"); retval |= WriteResult(TestShellSort_DArray());
	WritePrefix("ShellSort (integer LList)"); retval |= WriteResult(TestShellSort_LList());

	WritePrefix("QuickSort (integer array)"); retval |= WriteResult(TestQuickSort_IntArray());
	WritePrefix("QuickSort (integer DArray)"); retval |= WriteResult(TestQuickSort_DArray());
	WritePrefix("QuickSort (integer LList)"); retval |= WriteResult(TestQuickSort_LList());
#endif

	if (retval == 0) {
		g_console->WriteLine();
		g_console->WriteLine("All tests passed.");
		g_console->WriteLine();
	}

	g_console->Flush();

#ifdef TARGET_OS_WINDOWS
	system("pause");
#endif

	delete g_console;

	return retval;
}
