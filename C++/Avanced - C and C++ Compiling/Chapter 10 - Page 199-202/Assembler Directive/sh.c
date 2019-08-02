/*
	In order to eliminate the linker facing the duplicate symbols problem, you can create different names for different versions of the same function, which will be used for internal purposes only (will not be exported). These two functions are list_occupancy_1_0() and list_occupancy_2_0().
	From the outer world perspective, however, the linker will create the symbol featuring the expected function name list_occupancy(). As a consequence, both the older and the newer client binary will be able to identify the symbol they expect.
*/

__asm__(".symver list_occupancy_1_0, list_occupancy@MYLIBVERSION_1.0");
unsigned long list_occupancy_1_0()
{	// For library version 1.0.0+
	return 0;
}

// default function indicated by additional @
__asm__(".symver list_occupancy_2_0, list_occupancy@@MYLIBVERSION_2.0");
unsigned long list_occupancy_2_0()
{	// For library version 2.0.0+
	return 1;
}
