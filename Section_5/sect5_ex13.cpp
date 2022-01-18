//written by Jtaim
//date 8 Apr 2017
//Programming Principles and Practice Using C++ Second Edition, Bjarne Stroustrup

/*
Section 5 exercise 13
Bulls and Cows game.
random generate the numbers to guess
Guess the 4 numbers range(0 to 9)
*/

#include "section5.h"

using vType = std::vector<int>;
bool get_guesses(vType& input, std::size_t length);
int get_bulls(vType& guesses, vType& setSequence);
int get_cows(vType& guesses, vType& setSequence);
const vType::value_type foundMark = std::numeric_limits<vType::value_type>::max();
bool try_again(const std::string&);

int main()
try
{
  const int guessSize = 4;  // sets how many numbers to guess

  std::random_device rd;
  //Standard mersenne_twister_engine seeded with rd()
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 9);

  std::cout << "Guess " << guessSize << " numbers in the range of 0 - 9 to guess what I have.\n";
  std::cout << "If guess a correct number and the correct location will get a Bull.\n";
  std::cout << "If guess a correct number but not the correct location then will get a Cow.\n";
  std::cout << "Example: My set is 2345 and your guess was 5248, so there are 2 Cows (5 and 2)  1 Bull (4).\n\n";

  do
  {
    std::cout << "Enter your guess.\n\n";

    vType setNumbers;
    setNumbers.reserve(guessSize);
    vType guesses{};

    // create random guess_size numbers
    for (int i{}; i < guessSize; ++i)
    {
      setNumbers.push_back(dis(gen));
    }

    while (get_guesses(guesses, setNumbers.size()))
    {
      if (guesses == setNumbers)
      {
        std::cout << "You have " << setNumbers.size() << " Bulls, Congratulations!\n";
        break;
      }
      else
      {
        vType numbers = setNumbers;
        auto bulls = get_bulls(guesses, numbers);
        auto cows = get_cows(guesses, numbers);

        std::cout << "The result is " << cows << (cows == 1 ? " Cow" : " Cows");
        std::cout << " and " << bulls << (bulls == 1 ? " Bull" : " Bulls") << ". Try again.\n";
        guesses.clear();	// clear for new set of guesses
      }
    }
  } while (try_again("Would you like to try again (y or n).\n"));

  keep_window_open();
  return 0;
}
catch (std::exception& e)
{
  std::cerr << "error: " << e.what() << '\n';
  keep_window_open();
  return 1;
}
catch (...)
{
  std::cerr << "Oops: unknown exception!\n";
  keep_window_open();
  return 2;
}

/* function to get user input for guesses.
INPUT: vector reference to store guesses.
       size_t for length of number to guess.
OUPUT: bool true = got valid guesses
       bool false = insufficient guess entered.
ERROR: invalid guess.
*/
bool get_guesses(vType& input, std::size_t length)
{
  std::string user_guess;
  std::cin >> user_guess;

  if (user_guess.size() != length)
  {
    std::cout << "number of guesses entered must be " << length << " digits\n";
    return false;
  }

  for (unsigned char guess : user_guess)
  {
    // convert number char to integer and place into a vector
    if (isdigit(guess))
    {
      // '9'(57) - '0'(48) provides 0 to 9
      vType::value_type number = guess - '0';
      input.push_back(number);
    }
    else
    {
      error("guess is not valid!");
    }
  }
  return true;
}

/* function to bulls.
INPUT: vType reference to user input guesses.
       vType reference to number to guess.
OUPUT: int for number of bulls found
ERROR: input vector sizes do not match.
modifies guesses by setting matching elements to type max number
*/
int get_bulls(vType& guesses, vType& setSequence)
{
  if (guesses.size() != setSequence.size())
  {
    error("guess and answer size do not match!");
  }

  int bulls{};
  for (auto i{guesses.begin()}, j{setSequence.begin()}; i < guesses.cend(); ++i, ++j)
  {
    if (*i == *j)
    {
      ++bulls;
      *i = *j = foundMark;
    }
  }
  return bulls;
}

/* function to cows.
INPUT: vType reference to user input guesses.
       vType reference to number to guess.
OUPUT: int for number of cows found
ERROR: input vector sizes do not match.
modifies guesses by setting matching elements to type max number
*/
int get_cows(vType& guesses, 
vType& setSequence)
{
  if (guesses.size() != setSequence.size())
  {
    error("input vector sizes do not match!");
  }

  int cows{};
  for (auto& guess : guesses)
  {
    if (guess != foundMark)
    {
      auto itr = std::find(setSequence.begin(), setSequence.end(), guess);
      if (itr != setSequence.cend())
      {
        ++cows;
        guess = *itr = foundMark;
      }
    }
  }
  return cows;
}

/* function to get user input for a yes or no answer.
INPUT: string for message you want displayed.
OUPUT: bool
ERROR: none
*/
bool try_again(const std::string& s)
{
  std::cout << s;
  unsigned char again{};
  std::cin >> again;
  again = narrow_cast<char, int>(tolower(again));
  if (again == 'y')
  {
    return true;
  }
  std::cout << "Thanks for playing, goodbye.\n\n";
  return false;
}
