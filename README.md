[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=9909951&assignment_repo_type=AssignmentRepo)
 
# Chrono Checkers: Battle Through Time
 
 Authors: [Alvin Van De Geijn](https://github.com/avan046), [Ethan Ortega](https://github.com/YoungsterEthan), [Dalton Witt](https://github.com/citrushappy), [Agora Ngelale](https://github.com/AgoraNgelale), [Arhum Shahid](https://github.com/codingwitharhum)

## Project Description
  * Why is it important or interesting to you?
    * If we can get around to developing the story mode, we can create an interesting way to engage in checkers and learn about its history by allowing players to face off against potentially voice acted characters in different time periods that are relevant to the history of how the game has been played.
  * What languages/tools/technologies do you plan to use? (This list may change over the course of the project)
    * C++
    * A framework for graphical interfacing such as SDL2
  * What will be the input/output of your project?
    * Inputs:
      * User input, controlling the game
    * Outputs:
      * Visual and audio feedback from the game
  * What are the features that the project provides?
    * Our project will allow for the user to play either with a friend, or by themselves.
    * The project will allow for the user to interact with a GUI rather than a terminal.
    * The user will be able to save and load their games.
    * The user will be able to undo their moves if they choose to.


## Class Diagram
![image](https://user-images.githubusercontent.com/100615723/225549558-f2a13c52-3f6d-4dce-b7ea-7c7e169f8e78.png)

Inheritance: 

The AI class inherits from the Player class. makeMove() is overridden.

Composition: 

Checker, Board, and Player classes have an aggregation relationship with the Game class. The AI class involves the use of the move structure, which is responsible for determining different moves that the AI can make and choosing which one it will make.

Diagram Updates:

We seperated parts of the game class to be created as the Board, Player, and Checker class, which handle all of the logical components of the game. This involves the use of the Single Responsibility Principle, as the game class is no longer responsible for both the visual elements and logical elements of our game. Instead, the game class only handles the visual elements, and works together with the new classes to make our game function. Doing so also makes it easier for us to understand which parts of our code affect the game logic, and which parts affect the visual elements.

We created the Entity, Component, and Manager classes to help handle the visual elements of our game. To fulfill the Single Responsibility Principle, we took some of the responsibilities of the game class and moved them into these new classes. Doing so makes it easier for us to code the visual elements of our game, as we can understand what each class is responsible for.

The AI class is capable of substituting the player class, as it is able to play the game in place of a player. This allows us to create a singleplayer mode, where the player can choose to play alone instead of with a friend. Doing so also makes it possible for us to test our game by having an AI play it.
 
 ## Screenshots
 ![image](https://user-images.githubusercontent.com/100615723/224218172-b7b9e9f1-16d9-4dab-829f-cb9f8ebb7b73.png)
 ![image](https://user-images.githubusercontent.com/100615723/224218283-ab4c86f8-ba88-466e-8a68-1784e22fafed.png)

 ## Installation/Usage
 > Instructions on installing and running your application
 
 ## Testing
 We tested our program by checking for memory leaks and unit testing our code. Due to our program being mostly visual, we were only able to test the game logic portions of our code.
