#import <iostream>
int n, x, k;
main(){
    std::cin >> n;
    for(; n--; std::cin >> k)
        x ^= k ^ (n + 1);
    std::cout << x;
}
