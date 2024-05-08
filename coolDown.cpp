#include "coolDown.h"


bool coolDown(int coolDownSeconds){
    auto currentTime = std::chrono::steady_clock::now();
    static auto startTime = currentTime;
    auto timeSinceLast = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

    if (timeSinceLast < std::chrono::seconds(coolDownSeconds)) {
        std::cout << "Card is still on cooldown. Remaining time: " << (coolDownSeconds - timeSinceLast.count()) << " seconds." << std::endl;
        return false;
    }
     else {
        startTime = currentTime; 
        return true;  
    }
}
