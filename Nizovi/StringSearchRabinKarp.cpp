#include <cstring>
#include <iostream>
#include <string>
using namespace std;
// d is the maximum number of values for a character (2^8, 8 because a char is
// 8-bit)
#define D 256
#define PRIME 251

class RabinKarpSearch {
 private:
   static int mostSigDigitValue;

   //!MOST DIGIT
   /*
      On zapravo racuna potenciju s kojom mnozim,npr na 1,2,3 ovisi o zadatku
      
   */
   static void CalculateMostSigDigitValue(int length) {
      mostSigDigitValue = 1;
      for (int i = 0; i < length - 1; i++)
         mostSigDigitValue = (mostSigDigitValue * D) % PRIME;
   }


   //!GETHASH 
   /*
      Stvara hash u bazi 256 tj. to je abeceda s kojom radim, pa ako imam 
      4 znaka abcd, prvi ce bit ascii vrijednost npr. 65 na 3 pa onda 66 na 2 itd i hash je zbroj svih njih
   */
   static int GetHash(string s, int startIndex, int length) {
      int hash = 0;
      for (int i = 0; i < length; i++) {
         hash = (D * hash + s[startIndex + i]) % PRIME;
      }
      return hash;
   }



   //!REHASH

   /*
      Primi stari hash, stari leading digit i zadnji digit koji cu zborjit u hash.
      Od starog oduzme najveci clan, tj. 65 * 256 na 3.
      Onda pomnozi taj novi hash sa bazom tj. 256 da iduci clan bude na 3-cu
      I za kraj doda u taj novi hash zadnji clan tj lastdigit kojeg sam poslao, to bi zapravo bilo zadnji clan * 256 na 0 ili samo dodavanje zadnjeg clana
      I onda ako novi hash ispadne negativan, dodam PRIME ili prost broj koji govori koliko mjesta ima u tablici i to je to
   */
   static int ReHash(int oldHash, char leadingDigit, char lastDigit) {
      int oldHashWithoutLeadingDigit = oldHash - leadingDigit * mostSigDigitValue;
      int newHashwithoutLastDigit = oldHashWithoutLeadingDigit * D;
      int newHash = (newHashwithoutLastDigit + lastDigit) % PRIME;
      if (newHash < 0) // in case new hash is negative, covert to a positive num
         newHash += PRIME;
      return newHash;
   }





 public:
   //!SEARCH
   static int Search(string A, string pattern) {
      int i, j, n, m, h, p, t;
      n = A.length();
      m = pattern.length();

      p = GetHash(pattern, 0, m); 
      t = GetHash(A, 0, m);

      CalculateMostSigDigitValue(m);

      for (i = 0; i <= n - m; i++) {
         if (p == t) { // compare hash values of the input substring and the
                       // pattern string
            for (j = 0; j < m;
                 j++) { // check if the input substrings and pattern are exactly
                        // the same character by character
               if (A[i + j] != pattern[j])
                  break;
            }
            if (j == m) // both checks are OK, substring is found at index i
               return i;
         }
         if (i < n - m) {
            t = ReHash(t, A[i], A[i + m]); // create new hash for next substring
         }
      }
      return -1;
   }
};

int RabinKarpSearch ::mostSigDigitValue = 1;

//!MAIN
int main(void) {
   try {
      string A = "ababbaabaaab";
      string pattern = "abaa";
      int foundPosition = RabinKarpSearch::Search(A, pattern);
      if (foundPosition != -1) {
         std::cout << "Pattern found at position " << foundPosition;
      } else {
         std::cout << "Pattern was not found in the input string";
      }
   } catch (std::exception &e) {
      std::cerr << e.what();
   }
   std::cin.get();
   return 0;
}
