#include <iostream>

void PrintIntroduction()
{   
    //intro text
    std:: cout << "\n\n You're trapped in a rather average room, the only plausible way out seems to be a locked door across from you\n";
    std:: cout << "You notice a keypad on the door. It seems that to unlock the door you will need to enter the correct code in sequence...\n\n";
}

bool PlayGame()
{
    PrintIntroduction();

    // first lock
    const int a = 4;
    const int b = 2;
    const int c = 1;

    const int CodeSum = a + b + c; // adds each of the initialized variables together
    const  int CodeProduct = a * b * c;
    std:: cout << "++ There are 3 numbers in the code";
    std:: cout << "\n ++ The code adds up to: " << CodeSum; // prints sum (the total of a,b and c) to terminal
    std:: cout << "\n ++ And the the code multiplies to give: " << CodeProduct << std::endl; // prints sum (the total of a,b and c) to terminal

    //Store Player Guess
    int GuessA, GuessB, GuessC;
    std:: cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    //Check if Player Guess is Correct
    if (GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        std:: cout << "** Well Done, that was correct! **\n";
        return true;
    }
    else
    {
        std:: cout << "** That code was incorrect, try again**\n";
        return false;
    }

}

int main()
{
    while(true)
    {
        bool bLevelComplete = PlayGame;
        std::cin.clear(); // discards any erros from input - like text instead of numbers
        std::cin.ignore(); // discards the buffer
    }

    return 0;
}

