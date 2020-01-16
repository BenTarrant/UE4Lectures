#include <iostream>

int main()
{
    //intro text
    std:: cout << "You're trapped in a rather average room, the only plausible way out seems to be a locked door across from you";
    std:: cout << std:: endl; // adds a new line
    std:: cout << "You notice a keypad on the door. It seems that to unlock the door you will need to enter the correct code in sequence..." << std:: endl;
    std:: cout << std:: endl;
    
    // first lock
    const int a = 4;
    const int b = 2;
    const int c = 1;

    const int CodeSum = a + b + c; // adds each of the initialized variables together
    const  int CodeProduct = a * b * c;
    std:: cout << "++ There are 3 numbers in the code" << std:: endl;
    std:: cout << "++ The code adds up to: " << CodeSum << std:: endl; // prints sum (the total of a,b and c) to terminal
    std:: cout << "++ And the the code multiplies to give: " <<CodeProduct << std:: endl; // prints sum (the total of a,b and c) to terminal

    int GuessA, GuessB, GuessC;

    std:: cin >> GuessA;
    std:: cin >> GuessB;
    std:: cin >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

if (GuessSum == CodeSum && GuessProduct == CodeProduct)
{
     std:: cout << "** Well Done, that was correct! **" << std:: endl; 
}

else
{
    std:: cout << "** That code was incorrect **" << std:: endl; 
}

    return 0;
}