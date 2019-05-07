/*
 * Non static member functions require an object to work on and thus
 *  can't be passed and called like normal function pointers.
 */

class Button
{
  int buttonDownTime = 0;
  int debounceTime = 2000;
public:
  template<typename Callback>
  void debounce(Callback&& func) //Note the && here, without it func would need to be copied
  {
    if (millis() - buttonDownTime > debounceTime)
    {
      func();
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
