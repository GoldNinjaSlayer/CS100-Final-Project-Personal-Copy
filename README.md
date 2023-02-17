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
<img src="https://i.imgur.com/EbOJZ2s.png" width="860" height="800">
Inheritance: 

The AI class inherits from the Player class. makeMove() is overridden.

Aggregation: 

Checker, Board, and Player classes aggregate to form the game class

Composition:

There are no Checker, Board, or Player objects instantiated without a Game object first being instantiated.

 
 > ## Phase III
 > You will need to schedule a check-in for the second scrum meeting with the same reader you had your first scrum meeting with (using Calendly). Your entire team must be present. This meeting will occur on week 8 during lab time.
 
 > BEFORE the meeting you should do the following:
 > * Update your class diagram from Phase II to include any feedback you received from your TA/grader.
 > * Considering the SOLID design principles, reflect back on your class diagram and think about how you can use the SOLID principles to improve your design. You should then update the README.md file by adding the following:
 >   * A new class diagram incorporating your changes after considering the SOLID principles.
 >   * For each update in your class diagram, you must explain in 3-4 sentences:
 >     * What SOLID principle(s) did you apply?
 >     * How did you apply it? i.e. describe the change.
 >     * How did this change help you write better code?
 > * Perform a new sprint plan like you did in Phase II.
 > * You should also make sure that your README file (and Project board) are up-to-date reflecting the current status of your project and the most recent class diagram. Previous versions of the README file should still be visible through your commit history.
 
> During the meeting with your reader you will discuss: 
 > * How effective your last sprint was (each member should talk about what they did)
 > * Any tasks that did not get completed last sprint, and how you took them into consideration for this sprint
 > * Any bugs you've identified and created issues for during the sprint. Do you plan on fixing them in the next sprint or are they lower priority?
 > * What tasks you are planning for this next sprint.

 
 > ## Final deliverable
 > All group members will give a demo to the reader during lab time. ou should schedule your demo on Calendly with the same reader who took your second scrum meeting. The reader will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Project board.
 > * Make sure your README file and Project board are up-to-date reflecting the current status of your project (e.g. any changes that you have made during the project such as changes to your class diagram). Previous versions should still be visible through your commit history. 
 
 ## Screenshots
 <img src="https://i.imgur.com/lI0hO01.png" width="860" height="800">
 ## Installation/Usage
 > Instructions on installing and running your application
 ## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
 
