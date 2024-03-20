#ifndef PRINT_H
#define PRINT_H
/**
 * @brief print the value to the console with new line at the end
 *
 * @tparam T
 * @param Value anytype of value to be printed
 */
template <typename T>
void print(T Value) {
    std::cout << Value << std::endl;
}
/**
 * @brief print the value to the console without new line at the end
 *
 * @tparam U
 * @param s anytype of value to be printed
 */
template <typename U>
void printLn(U s) {
    std::cout << s;
};
// enter code here...
#endif