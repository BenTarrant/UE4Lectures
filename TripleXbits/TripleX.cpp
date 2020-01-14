#include <iostream>

int main()
{
    //intro text
    std:: cout << "You're trapped in a rather average room, the only plausible way out in a locked door across from you";
    std:: cout << std:: endl; // adds a new line
    std:: cout << "There's a number of keypads on the door. It seems that to unlock the door you will need to enter the correct codes in sequence...";
    std:: cout << std:: endl;
    
    // first lock
    int a = 4;
    int b = 2;
    int c = 1;

    int sum = a + b + c; // adds each of the initialized variables together
    int product = a * b * c;


    std:: cout << sum << std:: endl; // prints sum (the total of a,b and c) to terminal
    std:: cout << product << std:: endl;; // prints sum (the total of a,b and c) to terminal
    return 0;
}