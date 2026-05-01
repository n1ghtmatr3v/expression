#include <iostream> 
#include <vector>

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    while (n--) {
        int x;
        std::cin >> x;

        std::vector<int> six;
        std::vector<int> two;
        std::vector<int> none;
        std::vector<int> three;

        for (int i = 0; i < x; i++) {
            int t;
            std::cin >> t;

            if (t % 6 == 0) {
                six.push_back(t);
            }
            else if (t % 3 == 0) {
                three.push_back(t);
            }
            else if (t % 2 == 0) {
                two.push_back(t);
            }
            else {
                none.push_back(t);
            }
        }

        for (int f: six) {
            std::cout << f << " ";
        }
        for (int f: two) {
            std::cout << f << " ";
        }
        for (int f: none) {
            std::cout << f << " ";
        }
        for (int f: three) {
            std::cout << f << " ";
        }
        std::cout << std::endl;
    }


    


    

    return 0;
}