#include <stdio.h>

int in_order(char *, char *);

int in_order(char *str1, char *str2)
{
  int p;
  for(p = 0; p < sizeof(str1); p++)
  {
    if(*(str1+p) == *(str2+p)) continue;
    return (*(str1+p) < *(str2+p));
  }
  return 1;
}


int main()
{
    
    //For-loop through each president.
    for(i = 0; i < 2 ; i++)
    {
        //If current and next president are out of order, swap them.
        if ( ! in_order(potus[i], potus[i+1]))
        {
            //XOR swap so I don't have to use a temp variable. Not as confusing
            //  as it looks.
            dope_vector[i] ^= dope_vector[i+1] ^= dope_vector[i] ^= dope_vector[i+1];
            //Reset the counter. It will go back to 0 when it loops again.
            i = -1;
        }
    }





}

void trim(char *to_trim)
{
  int size = (int)strlen(to_trim);
  int i;

  for (i=size-1; i>0; i--)
  {
    //printf("%d,%u;", i, *(to_trim+i));
    if(*(to_trim+i) == ' ')
      *(to_trim+i) = '\0';
    else
      break;

  }
}
