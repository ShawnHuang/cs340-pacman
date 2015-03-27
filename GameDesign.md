# Making storyboards #

# Setting rules for each component #

**The World(MAP)**
  * Our world is bounded by map walls.
  * No one ( pacman / enemies) can go out of the world
  * When pacman / enemy collides with map boundary, it cannot go any further in that direction and has to change its direction.
  * It contains pacman food that is small dots.
  * There are big dots (less in number compare to small dots, may be say 2 or 3) as well which will make enemies vulnerable to pacman for attack
  * Something like cherries can do something as well. Cherries should appear intermittently.

**Pacman**
  * Takes birth with 100 health which reduces in step( 100 to 50 and thn to 0) only when hit by a bullet otherwise when hit by a enemy, it goes directly to 0 and pacman dies
  * Keyborad used to direct it
  * Cannot kill enemies until enemies are vulnerable ie when pacman east big round balls
  * Can be killed by a touch from enemy ( hopefully even bullets in higher levels)
  * Eats food(small dot, big dot, cherry) which appears on map.

**Food**
  * Small dots appearing on map will increase points when consumed by pacman
  * Big dots will make enemies vulnerable to attack by pacman
  * Cherry can do something like giving extra life.

**Enemies**
  * AI
  * No of enemis = ?,  will increase with level.
  * Movement will be haphazard for first few min of the game, thn their movement will be directed in order to  proceed towards pacman, trying to kill it.
  * Will become vulnerable to attach when pacman eats big dots
  * At higher level ( say after 4) , will start shooting bullet

# Prioritizing development, Developing main core of the game and thn trying to improve #
  * Creating Placeholder models (a symbol that will later be replaced by some literal stuff )

  * Creating main game loop:
    * Creating map (just ground with walls placed somewhere to create hindrances)
    * Adding pacman sprite and test its movements
    * Adding enemies and intial AI. Testing movements of AI
    * Adding food
    * Doing pacman/enemy/food test.

# Making FSMs #
**GAME FSM**
> _INTRO_
    * Display start screen
    * If clicked on “start game” , current state = INITPLAY
    * If “end game” clicked, EXIT the game

> _INITPLAY_
    * Initialize the game play
    * Current state =PLAY

> _PLAY_
    * Call main game processing function
    * Currentstate=PLAY

> _OUTRO_
    * Clean up game states
    * Display outro screen with scores
    * If clicked on “ok”, current state=INTRO

**PACMAN FSM**
> _INIT_
    * Reset the position of pacman
    * Current state=PLAY

> _PLAY_
    * Do navigation of pacman
    * If eat small dot -> increment player score
    * If eat big dot, make enemy vulnerable to attack, current state = KILL
    * If eat cherries, something ( increment life by 1)
    * Enemy touches pacman, current state=DYING

> _KILL_
    * Put all enemies in a list / array
> > > ![http://cs340-pacman.googlecode.com/files/table1.jpg](http://cs340-pacman.googlecode.com/files/table1.jpg)
    * Pacman navigation speed increases
    * Enemy currentstate = ENEMY FSM.VULNERABLE
> > > ![http://cs340-pacman.googlecode.com/files/table2.jpg](http://cs340-pacman.googlecode.com/files/table2.jpg)
    * If (Pacman kill enemy), currentstate of tht enemy = ENEMY FSM.DYING and remove that enemy from the list. Increment player point
    * For Example: EN1 was killed. The current list would be :
> > > ![http://cs340-pacman.googlecode.com/files/table3.jpg](http://cs340-pacman.googlecode.com/files/table3.jpg)
    * After some time (say x =sec), currentstate of pacman = PLAY and currentstate of remaining enemies = ENEMY FSM.PLAY


> _DYING_
    * Pacman dies
    * Decrease life by 1
    * Check for life:
    * (if life > 0) , Currentstate = INIT
    * Else, Current state = OUTRO

**ENEMY FSM ( for each enemy)**
> _INIT_
    * Generate it in the enemy box ( center of the map)
    * Currentstate = PLAY

> _PLAY_
    * Do AI navigation
    * If (enemy is close to pacman in distance), currentstate = DIRECTED NAVIGATION
    * Else currentstate = PLAY

> _DIRECTED NAVIGATION_
    * Enemies directed towards pacman
    * Enemies touch pacman, currentstate = PACMAN FSM.DYING
    * Check distance between enemy and pacman
    * If (enemy is close to pacman in distance), currentstate = DIRECTED NAVIGATION
    * Else currentstate = PLAY

> _VULNERABLE_
    * Enemy color = blue
    * Enemy cannot kill pacman
    * Enemy directed away from pacman

> _DYING_
    * The killed enemy disappears
    * currentstate of enemy = INIT

**BULLET FSM**
  * Pending