#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;


struct event_listener
{
  virtual void on_close() { }
  virtual void on_gain_focus() { }
  virtual void on_lose_focus() { }
  virtual void on_resize(sf::Event::SizeEvent) { }

  virtual void on_mouse_button_press(sf::Event::MouseButtonEvent) { }
  virtual void on_mouse_button_release(sf::Event::MouseButtonEvent) { }

  virtual void on_key_press(sf::Event::KeyEvent) { }
  virtual void on_key_release(sf::Event::KeyEvent) { }
};


{
  event_source(sf::Window& w)
    : window(&w)
  { }

  void
  listen(event_listener& l)
  {
    listeners.push_back(&l);
  }

  void
  poll()
  {
    sf::Event e;
    while (window->pollEvent(e))
      process(e);
  }

  void process(sf::Event const& e)
  {
    switch (e.type) {
    case Event::Closed:
      return notify([e](event_listener* l) { l->on_close(); });

    case Event::Resized:
      return notify([e](event_listener* l) { l->on_resize(e.size); });
    
    case Event::MouseButtonPressed:
      return notify([e](event_listener* l) { l->on_mouse_button_press(e.mouseButton); });
    case Event::MouseButtonReleased:
      return notify([e](event_listener* l) { l->on_mouse_button_release(e.mouseButton); });

    case Event::KeyPressed:
      return notify([e](event_listener* l) { l->on_key_press(e.key); });
    case Event::KeyReleased:
      return notify([e](event_listener* l) { l->on_key_press(e.key); });
    default:
      break;
    }
  }

  template<typename F>
  void notify(F fn)
  {
    for (event_listener* l : listeners)
      fn(l);    
  }

  sf::Window* window;

  std::vector<event_listener*> listeners;
};

int ts = 54;

struct doodle_jump_app : event_listener
{
  doodle_jump_app()
    : prng(std::random_device()()),
      window(VideoMode(740, 480), "Match-3 Game!"),
      grid(prng)
  {
    window.setFramerateLimit(120);
  }

  // Returns true if the app is open.
  bool is_open() const { return window.isOpen(); }

  // Close the application.
  void
  on_close() override
  {
    window.close();
  }

  void 
  on_mouse_button_press(sf::Event::MouseButtonEvent e) override
  {
    if (e.button == Mouse::Left) {
      // Only register clicks if we're not currently animating.
  bool moving = false; // True if moving.
};

struct debug_listener : event_listener
{
  debug_listener(doodle_jump_app& a)
    : app(&a)
  { }
  
  void on_close() override
  {
    std::cerr << "closing...\n";
  }

  void on_mouse_button_press(sf::Event::MouseButtonEvent e) override
  {
    std::cout << "mouse press: " << e.x << ' ' << e.y << '\n';
    std::cout << "  - click: " << app->click << '\n';
    std::cout << "  - moving: " << app->moving << '\n';
    std::cout << "  - swapping: " << app->swapping << '\n';
  }
  void on_mouse_button_release(sf::Event::MouseButtonEvent e) override
  {
    std::cout << "mouse release: " << e.x << ' ' << e.y << '\n';
    std::cout << "  - click: " << app->click << '\n';
    std::cout << "  - moving: " << app->moving << '\n';
    std::cout << "  - swapping: " << app->swapping << '\n';
  }

  bejeweled_app* app;
};


int
main()
{

  //set up window
  RenderWindow app(VideoMode(400, 533), "Doodle Game!");
  app.setFramerateLimit(60);

  //textures
  Texture t1, t2, t3;
  t1.loadFromFile("images/background.png");
  t2.loadFromFile("images/platform.png");
  t3.loadFromFile("images/doodle.png");

  Sprite sBackground(t1), sPlat(t2), sPers(t3);

   // Create the app data and window.
  doodle_jump_app app;

  // Create a debugger
  debug_listener debug(app);

  // Construct the event loop and listeners.  
  event_source events(app.window);
  events.listen(app);
  events.listen(debug);


  while (app.is_open()) {
   
    // Update game state.
    app.find_matches();
    app.animate_moves();
    app.animate_deletions();
    app.update_score();
    app.update_grid();

    // Redraw the game.
    app.draw();
  }
  
  return 0;
}


  