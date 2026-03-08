#include <stdio.h>

// 1. Standard single-line comment
/* 2. Standard 
   multi-line comment */

int main() {
    // 3. The classic edge case: splitting tokens
    // Note: Standard C compilers replace comments with a single space.
    // If your program completely deletes them, 'int/**/i' becomes 'inti'.
    int/**/i = 1;
    
    /*4. Comment immediately after a pointer or operator*/
    int *ptr = &i;
    int j = 10 /* comment */ / /* comment */ 2;

    // 5. Comment markers hidden inside strings (should NOT be removed)
    char* str1 = "This is // not a comment";
    char* str2 = "This is /* not a comment */ either";
    char* str3 = "String with escaped quotes \" // /* \"";
    
    // 6. Comment markers hidden inside character literals
    char c1 = '/'; // c1
    char c2 = '*'; // c2
    char c3 = '"'; // Testing quote escaping inside comments

    // 7. Escaped backslash before a comment marker in a string
    char* str4 = "Escaped backslash \\"; // This should still be a comment

    // 8. Line splicing / Continuations in single-line comments
    // This comment continues to the next line because of the backslash \
    int hidden_variable = 99; // This entire line should be removed!

    // 9. Line splicing inside strings containing comment markers
    char* str5 = "This string has a line continuation \
    // and this is still inside the string \
    /* still a string */";

    // 10. Tricky overlapping comment syntax
    int a = 5; /*//*/ int b = 6; // The multi-line comment eats the single-line marker
    int c = 7; // /* int d = 8; // The '/*' above is trapped in a single-line comment, so 'd' should compile.

    // 11. Un-nested multi-line comments
    // C doesn't support nested comments. The first '*/' closes the comment.
    /* This starts a comment /* this does NOT nest */ int e = 9; 

    // 12. Bizarre partial markers
    int f = 10; /****/ int g = 11;
    int h = 12; /*/*/ int k = 13; // Looks like an unclosed comment, but /*/ closes on the next */ -> */

    return i;
}
// 13. Single-line comment at EOF with no trailing newline