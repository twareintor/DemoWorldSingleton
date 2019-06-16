
/*************************** version.h **********************************/

#include <stdio.h>

// Pre-Development:
/*********************************************************************************************
Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.
*********************************************************************************************/

/*********** **************/
#define VER_MAJOR "000"
#define VER_MINOR "000"
/*********** **************/
#define VER_ALPHA
#define VER_BETA
#define VER_RELEASE
/*********** **************/
/*********** **************/
#ifdef VER_ALPHA
#define REL "A"
#elif defined(VER_BETA)
#define REL "B"
#else
#define REL "R"
#endif
/*********** **************/
#define COMPILED "16"  
/* this is not automated and the first one may not be 0 or 1 */
/*********** ************* ********************* ************************* */
#define COMMENT "\nDemo world with singleton as starting point for\n"\
	"another projects, useful in life-game simulations and games"

#define AUTHOR "Twareintor"
#define COPYRIGHT "Claudiu Ciutacu <mailto:ciutacu@gmail.com>"
/*********** ************* ********************* ************************* */


void printVersion()
{
	printf("\nVERSION: " VER_MAJOR "." VER_MINOR "." REL COMPILED "/" __DATE__ " " __TIME__ " -- " COMMENT "\n");
} 


