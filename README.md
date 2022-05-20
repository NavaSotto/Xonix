
# Xonix Game

In this project I worked together with another company. In this way I developed my ability to work as a team
We chose to implement the "Close Space" game, which is an experiential game in which the user must close space on the screen without being harmed by harmful objects that appear from time to time.
Realization of the game:
We chose to use the matrix to save screen space
The complexity of the project was the implementation of efficient algorithms for:
Identified closed area
For starters we kept a free cell about 0 and a busy cell about 1
We built an algorithm that scans the game space in real time and returns a matrix that includes two sub-areas (pixel groups) on which we will mark the new "closed" area and the "open" area created with the player's moves
 "Calculating the player's trajectory in order to transplant during it" elves
At the beginning of the game, elves appeared randomly placed on the screen
According to the player's movements, an algorithm was activated that calculated the distance between the player and the elf and placed the elf close to the player, which made it more difficult for him to play.


## Technologies
Work environment: visual studio
Technologies: C++ | SFML| OOP | Design patterns


## Demo

Insert gif or link to demo


## Deployment

To deploy this project run

```bash
  npm run deploy
```

## Documentation

[Documentation](https://linktodocumentation)


## Environment Variables

To run this project, you will need to add the following environment variables to your .env file

