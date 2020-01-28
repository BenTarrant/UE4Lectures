#include <iostream>

void PrintIntroduction(int Difficulty)
{   
    
    //intro text
    std:: cout << "\n\nYou're robbing a bank in the heart of Wall Street\n";
    std:: cout << "and you're currently trying to break into a Level " << Difficulty;
    std:: cout << " Grade Safe. \n\n It seems that to unlock it you will need to enter the correct code in sequence...\n\n";
}

void PrintSynop(int Difficulty)
{   
    
    //intro text
    std:: cout << "\n\nYou continue cracking the safes\n";
    std:: cout << "and you're now trying to break into a Level " << Difficulty;
    std:: cout << " Grade Safe. \n\n It seems harder than the previous safe too...\n\n";
}

bool PlayGame(int Difficulty)
{
    if (Difficulty == 1)
    {
        PrintIntroduction(Difficulty);
    }
    
    if (Difficulty >= 2)
    {
        PrintSynop(Difficulty);
    }

    // Lock Digits
    const int a = rand() % Difficulty + Difficulty; // Scales the difficulty and numbers of code. + Difficulty creates exponetial scale and removes 0 from the Modulus pool
    const int b = rand() % Difficulty + Difficulty;
    const int c = rand() % Difficulty + Difficulty;

    const int CodeSum = a + b + c; // adds each of the initialized variables together
    const  int CodeProduct = a * b * c;

    std:: cout << "++ There are 3 numbers in the code";
    std:: cout << "\n++ The code adds up to: " << CodeSum; // prints sum (the total of a,b and c) to terminal
    std:: cout << "\n++ And the the code multiplies to give: " << CodeProduct << std::endl; // prints sum (the total of a,b and c) to terminal

    //Store Player Guess
    int GuessA, GuessB, GuessC;
    std:: cin >> GuessA >> GuessB >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    //Check if Player Guess is Correct
    if (GuessSum == CodeSum && GuessProduct == CodeProduct)
    {
        std:: cout << "** Safe cracked, that was correct! **\n";
        return true;
    }
    else
    {
        std:: cout << "** That safe remains locked, try again**\n";
        return false;
    }

}

int main()
{


    int LevelDifficulty = 1;
    const int MaxDifficulty = 5;

    while (LevelDifficulty <= MaxDifficulty)
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear(); // discards any erros from input - like text instead of numbers
        std::cin.ignore(); // discards the buffer

        if (bLevelComplete)
        {
           ++LevelDifficulty;
        }
    }

    std:: cout << "\n\n\n** Congratualtions, that's all the safes cracked. Heist succesful!**\n";
    return 0;
}

