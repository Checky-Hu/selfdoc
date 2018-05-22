// '*' match 0~n any character
// '.' match 1 any character
// Is there any bugs? May be add testcase later.
#include <stdio.h>

int match(char * filter, char * target)
{
  char *wildchar_pos = NULL;
  char *p1 = filter, *p2 = target;
  while (*p2) {
    if (*p1 == '.' || *p1 == *p2)
      p1++, p2++;
    else if (*p1 == '*')
      wildchar_pos = p1, p1++;
    else {
      if (wildchar_pos) // Revert both p1 and p2 to (last match position + 1).
        p2 = p2 - (p1 - (wildchar_pos + 1)) + 1, p1 = wildchar_pos + 1;
      else
        return -1; // No '*' before, not match.
    }
  }

  // If there is any remainning characters except '*', not match.
  while (*p1) {
    if (*p1 == '*')
      p1++;
    else
      return -1;
  }
  return 0;
}

int main(int argc, char ** argv)
{
  if (argc != 3) {
    printf("please input filter and target string.\n");
    return -1;
  }

  printf("filter:%s\ntarget:%s\n", argv[1], argv[2]);
  if (match(argv[1], argv[2]))
    printf("Not match\n");
  else
    printf("Match\n");
  return 0;
}
