
# 42-Alcu

Alcu is a simple game, also known as the Nim game. The game starts with several piles of sticks, and two players take turns removing any number of objects from a single pile. The player who removes the last stick loses the game.

In this version, you can remove between 1 and 3 sticks only from the first pile. The AI starts, and then it's your turn to play. Be careful, any wrong move could give a considerable advantage to the AI!



## Usage

Generate a random map
```
make generate_map
```

Bonus version (ncurses lib required)
```bash
make bonus
./alcu_bonus maps/random.map
```

Simple version
```
make
./alcu maps/random.map
```


    
