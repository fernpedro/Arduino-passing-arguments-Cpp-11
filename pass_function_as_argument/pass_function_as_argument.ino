/*
 * https://stackoverflow.com/questions/44638938/c-arduino-pass-a-function-as-argument
 * Non static MF require an object to work on and thus can't be passed and
 * called like normal function pointers
 */

 /*
 VIP: std::remove_reference explained
 https://stackoverflow.com/questions/17000179/stdremove-reference-explained
 */

template <typename T>
struct remove_reference
{
  using type = T;
};

template <typename T>
struct remove_reference<T&>
{
  using type = T;
};

template <typename T>
struct remove_reference<T&&>
{
  using type = T;
};

template <typename T>
constexpr T&& forward(typename remove_reference<T>::type& t)
{
  return static_cast<T&&>(t);
}

template <typename T>
constexpr T&& forward(typename remove_reference<T>::type&& t)
{
  return static_cast<T&&>(t);
}

template <typename Callable, typename... Args>
auto invoke(Callable&& func, Args&&... args)
    -> decltype(forward<Callable>(func)(forward<Args>(args)...))
{
    return forward<Callable>(func)(forward<Args>(args)...);
}

template <typename Callable, typename Class, typename... Args>
auto invoke(Callable&& method, Class&& obj, Args&&... args)
    -> decltype((forward<Class>(obj).*method)(forward<Args>(args)...))
{
    return (forward<Class>(obj).*method)(forward<Args>(args)...);
}

class Button {
  int buttonDownTime = 0;
  int debounceTime = 2000;
  public:
  template<typename Callback, typename... Args>
  void debounce(Callback&& func, Args&&... args) {
   if (millis() - buttonDownTime > debounceTime) {
      invoke(forward<Callback>(func),
             forward<Args>(args)...);
   }
  }
};

class Player
{
  int playerCount = 0;
public:
  void incriment() {
    playerCount++;
  }
};

void setup(){}

void loop() {
  Player player;
  Button button;
  button.debounce([&player](){ player.incriment(); });
}
